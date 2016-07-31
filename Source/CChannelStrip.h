/*
  ==============================================================================

    CChannelStrip.h
    Created: 8 Jul 2016 2:14:30pm
    Author:  rajan

  ==============================================================================
*/

#ifndef CCHANNELSTRIP_H_INCLUDED
#define CCHANNELSTRIP_H_INCLUDED

#include <string>
#include <vector>

#include "CTascamUSB.h"

/**
* A CChannelStrip object represents a single channel of the Tascam device.
* It stores all the parameters, updates them via USB and you can access them
* via getter and setter functions.
* \todo int return values vor setters no longer neccessary, as exceptions will 
* be thrown.
* \todo some exception class based on std::exception would be much cooler!
*/
class CChannelStrip {
	

public:
	CChannelStrip(unsigned char, CTascamUSB*) throw(const char*);
	~CChannelStrip();
	
	// Setters
	void setVolume(char) throw(const char*);
	void setPan(char) throw(const char*);
	void setMuteOn(bool) throw(const char*);
    void setPhaseOn(bool) throw(const char*);

    void setCompThreshold(char) throw(const char*);
    void setCompAttack(unsigned char) throw(const char*);
    void setCompRelease(unsigned int) throw(const char*);
    void setCompGain(unsigned char) throw(const char*);
    void setCompRatio(float) throw(const char*);

	void setEQLowGain(char v) throw(const char*);
	void setEQLowMidGain(char v) throw(const char*);
	void setEQHiMidGain(char v) throw(const char*);
	void setEQHiGain(char v) throw(const char*);

	void setEQLowFreq(unsigned int v) throw(const char*);
	void setEQLowMidFreq(unsigned int v) throw(const char*);
	void setEQHiMidFreq(unsigned int v) throw(const char*);
	void setEQHiFreq(unsigned int v) throw(const char*);

	void setEQLowMidQ(float v) throw(const char*);
	void setEQHiMidQ(float v) throw(const char*);

	void setEQLowOn(bool v) throw(const char*);
	void setEQLowMidOn(bool v) throw(const char*);
	void setEQHiMidOn(bool v) throw(const char*);
	void setEQHiOn(bool v) throw(const char*);

	void setEQOn(bool v) throw(const char*);

	// Getters
    char getVolume();
    char getPan();
    bool getMuteOn();
    bool getPhaseOn();

    char getCompThreshold();
    unsigned char getCompAttack();
    unsigned int getCompRelease();
    unsigned char getCompGain();
    float getCompRatio();

	char getEQLowGain();
	char getEQLowMidGain();
	char getEQHiMidGain();
	char getEQHiGain();

	unsigned int getEQLowFreq();
	unsigned int getEQLowMidFreq();
	unsigned int getEQHiMidFreq();
	unsigned int getEQHiFreq();
	
    float getEQLowMidQ();
	float getEQHiMidQ();

	bool getEQLowOn();
	bool getEQLowMidOn();
	bool getEQHiMidOn();
	bool getEQHiOn();

    static const float* getCompRatioList();

    std::vector<unsigned int> getEQLowFreqList();
    std::vector<unsigned int> getEQLowMidFreqList();	
    std::vector<unsigned int> getEQHiMidFreqList();
    std::vector<unsigned int> getEQHiFreqList();

    std::vector<float> getEQLowMidQList();	
    std::vector<float> getEQHiMidQList();

    unsigned char getId();

private: 
    unsigned char channelId;
    
    // Values to store
    char vVolume; // main volume of the channel strip (fader)
    char vPan; // panning of the channel
    bool vMuteOn; // mute flag
    bool vPhaseOn; // phase or polarity flag
    bool vCompOn; // flag wether the compressor on this chan is active

    char vCompThreshold;
    unsigned char vCompAttack;
    unsigned int vCompRelease;
    unsigned char vCompGain;
    float vCompRatio;

    bool vEQLowOn;
    bool vEQLowMidOn;
    bool vEQHiMidOn;
    bool vEQHiOn;

    char vEQLowGain;
    char vEQLowMidGain;
    char vEQHiMidGain;
    char vEQHiGain;

    unsigned int vEQLowFreq;
    unsigned int vEQLowMidFreq;
    unsigned int vEQHiMidFreq;
    unsigned int vEQHiFreq;

    float vEQLowMidQ;
    float vEQHiMidQ;

	int updateComp() throw(const char*);

	int updateEQLow() throw(const char*);
	int updateEQLowMid() throw(const char*);
	int updateEQHiMid() throw(const char*);
	int updateEQHi() throw(const char*);

    static const float validCompRatios[];
	
	struct sFreqMap {
	    unsigned int freq;
	    char val;
	};
	
	std::vector<sFreqMap> freqMap;
	
	struct sQMap {
	    float q;
	    char val;
	};
	std::vector<sQMap> qMap;
	
	char lookupEQFreq(unsigned int) throw(const char*);
	char lookupEQQ(float) throw(const char*);
	char lookupEQGain(char) throw(const char*);
	
	CTascamUSB	*pUSB;
};


#endif  // CCHANNELSTRIP_H_INCLUDED
