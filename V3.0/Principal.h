#ifndef PRINCIPAL_H
#define PRINCIPAL_H
 
#include "Office.h"
#include "Person.h"
#include "Graph/Graph.h"

//Clase principal, equivalente a Empresa.
class Principal{
protected:
	vector<Person> persons;
	Graph<Office,int> offices;

public:
	Principal(){
		persons.clear();
	};

	void loadConnections(char* file);
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
	bool comparecodes(const char* g, const char* f);
	void fastboot();

	vector<Person> getpersons(){
		return persons;
	}
	Graph<Office,int> getoffices(){
		return offices;
	}
};

#endif

