#include <string>
using namespace std;
class Region{
private:
	string name;
	long code;
public:
	string getName(){
		return name;
	}
	void setName(string nname);
	long getCode(){
		return code;
	}
	void setCode(long ncode);
};