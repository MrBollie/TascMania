#include "CChannelStrip.h"
#include <iostream>
#include <iomanip>
#include <sstream>

const std::vector<float> CChannelStrip::validCompRatios = { 
        1, 1.1, 1.3, 1.5, 1.7, 2.0, 2.5, 3, 3.5, 4, 5, 6, 8, 16, 0 
};

CChannelStrip::CChannelStrip(unsigned char id, CTascamUSB* p) 
    throw(const char*) {
    if (id < 1 || id > 16)
        throw "Invalid channel ID. Must be 1-16";
        
    channelId = id;
    pUSB = p;
    
    // Setting up frequency steps
    char cnt=0x00;
    sFreqMap f;
    f.freq = 32;
    f.val = cnt++;
    freqMap.push_back(f);

    for (int i = 40 ; i < 100 ; i+=10) {
        f.freq = i;
        f.val = cnt++;
        freqMap.push_back(f);
    }
    
    for (int i = 100 ; i < 250 ; i+=25) {
        f.freq = i;
        f.val = cnt++;
        freqMap.push_back(f);
    }
    
    for (int i = 250 ; i < 500 ; i+=50) {
        f.freq = i;
        f.val = cnt++;
        freqMap.push_back(f);
    }

    for (int i = 500 ; i < 800 ; i+=100) {
        f.freq = i;
        f.val = cnt++;
        freqMap.push_back(f);
    }

    for (int i = 800 ; i < 1000 ; i+=50) {
        f.freq = i;
        f.val = cnt++;
        freqMap.push_back(f);
    }

    for (int i = 1000 ; i < 2000 ; i+=100) {  // starting field 30
        f.freq = i;
        f.val = cnt++;
        freqMap.push_back(f);
    }

    for (int i = 2000 ; i < 4000 ; i+=200) { // starting field 40
        f.freq = i;
        f.val = cnt++;
        freqMap.push_back(f);
    }

    for (int i = 4000 ; i < 8000 ; i+= 500) { // starting field 50
        f.freq = i;
        f.val = cnt++;
        freqMap.push_back(f);
    }

    for (int i = 8000 ; i <= 18000 ; i+= 1000) { // field 58 and ending 68
        f.freq = i;
        f.val = cnt++;
        freqMap.push_back(f);
    }

    // Initialize qMap
    cnt=0x00;
    sQMap q;
    q.q = 0.25;
    for (float i = 0.25 ; i <= 16 ; i*=2) {
        q.q = i;
        q.val = cnt++;
        qMap.push_back(q);
    }

    // Init Values
    vEQLowGain = 12;        // 0
    vEQLowMidGain = 12;     // 0
    vEQHiMidGain = 12;      // 0
    vEQHiGain = 12;         // 0
    vEQLowFreq = 0x05;      // 80
    vEQLowMidFreq = 0x0e;   // 300
    vEQHiMidFreq = 0x1b;    // 1200
    vEQHiFreq = 0x2f;       // 5000
    vEQLowMidQ = 0x02;      // 1
    vEQHiMidQ = 0x02;       // 1

    vEQLowOn = false;
    vEQLowMidOn = false;
    vEQHiMidOn = false;
    vEQHiOn = false;
}


CChannelStrip::~CChannelStrip() {
}


/**
* Sets the channels fader.
* \param value loudness in dB. (range: -196 to +6)
* \throw A message in case of an error
*/
void CChannelStrip::setVolume(char value) throw(const char*) {
    if (value < -97 || value > 6) 
        throw "Invalid volume range. Must be -196 to 6";
    if (value == -97) 
        value = 0x81;
	vVolume = value;

	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x81, 0x02, (unsigned char)value,
		0x00, 0x00 
	};
	pUSB->control(0x40, 29, 0x0000, 0, data, 11, 5000);
}


