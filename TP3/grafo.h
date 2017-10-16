#include <iostream>
#include <vector>

using namespace std;

/**
 * Versão da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N, A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N, A> *destino;
	Aresta(No<N, A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A>
class Grafo {
	vector< No<N, A> *> nos;
public:
	Grafo();
	~Grafo();
	Grafo & inserirNo(const N &dados);
	Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
	Grafo & eliminarAresta(const N &inicio, const N &fim);
	A & valorAresta(const N &inicio, const N &fim);
	int numArestas(void) const;
	int numNos(void) const;
	void imprimir(std::ostream &os) const;
};

//CONSTRUCTORS, DESTRUCTORS, SO ON(...)
//C
template <class N, class A>
Grafo<N, A>::Grafo() {}
//D
template <class N, class A>
Grafo<N, A>::~Grafo()
{
	for (unsigned int i = 0; i < nos.size(); i++)
	{
		delete nos.at(i);
	}
}

//FUNCTIONS FROM EXERCISES
template <class N, class A>
int Grafo<N, A>::numNos(void) const
{
	return nos.size();
}

template <class N, class A>
int Grafo<N, A>::numArestas(void) const
{
	unsigned int counter = 0;
	for (unsigned int i = 0; i<nos.size(); i++) {
		counter += no->arestas.size();
	}

	return counter;
}
//FINISHED a)


template <class N, class A>
Grafo<N, A> & Grafo<N, A>::inserirNo(const N &dados)
{
	//Checking if already exists
	for (unsigned int i = 0; i < nos.size(); i++)
		if (nos.at(i)->info == dados)
			throw NoRepetido<N>(dados);
		//Allocations, allocations
		No<N, A> *temp_no = new No<N, A>(dados);
		//pushing back to vec
		nos.push_back(temp_no);

		return *this;
}



template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);

// excecao  NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

