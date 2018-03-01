#ifndef PRINCIPAL_H
#define PRINCIPAL_H
 
#include "Oficina.h"
#include "Persona.h"

//Clase principal, equivalente a Empresa.
class Principal{
protected:
	list<Persona> personas;
	list<Oficina> oficinas;
public:
	list<Persona> loadPersons(char* archivo, list<Persona> personas);
	list<Oficina> loadPackages(char* archivo, list<Oficina> oficinas, list<Persona> personas);
	list<Persona> regPersons(list<Persona> personas);
	list<Oficina> regPackages(list<Oficina> oficinas, list<Persona> personas);
	void countPackages(list<Oficina> oficinas);
	
	list<Persona> getPersonas(){
		return personas;
	}
	list<Oficina> getOficinas(){
		return oficinas;
	}
	void setPersonas(list<Persona> x);
	void setOficinas(list<Oficina> x);
};

//#include "Principal.hxx"

#endif
