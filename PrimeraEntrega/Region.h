#ifndef Region_H
#define Region_H

#include <string>
#include "Oficina.h"
#include <iostream>

using namespace std;
class Region{
private:
	string nombre;
	long codigo;
	list<Oficina> oficinas;

public:
	string getNombre(){
		return nombre;
	}
	void setNombre(string nname);
	
	long getCodigo(){
		return codigo;
	}
	void setCodigo(long ncodigo);

	list<Oficina> getOficinas(){
		return oficinas;
	}
	void mostrarDatos(){
		cout<<"Nombre: "<<nombre<<endl;
		cout<<"Código: "<<codigo<<endl;
	}
};

#endif
