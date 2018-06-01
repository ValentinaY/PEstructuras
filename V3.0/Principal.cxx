#include "Principal.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

void Principal::fastboot(){
	loadOffices("data/ofi.csv");
	loadRegions("data/reg.csv");
	loadPersons("data/per.csv");
//	loadPackages("data/pak.csv");
//	loadConnections("data/cnx.csv");

}

//MÉTODOS DE CARGA------------------------------------------------------------------------------------------------
//Cargar conexiones
void Principal::loadConnections(char* file){
	ifstream reader;
	string line;
	string ofi1, ofi2;
	Office offi1, offi2;
	long index1, index2;

	int found=0;
	std::vector<Office> v = offices.getVertexes();
	int cost, costemp;
	reader.open(file);
	if(reader.is_open()){
		getline(reader, line);
		try{
			while(!reader.eof()){
				getline(reader, ofi1,',');
				getline(reader, ofi2,',');
				getline(reader, line);
				cost=atoi(line.c_str());
				for(unsigned int i=0; i<v.size(); i++){
					if(comparecodes(ofi1.c_str(),v[i].getCode().c_str())){
						offi1=v.at(i); found++;
					}
					if(comparecodes(ofi2.c_str(),v[i].getCode().c_str())){
						offi2=v.at(i); found+=2;
					}
				}
				index1 = offices.getIndexOf(offi1);
				index2 = offices.getIndexOf(offi2);
				if(found==3){
					if(offices.edgeExist(index1, index2)){
						costemp=offices.getCost(index1, index2);
						if(cost<costemp){
							offices.deleteEdge(index1, index2);
							offices.insertEdge(index1, index2, cost);
						}
					}
					else{
						offices.insertEdge(index1, index2, cost);
					}
					cout<<("Se ha creado la conexión.\n");
				}
				found=0;
			}
		}
		catch(invalid_argument& e){

		}
	}
	else{
		cout<<"No se pudo abrir el archivo "<<file<<".\n";
	}
}

//Cargar las personas.
void Principal::loadPersons(char* file){
	//Check if the person exists
	bool exists = false;
	int total = 0;
	Person persona;
	ifstream reader;
	vector<Office> op = this->offices.getVertexes();
	reader.open(file);
	try{

		if(reader.is_open()){
			cout<<"Cargando personas....\n";
			string linea;
			getline(reader, linea);
			getline(reader, linea, ',');
			while(!reader.eof()){
				persona.setName(linea);
				//Apellidos
				getline(reader, linea, ',');
				persona.setLname(linea);
				//Cedula
				getline(reader, linea, ',');
				persona.setId(linea);
				//Direccion
				getline(reader, linea, ',');
				persona.setAddress(linea);
				//Ciudad
				getline(reader, linea, ',');
				persona.setCity(linea);
				

				//Region
				getline(reader, linea, ',');
				Region reg;
				for(unsigned int i=0;i<op.size();i++){
					if(op[i].getRegions().find(linea) != op[i].getRegions().end()){
						cout<<"XMEN: "<<linea<<"."<<endl;
						cout<<"XMEN: "<<op[i].getRegions()[linea].getName()<<"."<<endl;

						reg = op[i].getRegions().at(linea);
						exists = true;
						reg.showData();
						break;
					}
				}
				bool x2 = false;
				if(exists){
					persona.setRegion(reg);
					for(int i=0;i< (int) persons.size();i++){
						if(persona.getId().compare(persons[i].getId())==0){
							cout<<"La persona con documento "<<persona.getId()<<" ya existe."<<endl;
							x2 = true;
							break;
						}
					}
				}
				else{
					cout<<"La region "<<linea<<" no existe."<<endl;
				}

				//Telefono y fin del linea
				getline(reader, linea);
				persona.setPhone(linea);
				

				if(!x2){
					cout<<"\t\tCargado ID: "<<persona.getId()<<endl;
					persons.push_back(persona);
					total++;
				}
				else{
					cout<<"Persona no cargada"<<endl;
				}
				// Nombre
				getline(reader, linea, ',');
				exists = false;
			}
			reader.close();
			cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
			cout<<"Se leyeron los datos de "<<total<<" personas."<<endl;
		}
		else{
			cout<<"No se pudo abrir el archivo "<<file<<".\n";
		}
	}
	catch(invalid_argument& e){
		cout<<("Ocurrió un error mientras se leía el archivo, verifique que los datos están en el formato correcto. \n");
	}
}

