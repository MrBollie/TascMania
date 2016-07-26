/*
  ==============================================================================

    CChannelStrip.cpp
    Created: 8 Jul 2016 2:14:30pm
    Author:  rajan

  ==============================================================================
*/

#include "CChannelStrip.h"
#include <iostream>
#include <iomanip>
#include <sstream>

CChannelStrip::CChannelStrip(unsigned char id, CTascamUSB* p) throw(const char*) {
    if (id < 1 || id > 16)
        throw "Invalid channel ID. Must be 1-16";

    if (p == NULL)
        throw "Internal USB failure.";
        
    channelId = id;
    pUSB = p;
    
    // Init Values
    vEQLowGain = 0;
    vEQLowMidGain = 0;
    vEQHiMidGain = 0;
    vEQHiGain = 0;
    vEQLowFreq = 80;
    vEQLowMidFreq = 300;
    vEQHiMidFreq = 1200;
    vEQHiFreq = 5000;
    vEQLowMidQ = 1;
    vEQHiMidQ = 1;

    vEQLowOn = false;
    vEQLowMidOn = false;
    vEQHiMidOn = false;
    vEQHiOn = false;
    
    
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
}

CChannelStrip::~CChannelStrip() {
}

/**
* This sets the channels fader
*/
int CChannelStrip::setVolume(char value) throw(const char*) {
    if (value < -97 || value > 6) 
        throw "Invalid volume range. Must be -196 to 6";
    if (value == -97) 
        value = 0x81;
	vVolume = value;

	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x81, 0x02, value,
		0x00, 0x00 
	};
	return pUSB->control(0x40, 29, 0x0000, 0, data, 11, 5000);
}


/**
* This sets the panning.
* Acceptable values are -128 to +127
*/
int CChannelStrip::setPan(char value) throw(const char*) {
    if (value < -128 || value > 127) 
        throw "Invalid volume range. Must be -128 to 128";
        
    vPan = value;
    
	std::cout << "Chan: " << (int)channelId << std::endl;
	std::cout << "Value: " << (int)value << std::endl;

	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x82, 0x02, value,
		0x00, 0x00 
	};
	return pUSB->control(0x40, 29, 0x0000, 0, data, 11, 5000);
}


/**
* This method mutes/unmutes the channel
*/
int CChannelStrip::setMute(bool value) throw(const char*) {            
	std::cout << "Chan: " << (int)channelId << std::endl;
	std::cout << "Value: " << (int)value << std::endl;
	
	vMuteOn = value;

	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x83, 0x02, (value ? 0x01 : 0x00),
		0x00, 0x00 
	};
	return pUSB->control(0x40, 29, 0x0000, 0, data, 11, 5000);
}


/** 
* This method sets the gain of the low band on the EQ
* Note that it passes on any exception coming from 
* the update method. Gain range goes from 0 to 12.
*/
int CChannelStrip::setEQLowGain(char v) throw(const char*) {
    vEQLowGain = v;
    return updateEQLow();
}


/** 
* This method sets the gain of the low mid band on the EQ
* Note that it passes on any exception coming from 
* the update method. Gain range goes from 0 to 12.
*/
int CChannelStrip::setEQLowMidGain(char v) throw(const char*) {
    vEQLowMidGain = v;
    return updateEQLowMid();
}


/** 
* This method sets the gain of the hi mid band on the EQ
* Note that it passes on any exception coming from 
* the update method. Gain range goes from 0 to 12.
*/
int CChannelStrip::setEQHiMidGain(char v) throw(const char*) {
    vEQHiMidGain = v;
    return updateEQHiMid();
}


/** 
* This method sets the gain of the hi band on the EQ
* Note that it passes on any exception coming from 
* the update method. Gain range goes from 0 to 12.
*/
int CChannelStrip::setEQHiGain(char v) throw(const char*) {
    vEQHiGain = v;
    return updateEQHi();
}


/** 
* This method sets the frequency of the low band on the EQ
* Note that it passes on any exception coming from 
* the update method.
* Parameter v actually is an index of the corresponding
* frequency from the map returned by getEQLowFreqList.
*/

int CChannelStrip::setEQLowFreq(unsigned int v) throw(const char*) {
    vEQLowFreq = v;
    return updateEQLow();
}

int CChannelStrip::setEQLowMidFreq(unsigned int v) throw(const char*) {
    vEQLowMidFreq = v;
    return updateEQLowMid();
}

int CChannelStrip::setEQHiMidFreq(unsigned int v) throw(const char*) {
    vEQHiMidFreq = v;
    return updateEQHiMid();
}

int CChannelStrip::setEQHiFreq(unsigned int v) throw(const char*) {
    vEQHiFreq = v;
    return updateEQHi();
}

int CChannelStrip::setEQLowMidQ(float v) throw(const char*) {
    vEQLowMidQ = v;
    return updateEQLowMid();
}

int CChannelStrip::setEQHiMidQ(float v) throw(const char*) {
    vEQHiMidQ = v;
    return updateEQHiMid();
}

int CChannelStrip::setEQLowOn(bool v) throw(const char*) {
    vEQLowOn = v;
    return updateEQLow();
}

int CChannelStrip::setEQLowMidOn(bool v) throw(const char*) {
    vEQLowMidOn = v;
    return updateEQLowMid();
}

int CChannelStrip::setEQHiMidOn(bool v) throw(const char*) {
    vEQHiMidOn = v;
    return updateEQHiMid();
}

int CChannelStrip::setEQHiOn(bool v) throw(const char*) {
    vEQHiOn = v;
    return updateEQHi();
}

