#ifndef CMASTERSTRIP_H_INCLUDED
#define CMASTERSTRIP_H_INCLUDED

#include <string>
#include <vector>

#include "CTascamUSB.h"

/**
* A CMasterStrip object represents the master channel of the Tascam device.
* It stores all the parameters, updates them via USB and you can access them
* via getter and setter functions.
* \todo int return values vor setters no longer neccessary, as exceptions will 
* be thrown.
* \todo some exception class based on std::exception would be much cooler!
* \todo All frequency values should be looked up for verification and internal
* storage and then be reverse-lookuped, when their getter is being called.
*/
class CMasterStrip {
	
public:
	CMasterStrip(unsigned char, CTascamUSB*) throw(const char*);
	~CMasterStrip();
	
	// Setters
	void setVolume(char) throw(const char*);
	void setMuteOn(bool) throw(const char*);

	// Getters
    char getVolume();
    bool getMuteOn();


private: 
    // Values to store
    char vVolume; // main volume of the channel strip (fader)
    bool vMuteOn; // mute flag

	
	CTascamUSB	*pUSB;
};


#endif  // CCHANNELSTRIP_H_INCLUDED
