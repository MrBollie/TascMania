#ifndef __CTASCAMUSB_H__
#define __CTASCAMUSB_H__

#include <libusb.h>

class CTascamUSB {
	private:
		libusb_context *pUSBContext;
		libusb_device_handle *pUSBDevHandle = NULL;
		libusb_device **pUSBDevList;
	public:
		CTascamUSB();
		~CTascamUSB();

        void init() throw(const char*);
		int control(uint8_t bmRequestType, uint8_t bRequest, 
			uint8_t wValue, uint8_t wIndex, 
			unsigned char* data, uint16_t wLength, 
			unsigned int timeout);

};
#endif
