#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>
#include <vector>
using namespace std;

typedef enum dir { GET_IN, GET_OUT, SEATED } DIRECTION;
typedef enum positions { FRONT_LEFT, BACK_RIGHT, BACK_MIDDLE, BACK_LEFT, LUGGAGE_AREA, ENTRANCE, OUT } Position;
typedef struct pos {
	signed int pos[3];
}Pos_class;

class ObjectCapture
{

	private:

	int id;
	int set; 
	Pos_class position;
	float motion;
	string category;
	string subcategroy;
	string name;
	string place;
	DIRECTION objDir; 
	

	


	/*setters*/
public:
	ObjectCapture();
	ObjectCapture(const ObjectCapture&);

	
	void setId(int id );
	void setSet(int set);
	void setMotion(float motion);
	void setCategory(string category);
	void setSubcategory(string subcategroy);
	void setName(string name);
	void setPlace(string place);
	void updatePosition(signed int * position);
	void setDirection(DIRECTION);
	


	/*getters*/
	
	int getId(void);
	int getSet(void);
	float getMotion(void);
	string getCategory(void);
	string getPlace(void);
	Pos_class getPosition(void);
	DIRECTION getDirection(void);

	




};
typedef struct vectorobj {
	int id;
	bool hasSeat;
	ObjectCapture ObjCapture_ID;
	vector<Pos_class> ObjCapture_ID_Pos;
	Position seat_num;
	signed int x;
}ObjectsData;


#endif