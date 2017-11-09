#ifndef USB_H_
#define USB_H_

#include <string>
#include "main.h"

using namespace std;
//using namespace System;
//using namespace System::IO::Ports;
//using namespace System::Threading;

public ref class Usb{
private:
	static System::IO::Ports::SerialPort^ serialPort;
	System::Threading::Thread^ usbThread;
	static bool pushing;
protected:
	static array<unsigned char>^ buffer;
public:
	Usb();
	Usb(int portn, int baud);
	~Usb();
	void start();
	static void read();
	static void push();
};

#endif /* USB_H_ */