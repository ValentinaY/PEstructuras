#include "Principal.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>

using namespace std;

//MÉTODOS DE CARGA------------------------------------------------------------------------------------------------
//Cargar las personas.
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
				persons.push_back(persona);
			}
			getline(lector, linea, ',');
			si = false;
		}
		lector.close();
		cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
		return;
	}
}

//Cargar los paquetes.
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
					paquete.setSender(persona);
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
					paquete.setReceiver(persona);
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
			getline(entrada, linea, ',');
			if(continuar)
				region.setCode(linea);

			//Nombre Region
			getline(entrada, linea, ',');
			if(continuar)
				region.setName(linea);

			//Id Sender / EOF
			getline(entrada, linea, ',');

			if(continuar){
				
				Node* nodo = NULL;
				nodo = offices.search(oficina);

				if(nodo != NULL){
					list<Region> regs = nodo->getData().getRegions();
					esta = false;
					for(list<Region>::iterator it = regs.begin(); it != regs.end(); it++){
						if(region == *it){
							region = *(it);
							paquete.setRegion(region);
							esta = true;
							break;
						}
					}
					if(esta){
						bool ex = false;
						queue<Package> cola = nodo->getData().getPackages();
						Package auxPak;
						for(int i = 0; i<cola.size();i++){
							auxPak = cola.front();
							if(auxPak.getGuiden() == paquete.getGuiden()){
								ex = true;
							}
							cola.pop();
							cola.push(auxPak);
						}
						if(!ex){
							nodo->getData().addPackage(paquete);
							cout<<"Paquete con número guía "<<paquete.getGuiden()<<" leído"<<endl;	
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

			}
		}//while
		entrada.close();
		cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
	}
	else
		cout<<"La información desde "<<file<<" no ha podido ser cargada"<<endl;
}

//Cargar las oficinas.
void Principal::loadOffices(char* file){
	ifstream reader;
	reader.open(file);
	printf("Cargando oficinas...\n");
	if(!reader.is_open()){
		printf("Ocurrió un error al leer el archivo, verifique el nombre e intente nuevamente.\n");
	}
	else{
		string line="";
		getline(reader,line);	//Se omite la cabecera del archivo.
		Office actual;
		while(!reader.eof()){
			getline(reader,line,',');
			if(line.size() == 8){	//Se verifica que las oficinas sean válidas.
				Office actual;
				actual.setCode(line);
				getline(reader,line,',');
				actual.setName(line);
				getline(reader,line,',');
				actual.setAddress(line);
				getline(reader,line);
				actual.setCity(line);

				if(offices.existence(actual) == false){
					
					Node* auxiliar = offices.searchGeneral(actual.getCity());
					if(auxiliar != NULL){
						auxiliar->insertNode(actual);
						cout<<"Carganda oficina "<<actual.getCode()<<endl;
					}
					else{
						offices.insert(actual);
						cout<<"Carganda oficina "<<actual.getCode()<<endl;
					}
				}
				else
					cout<<"Error en oficina "<<actual.getCode()<<endl;
			}
		}
		reader.close();
	}

	printf("Oficinas cargadas \n \n");
}

//Cargar las regiones.
void Principal::loadRegions(char* file){
	ifstream reader;
	Region actual;
	printf("Cargando regiones...\n");
	reader.open(file);
	if(!reader.is_open()){
		printf("Ocurrió un error al leer el archivo, verifique el nombre e intente nuevamente.\n");
	}
	else{
		string line="";
		getline(reader,line);	//Se omite la cabecera del archivo.
		while(!reader.eof()){
			getline(reader,line,',');
			actual.setCode(line);
			getline(reader,line,',');
			actual.setName(line);
			getline(reader,line);

			Node* node = offices.find(line);
			if(node!= NULL){
				list<Region> regs = node->getData().getRegions();
				list<Region>::iterator it = regs.begin();
				bool x = true;
				for(unsigned int i = 0; i<regs.size(); i++, it++){
					if(actual.getCode()==(*it).getCode()){
						cout<<"Región "<<actual.getCode()<<" no fue cargada. "<<endl;
						x = false;
					}
				}
				if(x){

					cout<<"Región "<<actual.getCode()<<" cargada. "<<endl;
				}
				node->getData().addRegion(actual);
			}
		}
	}
	printf("Regiones cargadas. \n \n");
	reader.close();
}

