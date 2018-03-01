#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Principal.h"

using namespace std;


void Principal::setPersonas(list<Persona> x){
	personas = x;
}
void Principal::setOficinas(list<Oficina> x){
	oficinas = x;
}

list<Persona> Principal::loadPersons(char* archivo, list<Persona> personas){
	
	bool si = false;
	Persona persona;
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
			persona.setNombre(linea);
			
			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
				return personas;
			}
			persona.setApellido(linea);
			
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
			persona.setDireccion(linea);
			
			getline(lector, linea, ',');
			if(lector.eof()){
				cout<<"El archivo "<<archivo<<" no contiene información válida."<<endl;
				return personas;
			}
			persona.setCiudad(linea);
			
			getline(lector, linea);
			persona.setTelefono(linea);
			
			for(list<Persona>::iterator it = personas.begin(); it != personas.end(); it++){
				if(persona.getId().compare((*it).getId())==0){	
					cout<<"La persona con documento "<<(*it).getId()<<" ya existe."<<endl;
					si = true;
					break;
				}
			}
			if(!si){
				persona.mostrarDatos();
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

list<Persona> Principal::regPersons(list<Persona> personas){
	cout<<"Estamos registrando personas\n";
	
	Persona persona;
	string aux;
	cout<<"Nombre de la persona: ";
	cin.ignore();
	getline(cin, aux);
	persona.setNombre(aux);
	cout<<"Apellidos de la persona: ";
	getline(cin, aux);
	persona.setApellido(aux);
	cout<<"Numero de identificacion: ";
	cin>>aux;
	persona.setId(aux);
	cout<<"Ciudad: ";
	cin>>aux;
	persona.setCiudad(aux);
	cout<<"Direccion: ";
	getline(cin, aux);
	getline(cin, aux);
	persona.setDireccion(aux);
	cout<<"Telefono: ";
	cin>>aux;
	persona.setTelefono(aux);
	
	for(list<Persona>::iterator it = personas.begin(); it != personas.end(); it++){
		cout<<(*it).getId()<<"::"<<endl;
	}
	
	for(list<Persona>::iterator it = personas.begin(); it != personas.end(); it++){
		if(persona.getId().compare((*it).getId())==0){	
			cout<<(*it).getId()<<endl;
			cout<<"La persona ya existe."<<endl;
			break;
		}
	}	
	personas.push_front(persona);
	
	cout<<"La información ha sido cargada exitosamente así:"<<endl;
	
	persona.mostrarDatos();
	return personas;
	
}


list<Oficina> Principal::loadPackages(char* archivo, list<Oficina> oficinas, list<Persona> personas){
	cout<<"Estamos cargando paquetes\n";
	bool esta = false, saltar = false;

	ifstream entrada;
	string linea;
	entrada.open(archivo);
	if(entrada.is_open()){

		getline(entrada, linea);	
		
		getline(entrada, linea, ',');	
		while(!entrada.eof()){	
			saltar = false;
			Paquete paquete;
			Persona persona;
			Region region;
			list <Region> regiones;
			list <Paquete> paquetes;
			Oficina oficina;
			for(list<Persona>::iterator it = personas.begin(); it != personas.end(); it++){
				if(linea.compare((*it).getId())==0){
					persona = (*it);
					paquete.setRemitente(persona);
					esta = true;
					break;
				}
			}
			if(esta == false){
				cout<<"Esa persona no se encuentra en nuestro registro\n";
			}
				esta = false;

				getline(entrada, linea, ',');
				for(list<Persona>::iterator it = personas.begin(); it != personas.end(); it++){
					if(linea.compare((*it).getId())==0){
						persona = *it;
						paquete.setDestinatario(persona);
						esta = true;
						break;
					}
				}
				if(esta == false){
					cout<<"Esa persona no se encuentra en nuestro registro\n";
				}

				
				getline(entrada, linea, ',');
				paquete.setPeso(toFloat(linea)); //función de string a float
				
				getline(entrada, linea, ',');
				paquete.setTipo(linea);

				getline(entrada, linea, ',');
				paquete.setNumGuia(linea);

				//Si no existe of
				getline(entrada, linea, ',');
				oficina.setCode(linea);

				getline(entrada, linea, ',');
				oficina.setNombre(linea);

				getline(entrada, linea, ',');
				oficina.setDireccion(linea);

				getline(entrada, linea, ',');
				oficina.setCiudad(linea);

				getline(entrada, linea, ',');
				region.setCodigo(linea);
				getline(entrada, linea);
				region.setNombre(linea);
				getline(entrada, linea, ',');

				bool ya = false;
				paquetes.push_back(paquete);

				cout<<"Leido el paquete con número guía: "<<paquete.getNumGuia()<<endl;
				for(list<Oficina>::iterator ito = oficinas.begin(); ito != oficinas.end() || ya; ito++){
					if(oficina.getCode().compare((*ito).getCode())==0){
						regiones = (*ito).getRegiones();
						oficina =(*ito);
						for(list<Region>::iterator itr = regiones.begin();itr != regiones.end() || ya; itr++){
							if((*itr).getCodigo().compare(region.getCodigo())==0){
								region = (*itr);
								region.addPaquetes(paquetes);

					region.setOficina(&oficina);
					paquete.setRegion(&region);
					regiones.push_back(region);
					oficina.setRegiones(regiones);
					oficinas.push_back(oficina);
								ya = true;
							}
						}
					}
				}

				
				if(!ya){
					paquete.setRegion(&region);
					region.setOficina(&oficina);
					region.setPaquetes(paquetes);
					regiones.push_back(region);
					oficina.setRegiones(regiones);
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


list<Oficina> Principal::regPackages(list<Oficina> oficinas, list<Persona> personas){
	cout<<"Estamos registrando paquetes\n";

	string temp, tempAux;
	Oficina oficina;
	Region region;
	Persona persona;
	Paquete paquete;
	int contador = 0;
	float aux;
	bool esta = false;

	do{
		cout<<"Identificador del remitente\n";
		cin>>temp;
		for(list<Persona>::iterator it = personas.begin(); it != personas.end(); it++){
			if(temp.compare((*it).getId())==0){
				persona = *it;
				paquete.setRemitente(persona);
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
		for(list<Persona>::iterator it = personas.begin(); it != personas.end(); it++){
			if(temp.compare((*it).getId())==0){
				persona = *it;
				paquete.setDestinatario(persona);
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
	paquete.setPeso(aux);
	cout<<"Tipo de contenido: \n";
	getline(cin, temp);
	getline(cin, temp);
	paquete.setTipo(temp);
	cout<<"Número de guia: \n";
	getline(cin, tempAux);
	paquete.setNumGuia(tempAux);

	cout<<"Código de oficina: \n";
	getline(cin, temp);
	for(list<Oficina>::iterator it = oficinas.begin(); it != oficinas.end() || esta; it++){
		if(temp.compare((*it).getCode())==0){
			esta = true;
			oficina = (*it);
		}
	}
	if(esta == false){
		oficina.setCode(temp);
		cout<<"Nombre de la oficina: \n";
		getline(cin, temp);
		oficina.setNombre(temp);
		cout<<"Direccion de la oficina: \n";
		getline(cin, temp);
		oficina.setDireccion(temp);
		cout<<"Ciudad de la oficina: \n";
		getline(cin, temp);
		oficina.setCiudad(temp);


		cout<<"Código de la región: \n";
		getline(cin, temp);
		region.setOficina(&oficina);
		region.setCodigo(temp);
		cout<<"Nombre de la Region: \n";
		getline(cin, temp);
		region.setNombre(temp);

		paquete.setRegion(&region);
		region.getPaquetes().push_back(paquete);
		oficina.getRegiones().push_back(region);
		oficinas.push_back(oficina);
		return oficinas;

	}

	esta = false;

	cout<<"Código de la región: \n";
	getline(cin, temp);
	for(list<Region>::iterator it = oficina.getRegiones().begin(); it != oficina.getRegiones().end() || esta; it++){
		if(temp.compare((*it).getCodigo()) == 0){
			esta = true;
			region = (*it);
		}
	}
	if(esta == false){
		region.setOficina(&oficina);
		region.setCodigo(temp);
		cout<<"Nombre de la Region: \n";
		getline(cin, temp);
		region.setNombre(temp);

		paquete.setRegion(&region);
		region.getPaquetes().push_back(paquete);
		oficina.getRegiones().push_back(region);
		oficinas.push_back(oficina);
		return oficinas;
	}

	for(list<Paquete>::iterator it = region.getPaquetes().begin(); it!= region.getPaquetes().end() || esta;it++){
		if(paquete.getNumGuia().compare((*it).getNumGuia()) == 0){
			cout<<"El paquete ya existe\n";
			return oficinas;
		}
	}

	paquete.setRegion(&region);
	region.setOficina(&oficina);

	list<Paquete> paquetes = region.getPaquetes();
	paquetes.push_back(paquete);
	region.setPaquetes(paquetes);

	list<Region> regiones = oficina.getRegiones();
	regiones.push_back(region);
	oficina.setRegiones(regiones);

	oficinas.push_back(oficina);
	return oficinas;

}


void Principal::countPackages(list<Oficina> oficinas){

	cout<<"Contando paquetes..."<<endl;	
	
	list<Region> regionesTotales;

	for(list<Oficina>::iterator ito = oficinas.begin(); ito != oficinas.end(); ito++){
		list<Region> regiones = (*ito).getRegiones();
		for(list<Region>::iterator itr = regiones.begin();itr != regiones.end(); itr++){
			cout<<"Hay "<<(*itr).getPaquetes().size()<<" paquetes por entregar en la region de reparto "<<(*itr).getNombre()<<endl;
		}
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