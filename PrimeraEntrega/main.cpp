#include <iostream>
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
	char read[30];
	
	bool finished=false;
	//Esto puede funcionar con un break. Pero, sería una mala práctica, etc. y en el taller de anagramas se usaba así.22
	while(!finished){
		printf("%s\n","Bienvenido al sistema de reparto. Puede ver la lista de comandos con el comando 'ayuda'");
		printf("%c",'$');
		scanf("%s",read);

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
				principal.loadPersons();
				break;
			}
			case str2int("carpa"):{
				principal.loadPackages();
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
			case str2int("cntpa"):{
				principal.countPackages();
				break;
			}
			case str2int("salir"):{
				finished=true;
				break;
			} 
			default:{
				printf("%s\n","El comando ingresado es desconocido. Escriba 'ayuda' para ver la lista de comandos.");
				break;
			}
		}
	}

	return 0;
}

void showhelp(){
	printf("Bienvenido al sistema de ayuda.\n");
	printf("carpe [nombre_de_archivo]\t Agrega las personas al sistema.\n");
	printf("carpa [nombre_de_archivo]\t Agrega los paquetes al sistema.\n");
	printf("regpe 			\t Registra personas en el sistema.\n");
	printf("regpa 			\t Registra paquetes en el sistema.\n");
	printf("cntpa 			\t Cuenta los paquetes.\n");
	printf("salir 			\t Salir.\n");
}