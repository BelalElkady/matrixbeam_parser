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
	bool HasSameSet(void);
public:
	void setTime(float);
	void setObjectsVector(vector<ObjectCapture>);
	void updateObject(int id);
	void sendCommand(int command);



};

