#include <string>
#include "Package.h"

void Package::setSender(Person* nsender){
	Package::sender=nsender;
}
void Package::setReceiver(Person* nreceiver){
	Package::receiver=nreceiver;
}
void Package::setWeight(float nweight){
	Package::weight=nweight;
}
void Package::setType(string ntype){
	Package::type=ntype;
}
void Package::setGuiden(string nguiden){
	Package::guiden=nguiden;
}

