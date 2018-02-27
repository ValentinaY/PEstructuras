#ifndef Region_H
#define Region_H

#include <string>

using namespace std;
class Region{
private:
	string nombre;
	long codigo;
public:
	string getNombre(){
		return nombre;
	}
	void setNombre(string nname);
	
	long getCodigo(){
		return codigo;
	}
	void setCodigo(long ncodigo);
};

#endif
