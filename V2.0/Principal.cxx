#include "Principal.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void Principal::setpersons(list<Person> x){
	Principal::persons = x;
}
void Principal::setoffices(list<Office> x){
	Principal::offices = x;
}

void Principal::showregions(){
	list<Office>::iterator ito;
	list<Region>::iterator itr;
	list<Office> offices=Principal::offices;
	list<Region> regions;
	for(ito==offices.begin();ito!=offices.end();ito++){
		regions=(*ito).getregions();
		for(itr==regions.begin();itr!=regions.end();itr++){
			printf("%s\t",(*itr).getcode());
			printf("%s\n",(*itr).getname());
		}
	}
}

list<Region> Principal::loadregions(char* file){
	ifstream reader;
	list<Region> regiones;
	Region actual;
	reader.open(file);
	if(!reader.is_open()){
		printf("Ocurrió un error al leer el archivo, verifique el nombre e intente nuevamente.\n");
	}
	else{
		string line="";
		getline(reader,line);	//Se omite la cabecera del archivo.
		getline(reader,line,',');
		while(!reader.eof()){
			actual.setcode(line);
			getline(reader,line,',');
			actual.setname(line);
			getline(reader,line,',');
			Principal::addregion(actual,line);
		}
	}
	reader.close();
	return regiones;
}

list<Person> Principal::loadpersons(char* archivo, list<Person> personas){
	
	bool si = false;
	Person persona;
	ifstream lector;
	lector.open(archivo);
	if(!lector.is_open())
		cout<<"El archivo "<<archivo<<" no existe o es ilegible."<<endl;
		
	
	else{
		cout<<"Estamos cargando las personas\n";
		string linea;
		getline(lector, linea);
		getline(lector, linea, ',');
		while(!lector.eof()){
			persona.setname(linea);
			
			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
				return personas;
			}
			persona.setlname(linea);
			
			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
				return personas;
			}
			persona.setid(linea);
			
			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
				return personas;
			}
			persona.setaddress(linea);
			
			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
				return personas;
			}
			persona.setcity(linea);
			
			getline(lector, linea);
			persona.setphone(linea);
			
			for(list<Person>::iterator it = personas.begin(); it != personas.end(); it++){
				if(persona.getid().compare((*it).getid())==0){	
					cout<<"La persona con documento "<<(*it).getid()<<" ya existe."<<endl;
					si = true;
					break;
				}
			}
			if(!si){
				persona.toString();
				personas.push_front(persona);
			}
			getline(lector, linea, ',');
			si = false;
		}
		lector.close();
		cout<<"La información desde "<<archivo<<" ha sido cargada exitosamente."<<endl;
		return personas;
	}
}

list<Person> Principal::regpersons(list<Person> personas){
	cout<<"Estamos registrando personas\n";
	
	Person persona;
	string aux;
	cout<<"Nombre de la persona: ";
	cin.ignore();
	getline(cin, aux);
	persona.setname(aux);
	cout<<"Apellidos de la persona: ";
	getline(cin, aux);
	persona.setlname(aux);
	cout<<"Numero de identificacion: ";
	cin>>aux;
	persona.setid(aux);
	cout<<"Ciudad: ";
	cin>>aux;
	persona.setcity(aux);
	cout<<"Direccion: ";
	getline(cin, aux);
	getline(cin, aux);
	persona.setaddress(aux);
	cout<<"Telefono: ";
	cin>>aux;
	persona.setphone(aux);
	
	for(list<Person>::iterator it = personas.begin(); it != personas.end(); it++){
		cout<<(*it).getid()<<"::"<<endl;
	}
	
	for(list<Person>::iterator it = personas.begin(); it != personas.end(); it++){
		if(persona.getid().compare((*it).getid())==0){	
			cout<<(*it).getid()<<endl;
			cout<<"La persona ya existe."<<endl;
			break;
		}
	}	
	personas.push_front(persona);
	
	cout<<"La información ha sido cargada exitosamente así:"<<endl;
	
	persona.toString();
	return personas;
	
}


