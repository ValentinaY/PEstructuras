#ifndef Oficina_H
#define Oficina_H

#include "Paquete.h"
#include <list>
#include <iostream>

using namespace std;

class Oficina{
protected:
	string codeID;
	string nombre;
	string direccion;
	string ciudad;
	list<Paquete> paquetes;
public:
	string getCode(){
		return codeID;
	}
	void setCode(string ncode);

	string getNombre(){
		return nombre;
	}
	void setNombre(string nnombre);

	string getDireccion(){
		return direccion;
	}
	void setDireccion(string ddireccion);

	string getCiudad(){
		return ciudad;
	}
	void setCiudad(string cciudad);

	list<Paquete> getPaquetes(){
		return paquetes;
	}
	
	void mostrarDatos(){
		cout<<"Código: "<<codeID<<endl;
		cout<<"Nombre: "<<nombre<<endl;
		cout<<"Dirección: "<<direccion<<endl;
		cout<<"Ciudad: "<<ciudad<<endl;
	}
};

#endif