//Cargar los paquetes.
void Principal::loadPackages(char* file){

	int existsperson = 0;
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
			// Sender
			getline(reader, sender, ',');
			// Destinatario
			getline(reader, receiver, ',');
			if(sender.compare(receiver) == 0){
				cout<<("El remitente no puede ser igual al destinatario. ");
				getline(reader, linea);
				remain=false;
			}
			if(remain){
				for(int i = 0;i< (int) persons.size() && remain;i++){
					if(sender.compare(persons[i].getId())==0){
						senderper=persons[i];
						existsperson++;
					}
					if(receiver.compare(persons[i].getId())==0){
						receiverper=persons[i];
						existsperson++;
					}
				}
				if(existsperson == 2 ){
					paquete.setSender(senderper);
					paquete.setReceiver(receiverper);
				}
				else{
					cout<<"Error. Uno o ambos numeros de identifiación no existen ";
					getline(reader, linea);
					remain=false;
				}
				existsperson=0;
			}//if remain
			if(remain){
				//Peso
				getline(reader, linea,',');
				paquete.setWeight(stof(linea));
				//Tipo
				getline(reader, linea,',');
				paquete.setType(linea);
				//Numero guia y fin de linea
				getline(reader, linea);
				paquete.setGuiden(linea);

				//Agregar a oficina
				Region inicial = paquete.getReceiver().getRegion();
				bool iceman = true;
				for(unsigned int i=0;i<offices.getVertexes().size();i++){
					if(offices.getVertexes()[i].getRegions().find(inicial.getCode()) != offices.getVertexes()[i].getRegions().end()){
						Office aux1 = offices.getVertexes()[i];
						aux1.addPackage(paquete);
						offices.getVertexes()[i] = aux1;
						iceman = false;
						total++;
						break;
					}
				}

				if(iceman)
					cout<<("Error desconcocido. ");
			}//if remain	
			else{
				cout<<("El paquete no se agregó.\n");
			}
			remain=true;
		}//while !reader.eof()
		cout<<"Se agregaron "<<total<<" paquetes.\n";
	}//if reader.is_open()
	else{
		cout<<"No se pudo abrir el archivo "<<file<<".\n";
	}
	reader.close();
}

//Cargar las oficinas.
void Principal::loadOffices(char* file){
	int total = 0;
	//Si el id ya existe.
	bool exists = false;


	ifstream reader;
	reader.open(file);
	if(reader.is_open()){
		cout<<"Cargando oficinas...\n";
		string line="";
		getline(reader,line);	//Se omite la cabecera del archivo.
		Office actual;
		while(!reader.eof()){
			Office actual;
			getline(reader,line,',');
			actual.setCode(line);
			getline(reader,line,',');
			actual.setName(line);
			getline(reader,line,',');
			actual.setAddress(line);
			getline(reader,line);	
			actual.setCity(line);

			if(!offices.getVertexes().empty()){
				//Se guardan temporalmente las oficinas para verificar si la que se intenta cargar ya existe.
				std::vector<Office> v = offices.getVertexes();
				for(unsigned int i=0; i<v.size();i++){
					if(v.at(i).getCode().compare(actual.getCode()) == 0){
						exists=true;
					}
				}
			}
			else{
				exists=false;
			}
			//Si la oficina no existe entonces se agrega en el grafo.
			if(!exists){
				total++;
				offices.insertVertex(actual);
				cout<<"Se cargó la oficina "<<actual.getCode()<<endl;
			}
			else{
				cout<<("Ya existe una oficina con ese número de identificación.\n");
			}
			exists=false;
		}
		cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
		cout<<"Se cargaron "<<total<<" Oficinas"<<endl;
		reader.close();
	}
	else{
		cout<<"No se pudo abrir el archivo "<<file<<".\n";
	}
}

