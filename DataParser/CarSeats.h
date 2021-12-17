#pragma once
#ifndef _CAR_SEAT_H_
#define _CAR_SEAT_H_

#define NUMBER_OF_SEATS 5

class CarSeats
{
private:

	bool CarSeatStatus[NUMBER_OF_SEATS] = { false/*frontLeft*/ , false /*backLeft*/, false/*backMiddle*/,
						false /*backRight*/, false/*luggArea*/};


public:
	CarSeats();
	void bookFrontLeft(void);
	void bookBackLeft(void);
	void bookBackMiddle(void);
	void bookBackRight(void);
	void bookLuggageArea(void);

	bool IsFrontLeftBooked(void);
	bool IsBackLeftBooked(void);
	bool IsBackMiddleBooked(void);
	bool IsBackRightBooked(void);
	bool IsLuggageAreaBooked(void);

	bool IsCarEmpty(void);

};
#endif