#ifndef Office_H
#define Office_H

#include "Region.h"
#include "Package.h"
#include <map>
#include <iterator>
#include <vector>
#include <iostream>

using namespace std;

class Office{
protected:
	string codeID;
	string name;
	string address;
	string city;
	map<string, Region> regions;
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

	map<string, Region> getRegions(){
		return regions;
	}

	void addRegion(Region nregion);

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
		else{
			map<string, Region>::iterator it;
			for(it=regions.begin(); it!= regions.end(); it++){
				cout<<"\t Código: "<<it->second.getName()<<endl;
			}
		}

		cout<<endl;
	}

	void showRegions(){
		map<string, Region>::iterator it;
	}

	void showPackages(){
		for(int i = 0; i<(int)packages.size();i++){
			packages[i].showData();
		}
	}

	bool existsRegion(Region region){
		bool t=false;
		map<string, Region>::iterator it;
		for(it=regions.begin(); it!= regions.end(); it++){
			if(region.getCode().compare( (it->second).getCode() ) == 0){
				t=true;
			}
		}
		return t;
	}

	bool operator == (Office o){
		return codeID == o.getCode();
	}
};

#endif
