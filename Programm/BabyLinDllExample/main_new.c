#include <stdio.h>
#include "BabyLINCAN.h"

#define SDF_FILENAME "SimpleWiperLDF-01.sdf"
#define MAX_DEVICES 10
#define MAX_CHANNELS 8

void frameCallback(BL_HANDLE channelHandle, BLC_FRAME frame, void* userData);

void main(int argc, char* argv[])
{
	const char* version;
	int rc;
	int size;
	BLC_PORTINFO portInfo[MAX_DEVICES];
	BL_HANDLE blHandle;
	int channelCount;
	int idx;
    BL_HANDLE channelHandles[MAX_CHANNELS];
    BLC_CHANNELINFO channelInfos[MAX_CHANNELS];
	BL_HANDLE channelHandle;
	int userData;

	// get BabyLIN DLL version
	version = BLC_getVersionString();

	printf("%s\n", version);
	
    // get all available BabyLINs
	size = MAX_DEVICES;
	rc = BLC_getBabyLinPorts(portInfo, &size);
	if(size < 1)
	{
		printf("No BabyLIN found\n");
		return;
	}

	// open connection to BabyLIN
	blHandle = BLC_open(portInfo[0].portNr);
	if( blHandle == 0 )
	{
		printf("Could not open BabyLIN\n");
		return;
	}

	printf("Opened BabyLIN found\n");

	// download SDF
	rc = BLC_loadSDF(blHandle, SDF_FILENAME, 1);
	
	if( rc != BL_OK)
	{
		printf("Could not load SDF file into BabyLIN\n");
		return;
	}

	printf("Loaded SDF file into BabyLIN\n");

    // get the number of available channels
    channelCount = BLC_getChannelCount(blHandle);

    // get channel infos
    for (idx = 0; idx < channelCount; idx++)
	{
		// connect to each channel
		channelHandles[idx] = BLC_getChannelHandle(blHandle, idx);
		if (channelHandles[idx] != 0)
		{
			// get channel info
			rc = BLC_getChannelInfo(channelHandles[idx], &channelInfos[idx]);
			if (rc == BL_OK)
			{
				printf("Channel info: Name=\"%s\", Type=%d, MaxBaudrate=%d\n", channelInfos[idx].name, channelInfos[idx].type, channelInfos[idx].maxbaudrate);
			}
		}
	}

    // for this example we will use the LIN channel
    if (channelCount <= 1)
    {
        printf("The connected device does not support LIN.");
    }

	// select the LIN channel
    channelHandle = channelHandles[1];
    if (channelHandle == 0)
    {
        printf("No connection to the LIN channel could be established.");
    }

	// start LIN bus
	rc = BLC_sendCommand(channelHandle, "start;");

	if( rc != BL_OK)
	{
		printf("Could not start LIN bus\n");
		return;
	}

	printf("LIN bus started\n");

	// subscribe to frames
	rc = BLC_sendCommand(channelHandle, "disframe 255 1;");
	
	if( rc != BL_OK)
	{
		printf("Could not subscribe to frames\n");
		return;
	}

	printf("Subscribed to frames\n");

	// register callback
	userData = 314;
	rc = BLC_registerUserDataFrameCallback(channelHandle, frameCallback, &userData);
	
	if( rc != BL_OK)
	{
		printf("Could not register callback\n");
		return;
	}

	printf("Registered callback\n");

	// final loop
	printf("Press Enter to stop\n");
	rc = getchar();
	while(rc == 32)
	{
		rc = getchar();
	}

	// close all Baby-LINs
	BLC_closeAll();
}

void frameCallback(BL_HANDLE channelHandle, BLC_FRAME frame, void* userData)
{
	int *userDataPtr = (int*)userData;
	printf("UserData: %d, Frame ID: %d\n", *userDataPtr, frame.frameId);
}