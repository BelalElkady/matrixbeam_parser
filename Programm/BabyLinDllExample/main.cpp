#include <stdio.h>
#include "BabyLIN.h"
#include <windows.h>
#include <string>





#define SDF_FILENAME "ici_light_func.sdf"

void frameCallback(BL_frame_t frame);

void main(int argc, char* argv[])
{
//	int major, minor;
//	const char* version;
//	int rc;
//	int size;
//	BL_portInfo_t portInfo;
//	BL_HANDLE blHandle;
//
//	// get BabyLIN DLL version
//	BL_getVersion(&major, &minor);
//	version = BL_getVersionString();
//
//	printf("v%d.%d, %s\n", major, minor, version);
//
//	// get an available BabyLIN
//	size = 1;
//	rc = BL_searchBabyLinPorts(&portInfo, &size);
//	printf(" %d  found baby lins", rc);
//
//	if(size != 1)
//	{
//		printf("No BabyLIN found\n");
//		 
//	}
//
//	// open connection to BabyLIN
//	blHandle = BL_open(portInfo.portNr);
//
//	if( blHandle == 0 )
//	{
//		printf("Could not open BabyLIN\n");
//		 
//	}
//
//	printf("Opened BabyLIN found\n");
//	
//	// download SDF
//	rc = BL_loadSDF(blHandle, SDF_FILENAME, 1);
//
//	if (rc != BL_OK)
//	{
//		printf("Could not load SDF file into BabyLIN\n");
//		return;
//	}
//
//	printf("Loaded SDF file into BabyLIN\n");
//
//	// start LIN bus
//	rc = BL_sendCommand(blHandle, "start;");
//
//	if (rc != BL_OK)
//	{
//		printf("Could not start LIN bus\n");
//		return;
//	}
//
//	printf("LIN bus started\n");
//
//	// subscribe to frames
//	rc = BL_sendCommand(blHandle, "disframe 255 1;");
//
//	if (rc != BL_OK)
//	{
//		printf("Could not subscribe to frames\n");
//		return;
//	}
//
//	printf("Subscribed to frames\n");
//
//	// register callback
//	rc = BL_registerFrameCallback(blHandle, &frameCallback);
//
//	if (rc != BL_OK)
//	{
//		printf("Could not register callback\n");
//		return;
//	}
//
//	printf("Registered callback\n");
//
//	// final loop
//	printf("Press Enter to stop\n");
//	rc = getchar();
//	while (rc == 32)
//	{
//		rc = getchar();
//	}
//}
//
//void frameCallback(BL_frame_t frame)
//{
//	printf("Frame ID: %d\n", frame.framedata[0].value);
//}
	int rc;
	int size;
	BL_portInfo_t portInfo[10];
	BL_HANDLE blHandle1;
	BL_HANDLE blHandle2;
	int channelCount;
	int idx;
	BL_HANDLE channelHandles[10];
	
	int userData;

	// get an available BabyLIN
	size = 10;
	rc = BL_searchBabyLinPorts(portInfo, &size);
	printf("found number of free ports %d \n", rc);
	if (size < 1)
	{
		printf( "No BabyLIN found");
	}
	printf ("BabyLIN found");
	int foundEmpty = BL_searchBabyLinPorts(NULL, NULL);
	printf(" number of free ports %d \n", foundEmpty);

	// open connection to BabyLIN
	blHandle1 = BL_open(static_cast<unsigned int>(portInfo[0].portNr));
	if (blHandle1 == nullptr)
	{
		printf("Could not open BabyLIN 1\n");
	}else printf("BabyLin 1 opened \n");
	blHandle2 = BL_open(static_cast<unsigned int>(portInfo[1].portNr));

	if (blHandle2 == nullptr)
	{
		printf("Could not open BabyLIN 2\n");
	}else printf("BabyLin 2 opened\n");
	// download SDF
	int rc2 = BL_loadSDF(blHandle2, SDF_FILENAME, 1);

	if (rc2 != BL_OK)
	{
		printf("Could not load SDF file into BabyLIN 2\n");
	}else printf("Loaded SDF file into BabyLIN 2\n");

	int rc1 = BL_loadSDF(blHandle1, SDF_FILENAME, 1);
	if (rc1 != BL_OK)
	{
		printf("Could not load SDF file into BabyLIN 1\n");
	}else printf("Loaded SDF file into BabyLIN 1\n");



	// start LIN bus


	rc2 = BL_sendCommand(blHandle2, "start;");

	if (rc2 != BL_OK)
	{
		printf("could not start lin bus 2\n");
	}
	else printf("lin bus 2 started \n");
	rc1 = BL_sendCommand(blHandle1, "start;");

	if( rc1 != BL_OK)
	{
		printf("Could not start LIN bus 1\n");
	}else printf("LIN bus 1 started \n");

	
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
	rc = BL_sendCommand(blHandle1, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle1, "setsig 188 1;");//Left or right 1/2
	rc = BL_sendCommand(blHandle1, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle1, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle1, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle1, "setsig 189 10;");//angle 0-12
	Sleep(1200);

//For Luggage_Area_front_left:
	rc = BL_sendCommand(blHandle1, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle1, "setsig 188 1;");//Left or right 1/2
	rc = BL_sendCommand(blHandle1, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle1, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle1, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle1, "setsig 189 6;");//angle 0-12
	Sleep(1200);
//For Luggage_Area_back_right:
	rc = BL_sendCommand(blHandle1, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle1, "setsig 188 1;");//Left or right 1/2
	rc = BL_sendCommand(blHandle1, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle1, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle1, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle1, "setsig 189 2;");//angle 0-12
	Sleep(1200);
//For Luggage_Area_back_left:
	rc = BL_sendCommand(blHandle1, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle1, "setsig 188 1;");//Left or right 1/2
	rc = BL_sendCommand(blHandle1, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle1, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle1, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle1, "setsig 189 4;");//angle 0-12
	Sleep(1200);
//For seat_mid_left:
	rc = BL_sendCommand(blHandle1, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle1, "setsig 188 2;");//Left or right 1/2
	rc = BL_sendCommand(blHandle1, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle1, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle1, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle1, "setsig 189 2;");//angle 0-12
	Sleep(1200);
//For seat_back_right:
	rc = BL_sendCommand(blHandle2, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle2, "setsig 188 1;");//Left or right 1/2
	rc = BL_sendCommand(blHandle2, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle2, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle2, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle2, "setsig 189 0;");//angle 0-12
	Sleep(1200);
//For seat_back_middle:
	rc = BL_sendCommand(blHandle2, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle2, "setsig 188 1;");//Left or right 1/2
	rc = BL_sendCommand(blHandle2, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle2, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle2, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle2, "setsig 189 4;");//angle 0-12
	Sleep(400);
	rc = BL_sendCommand(blHandle2, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle2, "setsig 188 2;");//Left or right 1/2
	rc = BL_sendCommand(blHandle2, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle2, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle2, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle2, "setsig 189 2;");//angle 0-12

//For seat_back_left:
	rc = BL_sendCommand(blHandle2, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle2, "setsig 188 2;");//Left or right 1/2
	rc = BL_sendCommand(blHandle2, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle2, "setsig 187 10;");//Focus 0-10
	rc = BL_sendCommand(blHandle2, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle2, "setsig 189 7;");//angle 0-12
	Sleep(400);
	rc = BL_sendCommand(blHandle2, "setsig 183 0;"); //1 ist aus und 0 ist an
	rc = BL_sendCommand(blHandle2, "setsig 188 2;");//Left or right 1/2
	rc = BL_sendCommand(blHandle2, "setsig 186 100;");//Dimming 0-100
	rc = BL_sendCommand(blHandle2, "setsig 187 0;");//Focus 0-10
	rc = BL_sendCommand(blHandle2, "setsig 185 10;");//auslenkung 0-12
	rc = BL_sendCommand(blHandle2, "setsig 189 4;");//angle 0-12
	Sleep(400);
	rc = BL_sendCommand(blHandle1, "setsig 183 1;");//1 ist aus und 0 ist an
	Sleep(400);
	rc = BL_sendCommand(blHandle2, "setsig 183 1;"); //1 ist aus und 0 ist an

}

