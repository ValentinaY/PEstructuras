#ifndef Person_H
#define Person_H

#include <string>
#include <iostream>

using namespace std;

class Person{
private:
	string name;
	string lname;
	string id;
	string address;
	string city;
	string phone;
public:
	/* Los getters no se implementan aparte http://www.learncpp.com/cpp-tutorial/89-class-code-and-header-files/
	*/
	string getName(){
		return name;
	}
	void setName(string nname);
	
	string getId(){
		return id;
	}
	void setId(string nidnum);

	string getLname(){
		return lname;
	}
	void setLname(string nlname);
	
	string getAddress(){
		return address;
	}
	void setAddress(string naddress);

	string getCity(){
		return city;
	}
	void setCity(string ncity);

	string getPhone(){
		return phone;
	}
	void setPhone(string nphone);

	void toString(){
		cout<<"Nombre: "<<name<<endl;
		cout<<"Apellido: "<<lname<<endl;
		cout<<"Identificación: "<<id<<endl;
		cout<<"Ciudad: "<<city<<endl;
		cout<<"Dirección: "<<address<<endl;
		cout<<"Teléfono: "<<phone<<endl<<endl;
	}
};

#endif
