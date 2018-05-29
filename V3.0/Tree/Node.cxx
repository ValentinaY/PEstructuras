#ifndef NODE_HXX
#define NODE_HXX

#include "Node.h"

// ------------------------------------------------------------------------

Node::Node() {
	this->desc.clear();
}

// ------------------------------------------------------------------------

Node::Node(const Region& val) {
	this->dato = val;
	this->desc.clear();
}

// ------------------------------------------------------------------------

Region& Node::getData() {
	return this->dato;
}

// ------------------------------------------------------------------------

void Node::setData(Region& val) {
	this->dato = val;
}

// ------------------------------------------------------------------------

typename Node::TList& Node::getDesc() {
	return this->desc;
}

// ------------------------------------------------------------------------

void Node::setDesc(TList& listaDesc) {
	this->desc = listaDesc;
}

// ------------------------------------------------------------------------

void Node::adicionarDesc(Region& nval) {
	Node *nNode = new Node;
	nNode->dato = nval;
	this->desc.push_back(nNode);
}

// ------------------------------------------------------------------------

bool Node::eliminarDesc(Region& val) {
	bool i = false;
	if(this->dato == val){
		this->desc.clear();
		return true;
	}
	else
		for (typename TList::iterator it = this->desc.begin(); it != this->desc.end() && (!i); it++)
			i =  (*it)->eliminarDesc(val);
	return i;
}

// ------------------------------------------------------------------------

Node* Node::buscarDesc(Region& val) {
	Node *p_it = NULL;

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

//-------------------------------------------------------------------------
Node* Node::findNode(string code){
	Node *p_it = NULL;
	string codef=code;
	if( codef.compare(this->getData().getCode()) == 0 ){
		p_it = this;
	}
	else{
		typename TList::iterator it;
		for (it = this->desc.begin(); it != this->desc.end(); it++) {
			p_it = (*it)->findNode(code);
			if (p_it != NULL){
				break;
			}
		}
	}

	return p_it;
}

// ------------------------------------------------------------------------

void Node::limpiarLista() {
	this->desc.clear();
}

// ------------------------------------------------------------------------

unsigned int Node::numDesc() {
	printf("113\n");
	return this->desc.size();
}

using namespace std;
// ------------------------------------------------------------------------

bool Node::insertNode(Region& padre, Region& n) {
	bool exit= false;

	if(padre == this->getData()){

		Node *nNode = new Node;
		nNode->dato = n;	
		this->desc.push_back(nNode);
		return true;
	}
	else
		for(typename TList::iterator it = this->desc.begin(); !exit && it != this->desc.end();it++)
			exit = (*it)->insertNode(padre,n);
	return exit;
}

// ------------------------------------------------------------------------

bool Node::insertNode(Region& n) {

	Node *nNode = new Node;
	nNode->dato = n;
	this->desc.push_back(nNode);
	return true;

}

// ------------------------------------------------------------------------
//pista: recursividad

bool Node::eraseNode(Region& n) {
	bool i = false;

	for (typename TList::iterator it = this->desc.begin(); it != this->desc.end() && (!i); it++){
		if((*it)->getData() == n){
			desc.erase(it);
			i = true;
			break;
		}
		if(!i){
			i =  (*it)->eraseNode(n);
		}
	}
	return i;

}

// ------------------------------------------------------------------------

Node* Node::buscarNode(Region& val) {
	Node *p_it = NULL;

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

bool Node::buscarExistenciaNode(Region& val) {
	bool be = false;

	if(this->getData() == val){
		return true;
	}
	else{
		for (typename TList::iterator it = this->desc.begin(); it != this->desc.end() && (be==false); it++){
			be = (*it)->buscarExistenciaNode(val);
		}
	}

		return be;
}

// ------------------------------------------------------------------------

int Node::altura() {
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

unsigned int Node::tamano() {
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

void Node::preOrden() {

	std::cout << this->dato.getCode() << "\t";
	if (this->numDesc() != 0) {
		typename TList::iterator it;
		for (it = desc.begin(); it != desc.end(); it++) {
			(*it)->preOrden();
		}
	}
}

// ------------------------------------------------------------------------

void Node::posOrden() {
	if (this->numDesc() != 0) {
		typename TList::iterator it;
		for (it = desc.begin(); it != desc.end(); it++) {
			(*it)->preOrden();
		}
	}
	std::cout << this->dato.getCode() << "\t";
}

// ------------------------------------------------------------------------

void Node::inOrden() {

	(*desc.begin())->preOrden();
	std::cout << this->dato.getCode() << "\t";
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

void Node::nivelOrden(int nivel, int lvActual) {
	typename TList::iterator it;
	if (nivel > lvActual)  {
		for (it = desc.begin(); it != desc.end(); it++) {
			(*it)->nivelOrden(nivel, lvActual+1);
		}
	}
	else if (nivel == lvActual)
		this->dato.showData();

}

void Node::nivelOrdenR(int nivel, int lvActual) {
	typename TList::iterator it;
	if (nivel > lvActual)  {
		for (it = desc.begin(); it != desc.end(); it++) {
			(*it)->nivelOrden(nivel, lvActual+1);
		}
	}
	else if (nivel == lvActual){
		this->dato.showData();
		//		std::cout<<this->dato.getCode()<<"\t";
	}
}


vector<Region> Node::getAllData(vector<Region> run){
	std::vector<Region> v=run;
	printf("3021\n");
	printf("306\n");
	Region r;
	r.setCode(this->getData().getCode());
	r.setName(this->getData().getName());
	printf("307\n");
	v.push_back(r);
	printf("308\n");
	if (this->numDesc() != 0) {
		printf("309\n");
		typename TList::iterator it;
		for (it = desc.begin(); it != desc.end(); it++) {
			printf("43\n");
			v = (*it)->getAllData(v);
		}
	}
	return v;
}

// eof - Node.hxx

#endif
