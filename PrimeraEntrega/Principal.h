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
};

#include "Principal.hxx"

#endif
