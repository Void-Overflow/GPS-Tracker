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

        if (String::Compare(incomingString, "world") == 1) {
            Console::WriteLine("COM Check: " + incomingString);
            isFound = true;
        }
        else {
            COM_Selector::check_counter++;
        }
     }

     if (isFound == true) {
         COM_Selector::selected_port = port;
         COM_Selector::connection_status = true;

         COM_Selector::check_counter = 0;

         box->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\green_led.png");
     }
     else {
         if (COM_Selector::check_counter >= 2) {
             COM_Selector::selected_port = "NONE";
             COM_Selector::connection_status = false;

             box->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\red_led.png");
         }
         else {}
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
        COM_Selector::check_counter++;
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
        COM_Selector::check_counter++;
        return " ";
    }

    return data;
}