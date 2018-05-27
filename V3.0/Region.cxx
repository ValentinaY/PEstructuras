#include "Region.h"
Region::Region(){} // @suppress("Class members should be properly initialized")

void Region::setName(string nname){
	this->name=nname;
}
void Region::setCode(string ncode){
	this->code=ncode;
}
void Region::setDistanceUp(int dist){
	this->distanceUp = dist;
}
