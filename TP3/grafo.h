#include <iostream>
#include <vector>

using namespace std;

/**
 * Versão da classe generica Grafo usando a classe vector
 */

//PROTOTYPING B O Y Z
template <class N, class A> class Aresta;

template <class N, class A> class No;

template <class N, class A> class Grafo;

template <class N> class ArestaRepetida;

template <class N> class NoRepetido;

template <class N> class NoInexistente;

template <class N> class ArestaInexistente;

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
		counter += nos.at(i)->arestas.size();
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
//FINISHED b)

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val)
{

	for(unsigned int i=0;i<nos.size();i++)
		if(nos.at(i)->info==inicio)
		{
			for(unsigned int j=0;j<nos.at(i)->arestas.size();j++)
				if(nos.at(i)->arestas.at(j).destino->info == fim)
					throw ArestaRepetida<N>(inicio,fim);

			No<N,A> *temp = new No<N,A>(fim);

			Aresta<N,A> a1(temp,val);
			nos.at(i)->arestas.push_back(a1);

			return *this;
		}

	throw NoInexistente<N>(inicio);
}
//FINISHED c)


template <class N, class A>
A & Grafo<N,A>::valorAresta(const N &inicio, const N &fim)
{
	for(int i=0;i<nos.size();i++)
		if(nos.at(i)->info==inicio)
		{
			for(int j=0;j<nos.at(i)->arestas.size();j++)
				if(nos.at(i)->arestas.at(j).destino->info==fim)
					return nos.at(i)->arestas.at(j).valor;

			throw ArestaInexistente<N>(inicio,fim);
		}

	throw NoInexistente<N>(inicio);
}
//FINISHED d)


template <class N, class A>
Grafo<N,A> & Grafo<N,A>::eliminarAresta(const N &inicio, const N &fim)
{
	for(int i=0;i<nos.size();i++)
			if(nos.at(i)->info==inicio)
			{
				for(int j=0;j<nos.at(i)->arestas.size();j++)
					if(nos.at(i)->arestas.at(j).destino->info==fim)
						{
							nos.at(i)->arestas.erase(nos.at(i)->arestas.begin()+i);
							return *this;
						}

				throw ArestaInexistente<N>(inicio,fim);
			}

		throw NoInexistente<N>(inicio);
}
//FINISHED e)


template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);

//EXCECOES

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


//excecao ArestaRepetida
template <class N>
class ArestaRepetida
{
public:
	N inicio;
	N destino;
	ArestaRepetida(N inicial, N destination) {
		inicio=inicial;
		destino=destination; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &aresta)
{
	out << "Aresta repetida: " << aresta.inicio << " , " << aresta.destino;
	return out;
}


//excecao ArestaInexistente

template <class N>
class ArestaInexistente
{
public:
	N inicio;
	N destino;
	ArestaInexistente(N inic, N dest) {
		inicio=inic;
		destino=dest; }
};
template <class N>
std::ostream & operator <<(std::ostream &out, const ArestaInexistente<N> &aresta)
{
	out << "Aresta inexistente: " << aresta.inicio << " , " << aresta.destino;
	return out;
}
