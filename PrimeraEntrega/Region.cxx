#include "Region.h"
void Region::setNombre(string nnombre){
	nombre=nnombre;
}
void Region::setCodigo(long ncodigo){
	codigo=ncodigo;
}

string mostrarDatos(){
	cout<<"Nombre: "<<peso<<endl
	<<"Código: "<<tipo<<endl;
}