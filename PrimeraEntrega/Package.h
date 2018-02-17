#include <string>
using namespace std;
class Package{
private:
	//Porque el código de la persona es de tipo long.22
	long sender;
	long recipient;
	float weight;
	string type;
	string trackingNumber;
public:
	long getSender(){
		return sender;
	}
	void setSender(long nsender);
	long getRecipient(){
		return recipient;
	}
	void setRecipient(long nrecipient);
	float getWeight(){
		return weight;
	}
	void setWeight(float s);
	string getType(){
		return type;
	}
	void setType(string ntype);
	string getTrackingNumber(){
		return trackingNumber;
	}
	void setTrackingNumber(string ntranum);

};