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
		road = new char[30]; read= new char[6]; file = new char[24];
		cout<<"Bienvenido al sistema de reparto. Puede ver la lista de comandos con el comando 'ayuda'";
		cout<<"\n$";
		cin.getline(road,30,'\n'); string r(road); string f(road);r=r.substr(0,5);
		if(f.length()>6){f=f.substr(6,23); 		strcpy(file,f.c_str());}

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
			case str2int("mosre"):{
				printf("Mostrando regiones\n");
				principal.showregions();
				break;
			}
			case str2int("carre"):{
				printf("Cargando regiones\n");
				principal.loadregions(file);
				break;
			}
			case str2int("carof"):{
				break;
			}
			case str2int("carpe"):{
				principal.setpersons(principal.loadpersons(file, principal.getpersons()));
				break;
			}
			case str2int("carpa"):{
				principal.setoffices(principal.loadpackages(file, principal.getoffices(),principal.getpersons()));
				break;
			}
			case str2int("regpe"):{
				principal.setpersons(principal.regpersons(principal.getpersons()));
				break;
			}
			case str2int("regpa"):{
				principal.setoffices(principal.regpackages(principal.getoffices(),principal.getpersons()));
				break;
			}
			case str2int("cntpa"):{
				principal.countpackages(principal.getoffices());
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
	cout<<"carre [nombre_de_archivo]\t Agrega las regiones al sistema.\n";
	cout<<"carof [nombre_de_archivo]\t Agrega las oficinas al sistema.\n";
	cout<<"regpe 			\t Registra personas en el sistema.\n";
	cout<<"regpa 			\t Registra paquetes en el sistema.\n";
	cout<<"cntpa 			\t Cuenta los paquetes.\n";
	cout<<"salir 			\t Salir.\n";
}
