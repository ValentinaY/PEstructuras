#include "Principal.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;


/* comando: registrarOficina
posibles salidas en pantalla:
(Oficina ya existe) La oficina con identificacion ofi_id ya se encuentra registrada en el
sistema.
(Resultado exitoso) La oficina con identificacion ofi_id ha sido registrada exitosamente.
descripción: Permite insertar en el sistema la información asociada de una oficina. La información básica
de la oficina (código de identificación, nombre, dirección, ciudad) debe solicitarse al usuario por teclado y
validarse adecuadamente */
void Principal::regOffice(){

	cout<<"Registro de oficinas:\n";

	Office newOffice;
	string aux;
	cout<<"Nombre de la oficina: ";
	cin.ignore();
	getline(cin, aux);
	newOffice.setName(aux);
	cout<<"Código: ";
	getline(cin, aux);
	newOffice.setCode(aux);
	cout<<"Dirección: ";
	cin>>aux;
	newOffice.setAddress(aux);
	cout<<"Ciudad: ";
	getline(cin,aux);
	newOffice.setCity(aux);

	for(list<Office>::iterator it = offices.begin(); it != offices.end(); it++){
		if(newOffice.getCode().compare((*it).getCode())==0){
			cout<<"Error :"<<(*it).getCode()<<endl;
			cout<<"La oficina con ese código ya existe."<<endl;
			break;
		}
	}

	offices.push_front(newOffice);

	cout<<"La información ha sido cargada exitosamente así:"<<endl;
	newOffice.showData();
}
/*
• comando: registrarRegion
posibles salidas en pantalla:
(Región ya existe) La region con codigo reg_id ya se encuentra registrada en el sistema.
(Resultado exitoso) La region con codigo reg_id ha sido registrada exitosamente.
descripción: Permite insertar en el sistema la información asociada de una región, e interconectarla con la
oficina respectiva. La información básica de la región (nombre, código, identificación de la oficina a la que
pertenece) debe solicitarse al usuario por teclado y validarse adecuadamente.
 */
void Principal::regRegion(){
	cout<<"Registro de Regiones:\n";

	Region newRegion;
	Office* office = NULL;
	string aux;
	cin.ignore();
	// While, erificacion a max 3
	int cont = 0;
	while(office == NULL){
		cout<<"Código de la Oficina: ";
		getline(cin, aux);
		newRegion.setCode(aux);
		for(list<Region>::iterator it = offices.begin(); it != offices.end(); it++){
			if(aux.compare((*it).getCode())==0){
				office = it;
				break;
			}
		}
		if(office == NULL)
			cout<<"El código de oficina no existe, intente nuevamente \n";

		if(cont >= 3)
			return;

		cont ++;
	}

	cout<<"Nombre de la región: ";
	getline(cin, aux);
	newRegion.setName(aux);
	cout<<"Código: ";
	getline(cin, aux);
	newRegion.setCode(aux);

	for(list<Region>::iterator it = office->getRegions().begin(); it != office->getRegions().end(); it++){
		if(newRegion.getCode().compare((*it).getCode())==0){
			cout<<"Error :"<<(*it).getCode()<<endl;
			cout<<"La región con ese código ya existe."<<endl;
			cout<<"La información no fue cargada"<<endl;
			return;
		}
	}

	office->addRegion(newRegion);
	cout<<"La información ha sido cargada exitosamente así:"<<endl;
	newRegion.showData();
}


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
		regions=(*ito).getRegions();
		for(itr==regions.begin();itr!=regions.end();itr++){
			printf("%s\t",(*itr).getCode());
			printf("%s\n",(*itr).getName());
		}
	}
}

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

void Principal::loadpersons(char* archivo, list<Person> personas){

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
				return personas;
			}
			persona.setLname(linea);

			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
				return personas;
			}
			persona.setId(linea);

			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
				return personas;
			}
			persona.setAddress(linea);

			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
				return personas;
			}
			persona.setCity(linea);

			getline(lector, linea);
			persona.setPhone(linea);

			for(list<Person>::iterator it = personas.begin(); it != personas.end(); it++){
				if(persona.getId().compare((*it).getId())==0){	
					cout<<"La persona con documento "<<(*it).getId()<<" ya existe."<<endl;
					si = true;
					break;
				}
			}
			if(!si){
				persona.showData();
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

	for(list<Person>::iterator it = personas.begin(); it != personas.end(); it++){
		cout<<(*it).getId()<<"::"<<endl;
	}

	for(list<Person>::iterator it = personas.begin(); it != personas.end(); it++){
		if(persona.getId().compare((*it).getId())==0){	
			cout<<(*it).getId()<<endl;
			cout<<"La persona ya existe."<<endl;
			break;
		}
	}	
	personas.push_front(persona);

	cout<<"La información ha sido cargada exitosamente así:"<<endl;

	persona.showData();
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
				if(linea.compare((*it).getId())==0){
					persona = (*it);
					paquete.setSender(persona);
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
					paquete.setReceiver(persona);
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
			oficina.setcity(linea);

			getline(entrada, linea, ',');
			region.setcode(linea);
			getline(entrada, linea);
			region.setName(linea);
			getline(entrada, linea, ',');

			bool ya = false;
			paquetes.push_back(paquete);

			cout<<"Leido el Package con número guía: "<<paquete.getGuiden()<<endl;
			for(list<Office>::iterator ito = oficinas.begin(); ito != oficinas.end() || ya; ito++){
				if(oficina.getCode().compare((*ito).getcode())==0){
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
				paquete.setSender(persona);
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
				paquete.setReceiver(persona);
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

void Principal::addregion(Region region, string ocode){
	list<Office>::iterator it;
	list<Office> noficinas= Principal::offices;
	if(!noficinas.empty()){
		for(it==noficinas.begin(); it!=noficinas.end();it++){
			if((*it).getCode()==ocode){
				(*it).addRegion(region);
			}
		}
	}
	else{
		printf("Error al agregar la región con código %s.\n",region.getCode());
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
