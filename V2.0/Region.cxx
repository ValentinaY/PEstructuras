#include "Region.h"
void Region::setname(string nname){
	Region::name=nname;
}
void Region::setcode(string ncode){
	Region::code=ncode;
}
void Region::setpackages(list <Package> pac){
	Region::packages = pac;
}
void Region::addpackages(list <Package> pack){
	for(list<Package>::iterator it=pack.begin(); it != pack.end() ;it++){
		Region::packages.push_back((*it));
	}
}

