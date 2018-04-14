#include <string>
#include "Package.h"

void Package::setSender(Person* nsender){
	this->sender=nsender;
}
void Package::setReceiver(Person* nreceiver){
	this->receiver=nreceiver;
}
void Package::setWeight(float nweight){
	this->weight=nweight;
}
void Package::setType(string ntype){
	this->type=ntype;
}
void Package::setGuiden(string nguiden){
	this->guideN=nguiden;
}

