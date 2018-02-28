#ifndef Region_H
#define Region_H

#include <string>
#include "Oficina.h"

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
};

#endif
