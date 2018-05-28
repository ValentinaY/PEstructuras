#include "Principal.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

//MÉTODOS DE CARGA------------------------------------------------------------------------------------------------
//Cargar las personas.
void Principal::loadPersons(char* file){
	//Check if the person exists
	bool exists = false;
	int total = 0;
	Person persona;
	ifstream reader;
	reader.open(file);
	try{

	if(reader.is_open()){
		cout<<"Cargando personas...\n";
		string linea;
		getline(reader, linea);
		getline(reader, linea, ',');
		while(!reader.eof()){
			persona.setName(linea);
			getline(reader, linea, ',');
			persona.setLname(linea);
			getline(reader, linea, ',');
			persona.setId(linea);
			getline(reader, linea, ',');
			persona.setAddress(linea);
			getline(reader, linea, ',');	
			persona.setCity(linea);
			getline(reader, linea);
			persona.setPhone(linea);
			for(int i=0;i< (int) persons.size();i++){
				if(persona.getId().compare(persons[i].getId())==0){
					cout<<"La persona con documento "<<persona.getId()<<" ya existe."<<endl;
					exists = true;
					break;
				}
			}
			if(!exists){
				persona.showData();
				persons.push_back(persona);
				total++;
			}
			getline(reader, linea, ',');
			exists = false;
		}
		reader.close();
		cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
		cout<<"Se leyeron los datos de "<<total<<" personas."<<endl;
	}
	else{
		cout<<"verifique la existecia del archivo."<<endl;
	}
	}
	catch(invalid_argument& e){
		printf("Ocurrió un error mientras se leía el archivo, verifique que los datos están en el formato correcto. \n");
	}
}

//Cargar los paquetes.
void Principal::loadPackages(char* file){

	int existsperson = 0;
	bool existsoffice=false;
	bool remain;
	int total=0;

	string sender, receiver;
	string linea;
	
	Package paquete;
	Person senderper, receiverper;
	Region region;
	Office oficina;
	std::vector<Office> v = offices.getVertexes();

	ifstream reader;
	reader.open(file);
	if(reader.is_open()){
		cout<<"Cargando paquetes...\n";
		getline(reader, linea);

		while(!reader.eof()){
			getline(reader, sender, ',');
			getline(reader, receiver, ',');
			if(sender.compare(receiver) == 0){
				printf("El remitente no puede ser igual al destinatario.\n");
				getline(reader, linea);
				remain=false;
			}
			if(remain){
				for(int i = 0;i< (int) persons.size() && remain;i++){
					if(sender.compare(persons[i].getId())==0){
						senderper=persons[i];
						existsperson++;
						printf("-1\n");
					}
					if(receiver.compare(persons[i].getId())==0){
						receiverper=persons[i];
						existsperson++;
						printf("-2\n");
					}
				}
				if(existsperson == 2 ){
					paquete.setSender(senderper);
					paquete.setReceiver(receiverper);
				}
				else{
					cout<<"Verifique que las personas se encuentran en el registro\n";
					getline(reader, linea);
					remain=false;
				}
				existsperson=0;
			}//if remain
			if(remain){
				getline(reader, linea,',');
				paquete.setWeight(toFloat(linea));
				getline(reader, linea,',');
				paquete.setType(linea);
				getline(reader, linea,',');
				paquete.setGuiden(linea);
				getline(reader, linea);
				string oficecode=linea;
				string oficeinvectorcode;
				if(v.size() == 0) printf("No hay oficinas.\n");

				printf("Agregando paquete...\n");
				for(int i=0; i<v.size(); i++){
					oficeinvectorcode=v.at(i).getCode();
					if(strcmp(oficeinvectorcode.c_str(), oficecode.c_str()) == 0){
						oficina=v.at(i);
						oficina.getPackages().push_back(paquete);
						total++;
						break;
					}
				}
			}//if remain	
			else{
				printf("El paquete no se agregó.\n");
			}
			remain=true;
		}//while !reader.eof()
	printf("Se agregaron %d paquetes.\n", total);
	}//if reader.is_open()
	reader.close();
}

//Cargar las oficinas.
void Principal::loadOffices(char* file){
	int total = 0;
	//Si el id ya existe.
	bool exists = false;
	//Se guardan temporalmente las oficinas para verificar si la que se intenta cargar ya existe.
	std::vector<Office> v = offices.getVertexes();
	
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
				
				for(int i=0; i<v.size();i++){
					if(v.at(i).getCode().compare(actual.getCode())){
						exists=true;
					}
				}
				//Si la oficina no existe entonces se agrega en el grafo.
				if(!exists){
					total++;
					offices.insertVertex(actual);
					cout<<"Cargada oficina "<<actual.getCode()<<endl;
				}
				else{
					printf("Ya existe una oficina con ese número de identificción.\n");
				}
			}
		}
		reader.close();
	}

	cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
	cout<<"Se cargaron "<<total<<" Oficinas"<<endl;
}

