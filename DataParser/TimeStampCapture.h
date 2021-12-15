#pragma once
#ifndef _TS_H_
#define _TS_H_
#endif // !_TS_H_

#include "ObjectCapture.h"

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
	void updateObject(int id);
	void sendCommand(int command);



};

