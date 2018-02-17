#include "Package.h"
#include "Region.h"
#include <list>
using namespace std;
class Office{
protected:
	string codeID;
	string name;
	string address;
	string city;
	list<Package> packages;
	list<Region> regions;
public:
	string getCode(){
		return codeID;
	}
	void setCode(string ncode);
	string getName(){
		return name;
	}
	void setName(string nname);
	string getAddress(){
		return address;
	}
	void setAddress(string naddress);
	string getCity(){
		return city;
	}
	void setCity(string ncity);
	//Creo que esto retorna una copia y no una lista, podemos usar un apuntador o implementar los métodos agregar y etc. dentro.
	list<Package> getPackages(){
		return packages;
	}
	list<Region> getRegions(){
		return regions;
	}
};