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
/* Esta função atualiza todas as contas existentes,
debitando a taxa de serviço correspondente às contas
normais.Retorna a soma dos saldos de todas as contas da
agência, após esta atualização.*/
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

//Gerente
int Gerente::getID() const {
	return ID;
}

string Gerente::getNome() const {
	return nome;
}