//Cargar las regiones.
void Principal::loadRegions(char* file){
	//Si el id ya existe.
	bool exists = false;
	//Se guardan temporalmente las oficinas para verificar si la que se intenta cargar ya existe.
	std::vector<Office> v = offices.getVertexes();
	Office office;

	int total;
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
			for(int i=0; i<v.size(); i++){
				if(line.compare(v.at(i).getCode()) == 0 ){
					office=v.at(i);
				}
			}
			getline(reader,line);
			int distance = atoi(line.c_str());
			actual.setDistanceUp(distance);
			office.getRegions().insert(actual);
		}
	}
	cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
	cout<<"Se cargaron "<<total<<" regiones"<<endl;
	reader.close();
}

//MÉTODOS DE REGISTRO---------------------------------------------------------------------------------------------
//Registrar las oficinas.
void Principal::regOffices(){

	cout<<"Registro de oficinas:\n";
	//Si el id ya existe.
	bool exists = true;
	//Se guardan temporalmente las oficinas para verificar si la que se intenta cargar ya existe.
	std::vector<Office> v = offices.getVertexes();
	
	//La oficina que se registrará.
	Office office;
	string aux;

	//Se verifica si el id que se intenta registrar ya existe.
	int cont=0;
	while(exists){
	cout<<"Código: \n >";
	getline(cin, aux);
		exists=false;
		for(int i=0; i<v.size();i++){
			if(v.at(i).getCode().compare(aux) ==0 ){
				printf("Ya existe una oficina con ese código.\n");
				exists=true;
				break;
			}
		}
		cont++;
		if(cont==5) {printf("Ha superado el límite máximo de intentos.\n"); break;}
	}
	
	if(!exists){
		office.setCode(aux);
		cout<<"Nombre de la oficina: \n >";
		getline(cin, aux);
		office.setName(aux);
		cout<<"Dirección: \n >";
		getline(cin, aux);
		office.setAddress(aux);
		cout<<"Ciudad: \n >";
		getline(cin, aux);
		office.setCity(aux);
		offices.insertVertex(office);
	}
	//Si ya existe, se nuncia que no se agregó.
	else{
		printf("La oficina no se agregó.\n");
	}
	exists=false;
}

//Registrar los paquetes
void Principal::regPackages(){
	cout<<"Estamos registrando Packages\n";
	bool existsoffice=false;
	bool existsreceiver=false;
	bool existssender=false;

	string receivertemp, sendertemp;
	int weight;
	string temp;
	Office office;
	Region region;
	Package paquete;
	int cont = 0;
	float aux;

	do{
		if(cont>1){
			printf("Intente con un número de identificación válido.\n");
		}
		if(!existssender){
			cout<<"Identificador del remitente: \n >";
			cin>>receivertemp;
		}
		if(!existsreceiver){
			cout<<"Identificador del destinatario: \n >";
			cin>>sendertemp;
		}
		for(int i = 0;i<persons.size();i++){
			if(!existssender && sendertemp.compare(persons[i].getId())==0){
				paquete.setSender(persons[i]);
				existssender=true;
				break;
			}
			if(!existsreceiver && sendertemp.compare(persons[i].getId())==0){
				paquete.setReceiver(persons[i]);
				existsreceiver=true;
				break;
			}
		}
		cont++;
		if(cont==5) {
			cout<<"Numero de intentos excedido.\n";
			return;
		}
	}while(cont<5);

	cout<<"Peso: \n >";
	cin>>weight;
	paquete.setWeight(weight);
	cout<<"Tipo de contenido: \n >";
	getline(cin, temp);
	paquete.setType(temp);
	cout<<"Número de guia: \n >";
	getline(cin, temp);
	paquete.setGuiden(temp);

	existsoffice=false;
	cont = 0;
	while(!existsoffice){
		if(cont >= 2){
			cout<<"Numero de intentos excedido.\n";
			return;
		}

		cout<<"Código de la Oficina: \n >";
		getline(cin, temp);
		office.setCode(temp);

		/*nodoOffice = offices.search(oficina);
		if(nodoOffice != NULL){
			existsoffice = true;
			cout<<"Oficina hallada\n";
		}

		if(!existsoffice)
			cout<<"El código de oficina no existe, intente nuevamente \n";
		cont ++;*/
	}

	cont = 0;
	existsoffice = false;
	/*
	do{
		vector<Region> regs = nodoOffice->getData().getRegions();
		cout<<"Codigo de Región: \n >";
		cin>>temp;

		for(int i = 0;i<regs.size();i++){
			if(temp.compare(regs[i].getCode())==0){
				paquete.setRegion(regs[i]);
				existsperson = true;
				break;
			}
		}
		if(existsperson == false){
			cout<<"Esta región no se encuentra en nuestro registro\n";
		}
		cont++;
		if(cont==5) {
			cout<<"Numero de intentos excedido.\n";
			return;
		}
	}while(existsperson ==  false);*/
/*
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

*/
}

