#ifndef PRINCIPAL_H
#define PRINCIPAL_H
 
#include "Oficina.h"
#include "Persona.h"
#include "Region.h"

//Clase principal, equivalente a Empresa.
class Principal{
protected:
	list<Region> regiones;
	list<Persona> personas;
public:
	void loadRegions();
	void loadPersons(char* archivo, list<Persona> personas);
	void loadPackages();
	void regPersons(list<Persona> personas);
	void regPackages();
	void countPackages();
	
	list<Persona> getPersonas(){
		return personas;
	}
	list<Region> getRegiones(){
		return regiones;
	}
};

//#include "Principal.hxx"

#endif
