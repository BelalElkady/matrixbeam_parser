
#ifndef _CAR_SEAT_H_
#define _CAR_SEAT_H_
#include "ObjectCapture.h"

#define NUMBER_OF_SEATS 5

class CarSeats
{
private:

	bool CarSeatStatus[NUMBER_OF_SEATS] = { false/*frontLeft*/ , false /*backRight*/, false/*backMiddle*/,
						false /*backLeft*/, false/*luggArea*/};


public:
	CarSeats();
	void bookFrontLeft(ObjectCapture * , ObjectsData*);
	void bookBackLeft(ObjectCapture *, ObjectsData*);
	void bookBackMiddle(ObjectCapture*, ObjectsData*);
	void bookBackRight(ObjectCapture* , ObjectsData*);
	void bookLuggageArea(ObjectCapture*);

	void freeFrontLeft(ObjectCapture*, ObjectsData* );
	void freeBackLeft(ObjectCapture*, ObjectsData* );
	void freeBackMiddle(ObjectCapture*, ObjectsData* );
	void freeBackRight(ObjectCapture*, ObjectsData* );
	void freeLuggageArea(ObjectCapture* );

	bool isFrontLeftBooked(void);
	bool isBackLeftBooked(void);
	bool isBackMiddleBooked(void);
	bool isBackRightBooked(void);
	bool isLuggageAreaBooked(void);

	bool isCarEmpty(void);

	bool isCarFull(void);

};
#endif