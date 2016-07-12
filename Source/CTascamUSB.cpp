#include "CTascamUSB.h"
#include <iostream>

CTascamUSB::CTascamUSB() throw(const char*){
	int r = libusb_init(&pUSBContext);
	if (r < 0) {
		throw "Error in creating USB context\n";
	}

	// Try opening the Tascam device
	pUSBDevHandle = libusb_open_device_with_vid_pid(pUSBContext, 0x644, 0x8047);

	if (pUSBDevHandle == NULL) {
		throw "No such device\n";	
	}
}

CTascamUSB::~CTascamUSB() {
	libusb_close(pUSBDevHandle);
	libusb_exit(pUSBContext);
}

/*
Wrapper function

bmRequestType	the request type field for the setup packet
bRequest	the request field for the setup packet
wValue		the value field for the setup packet
wIndex		the index field for the setup packet
data		a suitably-sized data buffer for either input or 
		output (depending on direction bits within 
		bmRequestType)
wLength		the length field for the setup packet. The data buffer should be at least this size.
timeout		timeout (in millseconds) that this function should wait before giving up due to no
 		response being received. For an unlimited timeout, use value 0. 
*/
int CTascamUSB::control(uint8_t bmRequestType, uint8_t bRequest, 
	uint8_t wValue, uint8_t wIndex, unsigned char* data, 
	uint16_t wLength, unsigned int timeout) {
	
	return libusb_control_transfer(pUSBDevHandle, bmRequestType, bRequest, 
		wValue, wIndex, data, wLength, timeout);
}
