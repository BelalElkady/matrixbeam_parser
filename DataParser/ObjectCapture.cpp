#include "ObjectCapture.h"




	/*setters*/

	void ObjectCapture::setId(int id) {
		this->id = id;
	}
	void ObjectCapture::setSet(int set) {
		this->set = set;
	}
	void ObjectCapture::setMotion(float motion){
		this->motion = motion; 
	}
	void ObjectCapture::setCategory(string categroy) {
		this->category = category;

	}
	void ObjectCapture::setSubcategory(string subcategroy) {
		this->subcategroy = subcategroy;
	}
	void ObjectCapture::setName(string name) {
		this->name = name;
	}
	void ObjectCapture::setPlace(string place) {
		this->place = place; 
	}
	void ObjectCapture::updatePosition(int* position) {
		for (int i = 0; i < 3; i++) this->position[i] = position[i];
	}


	/*getters*/

	int ObjectCapture::getId(void) {

		return this->id; 
	}
	int ObjectCapture::getSet(void) {

		return this->set;
	}
	float ObjectCapture::getMotion(void) {
		return this->motion; 
	}
	string ObjectCapture::getCategory(void) {

		return this->category;
	}
	string ObjectCapture::getPlace(void) {

		return this->place;
	}
	int* ObjectCapture::getPosition(void) {

		return this->position;
	}






