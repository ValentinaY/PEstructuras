#ifndef Region_H
#define Region_H

#include <string>
#include <list>
#include "Oficina.h"
#include "Paquete.h"
#include <iostream>

using namespace std;

class Oficina;
class Paquete;

class Region{
private:
	string nombre;
	string codigo;
	Oficina* oficina;
	list<Paquete> paquetes;

public:
	string getNombre(){
		return nombre;
	}
	void setNombre(string nname);
	
	string getCodigo(){
		return codigo;
	}
	void setCodigo(string ncodigo);

	Oficina* getOficina(){
		return oficina;
	}

	void setOficina(Oficina* ofic);

	list<Paquete> getPaquetes(){
		return paquetes;
	}

	void setPaquetes(list <Paquete> paq);

	void addPaquetes(list <Paquete> paq);	

	void mostrarDatos(){
		cout<<"Nombre: "<<nombre<<endl;
		cout<<"Código: "<<codigo<<endl;
	}
};

#endif
