#include <stdio.h>
#include "BabyLIN.h"
#include <windows.h>
#include <string>





#define SDF_FILENAME "ici_light_func.sdf"

void frameCallback(BL_frame_t frame);

void main(int argc, char* argv[])
{
	int major, minor;
	const char* version;
	int rc;
	int size;
	BL_portInfo_t portInfo;
	BL_HANDLE blHandle;

	// get BabyLIN DLL version
	BL_getVersion(&major, &minor);
	version = BL_getVersionString();

	printf("v%d.%d, %s\n", major, minor, version);

	// get an available BabyLIN
	size = 1;
	rc = BL_searchBabyLinPorts(&portInfo, &size);

	if(size != 1)
	{
		printf("No BabyLIN found\n");
		return ;
	}

	// open connection to BabyLIN
	blHandle = BL_open(portInfo.portNr);

	if( blHandle == 0 )
	{
		printf("Could not open BabyLIN\n");
		return;
	}

	printf("Opened BabyLIN found\n");

	// download SDF
	rc = BL_loadSDF(blHandle, SDF_FILENAME, 1);
	
	if( rc != BL_OK)
	{
		printf("Could not load SDF file into BabyLIN\n");
		return;
	}

	printf("Loaded SDF file into BabyLIN\n");

	// start LIN bus
	rc = BL_sendCommand(blHandle, "start;");

	if( rc != BL_OK)
	{
		printf("Could not start LIN bus\n");
		return;
	}

	printf("LIN bus started\n");

	
	//while (1)
	//{ 
	//
	////right matrix light
	//rc = bl_sendcommand(blhandle, "setsig 183 0;"); //1 ist aus und 0 ist an
	//rc = bl_sendcommand(blhandle, "setsig 188 1;");//left or right 1/2
	//rc = bl_sendcommand(blhandle, "setsig 187 0;");//focus 0-10
	//rc = bl_sendcommand(blhandle, "setsig 189 0;");//angle 0-12
	//rc = bl_sendcommand(blhandle, "setsig 185 0;");//auslenkung 0-12
	////rc = bl_sendcommand(blhandle, "setsig 186 5;");//dimming 0-100
	//for (int i = 0; i < 100; i++)
	//{
	//	std::string command = "";

	//	command += "setsig 186 ";
	//	command += std::to_string(i);
	//	command += ";";
	//	const char* khara = command.c_str();
	//	bl_sendcommand(blhandle, khara);
	//	//Sleep(1000);
	//}
	//Sleep(1000);
	//rc = bl_sendcommand(blhandle, "setsig 188 1;");//left or right 1/2
	//rc = bl_sendcommand(blhandle, "setsig 187 0;");//focus 0-10
	//rc = bl_sendcommand(blhandle, "setsig 186 0;");//dimming 0-100
	//rc = bl_sendcommand(blhandle, "setsig 189 0;");//angle 0-12
	//rc = bl_sendcommand(blhandle, "setsig 185 0;");//auslenkung 0-12

	//rc = bl_sendcommand(blhandle, "setsig 188 2;");//left or right 1/2
	//rc = bl_sendcommand(blhandle, "setsig 187 0;");//focus 0-10
	//rc = bl_sendcommand(blhandle, "setsig 189 0;");//angle 0-12
	//rc = bl_sendcommand(blhandle, "setsig 185 0;");//auslenkung 0-12
	//Sleep(1000);
	////rc = bl_sendcommand(blhandle, "setsig 186 5;");//dimming 0-100
	//for (int i = 0; i < 100; i++)
	//{
	//	std::string command = "";

	//	command += "setsig 186 "; //define left or right
	//	command += std::to_string(i);
	//	command += ";";
	//	//bl_sendcommand(blhandle, "setsig 186"); 
	//	//bl_sendcommand(blhandle, std::to_string(i));
	//	//bl_sendcommand(blhandle, ";");
	//	const char* khara = command.c_str();
	//	bl_sendcommand(blhandle, khara);
	//	//Sleep(1000);
	//}
	//rc = bl_sendcommand(blhandle, "setsig 188 1;");//left or right 1/2
	//rc = bl_sendcommand(blhandle, "setsig 187 0;");//focus 0-10
	//rc = bl_sendcommand(blhandle, "setsig 186 0;");//dimming 0-100
	//rc = bl_sendcommand(blhandle, "setsig 189 0;");//angle 0-12
	//rc = bl_sendcommand(blhandle, "setsig 185 0;");//auslenkung 0-12
	//Sleep(1000);
	//
	////Sleep(5000);
	////rc = bl_sendcommand(blhandle, "setsig 183 1;"); //1 ist aus und 0 ist an
	////rc = bl_sendcommand(blhandle, "setsig 188 1;");//left or right 1/2
	////rc = bl_sendcommand(blhandle, "setsig 187 0;");//focus 0-10
	////rc = bl_sendcommand(blhandle, "setsig 186 0;");//dimming 0-100
	////rc = bl_sendcommand(blhandle, "setsig 189 0;");//angle 0-12
	////rc = bl_sendcommand(blhandle, "setsig 185 0;");//auslenkung 0-12
	////Sleep(1200);
	////Sleep(5000);
	////bl_closeall();
	////left matrix light
	////rc = bl_sendcommand(blhandle, "setsig 183 0;"); //1 ist aus und 0 ist an
	////rc = bl_sendcommand(blhandle, "setsig 188 2;");//left or right 1/2
	////rc = bl_sendcommand(blhandle, "setsig 187 0;");//focus 0-10
	////rc = bl_sendcommand(blhandle, "setsig 186 5;");//dimming 0-100
	////rc = bl_sendcommand(blhandle, "setsig 189 0;");//angle 0-12
	////rc = bl_sendcommand(blhandle, "setsig 185 0;");//auslenkung 0-12

	////Sleep(5000);

	////rc = bl_sendcommand(blhandle, "setsig 183 1;"); //1 ist aus und 0 ist an
	//Sleep(1000);
	////rc = bl_sendcommand(blhandle, "reset;");
	//// final loop
	////printf("press enter to stop\n");
	////rc = getchar();
	////while(rc == 32)
	////{
	////	rc = getchar();
	////}
	//}
//For Luggage_Area_front_right:
	rc = BL_sendCommand(blHandle, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle, "setsig 188 1;");//Left or right 1/2
	rc = BL_sendCommand(blHandle, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle, "setsig 189 10;");//angle 0-12
	Sleep(1200);

//For Luggage_Area_front_left:
	rc = BL_sendCommand(blHandle, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle, "setsig 188 1;");//Left or right 1/2
	rc = BL_sendCommand(blHandle, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle, "setsig 189 6;");//angle 0-12
	Sleep(1200);
//For Luggage_Area_back_right:
	rc = BL_sendCommand(blHandle, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle, "setsig 188 1;");//Left or right 1/2
	rc = BL_sendCommand(blHandle, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle, "setsig 189 2;");//angle 0-12
	Sleep(1200);
//For Luggage_Area_back_left:
	rc = BL_sendCommand(blHandle, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle, "setsig 188 1;");//Left or right 1/2
	rc = BL_sendCommand(blHandle, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle, "setsig 189 4;");//angle 0-12
	Sleep(1200);
//For seat_mid_left:
	rc = BL_sendCommand(blHandle, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle, "setsig 188 2;");//Left or right 1/2
	rc = BL_sendCommand(blHandle, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle, "setsig 189 2;");//angle 0-12
	Sleep(1200);
//For seat_back_right:
	rc = BL_sendCommand(blHandle, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle, "setsig 188 1;");//Left or right 1/2
	rc = BL_sendCommand(blHandle, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle, "setsig 189 0;");//angle 0-12
	Sleep(1200);
//For seat_back_middle:
	rc = BL_sendCommand(blHandle, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle, "setsig 188 1;");//Left or right 1/2
	rc = BL_sendCommand(blHandle, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle, "setsig 189 4;");//angle 0-12
	Sleep(400);
	rc = BL_sendCommand(blHandle, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle, "setsig 188 2;");//Left or right 1/2
	rc = BL_sendCommand(blHandle, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle, "setsig 189 2;");//angle 0-12

//For seat_back_left:
	rc = BL_sendCommand(blHandle, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle, "setsig 188 2;");//Left or right 1/2
	rc = BL_sendCommand(blHandle, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle, "setsig 187 10;");//Focus 0-10
	rc = BL_sendCommand(blHandle, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle, "setsig 189 7;");//angle 0-12
	Sleep(400);
	rc = BL_sendCommand(blHandle, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle, "setsig 188 2;");//Left or right 1/2
	rc = BL_sendCommand(blHandle, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle, "setsig 189 4;");//angle 0-12




}

