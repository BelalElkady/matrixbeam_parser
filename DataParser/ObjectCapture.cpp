#include "ObjectCapture.h"

#include <iostream>

ObjectCapture::ObjectCapture() {

}
ObjectCapture::ObjectCapture(const ObjectCapture& obj) {
	this->id = obj.id;
	this->set = obj.set;
	this-> position = obj.position;
	this->motion = obj.motion;
	this->category = obj.category;
	this->subcategroy = obj.subcategroy;
	this->name = obj.name;
	this->place = obj.place;
	this->objDir = obj.objDir;
	
	
	

}
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
	void ObjectCapture::setCategory(string category) {
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
	void ObjectCapture::setDirection(DIRECTION dir) {
		this->objDir = dir;
	}
	/*void ObjectCapture::setSeatNum(Position seat) {
		this->seat_num = seat;
	}*/
	/*void ObjectCapture::setHasSeat(bool has_seat) {
		this->hasSeat = has_seat;
	}*/


	void ObjectCapture::updatePosition(signed int* position) {
		for (int i = 0; i < 3; i++) this->position.pos[i] = position[i];
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
	Pos_class ObjectCapture::getPosition(void) {

		return this->position;
	}
	DIRECTION ObjectCapture::getDirection(void) {
		return this->objDir;
	}

	/*Position ObjectCapture::getSeatNum(void) {
		return this->seat_num;
	}*/
	
	/*bool ObjectCapture::getHasSeat(void) {
		return this->hasSeat ;
	}*/



