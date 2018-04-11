#include "Node.h"
#include <queue>

// ------------------------------------------------------------------------
template< class T >
Node<T>::Node() {
	this->desc.clear();
}

// ------------------------------------------------------------------------
template< class T >
Node<T>::Node(const T& val) {
	this->dato = val;
	this->desc.clear();
}

// ------------------------------------------------------------------------
template< class T >
Node<T>::~Node() {
	typename TList::iterator it;
	for (it = this->desc.begin(); it != this->desc.end(); it++)
		delete *it;
	this->desc.clear();
}

// ------------------------------------------------------------------------
template< class T >
T& Node<T>::getData() {
	return this->dato;
}

// ------------------------------------------------------------------------
template< class T >
void Node<T>::setData(T& val) {
	this->dato = val;
}

// ------------------------------------------------------------------------
template< class T >
typename Node<T>::TList& Node<T>::obtenerDesc() {
	return this->desc;
}

// ------------------------------------------------------------------------
template< class T >
void Node<T>::fijarDesc(TList& listaDesc) {
	this->desc = listaDesc;
}

// ------------------------------------------------------------------------
template< class T >
void Node<T>::adicionarDesc(T& nval) {
	Node<T> *nNode = new Node<T>;
	nNode->dato = nval;	
	this->desc.push_back(nNode);
}

// ------------------------------------------------------------------------
template< class T >
bool Node<T>::eliminarDesc(T& val) {
	bool i = false;
	if(this->dato == val){
		delete this->desc;
		return true;
	}
	else
		for (typename TList::iterator it = this->desc.begin(); it != this->desc.end() && (!i); it++)
			i =  (*it)->eliminarDesc(val);
	return i;
}

// ------------------------------------------------------------------------
template< class T >
Node<T>* Node<T>::buscarDesc(T& val) {
	Node<T> *p_it = NULL;

	if(this->dato == val){
		p_it = this;
	}
	else{
		typename TList::iterator it;
		for (it = this->desc.begin(); it != this->desc.end(); it++) {
			p_it = (*it)->buscarDesc(val);
			if (p_it != NULL)
				break;
		}
	}
	return p_it;
}

// ------------------------------------------------------------------------
template< class T >
void Node<T>::limpiarLista() {
	this->desc.clear();
}

// ------------------------------------------------------------------------
template< class T >
unsigned int Node<T>::numDesc() {
	return this->desc.size();
}

using namespace std;
// ------------------------------------------------------------------------
template< class T >
bool Node<T>::insertarNode(T& padre, T& n) {
	bool exit= false;

	if(padre == this->getData()){

		Node<T> *nNode = new Node<T>;
		nNode->dato = n;	
		this->desc.push_back(nNode);
		return true;
	}
	else
		for(typename TList::iterator it = this->desc.begin(); !exit && it != this->desc.end();it++)
			exit = (*it)->insertarNode(padre,n);
	return exit;
}

// ------------------------------------------------------------------------
template< class T >
bool Node<T>::insertarNode(T& n) {

	Node<T> *nNode = new Node<T>;
	nNode->dato = n;
	this->desc.push_back(nNode);
	return true;

}

// ------------------------------------------------------------------------
//pista: recursividad
template< class T >
bool Node<T>::eliminarNode(T& n) {
	bool i = false;

	for (typename TList::iterator it = this->desc.begin(); it != this->desc.end() && (!i); it++){
		if((*it)->obtenerDato() == n){
			desc.erase(it);
			i = true;
			break;
		}
		if(!i){
			i =  (*it)->eliminarNode(n);
		}
	}
	return i;

}

// ------------------------------------------------------------------------
template< class T >
Node<T>* Node<T>::buscarNode(T& val) {
	Node<T> *p_it = NULL;

	if(this->getData() == val){
		p_it = this;
	}
	else{
		for (typename TList::iterator it = this->desc.begin(); it != this->desc.end() && (p_it==NULL); it++){
			p_it = (*it)->buscarNode(val);
		}
	}

	return p_it;

}

// ------------------------------------------------------------------------
template< class T >
bool Node<T>::buscarExistenciaNode(T& val) {
	Node<T> *p_it = NULL;

	if(this->getData() == val){
		return true;
	}
	else{
		for (typename TList::iterator it = this->desc.begin(); it != this->desc.end() && (p_it==NULL); it++){
			p_it = (*it)->buscarNode(val);
		}
	}

	return false;

}

// ------------------------------------------------------------------------
template< class T >
int Node<T>::altura() {
	int i = 0, j;

	if(this->desc.size() == 0){
		return i;
	}
	for(typename TList::iterator it = this->desc.begin(); it != this->desc.end(); it++){
		j = 1 + (*it)->altura();
		i < j ? i = j: i;	
	}

	return i;
}

// ------------------------------------------------------------------------
template< class T >
unsigned int Node<T>::tamano() {
	unsigned int i = 0;

	if (this->numDesc() != 0) {
		typename TList::iterator it;
		for (it = desc.begin(); it != desc.end(); it++) {
			i += (*it)->tamano();
		}
	}
	else
		return 1;

	return i+1;
}

// ------------------------------------------------------------------------
template< class T >
void Node<T>::preOrden() {

	std::cout << this->dato << "\t";
	if (this->numDesc() != 0) {
		typename TList::iterator it;
		for (it = desc.begin(); it != desc.end(); it++) {
			(*it)->preOrden();
		}
	}
}

// ------------------------------------------------------------------------
template< class T >
void Node<T>::posOrden() {
	if (this->numDesc() != 0) {
		typename TList::iterator it;
		for (it = desc.begin(); it != desc.end(); it++) {
			(*it)->preOrden();
		}
	}
	std::cout << this->dato << "\t";
}

// ------------------------------------------------------------------------
template< class T >
void Node<T>::inOrden() {

	(*desc.begin())->preOrden();
	std::cout << this->dato << "\t";
	if (this->numDesc() != 0) {
		typename TList::iterator it;
		it = desc.begin();
		it++;
		while (it != desc.end()) {
			(*it)->preOrden();
			it++;
		}
	}
}

// ------------------------------------------------------------------------
template< class T >
void Node<T>::nivelOrden(int nivel, int lvActual) {
	typename TList::iterator it;
	if (nivel > lvActual)  {
		for (it = desc.begin(); it != desc.end(); it++) {
			(*it)->nivelOrden(nivel, lvActual+1);
		}
	}
	else if (nivel == lvActual){
		std::cout<<this->dato<<"\t";
	}
}

// eof - Node.hxx
