#include "CRouting.h"
#include <stdlib.h>
#include <iostream>

CRouting::CRouting(CTascamUSB *p) {
	pUSB = p;
	init();
}

CRouting::~CRouting() {
}

void CRouting::init() {

	// Setup channels

	// Master Channels from internal busses
	aChannels[0].label = "Master L";
	aChannels[0].id = 1;
	aChannels[0].bus = 0x02;

	aChannels[1].label = "Master R";
	aChannels[1].id = 2;
	aChannels[1].bus = 0x02;

	// Computer busses
	for (int i = 2 ; i < 10 ; i++) {
		aChannels[i].label = "Computer " + std::to_string(i-1);
		aChannels[i].id = i-1;
		aChannels[i].bus = 0x03;		
	}

	// Setup physical outputs	
	for (int i = 0 ; i < 8 ; i++) {
		aOutputs[i].label = "ComboOut" + std::to_string(i+1);
		aOutputs[i].id = i+1;
		aOutputs[i].chan = &aChannels[i]; // Pointer here?
	}
}

int CRouting::setOutput(unsigned char oID, std::string cChan) 
                 throw(const char*) {
	_channel *pChan;
	_output *pOut;	

	// find output
	for (int i = 0 ; i < 8 ; i++) {
		if (aOutputs[i].id == oID) {
			pOut = &aOutputs[i];
			i = 8;
		}
	}

	if (pOut == NULL) {
		throw "No such output";
	}

	// find channel
	for (int i = 0 ; i < 10 ; i++) {
		if (aChannels[i].label.compare(cChan) == 0) {
			pChan = &aChannels[i];
			i = 10;
		}
	}

	if (pChan == NULL) {
		throw "No such channel";
	}

	return setOutputInt(pOut,pChan);
}

int CRouting::setOutputInt(_output *pOut, _channel *pChan) {
	pOut->chan = pChan;
	updateUSB(pOut);
	return 0;
}

int CRouting::updateUSB(_output *pOut) {
	std::cout << "Bus: " << (int)pOut->chan->bus << std::endl;
	std::cout << "Chan: " << (int)pOut->chan->id << std::endl;
	std::cout << "OID: " << (int)pOut->id << std::endl;

	unsigned char data[] = { 0x61, 0x02, 
		pOut->chan->bus, 
		0x62, 0x02, 
		pOut->chan->id, 
		0x41, 0x01, 0x61, 0x02, 0x01, 0x62, 0x02, 
		pOut->id,
		0x42, 0x01,
		0x43, 0x01, 0x00, 0x00 
	};
	return pUSB->control(0x40, 29, 0x0000, 0, data, 20, 5000);
}
