#include "CarSeats.h"


CarSeats::CarSeats() {

}

void CarSeats::bookFrontLeft(void) {
	this->CarSeatStatus[0] = true;
}
void CarSeats::bookBackLeft(void) {
	this->CarSeatStatus[1] = true;
}
void CarSeats::bookBackMiddle(void) {
	this->CarSeatStatus[2] = true;
}
void CarSeats::bookBackRight(void) {
	this->CarSeatStatus[3] = true;
}
void CarSeats::bookLuggageArea(void) {
	this->CarSeatStatus[4] = true;
}

bool CarSeats::IsFrontLeftBooked(void) {
	return this->CarSeatStatus[0];
}
bool CarSeats::IsBackLeftBooked(void) {
	return this->CarSeatStatus[1];
}
bool CarSeats::IsBackMiddleBooked(void) {
	return this->CarSeatStatus[2];
}
bool CarSeats::IsBackRightBooked(void) {
	return this->CarSeatStatus[3];
}
bool CarSeats::IsLuggageAreaBooked(void) {
	return this->CarSeatStatus[4];
}


bool CarSeats::IsCarEmpty(void) {
	for (int i = 0; i < NUMBER_OF_SEATS; i++) {
		if (this->CarSeatStatus[i] == true) return false;
	}
	return true;
}