#include "Oficina.h"
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

string mostrarDatos(){
	cout<<"Código: "<<codeID<<endl
	<<"Nombre: "<<nombre<<endl
	<<"Dirección: "<<direccion<<endl
	<<"Ciudad: "<<ciudad<<endl;
}
