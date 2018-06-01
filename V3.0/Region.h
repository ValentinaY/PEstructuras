#ifndef Region_H
#define Region_H

#include <string>
#include <iostream>

using namespace std;

class Region{
private:
	string name;
	string code;
	int distanceUp;

public:
	Region();

	string getName(){
		return name;
	}
	void setName(string nname);

	string getCode(){
		return code;
	}
	void setCode(string ncode);

	int getDistanceUp(){
		return distanceUp;
	}
	void setDistanceUp(int dist);

	void showData(){
		cout<<"Nombre: "<<name<<endl;
		cout<<"Código: "<<code<<endl<<endl;
	}

	bool operator == (Region o){
		return code == o.getCode();
	}
};

#endif
