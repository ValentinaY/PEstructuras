#ifndef PRINCIPAL_H
#define PRINCIPAL_H
 
#include "Office.h"
#include "Person.h"
#include "Tree/Tree.h"

//Clase principal, equivalente a Empresa.
class Principal{
protected:
	list<Person> persons;
	Tree offices;
	Node raiz;
public:
	Principal(){
		persons.clear();

		Office of;
		of.setCode("Principal");
		raiz.setData(of);
		offices.setRoot(&raiz);
	};

	void loadPersons(char* file);
	void loadPackages(char* file);
	void loadOffices(char* file);
	void loadRegions(char* file);
	void regPersons();
	void regPackages();
	void regOffices();
	void regRegions();
 	void countPackages(); //-> fix void countpackages(<Office> oficinas);
	void sendPackages(char* codeOf);
	void showPersons();
	void showPackages(char* codeOf); //TODO
	void showOffices();
	void showRegions();
	void addRegion(Region r, string office);

	float toFloat(string a);

	list<Person> getpersons(){
		return persons;
	}
	Tree getoffices(){
		return offices;
	}
};

#endif
