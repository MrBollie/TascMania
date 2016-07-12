#ifndef __CROUTING_H__
#define __CROUTING_H__

#include <string>

#include "CTascamUSB.h"

class CRouting {

private: 
	struct _channel {
		unsigned char	id;
		unsigned char	bus;
		std::string 	label;
	};

	struct _output {
		std::string 	label;
		unsigned char	id;
		struct _channel* chan;
	};

	struct _output aOutputs[8];
	struct _channel aChannels[10];
	CTascamUSB	*pUSB;

	void init();
	int setOutputInt(_output *pOut, _channel *pChan);
	int updateUSB(_output *pOut);
	

public:
	CRouting(CTascamUSB*);
	~CRouting();
	int setOutput(unsigned char oID, std::string cChan) throw(const char*);
};
#endif
