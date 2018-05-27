#ifndef Office_H
#define Office_H

#include "Region.h"
#include "Package.h"
#include "Tree/Tree.h"
#include <vector>
#include <iostream>

using namespace std;

class Office{
protected:
	string codeID;
	string name;
	string address;
	string city;
	Tree regions;
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

	Tree getRegions(){
		return regions;
	}

	void addRegion(Region nregion, Region padre);
	void addRegion(Region nregion, bool sig);
	void setRegions(Tree reg);

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
		if(regions.isEmpty())
			cout<<"No tiene regiones asociadas"<<endl;
		else{
			vector<Region> regs = regions.getAllData();
			for(unsigned int i=0;i< regs.size();i++){
				cout<<"\t Código: "<<regs[i].getName()<<endl;
			}
		}

		cout<<endl;
	}

	void showRegions(){
		vector<Region> regs = regions.getAllData();
		for(int i = 0;i<(int)regs.size();i++){
			regs[i].showData();
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
