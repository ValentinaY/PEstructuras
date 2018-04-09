#include "Office.h"

void Office::setCode(string ncode){
	Office::codeID=ncode;
}
void Office::setName(string nname){
	Office::name=nname;
}
void Office::setAddress(string naddress){
	Office::address=naddress;
}
void Office::setCity(string ncity){
	Office::city=ncity;
}
void Office::setRegions(list <Region> reg){
	Office::regions = reg;
}	

void Office::addRegions(list <Region> reg){
	for(list<Region>::iterator it=reg.begin(); it != reg.end() ;it++){
		Office::regions.push_back((*it));
	}
}

void Office::addRegion(Region reg){
	Office::regions.push_back(reg);
}
	
