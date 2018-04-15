#ifndef NODE_HXX
#define NODE_HXX

#include "Node.h"

#include <queue>

// ------------------------------------------------------------------------

Node::Node() {
	this->desc.clear();
}

// ------------------------------------------------------------------------

Node::Node(const Office& val) {
	this->dato = val;
	this->desc.clear();
}

// ------------------------------------------------------------------------

Node::~Node() {
	typename TList::iterator it;
	for (it = this->desc.begin(); it != this->desc.end(); it++)
		delete *it;
	this->desc.clear();
}

// ------------------------------------------------------------------------

Office& Node::getData() {
	return this->dato;
}

Office Node::getdata(){
	return this->dato;
}
// ------------------------------------------------------------------------

void Node::setData(Office& val) {
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

void Node::adicionarDesc(Office& nval) {
	Node *nNode = new Node;
	nNode->dato = nval;	
	this->desc.push_back(nNode);
}

// ------------------------------------------------------------------------

bool Node::eliminarDesc(Office& val) {
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

Node* Node::buscarDesc(Office& val) {
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
Node* Node::findnode(string code){
	Node *p_it = NULL;
	string codef=code;
	cout<<"Comparando  "+code+" con "+this->dato.getCode()<<endl;
	if( codef.compare(this->dato.getCode()) == 0 ){
		p_it = this;
	}
	else{
		typename TList::iterator it;
		for (it = this->desc.begin(); it != this->desc.end(); it++) {
			p_it = (*it)->findnode(code);
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
	return this->desc.size();
}

using namespace std;
// ------------------------------------------------------------------------

bool Node::insertarNode(Office& padre, Office& n) {
	bool exit= false;

	if(padre == this->getData()){

		Node *nNode = new Node;
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

bool Node::insertarNode(Office& n) {

	Node *nNode = new Node;
	nNode->dato = n;
	this->desc.push_back(nNode);
	return true;

}

// ------------------------------------------------------------------------
//pista: recursividad

bool Node::eliminarNode(Office& n) {
	bool i = false;

	for (typename TList::iterator it = this->desc.begin(); it != this->desc.end() && (!i); it++){
		if((*it)->getData() == n){
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

Node* Node::buscarNode(Office& val) {
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

bool Node::buscarExistenciaNode(Office& val) {
	Node *p_it = NULL;

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
	else if (nivel == lvActual){
		this->dato.showData();
		//		std::cout<<this->dato.getCode()<<"\t";
	}
}

void Node::nivelOrdenR(int nivel, int lvActual) {
	typename TList::iterator it;
	if (nivel > lvActual)  {
		for (it = desc.begin(); it != desc.end(); it++) {
			(*it)->nivelOrden(nivel, lvActual+1);
		}
	}
	else if (nivel == lvActual){
		this->dato.showDataR();
		//		std::cout<<this->dato.getCode()<<"\t";
	}
}

Node* Node::searchGeneral(string ciudad){
	for (TList::iterator it = desc.begin(); it != desc.end(); it++) {
		if((*it)->getData().getCity() == ciudad){
			return *it;
		}
	}
	return NULL;
}

void Node::showRegions(){
	if (this->numDesc() != 0) {
		typename TList::iterator it;
		for (it = desc.begin(); it != desc.end(); it++) {
			(*it)->showRegions();
		}
	}
	if(this->dato.getCode()!="Principal")
		this->dato.showRegions();
}

list<Office> Node::getAllData(list<Office> run){

	run.push_back(this->dato);
	if (this->numDesc() != 0) {
		typename TList::iterator it;
		for (it = desc.begin(); it != desc.end(); it++) {
			run = (*it)->getAllData(run);
		}
	}
	return run;
}

// eof - Node.hxx

#endif
