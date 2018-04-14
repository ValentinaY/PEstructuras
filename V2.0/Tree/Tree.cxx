#ifndef TREE_HXX
#define TREE_HXX

#include "Tree.h"
#include <list>

// ------------------------------------------------------------------------

Tree::Tree() : root(NULL){
}

// ------------------------------------------------------------------------

Tree::Tree(const Office& val) {
	Node *nNode = new Node(val);
	this->root = nNode;
}

// ------------------------------------------------------------------------

Tree::~Tree() {
	if (this->root != NULL)
		delete this->root;
}

// ------------------------------------------------------------------------

bool Tree::isEmpty() {
	if (this->root == NULL)
		return true;
	else
		return false;
}

// ------------------------------------------------------------------------

Node* Tree::getRoot() {
	return this->root;
}

// ------------------------------------------------------------------------

void Tree::setRoot(Node* nraiz) {
	this->root = nraiz;
}

// ------------------------------------------------------------------------

bool Tree::insert(Office& padre, Office& n) {
	bool ins = false;
	if (!this->isEmpty()) {
		ins = this->root->insertarNode(padre,n);
	}
	return ins;
}

// ------------------------------------------------------------------------

bool Tree::insert(Office& n) {

	if (!this->isEmpty()) {
		this->root->insertarNode(n);
		return true;
	}
	else{
		Node x;
		x.setData(n);
		this->setRoot(&x);
	}
	return false;
}

// ------------------------------------------------------------------------

bool Tree::erase(Office& n) {
	if(root->getData() == n){
		root=NULL;
		return true;
	}
	return root->eliminarNode(n);
}

// ------------------------------------------------------------------------

Node* Tree::search(Office& val) {
	return root->buscarNode(val);
}

// ------------------------------------------------------------------------

bool Tree::existence(Office& val) {
	return root->buscarExistenciaNode(val);
}

// ------------------------------------------------------------------------

int Tree::height() {
	return root->altura();
}

// ------------------------------------------------------------------------

unsigned int Tree::size() {
	return root->tamano();
}

// ------------------------------------------------------------------------

void Tree::preOrden() {
	if (!this->isEmpty()) {
		this->root->preOrden();
		std::cout << std::endl;
	}
	else
		std::cout<<"Vacío \n";
}

// ------------------------------------------------------------------------

void Tree::posOrden() {
	if (!this->isEmpty()) {
		this->root->posOrden();
		std::cout << std::endl;
	}
	else
		std::cout<<"Vacío \n";
}

// ------------------------------------------------------------------------

void Tree::inOrden() {
	if (!this->isEmpty()) {
		this->root->inOrden();
		std::cout << std::endl;
	}
	else
		std::cout<<"Vacío \n";
}

// ------------------------------------------------------------------------

void Tree::nivelOrden() {
	if (!this->isEmpty()) {
		this->root->nivelOrden(0,0);
		for(int i = 1; i <= this->height() ;i++){
			this->root->nivelOrdenR(i,0);
			std::cout << std::endl;
		}
	}
	else
		std::cout<<"Vacío \n";
}


// Métodos de oficinas

// ------------------------------------------------------------------------
Node* Tree::searchGeneral(string ciudad){
	return this->root->searchGeneral(ciudad);
}

void Tree::showRegions(){
	this->root->showRegions();
}


list<Office> Tree::getAllData(){
	list<Office> run;
	run.clear();
	run = this->root->getAllData(run);
	return run;
}

// eof - Tree.hxx
#endif
