#ifndef Office_H
#define Office_H

#include "Region.h"
#include "Package.h"
#include <list>
#include <queue>
#include <iostream>

using namespace std;

class Office{
protected:
	string codeID;
	string name;
	string address;
	string city;
	list<Region> regions;
	queue<Package> packages;

public:

	Office();

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

	queue<Package> getPackages(){
		return packages;
	}

	void setPackages(queue <Package> paq);
	void addPackage(Package paq);
	void addPackages(queue <Package> paq);

	void showData(){
		cout<<"Código: "<<codeID<<endl;
		cout<<"Nombre: "<<name<<endl;
		cout<<"Dirección: "<<address<<endl;
		cout<<"Ciudad: "<<city<<endl;
		cout<<endl;
	}

	void showDataR(){
		cout<<"Código: "<<codeID<<endl;
		cout<<"Nombre: "<<name<<endl;
		cout<<"Dirección: "<<address<<endl;
		cout<<"Ciudad: "<<city<<endl;
		cout<<"Regiones :"<<endl;
		if(regions.empty())
			cout<<"No tiene regiones asociadas"<<endl;
		else
			for(list<Region>::iterator it=regions.begin(); it != regions.end() ;it++){
				cout<<"\t Código: "<<it->getName()<<endl;
			}
		cout<<endl;
	}

	void showRegions(){
		for(list<Region>::iterator it=regions.begin(); it != regions.end() ;it++){
			it->showData();
		}
	}

	void showPackages(){
		for(int i = 0; i< packages.size();i++){
			Package aux = packages.front();
			aux.showData();
			packages.pop();
			packages.push(aux);
		}
	}


	bool operator == (Office o){
		return codeID == o.getCode();
	}
};

#endif
