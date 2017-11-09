#using <System.dll>
#include "usb.h"

using namespace std;
using namespace System;
using namespace System::IO::Ports;
using namespace System::Threading;

USB::USB(){
	usbThread = gcnew Thread(gcnew ThreadStart(USB::push));
	serialPort = gcnew SerialPort("COM1",57600); // ,0,8,1
	serialPort->ReadTimeout = 500;
	serialPort->WriteTimeout = 500;
	buffer = gcnew array<unsigned char>(200);
}
USB::USB(int portn, int baud){
	usbThread = gcnew Thread(gcnew ThreadStart(USB::push));
	System::String^ port;
	switch (portn){
		case 0: port = "COM1"; break;
		case 1: port = "COM2"; break;
		case 2: port = "COM3"; break;
		case 3: port = "COM4"; break;
		case 4: port = "COM5"; break;
		case 5: port = "COM6"; break;
		case 6: port = "COM7"; break;
		case 7: port = "COM8"; break;
		case 8: port = "COM9"; break;
		case 9: port = "COM10"; break;
		case 10: port = "COM11"; break;
		case 11: port = "COM12"; break;
		case 12: port = "COM13"; break;
		case 13: port = "COM14"; break;
		case 14: port = "COM15"; break;
		default: port = "COM1"; break;
	}
	serialPort = gcnew SerialPort(port,baud); // ,0,8,1
	serialPort->ReadTimeout = 500;
	serialPort->WriteTimeout = 500;
	buffer = gcnew array<unsigned char>(200);
}
USB::~USB(){
	usbThread->Join();
	serialPort->Close();
}
void USB::start(){
	serialPort->Open();
	usbThread->Start();
}
void USB::read(){}
void USB::push(){
	while(1){
		serialPort->Write(buffer,0,200);
	}
}