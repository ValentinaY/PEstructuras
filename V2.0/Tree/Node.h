#ifndef __Node__H__
#define __Node__H__

#include <iostream>
#include <list>

template< class T >
class Node {
public:
	//definicion mas corta del tipo
	typedef std::list< Node<T>* > TList;

public:
	//constructores
	Node();
	Node(const T& val);
	//destructor
	~Node();
	//manipuladores dato
	T& getData();
	void setData(T& val);

	//manipuladores lista descendientes
	TList& obtenerDesc();
	void fijarDesc(TList& listaDesc);

	//modificadores lista descendientes
	void adicionarDesc(T& nval);
	bool eliminarDesc(T& val);
	Node<T>* buscarDesc(T& val);
	void limpiarLista();
	unsigned int numDesc();

	//operaciones para arbol
	bool insertarNode(T& padre, T& n);
	bool insertarNode(T& n);
	bool eliminarNode(T& n);
	Node<T>* buscarNode(T& val);
	bool buscarExistenciaNode(T& val);
	int altura();
	unsigned int tamano();
	void preOrden();
	void posOrden();
	void inOrden();
	void nivelOrden(int nivel, int lvActual);

protected:
	T dato;
	TList desc;
};

#include "Node.hxx"

#endif // __Node__H__

// eof - Node.h

