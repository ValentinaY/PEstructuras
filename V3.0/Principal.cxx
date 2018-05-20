#include "Principal.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//MÉTODOS DE CARGA------------------------------------------------------------------------------------------------
//Cargar las personas.
void Principal::loadPersons(char* file){
	bool si = false;
	int leidos = 0;
	Person persona;
	ifstream lector;
	lector.open(file);
	if(lector.is_open()){
		cout<<"Cargando personas...\n";
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

			for(int i=0;i< (int) persons.size();i++){
				if(persona.getId().compare(persons[i].getId())==0){
					cout<<"La persona con documento "<<persona.getId()<<" ya existe."<<endl;
					si = true;
					break;
				}
			}
			if(!si){
				persona.showData();
				persons.push_back(persona);
				leidos++;
			}
			getline(lector, linea, ',');
			si = false;
		}
		lector.close();
		cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
		cout<<"Se leyeron los datos de "<<leidos<<" personas."<<endl;
	}
	else{
		cout<<"Ocurrió un error al leer el archivo, verifique el nombre e intente nuevamente.\n";
	}
}

//Cargar los paquetes.
void Principal::loadPackages(char* file){

	bool esta = false, continuar;
	int leidos=0;

	ifstream entrada;
	string linea;
	entrada.open(file);
	if(entrada.is_open()){
		cout<<"Cargando paquetes...\n";
		getline(entrada, linea);

		//Id sender

		while(!entrada.eof()){
			getline(entrada, linea, ',');
			continuar = true;
			Package paquete;
			Person persona;
			Region region;
			Office oficina;

			for(int i = 0;i< (int) persons.size() && continuar;i++){
				if(linea.compare(persons[i].getId())==0){
					paquete.setSender(persons[i]);
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
			for(int i = 0;i< (int) persons.size() && continuar;i++){
				if(linea.compare(persons[i].getId())==0){
					paquete.setReceiver(persons[i]);
					esta = true;
					break;
				}
			}
			if(esta == false){
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
			getline(entrada, linea);
			if(continuar)
				region.setName(linea);

			if(continuar){

				Node* nodo = NULL;
				nodo = offices.search(oficina);

				if(nodo != NULL){
					vector<Region> regs = nodo->getData().getRegions();
					esta = false;
					for(int i = 0;i< (int) regs.size();i++){
						if(region == regs[i]){
							paquete.setRegion(regs[i]);
							esta = true;
							break;
						}
					}
					if(esta){
						bool ex = false;
						vector<Package> paks = nodo->getData().getPackages();
						for(int i = 0; i< (int) paks.size();i++){
							if(paks[i].getGuiden() == paquete.getGuiden()){
								ex = true;
								break;
							}
						}
						if(!ex){
							nodo->getData().addPackage(paquete);
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

			}
		}//while
		entrada.close();
		cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
		cout<<"Se leyeron "<<leidos<<" paquetes."<<endl;
	}
	else
		cout<<"Ocurrió un error al leer el archivo, verifique el nombre e intente nuevamente.\n";
}

//Cargar las oficinas.
void Principal::loadOffices(char* file){
	int leidos = 0;
	ifstream reader;
	reader.open(file);
	if(!reader.is_open()){
		cout<<"Ocurrió un error al leer el archivo, verifique el nombre e intente nuevamente.\n";
	}
	else{
		cout<<"Cargando oficinas...\n";
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
					leidos++;
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

	cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
	cout<<"Se cargaron "<<leidos<<" Oficinas"<<endl;
}

//Cargar las regiones.
void Principal::loadRegions(char* file){
	int leidos;
	ifstream reader;
	Region actual;
	reader.open(file);
	if(!reader.is_open()){
		cout<<"Ocurrió un error al leer el archivo, verifique el nombre e intente nuevamente.\n";
	}
	else{
		cout<<"Cargando regiones...\n";
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
				vector<Region> regs = node->getData().getRegions();
				bool x = true;
				for(unsigned int i = 0; i<regs.size(); i++){
					if(actual.getCode()==regs[i].getCode()){
						cout<<"Región "<<actual.getCode()<<" no fue cargada, ya existe. "<<endl;
						x = false;
					}
				}
				if(!x){
					cout<<"Región "<<actual.getCode()<<" cargada. "<<endl;
					node->getData().addRegion(actual);
					leidos++;
				}
			}
		}
	}
	cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
	cout<<"Se cargaron "<<leidos<<" regiones"<<endl;
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
	Package paquete;
	int contador = 0;
	float aux;
	bool esta = false;

	do{
		cout<<"Identificador del remitente: \n >";
		cin>>temp;
		for(int i = 0;i<persons.size();i++){
			if(temp.compare(persons[i].getId())==0){
				paquete.setSender(persons[i]);
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
			for(int i = 0;i<persons.size();i++){
				if(temp.compare(persons[i].getId())==0){
					paquete.setReceiver(persons[i]);
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
		vector<Region> regs = nodoOffice->getData().getRegions();
		cout<<"Codigo de Región: \n >";
		cin>>temp;

		for(int i = 0;i<regs.size();i++){
			if(temp.compare(regs[i].getCode())==0){
				paquete.setRegion(regs[i]);
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
	vector<Package> paks = nodoOffice->getData().getPackages();
	for(int i = 0; i<paks.size();i++){
		if(paks[i].getGuiden() == paquete.getGuiden()){
			ex = true;
			break;
		}
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


	for(int i=0; i < persons.size();i++){
		if(persona.getId().compare(persons[i].getId())==0){
			cout<<persons[i].getId()<<endl;
			cout<<"La persona ya existe."<<endl;
			break;
		}
	}
	persons.push_back(persona);

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

	vector<Region> regs = office->getRegions();
	for(unsigned int i = 0; i<office->getRegions().size(); i++){
		if(newRegion.getCode().compare(regs[i].getCode())==0){
			cout<<"Error :"<<regs[i].getCode()<<endl;
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
	for(unsigned int i = 0;i<persons.size();i++){
		persons[i].showData();
	}
}

//Mostrar regiones.
void Principal::showRegions(){
	offices.showRegions();
}

//MÉTODOS EXTRA
void Principal::countPackages(){
	cout<<"Contando Paquetes..."<<endl;

	vector<Office> oficinas = offices.getAllData();
	for(unsigned int i=0;i<oficinas.size();i++){
		vector<Region> regiones = oficinas[i].getRegions();

		for(unsigned int j;j<regiones.size();j++){
			int k = 0;
			vector<Package> paks = oficinas[i].getPackages();
			for(unsigned int k=0;k<paks.size();k++){
				if(regiones[j].getCode() == paks[k].getRegion().getCode())
					k++;
			} 
			if(k>0)
				cout<<"Hay "<<k<<" paquetes en la oficina "<< oficinas[i].getCode()<<
				" con la region de reparto "<<regiones[j].getCode();
		}
	}
}

void Principal::sendPackages(char* codeOf){
	cout<<"Funcion comentada por el bien común\n";
	/*
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
	*/
}

float Principal::toFloat(string a){
	float x= 0;
	for(unsigned int i=0;i<a.size();i++){
		x = x*10;
		x+= (int) (a[i]) - 48;
	}
	return x;
}