list<Office> Principal::loadpackages(char* archivo, list<Office> oficinas, list<Person> personas){
	cout<<"Estamos cargando Packages\n";
	bool esta = false, saltar = false;

	ifstream entrada;
	string linea;
	entrada.open(archivo);
	if(entrada.is_open()){

		getline(entrada, linea);	
		
		getline(entrada, linea, ',');	
		while(!entrada.eof()){	
			saltar = false;
			Package paquete;
			Person persona;
			Region region;
			list <Region> regiones;
			list <Package> paquetes;
			Office oficina;
			for(list<Person>::iterator it = personas.begin(); it != personas.end(); it++){
				if(linea.compare((*it).getid())==0){
					persona = (*it);
					paquete.setsender(persona);
					esta = true;
					break;
				}
			}
			if(esta == false){
				cout<<"Esa persona no se encuentra en nuestro registro\n";
			}
				esta = false;

				getline(entrada, linea, ',');
				for(list<Person>::iterator it = personas.begin(); it != personas.end(); it++){
					if(linea.compare((*it).getid())==0){
						persona = *it;
						paquete.setreceiver(persona);
						esta = true;
						break;
					}
				}
				if(esta == false){
					cout<<"Esa persona no se encuentra en nuestro registro\n";
				}

				
				getline(entrada, linea, ',');
				paquete.setweight(toFloat(linea)); //función de string a float
				
				getline(entrada, linea, ',');
				paquete.settype(linea);

				getline(entrada, linea, ',');
				paquete.setguiden(linea);

				//Si no existe of
				getline(entrada, linea, ',');
				oficina.setcode(linea);

				getline(entrada, linea, ',');
				oficina.setname(linea);

				getline(entrada, linea, ',');
				oficina.setaddress(linea);

				getline(entrada, linea, ',');
				oficina.setcity(linea);

				getline(entrada, linea, ',');
				region.setcode(linea);
				getline(entrada, linea);
				region.setname(linea);
				getline(entrada, linea, ',');

				bool ya = false;
				paquetes.push_back(paquete);

				cout<<"Leido el Package con número guía: "<<paquete.getguiden()<<endl;
				for(list<Office>::iterator ito = oficinas.begin(); ito != oficinas.end() || ya; ito++){
					if(oficina.getcode().compare((*ito).getcode())==0){
						regiones = (*ito).getregions();
						oficina =(*ito);
						for(list<Region>::iterator itr = regiones.begin();itr != regiones.end() || ya; itr++){
							if((*itr).getcode().compare(region.getcode())==0){
								region = (*itr);
								region.addpackages(paquetes);

					regiones.push_back(region);
					oficina.setregions(regiones);
					oficinas.push_back(oficina);
								ya = true;
							}
						}
					}
				}

				
				if(!ya){
					region.setpackages(paquetes);
					regiones.push_back(region);
					oficina.setregions(regiones);
					oficinas.push_back(oficina);
				}
					
		} //while
		entrada.close();
		cout<<"La información desde "<<archivo<<" ha sido cargada exitosamente."<<endl;
	}	
	else
	cout<<"La información desde "<<archivo<<" no ha podido ser cargada"<<endl;	

	return oficinas;
}


