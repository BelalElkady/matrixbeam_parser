#include "CarSeats.h"


CarSeats::CarSeats() {

}

void CarSeats::bookSeat(ObjectCapture* obj, ObjectsData* allObjDB) {

	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = true;

		allObjDB->seat_num = FRONT_LEFT;
		this->CarSeatStatus[0] = true;
	}
}
void CarSeats::bookFrontLeft(ObjectCapture* obj , ObjectsData* allObjDB) {
	
	if(obj->getId()==allObjDB->id){
		allObjDB->hasSeat  =true;
		allObjDB->seat_num = FRONT_LEFT;
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
void CarSeats::bookLuggageArea_1(ObjectCapture* obj  , ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = true;
		allObjDB->seat_num = LUGGAGE_AREA_1;
		this->CarSeatStatus[4] = true;
	}
	
}
void CarSeats::bookLuggageArea_2(ObjectCapture* obj, ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = true;
		allObjDB->seat_num = LUGGAGE_AREA_2;
		this->CarSeatStatus[5] = true;
	}

}
void CarSeats::bookLuggageArea_3(ObjectCapture* obj, ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = true;
		allObjDB->seat_num = LUGGAGE_AREA_3;
		this->CarSeatStatus[6] = true;
	}

}
void CarSeats::bookLuggageArea_4(ObjectCapture* obj, ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = true;
		allObjDB->seat_num = LUGGAGE_AREA_4;
		this->CarSeatStatus[7] = true;
	}

}

void CarSeats::freeSeat(ObjectCapture* obj, ObjectsData* allObjDB) {

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
void CarSeats::freeLuggageArea_1(ObjectCapture* obj  , ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = false;
		allObjDB->seat_num = LUGGAGE_AREA_1;
		this->CarSeatStatus[4] = false;
	}
	
}
void CarSeats::freeLuggageArea_2(ObjectCapture* obj, ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = false;
		allObjDB->seat_num = LUGGAGE_AREA_2;
		this->CarSeatStatus[5] = false;
	}

}
void CarSeats::freeLuggageArea_3(ObjectCapture* obj, ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = false;
		allObjDB->seat_num = LUGGAGE_AREA_3;
		this->CarSeatStatus[6] = false;
	}

}
void CarSeats::freeLuggageArea_4(ObjectCapture* obj, ObjectsData* allObjDB) {
	if (obj->getId() == allObjDB->id) {
		allObjDB->hasSeat = false;
		allObjDB->seat_num = LUGGAGE_AREA_4;
		this->CarSeatStatus[7] = false;
	}

}


bool CarSeats::isFrontLeftBooked(void) {
	return this->CarSeatStatus[0];
}
bool CarSeats::isBackRightBooked(void) {
	return this->CarSeatStatus[1];
}
bool CarSeats::isBackMiddleBooked(void) {
	return this->CarSeatStatus[2];
}
bool CarSeats::isBackLeftBooked(void) {
	return this->CarSeatStatus[3];
}
bool CarSeats::isLuggageArea_1_Booked(void) {
	return this->CarSeatStatus[4];
}
bool CarSeats::isLuggageArea_2_Booked(void) {
	return this->CarSeatStatus[5];
}
bool CarSeats::isLuggageArea_3_Booked(void) {
	return this->CarSeatStatus[6];
}
bool CarSeats::isLuggageArea_4_Booked(void) {
	return this->CarSeatStatus[7];
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