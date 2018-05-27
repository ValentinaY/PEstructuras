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

	float toFloat(string a);

	vector<Person> getpersons(){
		return persons;
	}
	Graph<Office,int> getoffices(){
		return offices;
	}
};

#endif

/*
long index = offices.getIndexOf(oficina);
if(index > -1){
	Node* reg = offices.getNode(index).getRegions().search(region);
	if(reg!=NULL){
		paquete.setRegion(reg->getData());
		esta = true;
	}

	if(esta){
		bool ex = false;
		vector<Package> paks = offices.getNode(index).getPackages();
		for(int i = 0; i< (int) paks.size();i++){
			if(paks[i].getGuiden() == paquete.getGuiden()){
				ex = true;
				break;
			}
		}
		if(!ex){
			offices.getNode(index).addPackage(paquete);
			cout<<"Paquete con número guía "<<paquete.getGuiden()<<" leído"<<endl;
			leidos++;
		}else{
			cout<<"Paquete con número guía "<<paquete.getGuiden()<<" ya existe"<<endl;
		}
	}

	else
		cout<<"El código de la región no existe, paquete "<<paquete.getGuiden()<<" no cargado\n";


}
else{
	cout<<"El código de oficina no existe, paquete "<<paquete.getGuiden()<<" no cargado\n";
}
*/
