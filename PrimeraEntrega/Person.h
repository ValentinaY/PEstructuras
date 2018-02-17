#include <string>
using namespace std;
class Person{
protected:
	string name;
	string idNum;
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
	string getidNum(){
		return idNum;
	}
	void setidNum(string nidnum);
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
};