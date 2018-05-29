#ifndef TREE_HXX
#define TREE_HXX

#include "Tree.h"
#include <list>

// ------------------------------------------------------------------------

Tree::Tree() : root(NULL){
}

// ------------------------------------------------------------------------

Tree::Tree(const Region& val) {
	Node *nNode = new Node(val);
	this->root = nNode;
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

void Tree::setRoot(Region raiz) {
	Node* nraiz;
	nraiz->setData(raiz);
	this->root = nraiz;
}

// ------------------------------------------------------------------------

bool Tree::insert(Region& padre, Region& n) {
	bool ins = false;
	if (!this->isEmpty()) {
		ins = this->root->insertNode(padre,n);
	}
	return ins;
}

// ------------------------------------------------------------------------

bool Tree::insert(Region& n) {

	if (!this->isEmpty()) {
		this->root->insertNode(n);
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

bool Tree::erase(Region& n) {
	if(root->getData() == n){
		root=NULL;
		return true;
	}
	return root->eraseNode(n);
}

// ------------------------------------------------------------------------

Node* Tree::search(Region& val) {
	return root->buscarNode(val);
}

//-------------------------------------------------------------------------
Node* Tree::find(string code){
	return root->findNode(code);
}

// ------------------------------------------------------------------------

bool Tree::existence(Region& val) {
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
		for(int i = 1; i <= this->height() ;i++){
			this->root->nivelOrden(i,0);
			std::cout << std::endl;
		}
	}
	else
		std::cout<<"Vacío \n";
}


// Métodos de regiones

vector<Region> Tree::getAllData(){
	vector<Region> run;
	run.clear();
	if(this->root != NULL){
		run = this->root->getAllData(run);
	}
	return run;
}

// eof - Tree.hxx
#endif
