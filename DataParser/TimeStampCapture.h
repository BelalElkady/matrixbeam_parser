#pragma once
#ifndef _TS_H_
#define _TS_H_
#endif // !_TS_H_

#include "ObjectCapture.h"
#include "CarSeats.h"
typedef enum positions { ENTRANCE, LUGGAGE_AREA, FRONT_LEFT, BACK_RIGHT, BACK_MIDDLE, BACK_LEFT , OUT} Position;
class TimeStampCapture
{
private:
	float Time;
	int NoOfObj;
	vector<ObjectCapture> ObjCaptureVector;
	
	
public:
	void setNoOfObj(int);
	int  getNoOfObj(void);
	bool hasSameSet(void);
	void addObjects(ObjectCapture);
	void objectTracking(CarSeats*);
	Position positionMapping(ObjectCapture);
	void sendCommand(int command);
	void clearTimeStamp(void); 
	void humanPlaceSpot(ObjectCapture, CarSeats*);
	void thingPlaceSpot(ObjectCapture, CarSeats*);



};

