#include "Tree.h"

// ------------------------------------------------------------------------
template< class T >
Tree<T>::Tree() : root(NULL){
}

// ------------------------------------------------------------------------
template< class T >
Tree<T>::Tree(const T& val) {
	Node<T> *nNode = new Node<T>(val);
	this->root = nNode;
}

// ------------------------------------------------------------------------
template< class T >
Tree<T>::~Tree() {
	if (this->root != NULL)
		delete this->root;
}

// ------------------------------------------------------------------------
template< class T >
bool Tree<T>::isEmpty() {
	if (this->root == NULL)
		return true;
	else
		return false;
}

// ------------------------------------------------------------------------
template< class T >
Node<T>* Tree<T>::getRoot() {
	return this->root;
}

// ------------------------------------------------------------------------
template< class T >
void Tree<T>::setRoot(Node<T>* nraiz) {
	this->root = nraiz;
}

// ------------------------------------------------------------------------
template< class T >
bool Tree<T>::insert(T& padre, T& n) {
	bool ins = false;
	if (!this->isEmpty()) {
		ins = this->root->insertarNode(padre,n);
	}
	return ins;
}

// ------------------------------------------------------------------------
template< class T >
bool Tree<T>::insert(T& n) {

	if (!this->isEmpty()) {
		this->root->insertarNode(n);
		return true;
	}
	else{
		Node<T> x;
		x.setData(n);
		this->setRoot(&x);
	}
	return false;
}

// ------------------------------------------------------------------------
template< class T >
bool Tree<T>::erase(T& n) {
	if(root->obtenerDato() == n){
		root=NULL;
		return true;
	}
	return root->eliminarNode(n);
}

// ------------------------------------------------------------------------
template< class T >
Node<T>* Tree<T>::search(T& val) {
	return root->buscarNode(val);
}

// ------------------------------------------------------------------------
template< class T >
bool Tree<T>::existence(T& val) {
	return root->buscarExistenciaNode(val);
}

// ------------------------------------------------------------------------
template< class T >
int Tree<T>::height() {
	return root->altura();
}

// ------------------------------------------------------------------------
template< class T >
unsigned int Tree<T>::size() {
	return root->tamano();
}

// ------------------------------------------------------------------------
template< class T >
void Tree<T>::preOrden() {
	if (!this->isEmpty()) {
		this->root->preOrden();
		std::cout << std::endl;
	}
	else 
		std::cout<<"Vacío \n";
}

// ------------------------------------------------------------------------
template< class T >
void Tree<T>::posOrden() {
	if (!this->isEmpty()) {
		this->root->posOrden();
		std::cout << std::endl;
	}
	else 
		std::cout<<"Vacío \n";
}

// ------------------------------------------------------------------------
template< class T >
void Tree<T>::inOrden() {
	if (!this->isEmpty()) {
		this->root->inOrden();
		std::cout << std::endl;
	}
	else
		std::cout<<"Vacío \n";
}

// ------------------------------------------------------------------------
template< class T >
void Tree<T>::nivelOrden() {
	if (!this->isEmpty()) {
		for(int i = 0; i <= this->height() ;i++)
			this->root->nivelOrden(i,0);
		std::cout << std::endl;
	}
	else 
		std::cout<<"Vacío \n";
}

// eof - Tree.hxx
