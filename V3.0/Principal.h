#ifndef PRINCIPAL_H
#define PRINCIPAL_H
 
#include "Office.h"
#include "Person.h"
#include "Tree/Tree.h"

//Clase principal, equivalente a Empresa.
class Principal{
protected:
	vector<Person> persons;
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

	void loadOffices(char* file);
	void loadPackages(char* file);
	void loadPersons(char* file);
	void loadRegions(char* file);
	void regOffices();
	void regPackages();
	void regPersons();
	void regRegions();
	void showOffices();
	void showPackages(char* codeOf);
	void showPersons();
	void showRegions();
 	void countPackages();
	void sendPackages(char* codeOf);
	void addRegion(Region r, string office);

	float toFloat(string a);

	vector<Person> getpersons(){
		return persons;
	}
	Tree getoffices(){
		return offices;
	}
};

#endif
