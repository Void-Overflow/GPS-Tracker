#ifndef COM_SELECTOR_H
#define COM_SELECTOR_H

#include <string>

using namespace System;
using namespace System::Threading;
using namespace System::Windows::Forms;

ref class COM_Selector{
	static int check_counter = 0;
public:
	static String^ selected_port = "NONE";
	static bool connection_status = false;

	void writeCOM(String^ data, String^ selected_port);
	String^ readCOM(String^ selected_port);

	void checkConnection(Thread^ t, PictureBox^ box);
};

#endif
