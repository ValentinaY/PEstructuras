#include <string>
#include "Package.h"

void Package::setsender(Person nsender){
	Package::sender=nsender;
}
void Package::setreceiver(Person nreceiver){
	Package::receiver=nreceiver;
}
void Package::setweight(float nweight){
	Package::weight=nweight;
}
void Package::settype(string ntype){
	Package::type=ntype;
}
void Package::setguiden(string nguiden){
	Package::guiden=nguiden;
}

