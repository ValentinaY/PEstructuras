#include "Principal.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

/*

//Función que carga una una las regiones leídas.
void Principal::loadregions(char* file){
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
			actual.setCode(line);
			getline(reader,line,',');
			actual.setName(line);
			getline(reader,line,',');
			Principal::addregion(actual,line);
		}
	}
	reader.close();
	//	return regiones;
}

list<Office> Principal::loadpackages(char* archivo, list<Office> oficinas, list<Person> personas){
	cout<<"Estamos cargando Packages\n";
	bool esta = false;

	ifstream entrada;
	string linea;
	entrada.open(archivo);
	if(entrada.is_open()){

		getline(entrada, linea);	

		getline(entrada, linea, ',');	
		while(!entrada.eof()){	
			Package paquete;
			Person persona;
			Region region;
			list <Region> regiones;
			list <Package> paquetes;
			Office oficina;
			for(list<Person>::iterator it = personas.begin(); it != personas.end(); it++){
				if(linea.compare((*it).getId())==0){
					persona = (*it);
					paquete.setSender(&persona);
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
				if(linea.compare((*it).getId())==0){
					persona = *it;
					paquete.setReceiver(&persona);
					esta = true;
					break;
				}
			}
			if(esta == false){
				cout<<"Esa persona no se encuentra en nuestro registro\n";
			}


			getline(entrada, linea, ',');
			paquete.setWeight(toFloat(linea)); //función de string a float

			getline(entrada, linea, ',');
			paquete.setType(linea);

			getline(entrada, linea, ',');
			paquete.setGuiden(linea);

			//Si no existe of
			getline(entrada, linea, ',');
			oficina.setCode(linea);

			getline(entrada, linea, ',');
			oficina.setName(linea);

			getline(entrada, linea, ',');
			oficina.setAddress(linea);

			getline(entrada, linea, ',');
			oficina.setCity(linea);

			getline(entrada, linea, ',');
			region.setCode(linea);
			getline(entrada, linea);
			region.setName(linea);
			getline(entrada, linea, ',');

			bool ya = false;
			paquetes.push_back(paquete);

			cout<<"Leido el Package con número guía: "<<paquete.getGuiden()<<endl;
			for(list<Office>::iterator ito = oficinas.begin(); ito != oficinas.end() || ya; ito++){
				if(oficina.getCode().compare((*ito).getCode())==0){
					regiones = (*ito).getRegions();
					oficina =(*ito);
					for(list<Region>::iterator itr = regiones.begin();itr != regiones.end() || ya; itr++){
						if((*itr).getCode().compare(region.getCode())==0){
							region = (*itr);
							region.addPackages(paquetes);

							regiones.push_back(region);
							oficina.setRegions(regiones);
							oficinas.push_back(oficina);
							ya = true;
						}
					}
				}
			}


			if(!ya){
				region.setPackages(paquetes);
				regiones.push_back(region);
				oficina.setRegions(regiones);
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
			if(temp.compare((*it).getId())==0){
				persona = *it;
				paquete.setSender(&persona);
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
			if(temp.compare((*it).getId())==0){
				persona = *it;
				paquete.setReceiver(&persona);
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
	paquete.setWeight(aux);
	cout<<"Tipo de contenido: \n";
	getline(cin, temp);
	getline(cin, temp);
	paquete.setType(temp);
	cout<<"Número de guia: \n";
	getline(cin, tempAux);
	paquete.setGuiden(tempAux);

	cout<<"Código de oficina: \n";
	getline(cin, temp);
	for(list<Office>::iterator it = oficinas.begin(); it != oficinas.end() || esta; it++){
		if(temp.compare((*it).getCode())==0){
			esta = true;
			oficina = (*it);
		}
	}
	if(esta == false){
		oficina.setCode(temp);
		cout<<"Nombre de la oficina: \n";
		getline(cin, temp);
		oficina.setName(temp);
		cout<<"Direccion de la oficina: \n";
		getline(cin, temp);
		oficina.setAddress(temp);
		cout<<"Ciudad de la oficina: \n";
		getline(cin, temp);
		oficina.setCity(temp);


		cout<<"Código de la región: \n";
		getline(cin, temp);
		region.setCode(temp);
		cout<<"Nombre de la región: \n";
		getline(cin, temp);
		region.setName(temp);

		region.getPackages().push_back(paquete);
		oficina.getRegions().push_back(region);
		oficinas.push_back(oficina);
		return oficinas;

	}

	esta = false;

	cout<<"Código de la región: \n";
	getline(cin, temp);
	for(list<Region>::iterator it = oficina.getRegions().begin(); it != oficina.getRegions().end() || esta; it++){
		if(temp.compare((*it).getCode()) == 0){
			esta = true;
			region = (*it);
		}
	}
	if(esta == false){
		region.setCode(temp);
		cout<<"Nombre de la Region: \n";
		getline(cin, temp);
		region.setName(temp);

		region.getPackages().push_back(paquete);
		oficina.getRegions().push_back(region);
		oficinas.push_back(oficina);
		return oficinas;
	}

	for(list<Package>::iterator it = region.getPackages().begin(); it!= region.getPackages().end() || esta;it++){
		if(paquete.getGuiden().compare((*it).getGuiden()) == 0){
			cout<<"El Package ya existe\n";
			return oficinas;
		}
	}

	list<Package> Packages = region.getPackages();
	Packages.push_back(paquete);
	region.setPackages(Packages);

	list<Region> regiones = oficina.getRegions();
	regiones.push_back(region);
	oficina.setRegions(regiones);

	oficinas.push_back(oficina);
	return oficinas;

}


void Principal::countpackages(list<Office> oficinas){

	cout<<"Contando Packages..."<<endl;	

	list<Region> regionesTotales;

	for(list<Office>::iterator ito = oficinas.begin(); ito != oficinas.end(); ito++){
		list<Region> regiones = (*ito).getRegions();
		for(list<Region>::iterator itr = regiones.begin();itr != regiones.end(); itr++){
			cout<<"Hay "<<(*itr).getPackages().size()<<" Packages por entregar en la region de reparto "<<(*itr).getName()<<endl;
		}
	}
}

*/

