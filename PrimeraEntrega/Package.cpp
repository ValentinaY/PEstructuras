#include <string>
#include "Package.h"
void Package::setSender(long nsender){
	sender=nsender;
}
void Package::setRecipient(long nrecipient){
	recipient=nrecipient;
}
void Package::setWeight(float nweight){
	weight=nweight;
}
void Package::setType(string ntype){
	type=ntype;
}
void Package::setTrackingNumber(string ntranum){
	trackingNumber=ntranum;
}