#ifndef PRINCIPAL_H
#define PRINCIPAL_H
 
#include "Office.h"
#include "Person.h"

//Clase principal, equivalente a Empresa.
class Principal{
protected:
	list<Person> persons;
	list<Office> offices;
public:
	void showregions();
	list<Person> loadpersons(char* file, list<Person> persons);
	list<Region> loadregions(char* file);
	list<Office> loadpackages(char* file, list<Office> oficinas, list<Person> persons);
	list<Person> regpersons(list<Person> personas);
	list<Office> regpackages(list<Office> oficinas, list<Person> personas);
	void countpackages(list<Office> oficinas);
	void addregion(Region region, string ocode);
	float toFloat(string a);

	list<Person> getpersons(){
		return persons;
	}
	list<Office> getoffices(){
		return offices;
	}
	void setpersons(list<Person> x);
	void setoffices(list<Office> x);
};

#endif