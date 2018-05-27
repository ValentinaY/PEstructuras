#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include "../Region.h"

class Tree {
protected:
	Node* root;

public:
	//definicion mas corta del tipo
	typedef std::list< Node* > TList;

public:
	//constructores
	Tree();
	Tree(const Region& val);
	//verificador
	bool isEmpty();
	//manipuladores raiz
	Node* getRoot();
	void setRoot(Node* nraiz);
	void setRoot(Region raiz);
	//modificadores Tree
	bool insert(Region& padre, Region& n);
	bool insert(Region& n);
	bool erase(Region& n);
	Node* search(Region& val);
	Node* find(string code);
	bool existence(Region& val);
	int height();
	unsigned int size();
	void preOrden();
	void posOrden();
	void inOrden();
	void nivelOrden();

	// Métodos de regiones
	vector<Region> getAllData();
};

#endif // __Tree__H__

// eof - Tree.h

