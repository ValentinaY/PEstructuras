#include "Office.h"

Office::Office(){
	this->regions.clear();
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
void Office::setRegions(list <Region> reg){
	this->regions = reg;
}	

void Office::addRegions(list <Region> reg){
	for(list<Region>::iterator it=reg.begin(); it != reg.end() ;it++){
		this->regions.push_back((*it));
	}
}

void Office::addRegion(Region reg){
	this->regions.push_back(reg);
}

void Office::setPackages(list <Package> paq){
	this->packages = paq;
}

void Office::addPackage(Package paq){
	this->packages.push_back(paq);
}

void Office::addPackages(list <Package> paq){
	for(list<Package>::iterator it=paq.begin(); it != paq.end() ;it++){
		this->packages.push_back((*it));
	}
}

	
