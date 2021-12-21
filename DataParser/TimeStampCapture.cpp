#include "TimeStampCapture.h"
#include <iostream>
#include "CarSeats.h"

bool TimeStampCapture::hasSameSet(void) {
    if (this->getNoOfObj() > 1) {


       // if (ObjCaptureVector[0].getSet() == ObjCaptureVector[1].getSet()) return true;

       //0 else return false;

        return true;
    }
    else return false;


}

void TimeStampCapture::setNoOfObj(int NoOfObj) {

    this->NoOfObj = NoOfObj;

}


int TimeStampCapture::getNoOfObj(void) {

    return this->NoOfObj;

}


void TimeStampCapture::addObjects(ObjectCapture oc, vector<ObjectsData>* allObjDB, int timestamp) {
    bool firstTimeFlag = true;
       ObjectsData db;

      
	
    for (auto it = allObjDB->begin(); it !=allObjDB->end() ; ++it) {
      
        if (it->id == oc.getId()) {
           Pos_class pos_instant;
           it->ObjCapture_ID =oc;
           pos_instant.time_stamp = timestamp;
           for(int i = 0 ; i < 3 ; i ++)  pos_instant.pos[i] = oc.getPosition()[i];
           it->ObjCapture_ID_Pos.push_back(pos_instant);

            firstTimeFlag = false; 
        }
    }
    if (firstTimeFlag) {
        Pos_class pos_instant;
       db.id = oc.getId();
       db.hasSeat = false;
       db.ObjCapture_ID=oc;
       db.x=-116;
       pos_instant.time_stamp = timestamp;
       for (int i = 0; i < 3; i++)  pos_instant.pos[i] = oc.getPosition()[i];
       db.ObjCapture_ID_Pos.push_back(pos_instant);
       allObjDB->push_back(db);

    }
    
   
}


Position TimeStampCapture::positionMapping(signed int x , signed int z) {

  
    if (x < -85 && z >= -115) {
        return ENTRANCE;
    }
    else if (x >= -85 && x <= 35 && z >= 20 && z <= 150) {
        return LUGGAGE_AREA;
    }
    else if (x > 35 && x <= 85 && z >= 40 && z <= 120) {
        return FRONT_LEFT;
    }
    else if (x > -85 && x <= 35 && z >= 170 && z <= 220) {
        return BACK_RIGHT;
    }
    else if (x >= -35 && x <= 35 && z >= 170 && z <= 220) {
        return BACK_MIDDLE;
    }
    else if (x > 35 && x <= 85 && z >= 170 && z <= 220) {
        return BACK_LEFT;
    }
    else {
        return OUT;
    }

}

void TimeStampCapture::objectTracking(CarSeats* carSeat , vector<ObjectsData>* allObjDB , int timestamp) {
 
    if (!carSeat->isCarFull()) {
        for (int i = 0; i < timestamp; i++) {
       
            for (auto elem = allObjDB->begin(); elem != allObjDB->end(); ++elem) {
           
           
               
           
               for (auto& obj : elem->ObjCapture_ID_Pos) {
               
                
                  if (obj.time_stamp == i){
                               Position objectPos = positionMapping(obj.pos[0],
                                    obj.pos[2]);


                              if (obj.pos[0] > elem->x) {

                                elem->x = obj.pos[0];

                                elem->ObjCapture_ID.setDirection(GET_IN);


                                if (elem->ObjCapture_ID.getCategory().compare("Human") == 0) {



                                    humanPlaceSpot(&elem->ObjCapture_ID, objectPos, GET_IN, &(*elem), carSeat);



                                }
                                else { //thing

                                    thingPlaceSpot(&elem->ObjCapture_ID, objectPos, GET_IN, &(*elem), carSeat);

                                }
                            }
                            else if (obj.pos[0] < elem->x) {

                                elem->x = obj.pos[0];
                                elem->ObjCapture_ID.setDirection(GET_OUT);



                                if (elem->ObjCapture_ID.getCategory().compare("Human") == 0) {


                                    humanPlaceSpot(&elem->ObjCapture_ID, objectPos, GET_OUT, &(*elem), carSeat);

                                }
                                else { //thing

                                    thingPlaceSpot(&elem->ObjCapture_ID, objectPos, GET_OUT, &(*elem), carSeat);

                                }
                            }
                            else {

                                elem->x = obj.pos[0];
                                elem->ObjCapture_ID.setDirection(SEATED);



                                if (elem->ObjCapture_ID.getCategory().compare("Human") == 0) {


                                    humanPlaceSpot(&elem->ObjCapture_ID, objectPos, SEATED, &(*elem), carSeat);

                                }
                                else { //thing
                                    thingPlaceSpot(&elem->ObjCapture_ID, objectPos, SEATED, &(*elem), carSeat);

                                }
                            }

                        }

                       }
            }

        }
        std::cout << "loop ended" << std::endl;
           /* switch (this->getNoOfObj()) {
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
               
                                humanPlaceSpot(object1, carSeat);
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


            }*/
    }
    else {
        //nothing to do 
    }

}