//MÉTODOS DE REGISTRO---------------------------------------------------------------------------------------------
//Registrar las oficinas.
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
		auxiliar->insertNode(newOffice);
		cout<<"La información ha sido cargada exitosamente así:"<<endl;
		newOffice.showDataR();
	}
	else{
		offices.insert(newOffice);
		cout<<"La información ha sido cargada exitosamente así:"<<endl;
		newOffice.showData();
	}
}

//Registrar los paquetes
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
				paquete.setSender(persona);
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
					paquete.setReceiver(persona);
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
			cout<<"Oficina hallada\n";
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
				paquete.setRegion(reg);
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

	bool ex = false;
	queue<Package> cola = nodoOffice->getData().getPackages();
	Package auxPak;
	for(int i = 0; i<cola.size();i++){
		auxPak = cola.front();
		if(auxPak.getGuiden() == paquete.getGuiden()){
			ex = true;
		}
		cola.pop();
		cola.push(auxPak);
	}
	if(!ex){
		nodoOffice->getData().addPackage(paquete);
		cout<<endl<<"La información ha sido cargada exitosamente así:"<<endl;
		paquete.showData();
	}
	else{
		cout<<endl<<"El paquete con ese número de guía ya existe"<<endl;
	}
	

}

//Registrar personas.
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

//Registrar regiones.
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

//MÉTODOS DE VISUALIZACIÓN----------------------------------------------------------------------------------------

//Mostrar oficinas.
void Principal::showOffices(){
	offices.nivelOrden();
}

//Mostrar paquetes.
void Principal::showPackages(char* codeOf){
	string codigo = codeOf;
	Office ofAux;
	ofAux.setCode(codigo);
	Node* x = offices.search(ofAux);
	if(x != NULL){
		cout<<"La oficina tiene "<<x->getData().getPackages().size()<<" paquetes\n";
		x->getData().showPackages();
	}
	else
		cout<<"La oficina con código "<<codigo<<" no existe";
}

//Mostrar personas.
void Principal::showPersons(){
	for(list<Person>::iterator it = persons.begin(); it != persons.end(); it++){
		it->showData();
	}
}

//Mostrar regiones.
void Principal::showRegions(){
	offices.showRegions();
}

//MÉTODOS EXTRA
void Principal::countPackages(){
	cout<<"Contando Paquetes..."<<endl;

	list<Office> oficinas = offices.getAllData();
	for(list<Office>::iterator ito = oficinas.begin(); ito != oficinas.end(); ito++){
		list<Region> regiones = ito->getRegions();

		for(list<Region>::iterator itr = regiones.begin();itr != regiones.end(); itr++){
			int k = 0;
			queue<Package> cola = ito->getPackages();
			Package auxPak;
			for(int i=0;i<cola.size();i++){
				auxPak = cola.front();
				if(itr->getCode() == auxPak.getRegion().getCode())
					k++;
				cola.pop();
				cola.push(auxPak);
			} 
			if(k>0)
				cout<<"Hay "<<k<<" paquetes en la oficina "<< ito->getCode()<<
				" con la region de reparto "<<itr->getCode();
		}
	}
}

void Principal::sendPackages(char* codeOf){
	cout<<"Repartiendo paquetes..."<<endl;
	
	Package APack;
	string codigo = codeOf;
	Office ofAux;
	ofAux.setCode(codigo);
	Node* oficinaGeneral = offices.search(ofAux);
	if(oficinaGeneral != NULL){
		if(oficinaGeneral->altura()==1){
			list<Node*> oficinas =  oficinaGeneral->getDesc();
			for(list<Node*>::iterator ito = oficinas.begin();ito != oficinas.end(); ito++){
				queue<Package> cola = (*ito)->getData().getPackages();
				Package auxPak;
				for(int i=0;i<cola.size();i++){
					auxPak = cola.front();
					if(auxPak.isActive() == false){
						auxPak.send();
						cout<<"El paquete "<<auxPak.getGuiden()<<" se entregó\n ";	
					}
					cola.pop();
					cola.push(auxPak);
				}
				(*ito)->getData().setPackages(cola);
			}
		}
		else
			cout<<"no es una oficina general \n";
	}
	else{
		cout<<"Este código no se encuentra en el sistema \n";
	}
}

float Principal::toFloat(string a){
	float x= 0;
	for(unsigned int i=0;i<a.size();i++){
		x = x*10;
		x+= (int) (a[i]) - 48;
	}
	return x;
}
