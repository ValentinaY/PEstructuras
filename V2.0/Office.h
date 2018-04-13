#ifndef Office_H
#define Office_H

#include "Region.h"
#include <list>
#include <iostream>

using namespace std;

class Region;

class Office{
protected:
	string codeID;
	string name;
	string address;
	string city;
	list<Region> regions;
public:
	Office();
	~Office();
	string getcode(){
		return codeID;
	}
	void setcode(string ncode);

	string getname(){
		return name;
	}
	void setname(string nname);

	string getaddress(){
		return address;
	}
	void setaddress(string naddress);

	string getcity(){
		return city;
	}
	void setcity(string ncity);

	list<Region> getregions(){
		return regions;
	}

	void addregions(list <Region> reg);
	void addregion(Region nregion);
	void setregions(list <Region> reg);
	
	void toString(){
		cout<<"Código: "<<codeID<<endl;
		cout<<"Nombre: "<<name<<endl;
		cout<<"Dirección: "<<address<<endl;
		cout<<"Ciudad: "<<city<<endl;
	}
};

#endif
