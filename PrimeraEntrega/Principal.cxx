#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Principal.h"

using namespace std;

void Principal::loadRegions(){
	Region r;
	r.setNombre("Caribe, playitas bellas");
	Principal::regiones.push_front(r);
	r.setNombre("Selva");
	Principal::regiones.push_front(r);
	r.setNombre("Chocó");
	Principal::regiones.push_front(r);
	r.setNombre("Rolos");
	Principal::regiones.push_front(r);
	r.setNombre("Paisitas");
	Principal::regiones.push_front(r);
	r.setNombre("Llanos orientales");
	Principal::regiones.push_front(r);
}

void Principal::loadPersons(char* archivo, list<Persona> personas){
	
	cout<<"Estamos cargando personas\n";
	
	Persona persona;
	ifstream lector;
	lector.open(archivo);
	if(!lector.is_open())
		cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
	else if(!lector.is_open())
		cout<<"El archivo "<<archivo<<" no existe o es ilegible."<<endl;
	else{
		string linea, aux;
		while(!lector.eof()){
			getline(lector, linea, ',');
			//Eliminar las ' '
			linea.erase(linea.end()-1,linea.end());
			aux = linea.erase(0,1);
			persona.setNombre(aux);
			linea.erase(linea.end()-1,linea.end());
			aux = linea.erase(0,1);
			persona.setApellido(aux);
			linea.erase(linea.end()-1,linea.end());
			aux = linea.erase(0,1);
			persona.setId(aux);
			linea.erase(linea.end()-1,linea.end());
			aux = linea.erase(0,1);
			persona.setDireccion(aux);
			linea.erase(linea.end()-1,linea.end());
			aux = linea.erase(0,1);
			persona.setCiudad(aux);
			linea.erase(linea.end()-1,linea.end());
			aux = linea.erase(0,1);
			persona.setTelefono(aux);
			personas.push_front(persona);
		}
		lector.close();
		cout<<"La información desde "<<archivo<<" ha sido cargada exitosamente."<<endl;
	}
}

void Principal::loadPackages(){
	cout<<"Estamos cargando paquetes\n";
}

void Principal::regPersons(list<Persona> personas){
	cout<<"Estamos registrando personas\n";
	
	Persona persona;
	string aux;
	cout<<"Nombre de la persona: ";
	cin>>aux;
	persona.setNombre(aux);
	cout<<"Apellidos de la persona: ";
	cin>>aux;
	persona.setApellido(aux);
	cout<<"Numero de identificacion: ";
	cin>>aux;
	persona.setId(aux);
	cout<<"Direccion: ";
	cin>>aux;
	persona.setDireccion(aux);
	cout<<"Ciudad: ";
	cin>>aux;
	persona.setCiudad(aux);
	cout<<"Telefono: ";
	cin>>aux;
	persona.setTelefono(aux);
	
	for(list<Persona>::iterator it = personas.begin(); it != personas.end(); it++){
		if(persona.getId() == (*it).getId()){	
			cout<<"La persona ya existe."<<endl;
			break;
		}
	}
	
	cout<<"La información de "<<persona.getNombre()<<" ha sido cargada exitosamente."<<endl;
	
}
void Principal::regPackages(){
	cout<<"Estamos registrando paquetes\n";
}
void Principal::countPackages(){
	cout<<"Contando paquetes..."<<endl;	
	
	list<Region>::iterator itr;
	list<Oficina>::iterator ito;
	Region temp;
	list<Oficina> oficinas;
	int cont=0;
	for(itr=regiones.begin();itr!=regiones.end();++itr){
		temp=(*itr);
		oficinas=temp.getOficinas();
		for(ito=oficinas.begin();ito!=oficinas.end();++ito){
			cont+=ito->getPaquetes().size();
		}
		cout<<"La región "+itr->getNombre()+" tiene ";
		cout<<cont;
		cout<<" paquetes."<<endl;
		cont=0;
	}	
}

