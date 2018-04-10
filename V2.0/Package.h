#ifndef Package_H
#define Package_H

#include <string>
#include <iostream>
#include "Person.h"
using namespace std;

class Package{
private:
	Person* sender;
	Person* receiver;
	float weight;
	string type;
	string guideN;

public:
	Person* getSender(){
		return sender;
	}
	void setSender(Person* nsender);
	
	Person* getReceiver(){
		return receiver;
	}
	void setReceiver(Person* nreceiver);
	
	float getWeight(){
		return weight;
	}
	void setWeight(float s);
	
	string getType(){
		return type;
	}
	void setType(string ntype);
	
	string getGuiden(){
		return guideN;
	}
	void setGuiden(string nguide);

	void showData(){
		cout<<"Remitente: "<<sender->getLname()<<endl;
		cout<<"Destinatario: "<<receiver->getLname()<<endl;
		cout<<"Peso: "<<weight<<endl;
		cout<<"Tipo: "<<type<<endl;
		cout<<"Número Guía: "<<guideN<<endl;
	}

};

#endif
