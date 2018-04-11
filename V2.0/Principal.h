#ifndef PRINCIPAL_H
#define PRINCIPAL_H
 
#include "Office.h"
#include "Person.h"
#include "Tree/Tree.h"

//Clase principal, equivalente a Empresa.
class Principal{
protected:
	list<Person> persons;
	Tree<Office> offices;
	Node<Office> raiz;
public:
	Principal(){
		persons.clear();

		Office of;
		of.setCode("raiz");
		raiz.setData(of);
		offices.setRoot(&raiz);
	};

	void regOffice();
	void regRegion();
	/*cargar personas
		paquetes
		oficinas
		regiones
	registrar per
		paq
		oficinas
		regiones
	contar paq
	repartir*/

	void showregions();

	void loadpersons(char* file, list<Person> persons);
	void loadregions(char* file);
	list<Person> regpersons(list<Person> personas);
/*	list<Office> loadpackages(char* file, list<Office> oficinas, list<Person> persons);
	list<Office> regpackages(list<Office> oficinas, list<Person> personas);
	void countpackages(list<Office> oficinas);
	void addregion(Region region, string ocode);

*/
	float toFloat(string a);

	list<Person> getpersons(){
		return persons;
	}
	Tree<Office> getoffices(){
		return offices;
	}
	void setpersons(list<Person> x);
	void setoffices(list<Office> x);
};

#endif
