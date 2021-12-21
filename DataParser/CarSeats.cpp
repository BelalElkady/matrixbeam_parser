#include "CarSeats.h"


CarSeats::CarSeats() {

}

void CarSeats::bookFrontLeft(ObjectCapture* obj , ObjectsData* allObjDB) {
	
	if(obj->getId()==allObjDB->id){
		allObjDB->hasSeat  =true;
		allObjDB->seat_num =FRONT_LEFT;
		this->CarSeatStatus[0] = true;
	}
}
void CarSeats::bookBackLeft(ObjectCapture* obj, ObjectsData* allObjDB) {
	
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = true;
		allObjDB->seat_num = BACK_LEFT;
		this->CarSeatStatus[3] = true;
	}

}
void CarSeats::bookBackMiddle(ObjectCapture* obj, ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = true;
		allObjDB->seat_num = BACK_MIDDLE;
		this->CarSeatStatus[2] = true;
	}

}
void CarSeats::bookBackRight(ObjectCapture* obj, ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = true;
		allObjDB->seat_num = BACK_RIGHT;
		this->CarSeatStatus[1] = true;
	}

}
void CarSeats::bookLuggageArea(ObjectCapture* obj  , ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = true;
		allObjDB->seat_num = LUGGAGE_AREA;
		this->CarSeatStatus[4] = true;
	}
	
}

void CarSeats::freeFrontLeft(ObjectCapture* obj, ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = false;
		allObjDB->seat_num = OUT;
		this->CarSeatStatus[0] = false;
	}
	
}
void CarSeats::freeBackLeft(ObjectCapture* obj, ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = false;
		allObjDB->seat_num = OUT;
		this->CarSeatStatus[3] = false;
	}
	
}
void CarSeats::freeBackMiddle(ObjectCapture* obj, ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = false;
		allObjDB->seat_num = OUT;
		this->CarSeatStatus[2] = false;
	}

}
void CarSeats::freeBackRight(ObjectCapture* obj, ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = false;
		allObjDB->seat_num = OUT;
		this->CarSeatStatus[1] = false;
	}
	
}
void CarSeats::freeLuggageArea(ObjectCapture* obj  , ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = true;
		allObjDB->seat_num = LUGGAGE_AREA;
		this->CarSeatStatus[4] = false;
	}
	
}

bool CarSeats::isFrontLeftBooked(void) {
	return this->CarSeatStatus[0];
}
bool CarSeats::isBackLeftBooked(void) {
	return this->CarSeatStatus[1];
}
bool CarSeats::isBackMiddleBooked(void) {
	return this->CarSeatStatus[2];
}
bool CarSeats::isBackRightBooked(void) {
	return this->CarSeatStatus[3];
}
bool CarSeats::isLuggageAreaBooked(void) {
	return this->CarSeatStatus[4];
}


bool CarSeats::isCarEmpty(void) {
	for (int i = 0; i < NUMBER_OF_SEATS; i++) {
		if (this->CarSeatStatus[i] == true) return false;
	}
	return true;
}

bool CarSeats::isCarFull(void) {
	for (int i = 0; i < NUMBER_OF_SEATS-1; i++) {
		if (this->CarSeatStatus[i] == false) return false;
	}
	return true;
}