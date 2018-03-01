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