/**
* Sets the panning.
* \param v Panning value (range: -128 to +127)
* \throw Exception message in case of an error
*/
void CChannelStrip::setPan(char value) throw(const char*) {
    if (value < -128 || value > 127) 
        throw "Invalid pan range. Must be -128 to 128";
        
    vPan = value;
    
	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x82, 0x02, value,
		0x00, 0x00 
	};
	pUSB->control(0x40, 29, 0x0000, 0, data, 11, 5000);
}


/**
* This method mutes/unmutes the channel.
* \param value true for mute, false for umute
* \throw Exception message in case of an error
*/
void CChannelStrip::setMuteOn(bool value) throw(const char*) {            
	vMuteOn = value;

	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x83, 0x02, (value ? 0x01 : 0x00),
		0x00, 0x00 
	};
	pUSB->control(0x40, 29, 0x0000, 0, data, 11, 5000);
}


/**
* This method changes the polarity of the channel.
* \param value true reverse polarity
* \throw Exception message in case of an error
*/
void CChannelStrip::setPhaseOn(bool value) throw(const char*) {            	
	vPhaseOn = value;

	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x85, 0x02, (value ? 0x01 : 0x00),
		0x00, 0x00 
	};
	pUSB->control(0x40, 29, 0x0000, 0, data, 11, 5000);
}


/** 
* Sets the threshold of the compressor.
* \param v Threshold (range -32 to 0)
* \throw Exception message in case of an error
*/
void CChannelStrip::setCompThreshold(char v) throw(const char*) {
    if (v < -32 || v > 0) 
        throw "Invalid compressor threshold (use range -32 to 0)";

    vCompThreshold = v;
    updateComp();
}


/** 
* Sets the attack time of the compressor.
* \param v Attack in ms (range 2 to 200)
* \throw Exception message in case of an error
*/
void CChannelStrip::setCompAttack(unsigned char v) throw(const char*) {
    if (v < 2 || v > 200) 
        throw "Invalid compressor attack (use range 2 to 200)";
    vCompAttack = v;
    updateComp();
}


/** 
* Sets the release time of the compressor.
* \param v Release in ms (range 10 to 1000)
* \throw Exception message in case of an error
*/
void CChannelStrip::setCompRelease(unsigned int v) throw(const char*) {
    if (v < 1 || v > 100) 
        throw "Invalid compressor release (use range 10 to 1000)";
    vCompRelease = v;
    updateComp();
}


/** 
* Sets the gain of the compressor.
* \param v Gain (range 0 to 20)
* \throw Exception message in case of an error
*/
void CChannelStrip::setCompGain(unsigned char v) throw(const char*) {
    if (v < 0 || v > 20) 
        throw "Invalid compressor gain (use range 0 to 20)";
    vCompGain = v;
    updateComp();
}


/** 
* Sets the ratio of the compressor.
* \param v ratio (range 1.0, 1.1, 1.3, 1.5, 1.7, 2.0, 2.5, 3, 3.5, 4, 5, 6, 8,
* 16 and 0 for inf)
* \throw Exception message in case of an error
*/
void CChannelStrip::setCompRatio(float v) throw(const char*) {
    // Iterate over valid values and update comp, if a valid value has been 
    // found    
    for (int i = 0 ; i < 15 ; i++) {
        if (v == CChannelStrip::validCompRatios[i]) {
            vCompRatio = (v == 0 ? 0xff : (char)v * 10);
            updateComp();
            return;
        }
    }
    
    throw "Invalid compressor ratio (valid values: 1.0, 1.1, 1.3, 1.5, 1.7, "
        "2.0, 2.5, 3, 3.5, 4, 5, 6, 8, 16 and 0 for inf";
}


/** 
* Sets the gain of the low band on the EQ
* \param v gain of the band (range 0 to 12)
* \throw Exception message in case of an error
*/
void CChannelStrip::setEQLowGain(char v) throw(const char*) {
    if (v < 0 || v > 12) 
        throw "Invalid low EQ gain (use range 0 to 12)";

    vEQLowGain = lookupEQGain(v);
    updateEQLow();
}


