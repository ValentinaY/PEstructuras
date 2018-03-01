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
	list<Persona> loadPersons(char* archivo, list<Persona> personas);
	void loadPackages();
	list<Persona> regPersons(list<Persona> personas);
	void regPackages();
	void countPackages();
	
	list<Persona> getPersonas(){
		return personas;
	}
	list<Region> getRegiones(){
		return regiones;
	}
	void setPersonas(list<Persona> x);
	void setRegiones(list<Region> x);
};

//#include "Principal.hxx"

#endif