void Principal::loadPersons(char* archivo){

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
			persona.setName(linea);

			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
				return;
			}
			persona.setLname(linea);

			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
				return;
			}
			persona.setId(linea);

			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
				return;
			}
			persona.setAddress(linea);

			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
				return;
			}
			persona.setCity(linea);

			getline(lector, linea);
			persona.setPhone(linea);

			for(list<Person>::iterator it = persons.begin(); it != persons.end(); it++){
				if(persona.getId().compare((*it).getId())==0){
					cout<<"La persona con documento "<<(*it).getId()<<" ya existe."<<endl;
					si = true;
					break;
				}
			}
			if(!si){
				persona.showData();
				persons.push_front(persona);
			}
			getline(lector, linea, ',');
			si = false;
		}
		lector.close();
		cout<<"La información desde "<<archivo<<" ha sido cargada exitosamente."<<endl;
		return;
	}
}

void Principal::regPersons(){
	cout<<"Estamos registrando personas\n";

	Person persona;
	string aux;
	cout<<"Nombre de la persona: ";
	cin.ignore();
	getline(cin, aux);
	persona.setName(aux);
	cout<<"Apellidos de la persona: ";
	getline(cin, aux);
	persona.setLname(aux);
	cout<<"Numero de identificacion: ";
	cin>>aux;
	persona.setId(aux);
	cout<<"Ciudad: ";
	cin>>aux;
	persona.setCity(aux);
	cout<<"Direccion: ";
	getline(cin, aux);
	getline(cin, aux);
	persona.setAddress(aux);
	cout<<"Telefono: ";
	cin>>aux;
	persona.setPhone(aux);

	for(list<Person>::iterator it = persons.begin(); it != persons.end(); it++){
		if(persona.getId().compare((*it).getId())==0){
			cout<<(*it).getId()<<endl;
			cout<<"La persona ya existe."<<endl;
			break;
		}
	}
	persons.push_front(persona);

	cout<<"La información ha sido cargada exitosamente así:"<<endl;
	persona.showData();

}

void Principal::regOffices(){

	cout<<"Registro de oficinas:\n";

	Office newOffice;
	string aux;
	cout<<"Nombre de la oficina: ";
	getline(cin, aux);
	newOffice.setName(aux);
	cout<<"Código: ";
	getline(cin, aux);
	newOffice.setCode(aux);
	cout<<"Dirección: ";
	cin>>aux;
	newOffice.setAddress(aux);
	cout<<"Ciudad: ";
	cin>>aux;
	newOffice.setCity(aux);

	if(offices.existence(newOffice))
		return;

	Node* auxiliar = offices.searchGeneral(newOffice.getCity());
	if(auxiliar != NULL){
		auxiliar->insertarNode(newOffice);
	}
	else{
		offices.insert(newOffice);
	}
	cout<<"La información ha sido cargada exitosamente así:"<<endl;
	newOffice.showData();
}

void Principal::regRegions(){
	cout<<"Registro de Regiones:\n";

	Region newRegion;
	Node* nodoOffice = NULL;
	Office* office;
	Office of;
	string aux;
	int cont = 0;
	bool find = true;
	while(find){
		if(cont >= 2)
			return;

		cout<<"Código de la Oficina: ";
		getline(cin, aux);
		of.setCode(aux);

		nodoOffice = offices.search(of);
		if(nodoOffice != NULL)
			find = false;

		if(find)
			cout<<"El código de oficina no existe, intente nuevamente \n";
		cont ++;
	}

	office = &(nodoOffice->getData());

	cout<<"Nombre de la región: ";
	getline(cin, aux);
	newRegion.setName(aux);
	cout<<"Código: ";
	cin>> aux;
	newRegion.setCode(aux);

	list<Region>::iterator it = office->getRegions().begin();
	for(unsigned int i = 0; i<office->getRegions().size(); i++, it++){
		if(newRegion.getCode().compare((*it).getCode())==0){
			cout<<"Error :"<<(*it).getCode()<<endl;
			cout<<"La región con ese código ya existe, la información no fue cargada"<<endl;
			return;
		}
	}

	office->addRegion(newRegion);
	cout<<endl<<"La información ha sido cargada exitosamente así:"<<endl;
	cout<<"Codigo Oficina: "<<office->getCode()<<endl;
	newRegion.showData();
}

void Principal::showPersons(){
	for(list<Person>::iterator it = persons.begin(); it != persons.end(); it++){
			it->showData();
		}
}

void Principal::showPackages(char* codeOf){
	string codigo = codeOf;
	Office ofAux;
	ofAux.setCode(codigo);
	Node* x = offices.search(ofAux);
	if(x != NULL)
		x->getData().showPackages();
	else
		cout<<"La oficina con código"<<codigo<<" no existe";
}

void Principal::showOffices(){
	offices.nivelOrden();
}

void Principal::showRegions(){
	offices.showRegions();
}

float Principal::toFloat(string a){
	float x= 0;
	for(unsigned int i=0;i<a.size();i++){
		x = x*10;
		x+= (int) (a[i]) - 48;
	}
	return x;
}
