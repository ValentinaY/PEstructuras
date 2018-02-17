#ifndef PRINCIPAL_H
#define PRINCIPAL_H
 
#include "Office.h"
#include "Person.h"

//Clase principal, equivalente a Empresa.
class Principal{
protected:
	list<Office> offices;
	list<Person> persons;
public:
	void loadPersons();
	void loadPackages();
	void regPersons();
	void regPackages();
	void countPackages();
};
#endif