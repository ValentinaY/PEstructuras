#include "Office.h"
Office::Office(){
	Office::codeID="";
	Office::name="";
	Office::address="";
	Office::city="";
	Office::regions.clear();
}

Office::~Office(){
}

void Office::setcode(string ncode){
	Office::codeID=ncode;
}
void Office::setname(string nname){
	Office::name=nname;
}
void Office::setaddress(string naddress){
	Office::address=naddress;
}
void Office::setcity(string ncity){
	Office::city=ncity;
}
void Office::setregions(list <Region> reg){
	Office::regions = reg;
}	

void Office::addregions(list <Region> reg){
	for(list<Region>::iterator it=reg.begin(); it != reg.end() ;it++){
		Office::regions.push_back((*it));
	}
}

void Office::addregion(Region reg){
	Office::regions.push_back(reg);
}
	