//Registrar personas.
void Principal::regPersons(){
	bool existsperson=false;
	int cont=0;

	cout<<"Registro de personas\n";
	Person persona;
	string aux;
	do{
		cout<<"Numero de identificacion: \n >";
		getline(cin, aux);
		existsperson=false;
		for(int i=0; i < persons.size();i++){
			if(persona.getId().compare(persons[i].getId())==0){
				cout<<persons[i].getId()<<endl;
				cout<<"La persona con el id ya está registrada.\n"<<endl;
				existsperson=true;
				break;
			}
		}
		if(cont==5){printf("Ha superado el límite máximo de intentos.\n"); break;}
	}while(existsperson);
	if(!existsperson){
		persona.setId(aux);
		cout<<"Nombre de la persona: \n >";
		getline(cin, aux);
		persona.setName(aux);
		cout<<"Apellidos de la persona: \n >";
		getline(cin, aux);
		persona.setLname(aux);
		cout<<"Ciudad: \n >";
		getline(cin, aux);
		persona.setCity(aux);
		cout<<"Direccion: \n >";
		getline(cin, aux);
		persona.setAddress(aux);
		cout<<"Telefono: \n >";
		getline(cin, aux);
		persona.setPhone(aux);
		persons.push_back(persona);
		cout<<"La información ha sido cargada exitosamente así:"<<endl;
		persona.showData();
	}
	else{
		printf("La persona no se agregó.\n");
	}

}

//Registrar regiones.
void Principal::regRegions(){
	cout<<"Registro de Regiones:\n";

	Region region;  
	std::vector<Office> v= offices.getVertexes();
	Office office;
	string codeoffice;
	int cont = 0;
	bool existsoffice = false;
	bool existsregion=false;

	while(!existsoffice){
		printf("Código de la oficina: \n>");
		getline(cin, codeoffice);
		for(int i=0; i<v.size();i++){
			if(codeoffice.compare(v.at(i).getCode()) == 0){ office=v.at(i);	existsoffice=true;	break;}
		}
		if(!existsoffice)	cout<<"El código de oficina no existe, intente nuevamente \n>";
		
		cont ++;
		if(cont == 5){printf("Ha superado el número máximo de intentos.\n"); break;}
	}

	string aux;
	cout<<"Nombre de la región:\n>";
	getline(cin, aux);
	region.setName(aux);

	if(office.getRegions().isEmpty()){	existsregion=false;}
	else{
		vector<Region> regs = office.getRegions().getAllData();
		do{
			cout<<"Código de la región: ";
			cin>> aux;
			existsregion=false;
			for(int i = 0; i<regs.size(); i++){
				if(region.getCode().compare(regs[i].getCode())==0){
					cout<<"La región con ese código ya existe."<<endl;
					existsregion=true;
				}
			}
		cont ++;
		//Se limitan el número de intentos
		if(cont == 5){printf("Ha superado el número máximo de intentos.\n"); break;}
		}while(existsregion);
		region.setCode(aux);
	}
	if(!existsregion){
		office.getRegions().insert(region);
		cout<<endl<<"La información ha sido cargada exitosamente así:"<<endl;
		region.showData();
	}
	else{
		printf("No se agregó la región.\n");
	}

}

//MÉTODOS DE VISUALIZACIÓN----------------------------------------------------------------------------------------

//Mostrar oficinas.
void Principal::showOffices(){
	//offices.nivelOrden();
}

//Mostrar paquetes.
void Principal::showPackages(char* codeOf){
	string codigo = codeOf;
	Office ofAux;
	ofAux.setCode(codigo);
	/*Node* x = offices.search(ofAux);
	if(x != NULL){
		cout<<"La oficina tiene "<<x->getData().getPackages().size()<<" paquetes\n";
		x->getData().showPackages();
	}
	else
		cout<<"La oficina con código "<<codigo<<" no existe";*/
}

//Mostrar personas.
void Principal::showPersons(){
	for(unsigned int i = 0;i<persons.size();i++){
		persons[i].showData();
	}
}

//Mostrar regiones.
void Principal::showRegions(){
	//offices.getRegions().nivelOrden();
}

//MÉTODOS EXTRA
void Principal::countPackages(){
	cout<<"Contando Paquetes..."<<endl;

	vector<Office> oficinas = offices.getVertexes();
	for(unsigned int i=0;i<oficinas.size();i++){
		vector<Region> regiones = oficinas[i].getRegions().getAllData();

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
