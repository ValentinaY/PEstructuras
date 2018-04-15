#include "Principal.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;


//Función que carga una una las regiones leídas.
void Principal::loadRegions(char* file){
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
		while(!reader.eof()){
			getline(reader,line,',');
			printf("Cargando región...\n");
			actual.setCode(line);
			getline(reader,line,',');
			actual.setName(line);
			getline(reader,line);
			Principal::addRegion(actual,line);
		}
	}
	printf("Regiones cargadas.\n");
	reader.close();
}

void Principal::loadPersons(char* file){

	bool si = false;
	Person persona;
	ifstream lector;
	lector.open(file);
	if(!lector.is_open())
		cout<<"El archivo "<<file<<" no existe o es ilegible."<<endl;


	else{
		cout<<"Estamos cargando las personas\n";
		string linea;
		getline(lector, linea);
		getline(lector, linea, ',');
		while(!lector.eof()){
			persona.setName(linea);

			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<file<<" no contiene información válida."<<endl;
				return;
			}
			persona.setLname(linea);

			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<file<<" no contiene información válida."<<endl;
				return;
			}
			persona.setId(linea);

			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<file<<" no contiene información válida."<<endl;
				return;
			}
			persona.setAddress(linea);

			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<file<<" no contiene información válida."<<endl;
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
		cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
		return;
	}
}

void Principal::loadPackages(char* file){
	cout<<"Estamos cargando paquetes\n";
	bool esta = false, continuar;

	ifstream entrada;
	string linea;
	entrada.open(file);
	if(entrada.is_open()){
		getline(entrada, linea);

		//Id sender
		getline(entrada, linea, ',');
		while(!entrada.eof()){
			continuar = true;
			Package paquete;
			Person persona;
			Region region;
			Office oficina;

			for(list<Person>::iterator it = persons.begin(); it != persons.end() && continuar; it++){
				if(linea.compare((*it).getId())==0){
					persona = (*it);
					paquete.setSender(&persona);
					esta = true;
					break;
				}
			}
			if(esta == false){
				continuar = false;
				cout<<"Esa persona no se encuentra en nuestro registro\n";
			}
			esta = false;

			//Id receiver
			getline(entrada, linea, ',');
			for(list<Person>::iterator it = persons.begin(); it != persons.end() && continuar; it++){
				if(linea.compare((*it).getId())==0){
					persona = *it;
					paquete.setReceiver(&persona);
					esta = true;
					break;
				}
			}
			if(esta == false && continuar){
				continuar = false;
				cout<<"Esa persona no se encuentra en nuestro registro\n";
			}

			// Peso
			getline(entrada, linea, ',');
			if(continuar)
				paquete.setWeight(toFloat(linea)); //función de string a float

			// Tipo
			getline(entrada, linea, ',');
			if(continuar)
				paquete.setType(linea);

			// Guide Number
			getline(entrada, linea, ',');
			if(continuar)
				paquete.setGuiden(linea);

			// Codigo Oficina
			getline(entrada, linea, ',');
			if(continuar)
				oficina.setCode(linea);

			// Nombre Oficina
			getline(entrada, linea, ',');
			if(continuar)
				oficina.setName(linea);

			// Direcc Oficina
			getline(entrada, linea, ',');
			if(continuar)
				oficina.setAddress(linea);

			// Ciudad Oficina
			getline(entrada, linea, ',');
			if(continuar)
				oficina.setCity(linea);

			//Code Region
			getline(entrada, linea);
			if(continuar)
				region.setCode(linea);

			//Nombre Region
			getline(entrada, linea);
			if(continuar)
				region.setName(linea);

			//Id Sender / EOF
			getline(entrada, linea, ',');

			if(continuar){
				cout<<"Paquete con número guía "<<paquete.getGuiden()<<"leído"<<endl;

				Node* nodo = NULL;
				nodo = offices.search(oficina);

				if(nodo != NULL){
					list<Region> regs = nodo->getData().getRegions();
					esta = false;
					for(list<Region>::iterator it = regs.begin(); it != regs.end(); it++){
						if(region.getCode().compare((*it).getCode())==0){
							region = *(it);
							paquete.setRegion(&region);
							esta = true;
							break;
						}
					}
					if(esta)
						nodo->getData().addPackage(paquete);
					else
						cout<<"El código de la región no existe\n";


				}
				else{
					cout<<"El código de oficina no existe\n";
				}

			}
		}//while
		entrada.close();
		cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
	}
	else
		cout<<"La información desde "<<file<<" no ha podido ser cargada"<<endl;


}

//Función que carga una una las regiones leídas.
void Principal::loadOffices(char* file){
	ifstream reader;
	reader.open(file);
	printf("Cargando oficinas...\n");
	if(!reader.is_open()){
		printf("Ocurrió un error al leer el archivo, verifique el nombre e intente nuevamente.\n");
	}
	else{
		string line="";
		bool truee;
		getline(reader,line);	//Se omite la cabecera del archivo.
		Office actual;
		while(!reader.eof()){
			getline(reader,line,',');
			Office actual;
			cout<<"Código: "+line<<endl;
			actual.setCode(line);
			getline(reader,line,',');
			cout<<"Nombre: "+line<<endl;
			actual.setName(line);
			getline(reader,line,',');
			cout<<"Diro: "+line<<endl;
			actual.setAddress(line);
			getline(reader,line);
			cout<<"Ciudad: "+line<<endl;
			actual.setCity(line);
			truee = Principal::offices.insert( actual );
			printf("Cargando oficina...\n");
		}
		reader.close();
	}
}

