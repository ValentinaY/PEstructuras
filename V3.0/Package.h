#ifndef Package_H
#define Package_H

#include <string>
#include <iostream>
#include "Region.h"
#include "Person.h"
using namespace std;

class Package{
private:
	Person sender;
	Person receiver;
	Region region;
	float weight;
	string type;
	string guideN;
	bool active;

public:
	Package();

	Person getSender(){
		return sender;
	}
	void setSender(Person &nsender);

	Person getReceiver(){
		return receiver;
	}
	void setReceiver(Person &nreceiver);

	Region getRegion(){
		return region;
	}
	void setRegion(Region &nregion);

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

	bool isActive(){
		return active;
	}

	void send();

	void showData(){
		cout<<"\tId. Remitente: "<<sender.getId()<<endl;
		cout<<"\tId. Destinatario: "<<receiver.getId()<<endl;
		cout<<"\tCódigo región: "<<region.getCode()<<endl;
		cout<<"\tPeso: "<<weight<<endl;
		cout<<"\tTipo: "<<type<<endl;
		cout<<"\tNúmero Guía: "<<guideN<<endl;
		if(active)
			cout<<"\t El paquete fue repartido"<<endl;
	}
};

#endif
