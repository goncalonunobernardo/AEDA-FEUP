/*
 * Agencia.cpp
 */

#include "Agencia.h"

//Conta
Conta::Conta(int nConta, float sd, int nTrans) :
		numConta(nConta), saldo(sd), numTransacoes(nTrans), titular2(NULL) {
}

int Conta::getNumConta() const {
	return numConta;
}

float Conta::getSaldo() const {
	return saldo;
}

int Conta::getNumTransacoes() const {
	return numTransacoes;
}

void Conta::setTitular2(Cliente *cli2) {
	titular2 = cli2;
}

Cliente *Conta::getTitular2() const {
	return titular2;
}

void Conta::deposito(float valor) {
	saldo += valor;
	numTransacoes++;
}

Normal::Normal(int nConta, float sd, int nTrans) :
		Conta(nConta, sd, nTrans) {
}
bool Normal::levantamento(float valor) {
	if (saldo >= valor) {
		saldo = saldo - valor;
		numTransacoes++;
		return true;
	} else
		return false;
}

DeOperacao::DeOperacao(int nConta, float tx, float sd, int nTrans) :
		Conta(nConta, sd, nTrans), taxa(tx) {
}
bool DeOperacao::levantamento(float valor) {
	if (saldo >= valor) {
		if (valor >= 30) {
			if (numTransacoes == 0) //New client
					{
				saldo -= valor + 0.05;
				numTransacoes++;
				return true;
			} else				   //Older client
			{
				saldo -= valor + 0.03;
				numTransacoes++;
				return true;
			}
		} else {
			saldo -= valor;
			numTransacoes++;
			return true;
		}
	} else
		return false;
}

//Cliente
Cliente::Cliente(string nm) :
		nome(nm) {
}

string Cliente::getNome() const {
	return nome;
}

vector<Conta *> Cliente::getContas() const {
	return contas;
}

void Cliente::adicionaConta(Conta *c1) {
	contas.push_back(c1);
}

//Agencia
Agencia::Agencia(string desig) :
		designacao(desig) {
}

string Agencia::getDesignacao() const {
	return designacao;
}

vector<Cliente *> Agencia::getClientes() const {
	return clientes;
}

vector<Gerente> Agencia::getGerentes() const {
	return gerentes;
}

void Agencia::adicionaCliente(Cliente *cli1) {
	clientes.push_back(cli1);
}

Conta* Agencia::levantamento(string nomeCli, float valor) {

	for (size_t i = 0; i < clientes.size(); i++) {

		if (clientes.at(i)->nome == nomeCli) {
			for (size_t j = 0; j < clientes.at(i)->getContas().size(); j++) {
				if (clientes.at(i)->getContas().at(j)->levantamento(valor)) {
					return clientes.at(i)->getContas().at(j);
				}
			}
		}
	}
	return new Normal(-1);
}

float Agencia::fimMes() const{
	float saldofinal = 0;

	for(size_t i = 0; i < clientes.size(); i++)
	{
		for(size_t j= 0; j< clientes.at(i)->getContas().size(); j++)
		{
			if(clientes.at(i)->getContas().at(j)->getTipo() == "N")
				clientes.at(i)->getContas().at(j)->levantamento(1.5);
			saldofinal += clientes.at(i)->getContas().at(j)->getSaldo();
		}
	}

	return saldofinal;
}
/* Esta função retira o cliente de nome nomeCli do vetor clientes da agência. Desassocia este cliente
de todas as contas das quais é 2o titular. As contas das quais é 1otitular são passadas para o 2otitular,
caso exista, senão deixam de existir na agência. A função retorna estas últimas, isto é, as contas das
quais o cliente é 1o titular e que não possuem 2otitular.*/
//vector<Conta*> Agencia::removeCliente(string nomeCli)
//{
//
//
//
//}

float Agencia::operator<(const Agencia &a1)
{
	float sum1 = 0;
	float sum2 = 0;

	//sum1
	for(size_t i = 0; i< clientes.size(); i++)
	{
		for(size_t j = 0; j < clientes.at(i)->getContas().size(); j++)
		{
			sum1 += clientes.at(i)->getContas().at(j)->getSaldo();
		}
	}

	//sum2
	for(size_t i = 0; i< a1.clientes.size(); i++)
		{
			for(size_t j = 0; j < a1.clientes.at(i)->getContas().size(); j++)
			{
				sum2 += a1.clientes.at(i)->getContas().at(j)->getSaldo();
			}
		}

	sum1 = sum1 /((float)clientes.size());
	sum2 = sum2 /((float)a1.clientes.size());

	return sum1 < sum2;
}

float Agencia::operator()(string name)
{
	int ind = -1;
	float soma = 0;

	for(size_t i = 0; i<clientes.size(); i++)
	{
		if(clientes.at(i)->getNome() == name)
		{
			ind = i;
		}

	}

	if(ind != -1)
	{
		for(size_t i =0; i<clientes.at(ind)->getContas().size(); i++)
		{
			soma += clientes.at(ind)->getContas().at(i)->getSaldo();
		}

		return soma;
	}
	else
		return -1;
}



//Gerente
int Gerente::getID() const {
	return ID;
}

string Gerente::getNome() const {
	return nome;
}

