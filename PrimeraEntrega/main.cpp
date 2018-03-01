#include <iostream>
#include "Principal.h"
#include <string>
#include <cstring>
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
		road = new char[30]; read= new char[6]; file = new char[24];
		cout<<"Bienvenido al sistema de reparto. Puede ver la lista de comandos con el comando 'ayuda'";
		cout<<"\n$";
		cin.getline(road,30,'\n'); string r(road); string f(road);r=r.substr(0,5);
		if(f.length()>6){f=f.substr(6,23); 		strcpy(file,f.c_str());}

		strcpy(read,r.c_str());
		/*str2int convierte strings a enteros porque no es posible compararlas directamente, lo dice  0x499602D2 :) y el método está en: 
		 https://stackoverflow.com/questions/16388510/evaluate-a-string-with-a-switch-in-c.22
		 */

		//Cargamos las regiones (las quemamos) :).
		principal.loadRegions();

		//Se evalua el caso según el comando.
		switch(str2int(read)){
			case str2int("ayuda"):{
				showhelp();
				break;
			}
			case str2int("carpe"):{
				principal.setPersonas(principal.loadPersons(file, principal.getPersonas()));
				break;
			}
			case str2int("carpa"):{
				principal.loadPackages();
				break;
			}
			case str2int("regpe"):{
				principal.setPersonas(principal.regPersons(principal.getPersonas()));
				break;
			}
			case str2int("regpa"):{
				principal.regPackages();
				break;
			}
			case str2int("cntpa"):{
				principal.countPackages();
				break;
			}
			case str2int("salir"):{
				finished=true;
				break;
			} 
			default:{
				cout<<"El comando ingresado es desconocido. Escriba 'ayuda' para ver la lista de comandos.";
				break;
			}
		}
	}

	return 0;
}

void showhelp(){
	cout<<"Bienvenido al sistema de ayuda.\n";
	cout<<"carpe [nombre_de_archivo]\t Agrega las personas al sistema.\n";
	cout<<"carpa [nombre_de_archivo]\t Agrega los paquetes al sistema.\n";
	cout<<"regpe 			\t Registra personas en el sistema.\n";
	cout<<"regpa 			\t Registra paquetes en el sistema.\n";
	cout<<"cntpa 			\t Cuenta los paquetes.\n";
	cout<<"salir 			\t Salir.\n";
}
