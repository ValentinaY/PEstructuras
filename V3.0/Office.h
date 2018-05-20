#ifndef Office_H
#define Office_H

#include "Region.h"
#include "Package.h"
#include <vector>
#include <iostream>

using namespace std;

class Office{
protected:
	string codeID;
	string name;
	string address;
	string city;
	vector<Region> regions;
	vector<Package> packages;

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

	vector<Region> getRegions(){
		return regions;
	}

	void addRegions(vector <Region> reg);
	void addRegion(Region nregion);
	void setRegions(vector <Region> reg);

	vector<Package> getPackages(){
		return packages;
	}

	void setPackages(vector <Package> paq);
	void addPackage(Package paq);
	void addPackages(vector <Package> paq);

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
			for(int i=0;i<(int)regions.size();i++){
				cout<<"\t Código: "<<regions[i].getName()<<endl;
			}
		cout<<endl;
	}

	void showRegions(){
		for(int i = 0;i<(int)regions.size();i++){
			regions[i].showData();
		}
	}

	void showPackages(){
		for(int i = 0; i<(int)packages.size();i++){
			packages[i].showData();
		}
	}


	bool operator == (Office o){
		return codeID == o.getCode();
	}
};

#endif
