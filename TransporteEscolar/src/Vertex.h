#ifndef SRC_VERTEX_H_
#define SRC_VERTEX_H_

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;

template <class T>
class Vertex {
	T info;
	vector<Edge<T> > adj;
	bool visited;
	bool processing;
	int indegree;
	int dist;
	bool isPI;
	bool isSchool;
public:

	Vertex(T in);
	friend class Graph<T>;

	void addEdge(Vertex<T> *dest, double w, int id, string n);
	bool removeEdgeTo(Vertex<T> *d);

	T getInfo() const;
	void setInfo(T info);

	int getDist() const;
	int getIndegree() const;

	Vertex* path;

	int getNumAdjacents() const;
	Edge<T> getAdjacentNumber(int i) const;
	void setIsPI(bool estado);
	bool getIsPI();
	void setIsSchool(bool estado);
	bool getIsSchool();
	vector<Edge<T> > getAdjacents() const;
};


template <class T>
struct vertex_greater_than {
	bool operator()(Vertex<T> * a, Vertex<T> * b) const {
		return a->getDist() > b->getDist();
	}
};


template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	d->indegree--; //adicionado do exercicio 5
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false), processing(false),
indegree(0), dist(0) {
	path = NULL;
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w, int id, string n) {
	Edge<T> edgeD(dest,w,id,n);
	adj.push_back(edgeD);
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
int Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
void Vertex<T>::setInfo(T info) {
	this->info = info;
}

template <class T>
int Vertex<T>::getIndegree() const {
	return this->indegree;
}

template <class T>
int Vertex<T>::getNumAdjacents() const{
	return adj.size();
}

template <class T>
Edge<T> Vertex<T>::getAdjacentNumber(int i) const{
	if(i >= 0 && i < adj.size())
		return adj.at(i);
}

template<class T>
void Vertex<T>::setIsPI(bool estado){
	isPI = estado;
}

template<class T>
bool Vertex<T>::getIsPI(){
	return isPI;
}


template<class T>
void Vertex<T>::setIsSchool(bool estado){
	isSchool = estado;
}

template<class T>
bool Vertex<T>::getIsSchool(){
	return isSchool;
}

template<class T>
vector<Edge<T> > Vertex<T>::getAdjacents() const{
	return adj;
}

#endif /* SRC_VERTEX_H_ */
