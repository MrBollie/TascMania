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

class CChannelStrip {
	

public:
	CChannelStrip(unsigned char, CTascamUSB*) throw(const char*);
	~CChannelStrip();
	
	// Setters
	int setVolume(char) throw(const char*);
	int setPan(char) throw(const char*);
	int setMute(bool value) throw(const char*);
	int setEQLowGain(char v) throw(const char*);
	int setEQLowMidGain(char v) throw(const char*);
	int setEQHiMidGain(char v) throw(const char*);
	int setEQHiGain(char v) throw(const char*);

	int setEQLowFreq(unsigned int v) throw(const char*);
	int setEQLowMidFreq(unsigned int v) throw(const char*);
	int setEQHiMidFreq(unsigned int v) throw(const char*);
	int setEQHiFreq(unsigned int v) throw(const char*);

	int setEQLowMidQ(float v) throw(const char*);
	int setEQHiMidQ(float v) throw(const char*);

	int setEQLowOn(bool v) throw(const char*);
	int setEQLowMidOn(bool v) throw(const char*);
	int setEQHiMidOn(bool v) throw(const char*);
	int setEQHiOn(bool v) throw(const char*);

	void setEQOn(bool v) throw(const char*);

	// Getters
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
    char vVolume;
    char vPan;
    bool vMuteOn;
    bool vPhaseOn;
    bool vCompOn;

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

	int updateEQLow() throw(const char*);
	int updateEQLowMid() throw(const char*);
	int updateEQHiMid() throw(const char*);
	int updateEQHi() throw(const char*);
	
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
