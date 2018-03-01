#ifndef Paquete_H
#define Paquete_H

#include <string>
#include <iostream>
#include "Persona.h"
using namespace std;

class Region;

class Paquete{
private:
	Persona remitente;
	Persona destinatario;
	float peso;
	string tipo;
	string numGuia;
	Region* region;

public:
	Persona getRemitente(){
		return remitente;
	}
	void setRemitente(Persona nsender);
	
	Persona getDestinatario(){
		return destinatario;
	}
	void setDestinatario(Persona nrecipient);
	
	float getPeso(){
		return peso;
	}
	void setPeso(float s);
	
	string getTipo(){
		return tipo;
	}
	void setTipo(string ntipo);
	
	string getNumGuia(){
		return numGuia;
	}
	void setNumGuia(string nguia);
	
	Region* getRegion(){
		return region;
	}

	void setRegion(Region* reg);

	void mostrarDatos(){
		cout<<"Remitente: "<<remitente.getNombre()<<endl;
		cout<<"Destinatario: "<<destinatario.getNombre()<<endl;
		cout<<"Peso: "<<peso<<endl;
		cout<<"Tipo: "<<tipo<<endl;
		cout<<"Número Guía: "<<numGuia<<endl;
	}

};

#endif
