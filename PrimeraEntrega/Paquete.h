#ifndef Paquete_H
#define Paquete_H

#include <string>
#include "Persona.h"
using namespace std;
class Paquete{
private:
	Persona remitente;
	Persona destinatario;
	float peso;
	string tipo;
	string numGuia;
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

	string mostrarDatos();

};

#endif
