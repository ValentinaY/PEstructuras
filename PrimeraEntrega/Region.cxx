#include "Region.h"
using namespace std;
void Region::setNombre(string nnombre){
	nombre=nnombre;
}
void Region::setCodigo(string ncodigo){
	codigo=ncodigo;
}
void Region::setOficina(Oficina* ofic){
	oficina = ofic;
}
void Region::setPaquetes(list <Paquete> paq){
	paquetes = paq;
}
void Region::addPaquetes(list <Paquete> paq){
	for(list<Paquete>::iterator it=paq.begin(); it != paq.end() ;it++){
		paquetes.push_back((*it));
	}
}

