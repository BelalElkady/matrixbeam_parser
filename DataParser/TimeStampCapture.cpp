#include "TimeStampCapture.h"
#include <iostream>
#include "CarSeats.h"

bool TimeStampCapture::is_person_leaving(ObjectCapture* oc, vector<ObjectsData>* allObjDB, int timestamp) {
    int obj_set = oc->getSet();
    int obj_id = oc->getId();
    for (auto it = allObjDB->begin(); it != allObjDB->end(); ++it) {
        if (it->id != obj_id) {
            if (it->ObjCapture_ID.getSet() == obj_set) {
                for (auto& obj : it->ObjCapture_ID_Pos) {
                    if (obj.time_stamp == timestamp) {
                      if (!it-> hasSeat)
                          // does not have a seat
                        return true;
                    
                    }
                }
            }
        }

    }
    return false;

}

bool TimeStampCapture::hasSameSet(ObjectCapture* oc, vector<ObjectsData>* allObjDB, int timestamp) {
    int obj_set = oc->getSet();
    int obj_id = oc->getId();
    for (auto it = allObjDB->begin(); it != allObjDB->end(); ++it) {
        if (it->id != obj_id) {
            if (it->ObjCapture_ID.getSet() == obj_set) {
                for (auto& obj : it->ObjCapture_ID_Pos) {
                    if (obj.time_stamp == timestamp) {
                            return true;

                    }
                }
            }
        }

    }
    return false;

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
    else if (x >= -85 && x <= -25 && z >= 20 && z <= 85) {
        return LUGGAGE_AREA_1;
    }
    else if (x >= -25 && x <= 35 && z >= 20 && z <= 85) {
        return LUGGAGE_AREA_2;
    }
    else if (x >= -85 && x <= -25 && z >= 85 && z <= 150) {
        return LUGGAGE_AREA_3;
    }
    else if (x >= -25 && x <= 35 && z >= 85 && z <= 150) {
        return LUGGAGE_AREA_4;
    }
    else if (x > 35 && x <= 85 && z >= 40 && z <= 120) {
        return FRONT_LEFT;
    }
    else if (x > -85 && x <= -35 && z >= 170 && z <= 220) {
        return BACK_RIGHT;
    }
    else if (x > -35 && x <= 35 && z >= 170 && z <= 220) {
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
            std::cout << "time:" << i << std::endl;
            for (auto elem = allObjDB->begin(); elem != allObjDB->end(); ++elem) {
           
           
               
           
               for (auto& obj : elem->ObjCapture_ID_Pos) {
               
                
                  if (obj.time_stamp == i){
                               Position objectPos = positionMapping(obj.pos[0],
                                    obj.pos[2]);

                               std::cout << elem->id << " : " << elem->x << std::endl;
                               if ((obj.pos[0] > elem->x)&&(obj.pos[0] - elem->x > 5)) {

                                   elem->x = obj.pos[0];
                                   elem->ObjCapture_ID.setDirection(GET_IN);

                                   if (elem->ObjCapture_ID.getCategory().compare("Human") == 0) {
                                       std::cout << "getting in" << std::endl;
                                       humanPlaceSpot(&elem->ObjCapture_ID, objectPos, GET_IN, &(*elem), carSeat);
                                   }
                                   else { //thing
                                       if (hasSameSet( &(elem->ObjCapture_ID) , &(*allObjDB), i)) {
                                           thingPlaceSpot(&elem->ObjCapture_ID, objectPos, GET_IN, &(*elem), carSeat);
                                       }
                                       else {
                                           std::cout << "Bag is alone and no action to be done" << std::endl;
                                       }
                                   }
                               }
                               else if ((obj.pos[0] < elem->x)&&(elem->x - obj.pos[0] > 5)) {
                                   std::cout << "getting out :" <<obj.pos[0] << std::endl;
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
                                   if ((obj.pos[0] - elem->x <= 5) || (elem->x - obj.pos[0] <= 5)) {
                                       switch (objectPos)
                                       {
                                       case BACK_LEFT:
                                       case BACK_MIDDLE:
                                       case BACK_RIGHT:
                                       case FRONT_LEFT:
                                       {
                                           elem->x = obj.pos[0];
                                           elem->ObjCapture_ID.setDirection(SEATED);
                                           if (elem->ObjCapture_ID.getCategory().compare("Human") == 0) {
                                               std::cout << "Seated for Human" << std::endl;
                                               humanPlaceSpot(&elem->ObjCapture_ID, objectPos, SEATED, &(*elem), carSeat);

                                           }
                                           else {
                                               if (is_person_leaving(&(elem->ObjCapture_ID), &(*allObjDB), i)) {
                                                   std::cout << "You forgot your bag on :" << elem->seat_num << std::endl;
                                               }
                                               else {
                                                   std::cout << "Seated for Thing" << std::endl;
                                                   thingPlaceSpot(&elem->ObjCapture_ID, objectPos, SEATED, &(*elem), carSeat);
                                               }
                                           }
                                       }
                                       case LUGGAGE_AREA_1:
                                       case LUGGAGE_AREA_2:
                                       case LUGGAGE_AREA_3:
                                       case LUGGAGE_AREA_4:
                                       case ENTRANCE:
                                       {
                                           if (elem->ObjCapture_ID.getCategory().compare("Thing") == 0) {
                                               elem->x = obj.pos[0];
                                               elem->ObjCapture_ID.setDirection(SEATED);
                                               if (is_person_leaving(&(elem->ObjCapture_ID), &(*allObjDB), i)) {
                                                   std::cout << "DON`T forgot your bag on :" << elem->seat_num << std::endl;
                                               }
                                               else {
                                                   if (hasSameSet(&(elem->ObjCapture_ID), &(*allObjDB), i))
                                                   thingPlaceSpot(&elem->ObjCapture_ID, objectPos, SEATED, &(*elem), carSeat);
                                                   else
                                                       std::cout << "You forgot your bag on :" << elem->seat_num << std::endl;
                                               }
                                           }
                                           if (obj.pos[0] > elem->x) {


                                               if (elem->ObjCapture_ID.getCategory().compare("Human") == 0) {
                                                   elem->x = obj.pos[0];
                                                   elem->ObjCapture_ID.setDirection(GET_IN);
                                                   std::cout << "getting in" << std::endl;
                                                   humanPlaceSpot(&elem->ObjCapture_ID, objectPos, GET_IN, &(*elem), carSeat);
                                               }

                                           }
                                           else if (obj.pos[0] < elem->x) {
                                               std::cout << "getting out :" << obj.pos[0] << std::endl;
                                               if (elem->ObjCapture_ID.getCategory().compare("Human") == 0) {
                                                   elem->x = obj.pos[0];
                                                   elem->ObjCapture_ID.setDirection(GET_OUT);

                                                   humanPlaceSpot(&elem->ObjCapture_ID, objectPos, GET_OUT, &(*elem), carSeat);
                                               }

                                           }
                                       }
                                       default:
                                           break;
                                       }
                                   }
                                //elem->x = obj.pos[0];
                                //elem->ObjCapture_ID.setDirection(SEATED);

                                //if (elem->ObjCapture_ID.getCategory().compare("Human") == 0) {

                                //    humanPlaceSpot(&elem->ObjCapture_ID, objectPos, SEATED, &(*elem), carSeat);

                                //}
                                //else { //thing
                                //    thingPlaceSpot(&elem->ObjCapture_ID, objectPos, SEATED, &(*elem), carSeat);

                                //}
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
//    if (hasSameSet()) {   }
//    else {    }
}

void TimeStampCapture::clearTimeStamp(void) {
 //   this->ObjCaptureVector.clear();
}

void TimeStampCapture::reassign_seat (ObjectCapture* object ,Position objectPos,ObjectsData* vecObj, CarSeats* carSeat){
    if (vecObj->seat_num != objectPos) {
        std::cout <<"seat:" << vecObj->seat_num << " has been changed to seat : " << objectPos << std::endl;
        switch (vecObj->seat_num) {

        case FRONT_LEFT:
        {            carSeat->freeFrontLeft(object, vecObj);
        std::cout << "******************************************turn off front left " << std::endl;
        break; }
        case BACK_RIGHT:
        {   carSeat->freeBackRight(object, vecObj);
        std::cout << "******************************************turn off back right " << std::endl;
        break; }
        case BACK_MIDDLE:
        {   carSeat->freeBackMiddle(object, vecObj); 
        std::cout << "****************************turn off back middle " << std::endl;

        break; }
        case BACK_LEFT:
        {   carSeat->freeBackLeft(object, vecObj); 
        std::cout << "****************************turn off back left " << std::endl;

        break; }
        case LUGGAGE_AREA_1:
        {   carSeat->freeLuggageArea_1(object, vecObj); 
        std::cout << "******************************************luggage area 1 is  turrned off " << std::endl;

        break; }
        case LUGGAGE_AREA_2:
        {   carSeat->freeLuggageArea_2(object, vecObj); 
        std::cout << "******************************************luggage area 2 is  turrned off " << std::endl;

        break; }
        case LUGGAGE_AREA_3:
        {   carSeat->freeLuggageArea_3(object, vecObj); 
        std::cout << "******************************************luggage area 3 is  turrned off " << std::endl;

        break; }
        case LUGGAGE_AREA_4:
        {   carSeat->freeLuggageArea_4(object, vecObj); 
        std::cout << "******************************************luggage area 4 is  turrned off " << std::endl;

        break; }
        default: {
            break;
        }
        }
        vecObj->seat_num = objectPos;
        switch (vecObj->seat_num) {
            case FRONT_LEFT:
        {            carSeat->bookFrontLeft(object, vecObj); 
        std::cout << "******************************************seated on front left " << std::endl;

        break; }
            case BACK_RIGHT:
        {    carSeat->bookBackRight(object, vecObj); 
        std::cout << "******************************************seated on back right " << std::endl;

        break; }
            case BACK_MIDDLE:
        {   carSeat->bookBackMiddle(object, vecObj); 
        std::cout << "****************************seated on back middle " << std::endl;
        break; }
            case BACK_LEFT:
        {   carSeat->bookBackLeft(object, vecObj); 
        std::cout << "****************************seated on back left " << std::endl;
        break; }
            case LUGGAGE_AREA_1:
        {   carSeat->bookLuggageArea_1(object, vecObj); 
        std::cout << "seated on luggage area 1" << std::endl;

        break; }
            case LUGGAGE_AREA_2:
        {   carSeat->bookLuggageArea_2(object, vecObj); 
        std::cout << "seated on luggage area 2" << std::endl;

        break; }
            case LUGGAGE_AREA_3:
        {   carSeat->bookLuggageArea_3(object, vecObj); 
        std::cout << "seated on luggage area 3" << std::endl;

        break; }
            case LUGGAGE_AREA_4:
        {   carSeat->bookLuggageArea_4(object, vecObj); 
        std::cout << "seated on luggage area 4" << std::endl;

        break; }
        default: {
            break;
        }
        }

    }
}
void TimeStampCapture::humanPlaceSpot(ObjectCapture* object , Position objectPos, Direction objectDir, ObjectsData* vecObj, CarSeats* carSeat) {

//    std::cout << "OC:" << object->getId()<<std::endl;
//    std::cout << "OD:" << vecObj->id<<std::endl;
    

   
    switch (objectPos)
    {
    case ENTRANCE:
    case LUGGAGE_AREA_1:
    case LUGGAGE_AREA_2:
    case LUGGAGE_AREA_3:
    case LUGGAGE_AREA_4:

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

        case SEATED: {

            if (vecObj->hasSeat) {
                if (vecObj ->seat_num != objectPos)
                reassign_seat(object,objectPos, &(*vecObj), carSeat);

                std::cout << vecObj-> seat_num << std::endl;
                if (carSeat->isFrontLeftBooked() && vecObj->seat_num == FRONT_LEFT) {

                    std::cout << "******************************************turn off front left " << std::endl;
//                    carSeat->freeFrontLeft(object, vecObj);


                }
                else if (carSeat->isBackRightBooked() && vecObj->seat_num == BACK_RIGHT) {
                    std::cout << "******************************************turn off back right " << std::endl;
  //                  carSeat->freeBackRight(object, vecObj);


                }
                else if (carSeat->isBackLeftBooked() && vecObj->seat_num == BACK_LEFT) {
                    std::cout << "****************************turn off back left " << std::endl;
    //                carSeat->freeBackLeft(object, vecObj);

                }
                else if (carSeat->isBackMiddleBooked() && vecObj->seat_num == BACK_MIDDLE) {
                    std::cout << "****************************turn off back middle " << std::endl;
      //              carSeat->freeBackMiddle(object, vecObj);

                }
                else {

                }
            }




            break;

        }
        
        case GET_OUT:
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
void TimeStampCapture::thingPlaceSpot(ObjectCapture* object, Position objectPos, Direction objectDir, ObjectsData* vecObj, CarSeats* carSeat) {


    switch (objectPos)
    {
    case ENTRANCE:
    case LUGGAGE_AREA_1:
    case LUGGAGE_AREA_2:
    case LUGGAGE_AREA_3:
    case LUGGAGE_AREA_4:
    case FRONT_LEFT:
    case BACK_LEFT:
    case BACK_MIDDLE:
    case BACK_RIGHT:
    {
        switch (objectDir)
        {
        case GET_IN: {
            if (!vecObj->hasSeat) {
                if (carSeat->isCarEmpty() || !carSeat->isLuggageArea_1_Booked()) {
                    std::cout << "turn on luggage area 1" << std::endl;
                    carSeat->bookLuggageArea_1(object, vecObj);
                }
                else if (carSeat->isLuggageArea_1_Booked() && !carSeat->isLuggageArea_2_Booked()) {
                    std::cout << "turn on luggage area 2" << std::endl;
                    carSeat->bookLuggageArea_2(object, vecObj);
                }
                else if (carSeat->isLuggageArea_2_Booked() && !carSeat->isLuggageArea_3_Booked()) {
                    std::cout << "turn on luggage area 3" << std::endl;
                    carSeat->bookLuggageArea_3(object, vecObj);

                }
                else if (carSeat->isLuggageArea_3_Booked() && !carSeat->isLuggageArea_4_Booked()) {
                    std::cout << "turn on luggage area 4" << std::endl;
                    carSeat->bookLuggageArea_4(object, vecObj);
                }
                else {
                 
                }
            }
            else 
                std::cout << "getting in (thing ) " << std::endl;

            break;
        }

                   //                if (!vecObj->hasSeat) {
                   //                    std::cout << "turn on luggage area" << std::endl;
                   //                    carSeat->bookLuggageArea_1(object, vecObj);
                   //                }

        case GET_OUT: {

            if (vecObj->hasSeat) {
                if (carSeat->isLuggageArea_1_Booked() && vecObj->seat_num == LUGGAGE_AREA_1) {
                    std::cout << "******************************************luggage area 1 is  turrned off " << std::endl;
                    carSeat->freeLuggageArea_1(object, vecObj);
                }
                else if (carSeat->isLuggageArea_2_Booked() && vecObj->seat_num == LUGGAGE_AREA_2) {
                    std::cout << "******************************************luggage area 2 is  turrned off " << std::endl;
                    carSeat->freeLuggageArea_2(object, vecObj);
                }
                else if (carSeat->isLuggageArea_3_Booked() && vecObj->seat_num == LUGGAGE_AREA_3) {
                    std::cout << "****************************luggage area 3 is  turrned off " << std::endl;
                    carSeat->freeLuggageArea_3(object, vecObj);
                }
                else if (carSeat->isLuggageArea_4_Booked() && vecObj->seat_num == LUGGAGE_AREA_4) {
                    std::cout << "****************************luggage area 4 is  turrned off " << std::endl;
                    carSeat->freeLuggageArea_4(object, vecObj);
                }
                else if (carSeat->isFrontLeftBooked() && vecObj->seat_num == FRONT_LEFT) {

                    std::cout << "******************************************turn off front left (thing) " << std::endl;
                    carSeat->freeFrontLeft(object, vecObj);
                }
                else if (carSeat->isBackRightBooked() && vecObj->seat_num == BACK_RIGHT) {
                    std::cout << "******************************************turn off back right (thing)" << std::endl;
                    carSeat->freeBackRight(object, vecObj);
                }
                else if (carSeat->isBackLeftBooked() && vecObj->seat_num == BACK_LEFT) {
                    std::cout << "****************************turn off back left (thing)" << std::endl;
                    carSeat->freeBackLeft(object, vecObj);
                }
                else if (carSeat->isBackMiddleBooked() && vecObj->seat_num == BACK_MIDDLE) {
                    std::cout << "****************************turn off back middle (thing)" << std::endl;
                    carSeat->freeBackMiddle(object, vecObj);
                }
                else {

                }
            }




            break;
        }

        case SEATED: {

            if (vecObj->hasSeat) {
                if (vecObj->seat_num != objectPos)
                reassign_seat(object, objectPos, &(*vecObj), carSeat);
                std::cout << vecObj->seat_num << std::endl;
                if (carSeat->isLuggageArea_1_Booked() && vecObj->seat_num == LUGGAGE_AREA_1) {

                    std::cout << "****************************Luggage area 1 is seated " << std::endl;
                    //                    carSeat->freeFrontLeft(object, vecObj);


                }
                else if (carSeat->isLuggageArea_2_Booked() && vecObj->seat_num == LUGGAGE_AREA_2) {
                    std::cout << "****************************Luggage area 2 is seated " << std::endl;
                    //                  carSeat->freeBackRight(object, vecObj);


                }
                else if (carSeat->isLuggageArea_3_Booked() && vecObj->seat_num == LUGGAGE_AREA_3) {
                    std::cout << "****************************Luggage area 3 is seated " << std::endl;
                    //                carSeat->freeBackLeft(object, vecObj);

                }
                else if (carSeat->isLuggageArea_4_Booked() && vecObj->seat_num == LUGGAGE_AREA_4) {
                    std::cout << "****************************Luggage area 4 is seated " << std::endl;
                    //              carSeat->freeBackMiddle(object, vecObj);

                }
                else {

                }
            }
            //std::cout << "thing is seated" << std::endl;
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
            break;
        }
        }

    }
