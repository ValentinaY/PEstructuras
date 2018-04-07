#ifndef Package_H
#define Package_H

#include <string>
#include <iostream>
#include "Person.h"
using namespace std;

class Package{
private:
	Person sender;
	Person receiver;
	float weight;
	string type;
	string guiden;

public:
	Person getsender(){
		return sender;
	}
	void setsender(Person nsender);
	
	Person getreceiver(){
		return receiver;
	}
	void setreceiver(Person nreceiver);
	
	float getweight(){
		return weight;
	}
	void setweight(float s);
	
	string gettype(){
		return type;
	}
	void settype(string ntype);
	
	string getguiden(){
		return guiden;
	}
	void setguiden(string nguide);

	void toString(){
		cout<<"Remitente: "<<sender.getname()<<endl;
		cout<<"Destinatario: "<<receiver.getname()<<endl;
		cout<<"Peso: "<<weight<<endl;
		cout<<"Tipo: "<<type<<endl;
		cout<<"Número Guía: "<<guiden<<endl;
	}

};

#endif
