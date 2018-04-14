#ifndef Region_H
#define Region_H

#include "Package.h"

#include <string>
#include <list>
#include <iostream>

using namespace std;

class Region{
private:
	string name;
	string code;

public:
	string getName(){
		return name;
	}
	void setName(string nname);
	
	string getCode(){
		return code;
	}
	void setCode(string ncode);

	void showData(){
		cout<<"Nombre: "<<name<<endl;
		cout<<"Código: "<<code<<endl;
	}
};

#endif
