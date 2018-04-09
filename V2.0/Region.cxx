#include "Region.h"
void Region::setName(string nname){
	Region::name=nname;
}
void Region::setCode(string ncode){
	Region::code=ncode;
}
void Region::setPackages(list <Package> pac){
	Region::packages = pac;
}
void Region::addPackages(list <Package> pack){
	for(list<Package>::iterator it=pack.begin(); it != pack.end() ;it++){
		Region::packages.push_back((*it));
	}
}