void Principal::regPersons(){
	cout<<"Estamos registrando personas\n";

	Person persona;
	string aux;
	cout<<"Nombre de la persona: \n >";
	getline(cin, aux);
	persona.setName(aux);
	cout<<"Apellidos de la persona: \n >";
	getline(cin, aux);
	persona.setLname(aux);
	cout<<"Numero de identificacion: \n >";
	cin>>aux;
	persona.setId(aux);
	cout<<"Ciudad: \n >";
	cin>>aux;
	persona.setCity(aux);
	cout<<"Direccion: \n >";
	getline(cin, aux);
	getline(cin, aux);
	persona.setAddress(aux);
	cout<<"Telefono: \n >";
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

void Principal::regPackages(){
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
		cout<<"Identificador del remitente: \n >";
		cin>>temp;
		for(list<Person>::iterator it = persons.begin(); it != persons.end(); it++){
			if(temp.compare((*it).getId())==0){
				persona = *it;
				paquete.setSender(&persona);
				esta = true;
				tempAux = temp;
				break;
			}
		}
		if(esta == false){
			cout<<"Esa persona no se encuentra en nuestro registro\n";
		}
		contador++;
		if(contador==5) {
			cout<<"Numero de intentos excedido.\n";
			return;
		}
	}while(esta ==  false);

	esta = false;
	contador=0;
	do{
		cout<<"Identificador del destinatario: \n >";
		cin>>temp;
		if(temp != tempAux){
			for(list<Person>::iterator it = persons.begin(); it != persons.end(); it++){
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
		}
		else{
			cout<<"El remitente no puede ser destinatario\n";
		}
		if(contador==5) {
			cout<<"Numero de intentos excedido.\n";
			return;
		}
	}while(esta ==  false);


	cout<<"Peso: \n >";
	cin>>aux;
	paquete.setWeight(aux);
	cout<<"Tipo de contenido: \n >";
	cin.ignore();
	getline(cin, temp);
	paquete.setType(temp);
	cout<<"Número de guia: \n >";
	getline(cin, tempAux);
	paquete.setGuiden(tempAux);

	Node* nodoOffice = NULL;

	esta = false;
	contador = 0;
	while(!esta){
		if(contador >= 2){
			cout<<"Numero de intentos excedido.\n";
			return;
		}

		cout<<"Código de la Oficina: \n >";
		getline(cin, temp);
		oficina.setCode(temp);

		nodoOffice = offices.search(oficina);
		if(nodoOffice != NULL){
			esta = true;
			cout<<"Oficina hallada";
		}

		if(!esta)
			cout<<"El código de oficina no existe, intente nuevamente \n";
		contador ++;
	}

	contador = 0;
	esta = false;
	do{
		Region reg;
		list<Region> regs = nodoOffice->getData().getRegions();
		cout<<"Codigo de Región: \n >";
		cin>>temp;

		for(list<Region>::iterator it = regs.begin(); it != regs.end(); it++){
			if(temp.compare((*it).getCode())==0){
				reg = *it;
				paquete.setRegion(&reg);
				esta = true;
				break;
			}
		}
		if(esta == false){
			cout<<"Esta región no se encuentra en nuestro registro\n";
		}
		contador++;
		if(contador==5) {
			cout<<"Numero de intentos excedido.\n";
			return;
		}
	}while(esta ==  false);

	nodoOffice->getData().addPackage(paquete);
	cout<<endl<<"La información ha sido cargada exitosamente así:"<<endl;
	paquete.showData();

}

void Principal::regOffices(){

	cout<<"Registro de oficinas:\n";

	Office newOffice;
	string aux;
	cout<<"Nombre de la oficina: \n >";
	getline(cin, aux);
	newOffice.setName(aux);
	cout<<"Código: \n >";
	getline(cin, aux);
	newOffice.setCode(aux);
	cout<<"Dirección: \n >";
	cin>>aux;
	newOffice.setAddress(aux);
	cout<<"Ciudad: \n >";
	cin>>aux;
	newOffice.setCity(aux);

	if(offices.existence(newOffice))
		return;

	Node* auxiliar = offices.searchGeneral(newOffice.getCity());
	if(auxiliar != NULL){
		auxiliar->insertarNode(newOffice);
		cout<<"La información ha sido cargada exitosamente así:"<<endl;
		newOffice.showDataR();
	}
	else{
		offices.insert(newOffice);
		cout<<"La información ha sido cargada exitosamente así:"<<endl;
		newOffice.showData();
	}
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

void Principal::addRegion(Region r, string office){
	Node* node = Principal::offices.find(office);
	if(node!= NULL){
		string s= node->getData().getCode();
		cout<<s<<endl;
		node->getData().addRegion(r);
	}
}

void Principal::countPackages(){
	cout<<"Contando Packages..."<<endl;

	list<Office> oficinas = offices.getAllData();

	for(list<Office>::iterator ito = oficinas.begin(); ito != oficinas.end(); ito++){
		list<Region> regiones = ito->getRegions();

		for(list<Region>::iterator itr = regiones.begin();itr != regiones.end(); itr++){
			int i = 0;
			for(list<Package>::iterator itp = ito->getPackages().begin(); itp != ito->getPackages().end(); itp++){
				if(itr->getCode() == itp->getRegion()->getCode())
					i++;
			}
			if(i>0)
				cout<<"Hay "<<i<<"paquetes en la oficina "<< ito->getCode()<<
				" con la region de reparto "<<itr->getCode();
		}
	}
}

void Principal::sendPackages(char *codeOf){

}

float Principal::toFloat(string a){
	float x= 0;
	for(unsigned int i=0;i<a.size();i++){
		x = x*10;
		x+= (int) (a[i]) - 48;
	}
	return x;
}
