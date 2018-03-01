#ifndef Persona_H
#define Persona_H

#include <string>
#include <iostream>

using namespace std;

class Persona{
private:
	string nombre;
	string apellido;
	string id;
	string direccion;
	string ciudad;
	string telefono;
public:
	/* Los getters no se implementan aparte http://www.learncpp.com/cpp-tutorial/89-class-code-and-header-files/
	*/
	string getNombre(){
		return nombre;
	}
	void setNombre(string nname);
	string getId(){
		return id;
	}string getApellido(){
		return apellido;
	}
	void setApellido(string nname);
	
	void setId(string nidnum);
	string getDireccion(){
		return direccion;
	}
	void setDireccion(string naddress);
	string getCiudad(){
		return ciudad;
	}
	void setCiudad(string ncity);
	string getTelefono(){
		return telefono;
	}
	void setTelefono(string nphone);
	void mostrarDatos(){
		cout<<"Nombre: "<<nombre<<endl;
		cout<<"Apellido: "<<apellido<<endl;
		cout<<"Identificación: "<<id<<endl;
		cout<<"Ciudad: "<<direccion<<endl;
		cout<<"Teléfono: "<<telefono<<endl<<endl;
	}
};

#endif // Persona_H
