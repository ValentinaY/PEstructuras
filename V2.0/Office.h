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
	string getCode(){
		return codeID;
	}
	void setCode(string ncode);

	string getName(){
		return name;
	}
	void setName(string nname);

	string getAddress(){
		return address;
	}
	void setAddress(string naddress);

	string getCity(){
		return city;
	}
	void setCity(string ncity);

	list<Region> getRegions(){
		return regions;
	}

	void addRegions(list <Region> reg);
	void addRegion(Region nregion);
	void setRegions(list <Region> reg);
	
	void toString(){
		cout<<"Código: "<<codeID<<endl;
		cout<<"Nombre: "<<name<<endl;
		cout<<"Dirección: "<<address<<endl;
		cout<<"Ciudad: "<<city<<endl;
		cout<<"Regiones :"<<endl;
		for(list<Region>::iterator it=regions.begin(); it != regions.end() ;it++){
			cout<<"\t"<<it->getName();
		}
	}
};

#endif
