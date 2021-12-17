#include "TimeStampCapture.h"
#include <iostream>
#include "CarSeats.h"

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


Position TimeStampCapture::positionMapping(ObjectCapture ObCapture) {

    signed int* pos = ObCapture.getPosition();

    if (pos[0] < -85 && pos[0] >= -115) {
        return ENTRANCE;
    }
    else if (pos[0] >= -85 && pos[0] <= 35 && pos[2] >= 20 && pos[2] <= 150) {
        return LUGGAGE_AREA;
    }
    else if (pos[0] > 35 && pos[0] <= 85 && pos[2] >= 40 && pos[2] <= 120) {
        return FRONT_LEFT;
    }
    else if (pos[0] > -85 && pos[0] <= 35 && pos[2] >= 170 && pos[2] <= 220) {
        return BACK_RIGHT;
    }
    else if (pos[0] >= -35 && pos[0] <= 35 && pos[2] >= 170 && pos[2] <= 220) {
        return BACK_MIDDLE;
    }
    else if (pos[0] > 35 && pos[0] <= 85 && pos[2] >= 170 && pos[2] <= 220) {
        return BACK_LEFT;
    }
    else {
        return OUT;
    }

}
void TimeStampCapture::objectTracking(CarSeats* carSeat) {

    
    
    switch (this->getNoOfObj()) {
    case 1 : 
    {
        
        ObjectCapture object = this->ObjCaptureVector[0];
        if (object.getCategory().compare("Human") == 0) {
           
            humanPlaceSpot(object , carSeat);
        }
        else { //thing

        }
        break;
    }
    case 2 : 
    {
        ObjectCapture object1 = this->ObjCaptureVector[0];
        ObjectCapture object2 = this->ObjCaptureVector[1];
        if (object1.getCategory().compare("Human") == 0 && object2.getCategory().compare("Thing") == 0) {
            if (hasSameSet()) {
                humanPlaceSpot(object1,carSeat);
                thingPlaceSpot(object2, carSeat);

            }
            else {
                //logically thing will not ride on its own 
            }

                
        
        }
        else if (object1.getCategory().compare("Thing") == 0 && object2.getCategory().compare("Human") == 0) {
            if (hasSameSet()) {
                humanPlaceSpot(object2, carSeat);
                thingPlaceSpot(object1, carSeat);

            }
            else {
                //logically thing will not ride on its own 
            }



        }
        else if (object1.getCategory().compare("Human") == 0 && object2.getCategory().compare("Human") == 0) {
            
                humanPlaceSpot(object2, carSeat);
                humanPlaceSpot(object1, carSeat);

          


        }
        else {
            //nothing
        }

    }

    default:
    {
        
        break;
    }


    }
   

}
void TimeStampCapture::sendCommand(int command) {
    if (hasSameSet()) {

    }
    else {

    }
}

void TimeStampCapture::clearTimeStamp(void) {
    this->ObjCaptureVector.clear();
}

void TimeStampCapture::humanPlaceSpot(ObjectCapture object , CarSeats* carSeat) {

    Position objectPos = positionMapping(object);

    switch (objectPos)
    {
    case ENTRANCE:
    case LUGGAGE_AREA:
    {


        if (carSeat->IsCarEmpty() || !carSeat->IsFrontLeftBooked()) {
            std::cout << "turn on front left " << std::endl;
            carSeat->bookFrontLeft();

        }
        else if (carSeat->IsFrontLeftBooked() && !carSeat->IsBackRightBooked()) {
            std::cout << "turn on back right " << std::endl;
            carSeat->bookBackRight();
        }
        else if (carSeat->IsBackRightBooked() && !carSeat->IsBackMiddleBooked()) {
            std::cout << "turn on back middle " << std::endl;
            carSeat->bookBackMiddle();
        }
        else if (carSeat->IsBackMiddleBooked() && !carSeat->IsBackLeftBooked()) {
            std::cout << "turn on back left " << std::endl;
            carSeat->bookBackLeft();
        }
        else {

        }
        break;
    }
    default:
    {
        std::cout << "turn off all lights" << std::endl;
        break;
    }
    }


}
void TimeStampCapture::thingPlaceSpot(ObjectCapture object, CarSeats* carSeat) {

    Position objectPos = positionMapping(object);

    switch (objectPos)
    {
    case ENTRANCE:
    case LUGGAGE_AREA:
    case FRONT_LEFT:
    case BACK_LEFT:
    case BACK_MIDDLE:
    case BACK_RIGHT:
    {

        std::cout << "turn on luggage area" << std::endl;
        
        break;
    }
    default:
    {
        std::cout << "turn off all lights" << std::endl;
        break;
    }
    }


}