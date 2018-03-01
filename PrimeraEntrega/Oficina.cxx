#include "Oficina.h"

using namespace std;
void Oficina::setCode(string ncode){
	codeID=ncode;
}
void Oficina::setNombre(string nnombre){
	nombre=nnombre;
}
void Oficina::setDireccion(string ddireccion){
	direccion=ddireccion;
}
void Oficina::setCiudad(string cciudad){
	ciudad=cciudad;
}
void Oficina::setRegiones(list <Region> reg){
	regiones = reg;
}	

void Oficina::addRegiones(list <Region> reg){
	for(list<Region>::iterator it=reg.begin(); it != reg.end() ;it++){
		regiones.push_back((*it));
	}
}
	
