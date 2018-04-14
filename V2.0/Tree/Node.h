#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <list>
#include "../Office.h"

class Node {
public:
	//definicion mas corta del tipo
	typedef std::list<Node*> TList;

public:
	//constructores
	Node();
	Node(const Office& val);
	//destructor
	~Node();
	//manipuladores dato
	Office& getData();
	void setData(Office& val);

	//manipuladores lista descendientes
	TList& getDesc();
	void setDesc(TList& listaDesc);

	//modificadores lista descendientes
	void adicionarDesc(Office& nval);
	bool eliminarDesc(Office& val);
	Node* buscarDesc(Office& val);
	void limpiarLista();
	unsigned int numDesc();

	//operaciones para arbol
	bool insertarNode(Office& padre, Office& n);
	bool insertarNode(Office& n);
	bool eliminarNode(Office& n);
	Node* buscarNode(Office& val);
	bool buscarExistenciaNode(Office& val);
	int altura();
	unsigned int tamano();
	void preOrden();
	void posOrden();
	void inOrden();
	void nivelOrden(int nivel, int lvActual);
	void nivelOrdenR(int nivel, int lvActual);

	// Metodos Oficina
	Node* searchGeneral(string ciudad);
	void showRegions();
	list<Office> getAllData(list<Office> run);

protected:
	Office dato;
	TList desc;
};

#endif // __Node__H__

// eof - Node.h

