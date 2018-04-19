all: main

main: Person.cxx Package.cxx Region.cxx Office.cxx Principal.cxx main.cpp Tree/Node.cxx Tree/Tree.cxx 
	g++ -std=c++11 -g -o main Person.cxx Package.cxx Region.cxx Office.cxx Principal.cxx main.cpp Tree/Node.cxx Tree/Tree.cxx && ./main

rmaall:
	rm main
	g++ -std=c++11 -o main Person.cxx Package.cxx Region.cxx Office.cxx Principal.cxx main.cpp Tree/Node.cxx Tree/Tree.cxx

clean:
	rm main
	
#carpe ./data/per.csv
#carof ./data/ofi.csv
#carre ./data/reg.csv
#carpa ./data/pak.csv