void TimeStampCapture::sendCommand(int command) {
    if (hasSameSet()) {

    }
    else {

    }
}

void TimeStampCapture::clearTimeStamp(void) {
 //   this->ObjCaptureVector.clear();
}

void TimeStampCapture::humanPlaceSpot(ObjectCapture* object , Position objectPos, Direction objectDir, ObjectsData* vecObj, CarSeats* carSeat) {

   
   
    switch (objectPos)
    {
    case ENTRANCE:
    case LUGGAGE_AREA:

    {
      
        switch (objectDir)
        {
        case GET_IN: {

          
            if (!vecObj->hasSeat) {

                if (carSeat->isCarEmpty() || !carSeat->isFrontLeftBooked()) {
                    std::cout << "******************************************turn on front left " << std::endl;
                    carSeat->bookFrontLeft(object, vecObj);


                }
                else if (carSeat->isFrontLeftBooked() && !carSeat->isBackRightBooked()) {
                    std::cout << "******************************************turn on back right " << std::endl;
                    carSeat->bookBackRight(object, vecObj);


                }
                else if (carSeat->isBackRightBooked() && !carSeat->isBackMiddleBooked()) {
                    std::cout << "****************************turn on back middle " << std::endl;
                    carSeat->bookBackMiddle(object, vecObj);

                }
                else if (carSeat->isBackMiddleBooked() && !carSeat->isBackLeftBooked()) {
                    std::cout << "****************************turn on back left " << std::endl;
                    carSeat->bookBackLeft(object, vecObj);

                }
                else {

                }
            }

            break;
        }
        case GET_OUT: {

            if (vecObj->hasSeat) {
              
                if (carSeat->isFrontLeftBooked() && vecObj->seat_num == FRONT_LEFT) {

                    std::cout << "******************************************turn off front left " << std::endl;
                    carSeat->freeFrontLeft(object, vecObj);


                }
                else if (carSeat->isBackRightBooked() && vecObj->seat_num == BACK_RIGHT) {
                    std::cout << "******************************************turn off back right " << std::endl;
                    carSeat->freeBackRight(object, vecObj);


                }
                else if (carSeat->isBackLeftBooked() && vecObj->seat_num == BACK_LEFT) {
                    std::cout << "****************************turn off back left " << std::endl;
                    carSeat->freeBackLeft(object, vecObj);

                }
                else if (carSeat->isBackMiddleBooked() && vecObj->seat_num == BACK_MIDDLE) {
                    std::cout << "****************************turn off back middle " << std::endl;
                    carSeat->freeBackMiddle(object, vecObj);

                }
                else {

                }
            }




            break;
        }
        default: {
            break;
        }
        }
        break;
    }
    case FRONT_LEFT:
    case BACK_RIGHT:
    case BACK_MIDDLE:
    case BACK_LEFT:

    {

        switch (objectDir)
        {

        case GET_OUT: {

            if (vecObj->hasSeat) {
                std::cout << vecObj->seat_num << std::endl;
                if (carSeat->isFrontLeftBooked() && vecObj->seat_num == FRONT_LEFT) {

                    std::cout << "******************************************turn off front left " << std::endl;
                    carSeat->freeFrontLeft(object, vecObj);


                }
                else if (carSeat->isBackRightBooked() && vecObj->seat_num == BACK_RIGHT) {
                    std::cout << "******************************************turn off back right " << std::endl;
                    carSeat->freeBackRight(object, vecObj);


                }
                else if (carSeat->isBackLeftBooked() && vecObj->seat_num == BACK_LEFT) {
                    std::cout << "****************************turn off back left " << std::endl;
                    carSeat->freeBackLeft(object, vecObj);

                }
                else if (carSeat->isBackMiddleBooked() && vecObj->seat_num == BACK_MIDDLE) {
                    std::cout << "****************************turn off back middle " << std::endl;
                    carSeat->freeBackMiddle(object, vecObj);

                }
                else {

                }
            }




            break;

        }
        default:
        {
            break;
        }
        }

        break;
    }



    default:
    {
        //  std::cout << "turn off all lights" << std::endl;
        break;
    }



    }
}
void TimeStampCapture::thingPlaceSpot(ObjectCapture* object,Position objectPos,Direction objectDir, ObjectsData* vecObj, CarSeats* carSeat) {

    
    switch (objectPos)
    {
    case ENTRANCE:
    case LUGGAGE_AREA:
    case FRONT_LEFT:
    case BACK_LEFT:
    case BACK_MIDDLE:
    case BACK_RIGHT:
    {
        switch (objectDir)
        {
            case GET_IN: {


                if (!vecObj->hasSeat) {
                    std::cout << "turn on luggage area" << std::endl;
                    carSeat->bookLuggageArea(object, vecObj);
                }
                break;
            }
            case GET_OUT: {

                if (vecObj->hasSeat) {
                    std::cout << "turn off luggage area" << std::endl;
                    carSeat->freeLuggageArea(object, vecObj);
                }
                break;
            }
            default:
            {
                break;
            }
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