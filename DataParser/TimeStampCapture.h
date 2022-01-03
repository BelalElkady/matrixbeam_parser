
#ifndef _TS_H_
#define _TS_H_
#endif // !_TS_H_

#include "ObjectCapture.h"
#include "CarSeats.h"


class TimeStampCapture
{
private:
	float Time;
	int NoOfObj;
	
	
	
public:
	
	void setNoOfObj(int);
	int  getNoOfObj(void);
	bool hasSameSet(ObjectCapture*,vector<ObjectsData>*,int);
	bool is_person_leaving(ObjectCapture*, vector<ObjectsData>*, int);
	void addObjects(ObjectCapture , vector<ObjectsData>* , int);
	void objectTracking(CarSeats*, vector<ObjectsData>* ,int);
	Position positionMapping(signed int x , signed int z);
	void sendCommand(int command);
	void clearTimeStamp(void); 
	void reassign_seat(ObjectCapture*,Position,ObjectsData*, CarSeats*);
	void humanPlaceSpot(ObjectCapture*,Position , Direction, ObjectsData* ,CarSeats*);
	void thingPlaceSpot(ObjectCapture*, Position, Direction, ObjectsData*, CarSeats*);
	



};