/** 
* Sets the gain of the low mid band on the EQ
* \param v Gain range goes from 0 to 12.
* \todo range check
*/
void CChannelStrip::setEQLowMidGain(char v) throw(const char*) {
    vEQLowMidGain = lookupEQGain(v);
    updateEQLowMid();
}


/** 
* Sets the gain of the hi mid band on the EQ
* \param v Gain range goes from 0 to 12.
* \todo range check
*/
void CChannelStrip::setEQHiMidGain(char v) throw(const char*) {
    vEQHiMidGain = lookupEQGain(v);
    updateEQHiMid();
}


/** 
* Sets the gain of the hi band on the EQ
* \param v Gain range goes from 0 to 12.
* \todo range check
*/
void CChannelStrip::setEQHiGain(char v) throw(const char*) {
    vEQHiGain = lookupEQGain(v);
    updateEQHi();
}


/** 
* Sets the frequency of the low band on the EQ
* \param v actually is an index of the corresponding
* frequency from the map returned by getEQLowFreqList.
* \todo range check
*/
void CChannelStrip::setEQLowFreq(unsigned int v) throw(const char*) {
    vEQLowFreq = lookupEQFreq(v);
    updateEQLow();
}


/**
* Sets the EQs low mid band frequency.
* \param v Frequency of the low mid band
* \throw Exception message in case of an error
* \todo range check
*/
void CChannelStrip::setEQLowMidFreq(unsigned int v) throw(const char*) {
    vEQLowMidFreq = lookupEQFreq(v);
    updateEQLowMid();
}


/**
* Sets the EQs hi mid band frequency.
* \param v Frequency of the hi mid band
* \throw Exception message in case of an error
* \todo range check
*/
void CChannelStrip::setEQHiMidFreq(unsigned int v) throw(const char*) {
    vEQHiMidFreq = lookupEQFreq(v);
    updateEQHiMid();
}


/**
* Sets the EQs hi band frequency.
* \param v Frequency of the hi band
* \throw Exception message in case of an error
* \todo range check
*/
void CChannelStrip::setEQHiFreq(unsigned int v) throw(const char*) {
    vEQHiFreq = lookupEQFreq(v);
    updateEQHi();
}


/**
* Sets the EQs low mid band quality.
* \param v low mid band quality. See method getEQLowMidQList for valid  
* values.
* \throw Exception message in case of an error
*/
void CChannelStrip::setEQLowMidQ(float v) throw(const char*) {
    vEQLowMidQ = lookupEQQ(v);
    updateEQLowMid();
}


/**
* Sets the EQs hi mid band quality.
* \param v hi mid band quality. See method getEQHiMidQList for valid  
* values.
* \throw Exception message in case of an error
*/
void CChannelStrip::setEQHiMidQ(float v) throw(const char*) {
    vEQHiMidQ = lookupEQQ(v);
    updateEQHiMid();
}


/**
* Switches the EQs low band on or off.
* \param v true == on, false == off
* \throw Exception message in case of an error
*/
void CChannelStrip::setEQLowOn(bool v) throw(const char*) {
    vEQLowOn = v;
    updateEQLow();
}


/**
* Switches the EQs low mid band on or off.
* \param v true == on, false == off
* \throw Exception message in case of an error
*/
void CChannelStrip::setEQLowMidOn(bool v) throw(const char*) {
    vEQLowMidOn = v;
    updateEQLowMid();
}


/**
* Switches the EQs hi mid band on or off.
* \param v true == on, false == off
* \throw Exception message in case of an error
*/
void CChannelStrip::setEQHiMidOn(bool v) throw(const char*) {
    vEQHiMidOn = v;
    updateEQHiMid();
}


/**
* Switches the EQs hi band on or off.
* \param v true == on, false == off
* \throw Exception message in case of an error
*/
void CChannelStrip::setEQHiOn(bool v) throw(const char*) {
    vEQHiOn = v;
    updateEQHi();
}


