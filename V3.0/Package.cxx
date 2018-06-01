#include <string>
#include "Package.h"


Package::Package(){
	weight = -1;
	active = false;
}

void Package::setSender(Person &nsender){
	this->sender=nsender;
}
void Package::setReceiver(Person &nreceiver){
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
void Package::send(){
	active = true;
}