//Cargar las regiones.
void Principal::loadRegions(char* file){
	//Si el id ya existe.
	bool existsregion = false;
	bool existsoffice=false;
	//Se guardan temporalmente las oficinas para verificar si la que se intenta cargar ya existe.
	std::vector<Office> v = offices.getVertexes();
	Office* office;
	Region tempregion;
	int total=0;
	ifstream reader;
	reader.open(file);
	if(reader.is_open()){
		cout<<"Cargando regiones...\n";
		string line="";
		map<string, Region> temp;
		unsigned int i=0;
		getline(reader,line);	//Se omite la cabecera del archivo.
		while(!reader.eof()){
			v = offices.getVertexes();
			Region actual;
			getline(reader,line,',');
			actual.setCode(line);
			getline(reader,line,',');
			actual.setName(line);
			getline(reader,line, ',');
			for(i=0; i<v.size(); i++){
				if(line.compare(v[i].getCode()) == 0 ){
					office = &offices.getVertexes()[i];
					existsoffice=true;
					break;
				}
			}
			getline(reader,line);
			int distance = atoi(line.c_str());
			if(existsoffice){
				temp=office->getRegions();
				if(office->getRegions().size()!=0){
					if( office->existsRegion(actual) ){
						cout<<"Se intentó cargar una región con un código que ya existe."<<endl;
						existsregion=true;
					}
				}
				if(!existsregion){
					actual.setDistanceUp(distance);
					office->addRegion(actual);
					cout<<"Se cargó la región "<<actual.getCode()<<endl;
					total++;
				}
			}
			else{
				cout<<"La oficina que se intenta relacionar no existe.\n";
			}
			existsregion=false;
			existsoffice=false;
		}

		cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
		cout<<"Se cargaron "<<total<<" regiones"<<endl;
		reader.close();
	}
	else{
		cout<<"No se pudo abrir el archivo "<<file<<".\n";
	}
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
		for(unsigned int i=0; i<v.size();i++){
			if(v.at(i).getCode().compare(aux) ==0 ){
				cout<<("Ya existe una oficina con ese código.\n");
				exists=true;
				break;
			}
		}
		cont++;
		if(cont==5) {cout<<("Ha superado el límite máximo de intentos.\n"); break;}
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
		cout<<("La oficina no se agregó.\n");
	}
	exists=false;
}

