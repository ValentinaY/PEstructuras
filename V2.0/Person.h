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
	string getname(){
		return name;
	}
	void setname(string nname);
	
	string getid(){
		return id;
	}
	void setid(string nidnum);

	string getlname(){
		return lname;
	}
	void setlname(string nlname);
	
	string getaddress(){
		return address;
	}
	void setaddress(string naddress);

	string getcity(){
		return city;
	}
	void setcity(string ncity);

	string getphone(){
		return phone;
	}
	void setphone(string nphone);

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
