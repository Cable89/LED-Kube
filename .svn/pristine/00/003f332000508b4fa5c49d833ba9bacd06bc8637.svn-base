#ifndef USB_H_
#define USB_H_

#using <System.dll>
#include <string>
#include "main.h"

using namespace std;
using namespace System;
using namespace System::IO::Ports;
using namespace System::Threading;

public ref class USB{
private:
	static SerialPort^ serialPort;
	static array<unsigned char>^ buffer;
	Thread^ usbThread;
public:
	USB();
	USB(int portn, int baud);
	~USB();
	static void start();
	static void read();
	static void push();
};

#endif /* USB_H_ */