/**
* Switches the EQ entirely on or off.
* \param v true == on, false == off
* \throw Exception message in case of an error
*/
void CChannelStrip::setEQOn(bool v) throw(const char*) {
    setEQLowOn(v);
    setEQLowMidOn(v);
    setEQHiMidOn(v);
    setEQHiOn(v);
}


/**
* Returns the compressor's threshold.
* \return t Threshold value
*/
char CChannelStrip::getCompThreshold() {
    return vCompThreshold;
}


/**
* Returns the compressor's attack time.
* \return t Attack time in ms
*/
unsigned char CChannelStrip::getCompAttack() {
    return vCompAttack;
}


/**
* Returns the compressor's release time.
* \return t Release time in ms
*/
unsigned int CChannelStrip::getCompRelease() {
    return vCompRelease;
}


/**
* Returns the compressor's gain.
* \return t Gain
*/
unsigned char CChannelStrip::getCompGain() {
    return vCompGain;
}


/**
* Returns the compressor's ratio.
* \return t Ratio
*/
float CChannelStrip::getCompRatio() {
    return vCompRatio/10;
}

/**
* Returns an array of valid compressor ratios.
* \return validCompRatios An array containing valid comp ratios.
*/
const std::vector<float> CChannelStrip::getCompRatioList() {
    return validCompRatios;
}


/**
* Returns the EQ's low band gain value.
* \return low band gain
*/
char CChannelStrip::getEQLowGain() {
    return revLookupEQGain(vEQLowGain);
}


/**
* Returns the EQ's low mid band gain value.
* \return low mid band gain
*/
char CChannelStrip::getEQLowMidGain() {
    return revLookupEQGain(vEQLowMidGain);
}


/**
* Returns the EQ's hi mid band gain value.
* \return hi mid band gain
*/
char CChannelStrip::getEQHiMidGain() {
    return revLookupEQGain(vEQHiMidGain);
}


/**
* Returns the EQ's hi band gain value.
* \return hi band gain
*/
char CChannelStrip::getEQHiGain() {
    return revLookupEQGain(vEQHiGain);
}

unsigned int CChannelStrip::getEQLowFreq() {
    return revLookupEQFreq(vEQLowFreq);
}

unsigned int CChannelStrip::getEQLowMidFreq() {
    return revLookupEQFreq(vEQLowMidFreq);
}

unsigned int CChannelStrip::getEQHiMidFreq() {
    return revLookupEQFreq(vEQHiMidFreq);
}

unsigned int CChannelStrip::getEQHiFreq() {
    return revLookupEQFreq(vEQHiFreq);
}

float CChannelStrip::getEQLowMidQ() {
    return revLookupEQQ(vEQLowMidQ);
}

float CChannelStrip::getEQHiMidQ() {
    return revLookupEQQ(vEQHiMidQ);
}

bool CChannelStrip::getEQLowOn() {
    return vEQLowOn;
}

bool CChannelStrip::getEQLowMidOn() {
    return vEQLowMidOn;
}

bool CChannelStrip::getEQHiMidOn() {
    return vEQHiMidOn;
}

bool CChannelStrip::getEQHiOn() {
    return vEQHiOn;
}


/**
* Returns the channels numeric ID.
* \return id Channel ID
*/
unsigned char CChannelStrip::getId() { 
    return channelId; 
}


/**
* Updates the compressor
*/
int CChannelStrip::updateComp() throw(const char*) {
    unsigned char ratio = 
        (vCompRatio == 0 ? 0xff : (unsigned char)(vCompRatio * 10));
    
	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x91, 0x02, (unsigned char)(vCompThreshold*-1), 
        0x92, 0x02, ratio,
        0x93, 0x02, vCompAttack,
        0x94, 0x02, (unsigned char)(vCompRelease / 10),
        0x95, 0x02, vCompGain,
        0x96, 0x02, 0x01,
        0x97, 0x02, (vCompOn ? 0x01 : 0x00),
        0x00, 0x00
	};

	return pUSB->control(0x40, 29, 0x0000, 0, data, 29, 5000);
}


