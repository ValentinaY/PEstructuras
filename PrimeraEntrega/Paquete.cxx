#include <string>
#include "Paquete.h"
using namespace std;

void Paquete::setRemitente(Persona nremitente){
	remitente=nremitente;
}
void Paquete::setDestinatario(Persona ndest){
	destinatario=ndest;
}
void Paquete::setPeso(float npeso){
	peso=npeso;
}
void Paquete::setTipo(string ntipo){
	tipo=ntipo;
}
void Paquete::setNumGuia(string nguia){
	numGuia=nguia;
}
void Paquete::setRegion(Region* reg){
	region = reg;
}

