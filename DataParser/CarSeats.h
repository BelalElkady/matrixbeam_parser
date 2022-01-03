
#ifndef _CAR_SEAT_H_
#define _CAR_SEAT_H_
#include "ObjectCapture.h"

#define NUMBER_OF_SEATS 8

class CarSeats
{
private:

	bool CarSeatStatus[NUMBER_OF_SEATS] = { false/*frontLeft*/ , false /*backRight*/, false/*backMiddle*/,
						false /*backLeft*/, false/*luggArea1*/,false/*luggArea2*/ ,false/*luggArea3*/ ,false/*luggArea4*/ };


public:
	CarSeats();
	void bookSeat(ObjectCapture*, ObjectsData*);
	void bookFrontLeft(ObjectCapture * , ObjectsData*);
	void bookBackLeft(ObjectCapture *, ObjectsData*);
	void bookBackMiddle(ObjectCapture*, ObjectsData*);
	void bookBackRight(ObjectCapture* , ObjectsData*);
	void bookLuggageArea_1(ObjectCapture*, ObjectsData*);
	void bookLuggageArea_2(ObjectCapture*, ObjectsData*);
	void bookLuggageArea_3(ObjectCapture*, ObjectsData*);
	void bookLuggageArea_4(ObjectCapture*, ObjectsData*);


	void freeSeat(ObjectCapture*, ObjectsData*);
	void freeFrontLeft(ObjectCapture*, ObjectsData* );
	void freeBackLeft(ObjectCapture*, ObjectsData* );
	void freeBackMiddle(ObjectCapture*, ObjectsData* );
	void freeBackRight(ObjectCapture*, ObjectsData* );
	void freeLuggageArea_1(ObjectCapture*, ObjectsData*);
	void freeLuggageArea_2(ObjectCapture*, ObjectsData*);
	void freeLuggageArea_3(ObjectCapture*, ObjectsData*);
	void freeLuggageArea_4(ObjectCapture*, ObjectsData*);


	bool isFrontLeftBooked(void);
	bool isBackLeftBooked(void);
	bool isBackMiddleBooked(void);
	bool isBackRightBooked(void);
	bool isLuggageArea_1_Booked(void);
	bool isLuggageArea_2_Booked(void);
	bool isLuggageArea_3_Booked(void);
	bool isLuggageArea_4_Booked(void);

	bool isCarEmpty(void);

	bool isCarFull(void);

};
#endif