//Registrar los paquetes
void Principal::regPackages(){
	cout<<"Estamos registrando Packages\n";
	bool existsreceiver=false;
	bool existssender=false;

	string receivertemp, sendertemp;
	int weight;
	string temp;
	Region region;
	Package paquete;
	int cont = 0;

	do{
		if(cont>1){
			cout<<("Intente con un número de identificación válido.\n");
		}
		if(!existssender){
			cout<<"Identificador del remitente: \n >";
			cin>>receivertemp;
		}
		if(!existsreceiver){
			cout<<"Identificador del destinatario: \n >";
			cin>>sendertemp;
		}
		for(unsigned int i = 0;i<persons.size();i++){
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

	cont = 0;
	Region inicial = paquete.getReceiver().getRegion();
	bool iceman = true;
	for(unsigned int i=0;i<offices.getVertexes().size();i++){
		if(offices.getVertexes()[i].getRegions().find(inicial.getCode()) != offices.getVertexes()[i].getRegions().end()){
			Office aux1 = offices.getVertexes()[i];
			aux1.addPackage(paquete);
			offices.getVertexes()[i] = aux1;
			iceman = false;
			cout<<"Se cargó la información así: \n";
			paquete.showData();
			break;
		}
	}

	if(iceman)
		cout<<"Error desconcocido. \n";

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
		for(unsigned int i=0; i < persons.size();i++){
			if(persona.getId().compare(persons[i].getId())==0){
				cout<<"La persona con el id"<<persona.getId()<<"ya está registrada.\n"<<endl;
				existsperson=true;
				break;
			}
		}
		if(cont==5){cout<<("Ha superado el límite máximo de intentos.\n"); break;}
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
		cout<<"Código de región: \n >";
		getline(cin, aux);

		bool carga = false;
		persona.setPhone(aux);
		vector<Office> op = offices.getVertexes();
		Region reg;
		for(unsigned int i=0;i<op.size();i++){
			if(op[i].getRegions().find(aux) != op[i].getRegions().end()){
				reg = op[i].getRegions()[aux];
				carga = true;
				break;
			}
		}
		if(carga){
			persons.push_back(persona);
			cout<<"La información ha sido cargada exitosamente así:"<<endl;
			persona.showData();
		}
		else{
			cout<<"La persona no se agregó.\n";
		}
	}
	else{
		cout<<"La persona no se agregó.\n";
	}

}

//Registrar regiones.
void Principal::regRegions(){
	cout<<"Registro de Regiones:\n";

	Region region;  
	std::vector<Office> v= offices.getVertexes();
	Office* office;
	string codeoffice;
	int cont = 0;
	bool existsoffice = false;
	bool existsregion=false;

	string aux;

	while(!existsoffice){
		cout<<("Código de la oficina:\n>");
		getline(cin, codeoffice);
		for(unsigned int i=0; i<v.size();i++){
			if(codeoffice.compare(v.at(i).getCode()) == 0){ office=&v[i];	existsoffice=true;	break;}
		}
		if(!existsoffice)	cout<<"El código de oficina no existe, intente nuevamente \n>";

		cont ++;
		if(cont == 5){cout<<("Ha superado el número máximo de intentos.\n"); break;}
	}

	if(existsoffice){
		cout<<"Nombre de la región:\n>";
		getline(cin, aux);
		region.setName(aux);

		do{
			cout<<"Código de la región:\n>";
			getline(cin, aux);
			region.setCode(aux);
			existsregion=office->existsRegion(region);
			if(existsregion) cout<<"Ya existe una región con el código "<<region.getCode()<<"."<<endl;			
			cont ++;
			//Se limitan el número de intentos
			if(cont == 5){cout<<("Ha superado el número máximo de intentos.\n"); break;}
		}while(existsregion);
	}

	if(!existsregion){
		int distance;
		cout<<"Distancia a la oficina principal:\n>"<<endl;
		cin>>distance;
		region.setDistanceUp(distance);
		office->addRegion(region);
		cout<<"Se cargó la región "<<region.getCode()<<endl;
	}

}

//MÉTODOS DE VISUALIZACIÓN----------------------------------------------------------------------------------------

//Mostrar oficinas.
void Principal::showOffices(){
	for(unsigned int i=0;i<offices.getVertexes().size();i++){
		offices.getVertexes()[i].showData();
	}
}

//Mostrar paquetes.
void Principal::showPackages(char* codeOf){
	for(unsigned int i=0;i<offices.getVertexes().size();i++){
		if(offices.getVertexes()[i].getCode().compare(codeOf) == 0){
			for(unsigned int k=0;k<offices.getVertexes()[i].getPackages().size();k++){
				offices.getVertexes()[i].getPackages()[k].showData();
			}
		}
	}
}

//Mostrar personas.
void Principal::showPersons(){
	for(unsigned int i = 0;i<persons.size();i++){
		persons[i].showData();
	}
}

//Mostrar regiones.
void Principal::showRegions(){
	vector<Region> full;
	map<string,Region>aux;
	for(unsigned int i=0;i<offices.getVertexes().size();i++){
		aux = offices.getVertexes()[i].getRegions();
		map<string,Region>::iterator j = aux.begin();
		while(j != aux.end()){
			full.push_back(j->second);
			j++;
		}
	}
	for(unsigned int i=0;i<full.size();i++){
		full[i].showData();
	}
}

//MÉTODOS EXTRA
void Principal::countPackages(){
	vector<Region> full;
	vector<Package> paks;
	map<string,Region>aux;
	for(unsigned int i=0;i<offices.getVertexes().size();i++){
		aux = offices.getVertexes()[i].getRegions();
		for(unsigned int j=0;j<offices.getVertexes().size();j++){
			paks.push_back(offices.getVertexes()[i].getPackages()[j]);
		}
		map<string,Region>::iterator j = aux.begin();
		while(j != aux.end()){
			full.push_back(j->second);
			j++;
		}
	}
	for(unsigned int i=0;i<full.size();i++){
		int cont = 0;
		full[i].showData();
		for(unsigned int j=0;j<paks.size();j++){
			if(paks[j].isActive()){
				if(full[i].getCode() == paks[j].getSender().getRegion().getCode()){
					cont++;
				}
			}
			else{
				if(full[i].getCode() == paks[j].getReceiver().getRegion().getCode()){
					cont++;
				}
			}
		}
		cout<<"Hay "<<cont<<" paquetes en la region de reparto "<<full[i].getCode();

	}
}

void Principal::sendPackages(char* codeOf){
	cout<<"Funcion comentada por el bien común\n";
	/*
	 * Hay que:
	 * Buscar la oficina
	 * Poner todos los paquetes con active = true
	 * quitarlos y ponerlos en la nueva oficina
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

bool Principal::comparecodes(const char* g, const char* f){
	bool t=true;
	if(strlen(g) != strlen(f)){
		t=false;
	}
	else{
		for(unsigned int i=0; i<strlen(g);i++){
			if(g[i] != f[i]){
				t=false;
			}
		}
	}
	return t;
}

