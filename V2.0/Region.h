#ifndef Region_H
#define Region_H

#include "Package.h"

#include <string>
#include <list>
#include <iostream>

using namespace std;

class Region{
private:
	string name;
	string code;
	list<Package> packages;

public:
	string getname(){
		return name;
	}
	void setname(string nname);
	
	string getcode(){
		return code;
	}
	void setcode(string ncode);

	list<Package> getpackages(){
		return packages;
	}

	void setpackages(list <Package> paq);

	void addpackages(list <Package> paq);	

	void mostrarDatos(){
		cout<<"Nombre: "<<name<<endl;
		cout<<"Código: "<<code<<endl;
	}
};

#endif
