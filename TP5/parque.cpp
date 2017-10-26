#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	//+1 on the freq
	clientes.at(pos).frequencia++;
	clientes[pos].presente = true;
	vagas--;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

//EXERCISE A)
// CHANGING SO IT USES SEQUENTIAL SEARCH
// We have to use the == operator because SSrch compares two values
bool InfoCartao::operator == (const InfoCartao &ic1) const {	
	return this->nome == ic1.nome;
}
int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	//in order to use the sequential search provided, we need to create
	//a temporary object. Therefore:
	InfoCartao ic;
	ic.nome = nome;

	return sequentialSearch(this->clientes, ic);
}

//EXERCISE B)
//Got to change AdicionCliente, entrar and getFrequencia, and create a class with the exception
int ParqueEstacionamento::getFrequencia(const string &nome) const {
	int index = posicaoCliente(nome);
	
	if (index == -1)//Client not found
		throw ClienteNaoExistente(nome);
	else
		return clientes.at(index).frequencia;
}
//ClienteNaoExistente "exception class"
ClienteNaoExistente::ClienteNaoExistente(const string &nome) : nome(nome) {} //the fun & easy way
//getNome function
string ClienteNaoExistente::getNome() const {
	return this->nome;
}