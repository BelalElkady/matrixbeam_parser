#include "TimeStampCapture.h"
#include <iostream>

bool TimeStampCapture::hasSameSet(void) {
    if (this->getNoOfObj() > 1) {


        if (ObjCaptureVector[0].getSet() == ObjCaptureVector[1].getSet()) return true;

        else return false;


    }
    else return false;


}

void TimeStampCapture::setNoOfObj(int NoOfObj) {

    this->NoOfObj = NoOfObj;

}


int TimeStampCapture::getNoOfObj(void) {

    return this->NoOfObj;

}


void TimeStampCapture::addObjects(ObjectCapture oc ) {

	this->ObjCaptureVector.push_back(oc);
 

}
/*void TimeStampCapture::updateObject(int id) {

}*/
void TimeStampCapture::sendCommand(int command) {
    if (hasSameSet()) {

    }
    else {

    }
}

void TimeStampCapture::clearTimeStamp(void) {
    this->ObjCaptureVector.clear();
}