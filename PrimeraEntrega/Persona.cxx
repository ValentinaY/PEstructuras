#include "Persona.h"

void Persona::setNombre(string nname){
	nombre=nname;
}
void Persona::setApellido(string nname){
	apellido=nname;
}
void Persona::setId(string nidnum){
	id=nidnum;
}
void Persona::setDireccion(string naddress){
	direccion=naddress;
}
void Persona::setCiudad(string ncity){
	ciudad=ncity;
}
void Persona::setTelefono(string nphone){
	telefono=nphone;
}

string mostrarDatos(){
	cout<<"Nombre: "<<nombre<<endl
	<<"Apellido: "<<apellido<<endl
	<<"Identificación: "<<id<<endl
	<<"Ciudad: "<<direccion<<endl
	<<"Teléfono: "<<telefono<<endl;
}
