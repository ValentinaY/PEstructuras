#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <list>
#include "../Region.h"

class Node {
public:
	//definicion mas corta del tipo
	typedef std::list<Node*> TList;

public:
	//constructores
	Node();
	Node(const Region& val);
	//manipuladores dato
	Region& getData();
	Region getdata();
	void setData(Region& val);

	//manipuladores lista descendientes
	TList& getDesc();
	void setDesc(TList& listaDesc);

	//modificadores lista descendientes
	void adicionarDesc(Region& nval);
	bool eliminarDesc(Region& val);
	Node* buscarDesc(Region& val);
	Node* findNode(string code);
	void limpiarLista();
	unsigned int numDesc();

	//operaciones para arbol
	bool insertNode(Region& padre, Region& n);
	bool insertNode(Region& n);
	bool eraseNode(Region& n);
	Node* buscarNode(Region& val);
	bool buscarExistenciaNode(Region& val);
	int altura();
	unsigned int tamano();
	void preOrden();
	void posOrden();
	void inOrden();
	void nivelOrden(int nivel, int lvActual);
	void nivelOrdenR(int nivel, int lvActual);

	// Metodos Region
	vector<Region> getAllData(vector<Region> run);

protected:
	Region dato;
	TList desc;
};

#endif // __Node__H__

// eof - Node.h

