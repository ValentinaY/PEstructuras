#ifndef __Tree__H__
#define __Tree__H__

#include "Node.h"

template <class T>
class Tree {
protected:
	Node<T>* root;

public:
	//definicion mas corta del tipo
	typedef std::list< Node<T>* > TList;

public:
	//constructores
	Tree();
	Tree(const T& val);
	//destructor
	~Tree();
	//verificador
	bool isEmpty();
	//manipuladores raiz
	Node<T>* getRoot();
	void setRoot(Node<T>* nraiz);
	//modificadores Tree
	bool insert(T& padre, T& n);
	bool insert(T& n);
	bool erase(T& n);
	Node<T>* search(T& val);
	bool existence(T& val);
	int height();
	unsigned int size();
	void preOrden();
	void posOrden();
	void inOrden();
	void nivelOrden();
};

#include "Tree.hxx"

#endif // __Tree__H__

// eof - Tree.h

