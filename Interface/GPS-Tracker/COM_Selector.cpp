#include "COM_Selector.h"

using namespace System;
using namespace System::IO::Ports;
using namespace System::Drawing;


void COM_Selector::checkConnection(Thread^ t, PictureBox^ box) {
     array<String^>^ aports = SerialPort::GetPortNames();
     String^ port = " ";
     bool isFound = false;

     for each(port in aports) {
        writeCOM("hello", port);
        
        t->Sleep(400);

        String^ incomingString = readCOM(port);
        Console::WriteLine("COM Check: " + incomingString);

        if (String::Compare(incomingString, "world") == 1)
            isFound = true;
     }

     if (isFound == true) {
         COM_Selector::selected_port = port;
         COM_Selector::connection_status = true;

         box->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\green_led.png");
     }
     else {
         COM_Selector::selected_port = "NONE";
         COM_Selector::connection_status = false;

         box->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\red_led.png");
     }

     t->Sleep(5000);
}

void COM_Selector::writeCOM(String^ data, String^ selected_port) {
    SerialPort^ port = gcnew SerialPort(
        selected_port, 9600, Parity::None, 8, StopBits::One);

    try {
        port->Open();
        port->Write(data);
        port->Close();
    }

    catch (Exception^ ex) {
        Console::WriteLine(ex);
    }
}

String^ COM_Selector::readCOM(String^ selected_port) {
    SerialPort^ port = gcnew SerialPort(
        selected_port, 9600, Parity::None, 8, StopBits::One);
    port->Handshake = Handshake::None;
    port->RtsEnable = true;

    String^ data = " ";

    try {
        port->Open();
        data = port->ReadLine();
        port->Close();

    }
    catch (Exception^ ex) {
        Console::WriteLine(ex);
        return " ";
    }

    return data;
}