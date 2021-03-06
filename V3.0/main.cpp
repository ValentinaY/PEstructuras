#include <iostream>
#include <string>
#include <cstring>

#include "Principal.h"

using namespace std;

//No sé dónde debería ir este método, en una clase Utils no habrían muchos entonces no vale la pena compilar tantos archivos.
constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

void showhelp();
int main(){
	Principal principal;
	//El arreglo con el comando es read y el arreglo con el archivo es file.
	char *road;
	char *read;
	char *file;	
	bool finished=false;
	//Esto puede funcionar con un break. Pero, sería una mala práctica, etc. y en el taller de anagramas se usaba así.22

	while(!finished){
		bool go = false;
		road = new char[106]; read= new char[6]; file = new char[100];
		cout<<"Bienvenido al sistema de reparto. Puede ver la lista de comandos con el comando 'ayuda'";
		cout<<"\n$";
		cin.getline(road,30,'\n');
		string r(road);
		string f(road);
		r=r.substr(0,5);
		if(f.length()>6){
			f=f.substr(6,23);
			strcpy(file,f.c_str());
		}
		else{
			go = true;
		}

		strcpy(read,r.c_str());
		/*str2int convierte strings a enteros porque no es posible compararlas directamente, lo dice  0x499602D2 :) y el método está en: 
		 https://stackoverflow.com/questions/16388510/evaluate-a-string-with-a-switch-in-c.22
		 */

		//Se evalua el caso según el comando.
		switch(str2int(read)){
		case str2int("ayuda"):{
			showhelp();
			break;
		}

		case str2int("carpe"):{
			principal.loadPersons(file);
			break;
		}
		case str2int("carpa"):{
			principal.loadPackages(file);
			break;
		}
		case str2int("carof"):{
			principal.loadOffices(file);
			break;
		}
		case str2int("carre"):{
			principal.loadRegions(file);
			break;
		}
		case str2int("carco"):{
			principal.loadConnections(file);
			break;
		}

		case str2int("regpe"):{
			principal.regPersons();
			break;
		}
		case str2int("regpa"):{
			principal.regPackages();
			break;
		}
		case str2int("regof"):{
			principal.regOffices();
			break;
		}
		case str2int("regre"):{
			principal.regRegions();
			break;
		}
		case str2int("cntpa"):{
			principal.countPackages();
			break;
		}
		case str2int("entpa"):{
			principal.sendPackages(file);
			break;
		}
		case str2int("rutre"):{
			cout<<"Comando fallido, contacte un administrador del sistema\n";
//			principal.sendRoute(file);
			break;
		}
		case str2int("mospe"):{
			principal.showPersons();
			break;
		}
		case str2int("mospa"):{
			if(go)
				principal.showPackages();
			else
				principal.showPackages(file);
			break;
		}
		case str2int("mosof"):{
			principal.showOffices();
			break;
		}
		case str2int("mosre"):{
			principal.showRegions();
			break;
		}

		case str2int("salir"):{
			finished=true;
			break;
		}
		case str2int("fastb"):{
			principal.fastboot();
			break;
		}
		default:{
			cout<<"El comando ingresado es desconocido. Escriba 'ayuda' para ver la lista de comandos.\n";
			break;
		}
		}
	}

	return 0;
}

void showhelp(){
	cout<<"Bienvenido al sistema de ayuda.\n";
	cout<<">>> Carga por archivos:\n";
	cout<<" carpe [nombre_de_archivo]	\t Agrega las personas al sistema.\n";
	cout<<" carpa [nombre_de_archivo]	\t Agrega los paquetes al sistema.\n";
	cout<<" carof [nombre_de_archivo]	\t Agrega las oficinas al sistema.\n";
	cout<<" carre [nombre_de_archivo]	\t Agrega las regiones al sistema.\n";
	cout<<" carco [nombre_de_archivo]	\t Agrega conexiones al sistema.\n";

	cout<<">>> Carga por registro:\n";
	cout<<" regpe	\t Registra personas en el sistema.\n";
	cout<<" regpa	\t Registra paquetes en el sistema.\n";
	cout<<" regof	\t Registra oficinas en el sistema.\n";
	cout<<" regre	\t Registra regiones en el sistema.\n";

	cout<<">>> Manejo de paquetes:\n";
	cout<<" cntpa	\t Cuenta todos los paquetes sin entregar.\n";
	cout<<" entpa [codigo_oficina]	\t Entrega los paquetes de una oficina.\n";
	cout<<" rutre [cod_ofi_origen] [cod_ofi_destino] Muestra la ruta más corta entre las dos oficinas.\n";

	cout<<">>> Ver datos en sistema:\n";
	cout<<" mospe	\t Muestra las personas en el sistema.\n";
	cout<<" mospa [codigo_oficina]	\t Muestra los paquetes sin entregar en una oficina.\n";
	cout<<" mosof 	\t Muestra las oficinas.\n";
	cout<<" mosre 	\t Muestra las regiones.\n";

	cout<<"salir 	\t Salir del sistema.\n";
}

// TODO: De preferencia arreglar el registrar region