void CChannelStrip::setEQOn(bool v) throw(const char*) {
    setEQLowOn(v);
    setEQLowMidOn(v);
    setEQHiMidOn(v);
    setEQHiOn(v);
}


char CChannelStrip::getEQLowGain() {
    return vEQLowGain;
}

char CChannelStrip::getEQLowMidGain() {
    return vEQLowMidGain;
}

char CChannelStrip::getEQHiMidGain() {
    return vEQHiMidGain;
}

char CChannelStrip::getEQHiGain() {
    return vEQHiGain;
}

unsigned int CChannelStrip::getEQLowFreq() {
    return vEQLowFreq;
}

unsigned int CChannelStrip::getEQLowMidFreq() {
    return vEQLowMidFreq;
}

unsigned int CChannelStrip::getEQHiMidFreq() {
    return vEQHiMidFreq;
}

unsigned int CChannelStrip::getEQHiFreq() {
    return vEQHiFreq;
}

float CChannelStrip::getEQLowMidQ() {
    return vEQLowMidQ;
}

float CChannelStrip::getEQHiMidQ() {
    return vEQHiMidQ;
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

unsigned char CChannelStrip::getId() { return channelId; }

int CChannelStrip::updateEQLow() throw(const char*) {
    char f = lookupEQFreq(vEQLowFreq);
    char g = lookupEQGain(vEQLowGain);
    
	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x51, 0x02, 0x01,
		0x52, 0x02, g,
		0x53, 0x02, f,
		0x54, 0x02, 0xff,
		0x55, 0x02, (vEQLowOn ? 0x01 : 0x00),
		0x00, 0x00
	};

	return pUSB->control(0x40, 29, 0x0000, 0, data, 23, 5000);
}

int CChannelStrip::updateEQLowMid() throw(const char*) {            	
    char f = lookupEQFreq(vEQLowMidFreq);
    char g = lookupEQGain(vEQLowMidGain);
    char q = lookupEQQ(vEQLowMidQ);

	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x51, 0x02, 0x02,
		0x52, 0x02, g,
		0x53, 0x02, f,
		0x54, 0x02, q,
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
    char f = lookupEQFreq(vEQHiMidFreq);
    char g = lookupEQGain(vEQHiMidGain);
    char q = lookupEQQ(vEQLowMidQ);

	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x51, 0x02, 0x03,
		0x52, 0x02, g,
		0x53, 0x02, f,
		0x54, 0x02, q,
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
    char f = lookupEQFreq(vEQHiFreq);
    char g = lookupEQGain(vEQHiGain);

	unsigned char data[] = { 
	    0x61, 0x02, 0x04, 
		0x62, 0x02, channelId, 
		0x51, 0x02, 0x04,
		0x52, 0x02, g,
		0x53, 0x02, f,
		0x54, 0x02, 0xff,
		0x55, 0x02, (vEQHiOn ? 0x01 : 0x00),
		0x00, 0x00
	};
	return pUSB->control(0x40, 29, 0x0000, 0, data, 23, 5000);
}


/**
* This method converts from the gain range -12 to +12 to 
* the corresponding value, that we transfer via USB
*/
char CChannelStrip::lookupEQGain(char g) throw(const char*) {
    if (g < -12 or g > 12) 
        throw "Invalid EQ gain range. Must be from -12 to 12dB";
    
    // Normalize it to 0
    return (char)g+12;
}


/**
* This method takes a frequency f and tries to find the matching
* value on the frequency map. It then returns its value used
* for USB communication. For a list of valid frequencies check out
* the getEQ.*FreqList() methods. It will throw an exception if 
* it can't find a valid mapping.
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
* This method takes a quality value and tries to find the corresponding
* value on the Q-map. It then returns its value used for USB
* communication. For a list of valid quality values, see the
* getEQ.*QList()-methods. It will throw an exception if 
* it can't find a valid mapping.
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
* Retrieves a list of possible low freq values
*/
std::vector<unsigned int> CChannelStrip::getEQLowFreqList() {
    std::vector<unsigned int> lft;
    for (int i = 0 ; i < 32 ; i++) {
        lft.push_back(freqMap[i].freq);
    }
    return lft;
}

/**
* Retrieves a list of possible low mid freq values
*/
std::vector<unsigned int> CChannelStrip::getEQLowMidFreqList() {
    std::vector<unsigned int> lft;
    for (int i = 0 ; i < 32 ; i++) {
        lft.push_back(freqMap[i].freq);
    }
    return lft;
}

/**
* Retrieves a list of possible hi mid freq values
*/
std::vector<unsigned int> CChannelStrip::getEQHiMidFreqList() {
    std::vector<unsigned int> lft;
    for (int i = 0 ; i < 32 ; i++) {
        lft.push_back(freqMap[i].freq);
    }
    return lft;
}

/**
* Retrieves a list of possible hi freq values
*/
std::vector<unsigned int> CChannelStrip::getEQHiFreqList() {
    std::vector<unsigned int> lft;
    for (int i = 32 ; i < freqMap.size() ; i++) {
        lft.push_back(freqMap[i].freq);
    }
    return lft;
}


/**
* Retrieves a list of possible low mid q values
*/
std::vector<float> CChannelStrip::getEQLowMidQList() {
    std::vector<float> qs;
    for (int i = 0 ; i < qMap.size() ; i++) {
        qs.push_back(qMap[i].q);
    }
    return qs;
}

/**
* Retrieves a list of possible hi mid q values
*/
std::vector<float> CChannelStrip::getEQHiMidQList() {
    std::vector<float> qs;
    for (int i = 0 ; i < qMap.size() ; i++) {
        qs.push_back(qMap[i].q);
    }
    return qs;
}

