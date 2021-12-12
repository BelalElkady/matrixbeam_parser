#ifndef OBJECT_H_
#define OBJECT_H_
#include <vector>
#include <string>

using namespace std;

class ObjectCapture
{

	private:

	int id;
	int set; 
	signed int position[3];
	float motion;
	string category;
	string subcategroy;
	string name;
	string place;


	//ObjectCapture();

	/*setters*/
public:
	void setId(int id );
	void setSet(int set);
	void setMotion(float motion);
	void setCategory(string categroy);
	void setSubcategory(string subcategroy);
	void setName(string name);
	void setPlace(string place);
	void updatePosition(int* position);


	/*getters*/

	int getId(void);
	int getSet(void);
	float getMotion(void);
	string getCategory(void);
	string getPlace(void);
	int* getPosition(void);
	




};

#endif