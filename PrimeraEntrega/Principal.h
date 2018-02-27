#ifndef PRINCIPAL_H
#define PRINCIPAL_H
 
#include "Oficina.h"
#include "Persona.h"

//Clase principal, equivalente a Empresa.
class Principal{
protected:
	list<Oficina> oficinas;
	list<Persona> personas;
public:
	void loadPersons(char* archivo, list<Persona> personas);
	void loadPackages();
	void regPersons(list<Persona> personas);
	void regPackages();
	void countPackages();
	
	list<Persona> getPersonas(){
		return personas;
	}
	list<Oficina> getOficinas(){
		return oficinas;
	}
};

//#include "Principal.hxx"

#endif