list<Office> Principal::regpackages(list<Office> oficinas, list<Person> personas){
	cout<<"Estamos registrando Packages\n";

	string temp, tempAux;
	Office oficina;
	Region region;
	Person persona;
	Package paquete;
	int contador = 0;
	float aux;
	bool esta = false;

	do{
		cout<<"Identificador del remitente\n";
		cin>>temp;
		for(list<Person>::iterator it = personas.begin(); it != personas.end(); it++){
			if(temp.compare((*it).getid())==0){
				persona = *it;
				paquete.setsender(persona);
				esta = true;
				break;
			}
		}
		if(esta == false){
			cout<<"Esa persona no se encuentra en nuestro registro\n";
		}
		contador++;
		if(contador==5) {
			cout<<"Numero de intentos excedido.\n";
			return oficinas;
		}
	}while(esta ==  false);
	
	esta = false;
	contador=0;
	do{	
		cout<<"Identificador del destinatario\n";
		cin>>temp;
		for(list<Person>::iterator it = personas.begin(); it != personas.end(); it++){
			if(temp.compare((*it).getid())==0){
				persona = *it;
				paquete.setreceiver(persona);
				esta = true;
				break;
			}
		}
		if(esta == false){
			cout<<"Esa persona no se encuentra en nuestro registro\n";
		}
		contador++;
		if(contador==5) {
			cout<<"Numero de intentos excedido.\n";
			return oficinas;
		}
	}while(esta ==  false);
	
	esta = false;

	cout<<"Peso: \n";
	cin>>aux;
	paquete.setweight(aux);
	cout<<"Tipo de contenido: \n";
	getline(cin, temp);
	getline(cin, temp);
	paquete.settype(temp);
	cout<<"Número de guia: \n";
	getline(cin, tempAux);
	paquete.setguiden(tempAux);

	cout<<"Código de oficina: \n";
	getline(cin, temp);
	for(list<Office>::iterator it = oficinas.begin(); it != oficinas.end() || esta; it++){
		if(temp.compare((*it).getcode())==0){
			esta = true;
			oficina = (*it);
		}
	}
	if(esta == false){
		oficina.setcode(temp);
		cout<<"Nombre de la oficina: \n";
		getline(cin, temp);
		oficina.setname(temp);
		cout<<"Direccion de la oficina: \n";
		getline(cin, temp);
		oficina.setaddress(temp);
		cout<<"Ciudad de la oficina: \n";
		getline(cin, temp);
		oficina.setcity(temp);


		cout<<"Código de la región: \n";
		getline(cin, temp);
		region.setcode(temp);
		cout<<"Nombre de la región: \n";
		getline(cin, temp);
		region.setname(temp);

		region.getpackages().push_back(paquete);
		oficina.getregions().push_back(region);
		oficinas.push_back(oficina);
		return oficinas;

	}

	esta = false;

	cout<<"Código de la región: \n";
	getline(cin, temp);
	for(list<Region>::iterator it = oficina.getregions().begin(); it != oficina.getregions().end() || esta; it++){
		if(temp.compare((*it).getcode()) == 0){
			esta = true;
			region = (*it);
		}
	}
	if(esta == false){
		region.setcode(temp);
		cout<<"Nombre de la Region: \n";
		getline(cin, temp);
		region.setname(temp);

		region.getpackages().push_back(paquete);
		oficina.getregions().push_back(region);
		oficinas.push_back(oficina);
		return oficinas;
	}

	for(list<Package>::iterator it = region.getpackages().begin(); it!= region.getpackages().end() || esta;it++){
		if(paquete.getguiden().compare((*it).getguiden()) == 0){
			cout<<"El Package ya existe\n";
			return oficinas;
		}
	}

	list<Package> Packages = region.getpackages();
	Packages.push_back(paquete);
	region.setpackages(Packages);

	list<Region> regiones = oficina.getregions();
	regiones.push_back(region);
	oficina.setregions(regiones);

	oficinas.push_back(oficina);
	return oficinas;

}


void Principal::countpackages(list<Office> oficinas){

	cout<<"Contando Packages..."<<endl;	
	
	list<Region> regionesTotales;

	for(list<Office>::iterator ito = oficinas.begin(); ito != oficinas.end(); ito++){
		list<Region> regiones = (*ito).getregions();
		for(list<Region>::iterator itr = regiones.begin();itr != regiones.end(); itr++){
			cout<<"Hay "<<(*itr).getpackages().size()<<" Packages por entregar en la region de reparto "<<(*itr).getname()<<endl;
		}
	}
}

void Principal::addregion(Region region, string ocode){
	list<Office>::iterator it;
	list<Office> noficinas= Principal::offices;
	if(!noficinas.empty()){
		for(it==noficinas.begin(); it!=noficinas.end();it++){
		if((*it).getcode()==ocode){
			(*it).addregion(region);
		}
	}
	}
	else{
		printf("Error al agregar la región con código %s.\n",region.getcode());
	}
}

float Principal::toFloat(string a){
	float x= 0;
	for(int i=0;i<a.size();i++){
		x*10;
		x+= (int) (a[i]) - 48;
	}
	return x;
}