int CChannelStrip::updateEQLow() throw(const char*) {
	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x51, 0x02, 0x01,
		0x52, 0x02, vEQLowGain,
		0x53, 0x02, vEQLowFreq,
		0x54, 0x02, 0xff,
		0x55, 0x02, (vEQLowOn ? 0x01 : 0x00),
		0x00, 0x00
	};

	return pUSB->control(0x40, 29, 0x0000, 0, data, 23, 5000);
}

int CChannelStrip::updateEQLowMid() throw(const char*) {            	
	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x51, 0x02, 0x02,
		0x52, 0x02, vEQLowMidGain,
		0x53, 0x02, vEQLowMidFreq,
		0x54, 0x02, vEQLowMidQ,
		0x55, 0x02, (vEQLowMidOn ? 0x01 : 0x00),
		0x00, 0x00
	};
	for (int i = 0 ; i < 23 ; i++) {
	    std::stringstream stream;
        stream << std::hex << (int)data[i];
        std::string result = stream.str();
	    std::cerr << result << " ";
	}
	std::cerr << std::endl;
	return pUSB->control(0x40, 29, 0x0000, 0, data, 23, 5000);
}

int CChannelStrip::updateEQHiMid() throw(const char*) {            	
	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x51, 0x02, 0x03,
		0x52, 0x02, vEQHiMidGain,
		0x53, 0x02, vEQHiMidFreq,
		0x54, 0x02, vEQLowMidQ,
		0x55, 0x02, (vEQHiMidOn ? 0x01 : 0x00),
		0x00, 0x00
	};
	for (int i = 0 ; i < 23 ; i++) {
	    std::stringstream stream;
        stream << std::hex << (int)data[i];
        std::string result = stream.str();
	    std::cerr << result << " ";
	}
	std::cerr << std::endl;
	return pUSB->control(0x40, 29, 0x0000, 0, data, 23, 5000);
}

int CChannelStrip::updateEQHi() throw(const char*) {            	
	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x51, 0x02, 0x04,
		0x52, 0x02, vEQHiGain,
		0x53, 0x02, vEQHiFreq,
		0x54, 0x02, 0xff,
		0x55, 0x02, (vEQHiOn ? 0x01 : 0x00),
		0x00, 0x00
	};
	return pUSB->control(0x40, 29, 0x0000, 0, data, 23, 5000);
}


/**
* This method converts from the EQ gain range -12 to +12 to 
* the corresponding value, that we transfer via USB.
* \return g Gain value usable for USB communication
* \throw Exception message in case of an error
*/
char CChannelStrip::lookupEQGain(char g) throw(const char*) {
    if (g < -12 or g > 12) 
        throw "Invalid EQ gain range. Must be from -12 to 12dB";
    
    // Normalize it to 0
    return (char)g+12;
}


/**
* This method converts from the internal EQ gain value to the display value.
* \param g Internal gain value
* \return g Display gain value
* \throw Exception message in case of an error
*/
char CChannelStrip::revLookupEQGain(char g) throw(const char*) {
    if (g < 0 or g > 24) 
        throw "Invalid EQ gain supplied.";
    
    // Normalize it to 0
    return (char)g-12;
}


/**
* This method takes a frequency f and tries to find the matching
* value on the frequency map. It then returns its value used
* for USB communication. For a list of valid frequencies check out
* the getEQ.*FreqList() methods. It will throw an exception if 
* it can't find a valid mapping.
* \param f Frequency to lookup
* \return freqval The corresponding value for USB communication
* \throw Exception message in case of an error 
*/
char CChannelStrip::lookupEQFreq(unsigned int f) throw(const char*) {
    for (int i = 0 ; i < freqMap.size() ; i++) {
        if (freqMap[i].freq == f) {
            return freqMap[i].val;
        }
    }
    throw "Invalid Frequency supplied.";
    return -1;
}


