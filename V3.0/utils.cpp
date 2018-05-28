float Principal::toFloat(string a){
	float x= 0;
	for(unsigned int i=0;i<a.size();i++){
		x = x*10;
		x+= (int) (a[i]) - 48;
	}
	return x;
}

bool comparecodes(const char* g, const char* f){
	bool t=true;
	if(strlen(g) != strlen(f)){
		t=false;
	}
	else{
		for(int i=0; i<strlen(g);i++){
			if(g[i] != f[i]){
				t=false;
			}
		}
	}
	return t;
}