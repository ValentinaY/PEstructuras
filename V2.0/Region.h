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
	string getName(){
		return name;
	}
	void setName(string nname);
	
	string getCode(){
		return code;
	}
	void setCode(string ncode);

	list<Package> getPackages(){
		return packages;
	}

	void setPackages(list <Package> paq);

	void addPackages(list <Package> paq);

	void mostrarDatos(){
		cout<<"Nombre: "<<name<<endl;
		cout<<"Código: "<<code<<endl;
	}
};

#endif
