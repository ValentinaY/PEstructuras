#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include "../Office.h"

class Tree {
protected:
	Node* root;

public:
	//definicion mas corta del tipo
	typedef std::list< Node* > TList;

public:
	//constructores
	Tree();
	Tree(const Office& val);
	//verificador
	bool isEmpty();
	//manipuladores raiz
	Node* getRoot();
	void setRoot(Node* nraiz);
	//modificadores Tree
	bool insert(Office& padre, Office& n);
	bool insert(Office& n);
	bool erase(Office& n);
	Node* search(Office& val);
	Node* find(string code);
	bool existence(Office& val);
	int height();
	unsigned int size();
	void preOrden();
	void posOrden();
	void inOrden();
	void nivelOrden();

	// Métodos de oficinas
	Node* searchGeneral(string ciudad);
	void showRegions();
	list<Office> getAllData();
};

#endif // __Tree__H__

// eof - Tree.h

