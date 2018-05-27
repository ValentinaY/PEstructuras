#include "Principal.h"
#include <iostream>
#include <fstream>
#include <string>
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

	bool esta = false, continuar;
	int total=0;

	ifstream entrada;
	string linea;
	entrada.open(file);
	if(entrada.is_open()){
		cout<<"Cargando paquetes...\n";
		getline(entrada, linea);

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

			/*if(continuar){

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
		cout<<"Se leyeron "<<leidos<<" paquetes."<<endl;*/
		}
	}
	else
		cout<<"Ocurrió un error al leer el archivo, verifique el nombre e intente nuevamente.\n";
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
					cout<<"Carganda oficina "<<actual.getCode()<<endl;
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
			/*Office temp=
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
					total++;
				}
			}*/
		}
	}
	cout<<"La información desde "<<file<<" ha sido cargada exitosamente."<<endl;
	cout<<"Se cargaron "<<total<<" regiones"<<endl;
	reader.close();
}

//MÉTODOS DE REGISTRO---------------------------------------------------------------------------------------------
//Registrar las oficinas.
void Principal::regOffices(){
	//Si el id ya existe.
	bool exists = false;
	//Se guardan temporalmente las oficinas para verificar si la que se intenta cargar ya existe.
	std::vector<Office> v = offices.getVertexes();
	
	//La oficina que se registrará.
	Office office;

	cout<<"Registro de oficinas:\n";
	string aux;
	cout<<"Nombre de la oficina: \n >";
	getline(cin, aux);
	office.setName(aux);
	cout<<"Código: \n >";
	getline(cin, aux);
	office.setCode(aux);
	cout<<"Dirección: \n >";
	cin>>aux;
	office.setAddress(aux);
	cout<<"Ciudad: \n >";
	cin>>aux;
	office.setCity(aux);

	//Se verifica si el id que se intenta registrar ya existe.
	for(int i=0; i<v.size();i++){
		if(v.at(i).getCode().compare(office.getCode())){
			exists=true;
		}
	}

	if(!exists){
		offices.insertVertex(office);
		return;
	}
	else{
		printf("Ya existe una oficina con el mismo código.\n");
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
				esta = true;
				break;
			}
		}
		if(esta == false){
			cout<<"Esta región no se encuentra en nuestro registro\n";
		}
		cont++;
		if(cont==5) {
			cout<<"Numero de intentos excedido.\n";
			return;
		}
	}while(esta ==  false);*/
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
	cout<<"Registro de personas\n";
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
			existsperson=true;
			break;
		}
	}
	if(!existsperson){
		persons.push_back(persona);
		cout<<"La información ha sido cargada exitosamente así:"<<endl;
		persona.showData();
	}
	else{
		printf("La persona ya existe.\n");
	}

}

//Registrar regiones.
void Principal::regRegions(){
	cout<<"Registro de Regiones:\n";

	Region newRegion;
	Office office;
	string aux;
	int cont = 0;
	bool find = true;
	while(find){
		if(cont >= 2)
			return;

		cout<<"Código de la Oficina: ";
		getline(cin, aux);
/*
		nodoOffice = offices.search(of);
		if(nodoOffice != NULL)
			find = false;
*/
		if(find)
			cout<<"El código de oficina no existe, intente nuevamente \n";
		cont ++;
	}

	//office = &(nodoOffice->getData());

	cout<<"Nombre de la región: ";
	getline(cin, aux);
	newRegion.setName(aux);
	cout<<"Código: ";
	cin>> aux;
	newRegion.setCode(aux);

	vector<Region> regs = office.getRegions().getAllData();
	for(unsigned int i = 0; i<regs.size(); i++){
		if(newRegion.getCode().compare(regs[i].getCode())==0){
			cout<<"Error :"<<regs[i].getCode()<<endl;
			cout<<"La región con ese código ya existe, la información no fue cargada"<<endl;
			return;
		}
	}

	//office.addRegion(newRegion);
	cout<<endl<<"La información ha sido cargada exitosamente así:"<<endl;
	//cout<<"Codigo Oficina: "<<office->getCode()<<endl;
	newRegion.showData();
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
