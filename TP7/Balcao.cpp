#include <queue>
#include <cstdlib>
#include "Balcao.h"
#include "exceptions.h"

using namespace std;


Cliente::Cliente() : numPresentes(rand()%5 + 1){}


int Cliente::getNumPresentes() const {
	return numPresentes;
}


Balcao::Balcao(int te) : tempo_embrulho(te), tempo_atual(0), prox_chegada((rand()%20) + 1), prox_saida(0), clientes_atendidos(0) {}


void Balcao:: proximoEvento()
{
	// a alterar
}


void Balcao::chegada()
{
	Cliente c1;

	prox_chegada = tempo_atual + (rand()%20) +1;

	if(clientes.empty())
		prox_saida = tempo_atual + c1.getNumPresentes() * tempo_embrulho;

	//inserting client
	clientes.push(c1);

	//prints
	cout << "tempo= " << tempo_atual <<"\nchegou com novo cliente com " << c1.getNumPresentes() << " presentes\n";
}   


void Balcao::saida()
{
	Cliente c1;
	try {
		c1 = getProxCliente();
	}
	catch(FilaVazia &emp)
	{
		cout << emp.getMsg();
		prox_saida = 0;
		return;
	}

	//Removing
	clientes.pop();

	//update
	prox_saida = tempo_atual + c1.getNumPresentes() * tempo_embrulho;

	clientes_atendidos++;

	//printing
	cout << "tempo= " << tempo_atual << "\nSaiu um cliente e chegou novo cliente com " << c1.getNumPresentes() << " presentes";
}


int Balcao::getTempoAtual() const { return tempo_atual; }


int Balcao::getProxChegada() const { return prox_chegada; }


ostream & operator << (ostream & out, const Balcao & b1)
{
	// a alterar
     return out;
}


int Balcao::getTempoEmbrulho() const {

	return tempo_embrulho;
}


int Balcao::getProxSaida() const {
	return prox_saida;
}


int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}


Cliente & Balcao::getProxCliente() {
	if(clientes.empty())		//QUEUE is empty af
		throw FilaVazia();

	//Return front of queue
	return clientes.front();
}

      
