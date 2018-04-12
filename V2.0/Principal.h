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
//TODO fix	void loadPackages(char* file); //-> list<Office> loadpackages(char* file, list<Office> oficinas, list<Person> persons);
//TODO rev	void loadOffices(char* file);
//TODO rev	void loadRegions(char* file);
	void regPersons(); //-> fix	list<Person> regpersons(list<Person> personas);
//TODO fix	void regPackages(); //-> fix	list<Office> regpackages(list<Office> oficinas, list<Person> personas);
	void regOffices();
	void regRegions();
//TODO fix 	void countPackages(); //-> fix void countpackages(<Office> oficinas);
//TODO 	|	void sendPackages(char* codeOf);
	void showPersons();
	void showPackages(char* codeOf); //TODO
	void showOffices();
	void showRegions();

	float toFloat(string a);

	list<Person> getpersons(){
		return persons;
	}
	Tree getoffices(){
		return offices;
	}
};

#endif
