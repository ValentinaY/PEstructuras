#include "Office.h"

Office::Office(){
	this->packages.clear();
}

void Office::setCode(string ncode){
	this->codeID=ncode;
}
void Office::setName(string nname){
	this->name=nname;
}
void Office::setAddress(string naddress){
	this->address=naddress;
}
void Office::setCity(string ncity){
	this->city=ncity;
}
void Office::setRegions(Tree reg){
	this->regions = reg;
}	


void Office::addRegion(Region reg, Region padre){
	this->regions.insert(padre,reg);
}

void Office::addRegion(Region reg, bool sig){
	this->regions.insert(reg);
}


void Office::setPackages(vector <Package> paq){
	this->packages = paq;
}

void Office::addPackage(Package paq){
	this->packages.push_back(paq);
}

void Office::addPackages(vector <Package> paq){
	for(int i=0;i<paq.size();i++){
		this->packages.push_back(paq[i]);
	}
}

	