/**
* This method takes the internal represenation of frequency f and tries to find 
* the matching frequency from the map. It then returns this value. For a list of
* valid frequencies check out the getEQ.*FreqList() methods. It will throw an 
* exception if it can't find a valid mapping.
* \param f Internal representation of the frequency
* \return freq The corresponding frequency
* \throw Exception message in case of an error 
*/
unsigned int CChannelStrip::revLookupEQFreq(char f) throw(const char*) {
    for (int i = 0 ; i < freqMap.size() ; i++) {
        if (freqMap[i].val == f) {
            return freqMap[i].freq;
        }
    }
    throw "Invalid internal frequency supplied.";
    return -1;
}


/**
* This method takes an EQ quality value and tries to find the corresponding
* value on the Q-map. It then returns its value used for USB communication. 
* For a list of valid quality values, see the getEQ.*QList()-methods. It will 
* throw an exception if it can't find a valid mapping.
* \param q Value to look up
* \return qval The corresponding value for USB communication
* \throw Exception message in case of an error 
*/
char CChannelStrip::lookupEQQ(float q) throw(const char*) {
    for (int i = 0 ; i < qMap.size() ; i++) {
        if (qMap[i].q == q) {
            return qMap[i].val;
        }
    }
    throw "Invalid Q supplied.";
    return -1;
}


/**
* This method takes the interal EQ quality value and tries to find the 
* corresponding display value on the Q-map. It then this value. For a list of 
* valid quality values, see the getEQ.*QList()-methods. It will throw an 
* exception if it can't find a valid mapping.
* \param q Internal value to look up
* \return qval The corresponding display value
* \throw Exception message in case of an error 
*/
float CChannelStrip::revLookupEQQ(char q) throw(const char*) {
    for (int i = 0 ; i < qMap.size() ; i++) {
        if (qMap[i].val == q) {
            return qMap[i].q;
        }
    }
    throw "Invalid internal Q supplied.";
    return -1;
}


/**
* Retrieves a list of possible freq values for the EQ's low band.
* \return lft A vector containing low freq values
*/
std::vector<unsigned int> CChannelStrip::getEQLowFreqList() {
    std::vector<unsigned int> lft;
    for (int i = 0 ; i < 32 ; i++) {
        lft.push_back(freqMap[i].freq);
    }
    return lft;
}


/**
* Retrieves a list of possible freq values for the EQ's low mid band.
* \return lft A vector containing low mid freq values
*/
std::vector<unsigned int> CChannelStrip::getEQLowMidFreqList() {
    std::vector<unsigned int> lft;
    for (int i = 0 ; i < 32 ; i++) {
        lft.push_back(freqMap[i].freq);
    }
    return lft;
}


/**
* Retrieves a list of possible freq values for the EQ's hi mid band.
* \return lft A vector containing hi mid freq values
*/
std::vector<unsigned int> CChannelStrip::getEQHiMidFreqList() {
    std::vector<unsigned int> lft;
    for (int i = 0 ; i < 32 ; i++) {
        lft.push_back(freqMap[i].freq);
    }
    return lft;
}


/**
* Retrieves a list of possible freq values for the EQ's hi band.
* \return qs A vector containing hi freq values
*/
std::vector<unsigned int> CChannelStrip::getEQHiFreqList() {
    std::vector<unsigned int> lft;
    for (int i = 32 ; i < freqMap.size() ; i++) {
        lft.push_back(freqMap[i].freq);
    }
    return lft;
}


/**
* Retrieves a list of possible quality values for the EQ's low mid band.
* \return qs A vector containing low mid q values
*/
std::vector<float> CChannelStrip::getEQLowMidQList() {
    std::vector<float> qs;
    for (int i = 0 ; i < qMap.size() ; i++) {
        qs.push_back(qMap[i].q);
    }
    return qs;
}


/**
* Retrieves a list of possible quality values for the EQ's hi mid band.
* \return qs A vector containing hi mid q values
*/
std::vector<float> CChannelStrip::getEQHiMidQList() {
    std::vector<float> qs;
    for (int i = 0 ; i < qMap.size() ; i++) {
        qs.push_back(qMap[i].q);
    }
    return qs;
}

