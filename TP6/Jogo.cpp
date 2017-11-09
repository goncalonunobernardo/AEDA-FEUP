/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
#include <sstream>
#include <iterator>
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
using namespace std;


unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;
  int n=1;
  int pos = frase.find(' ');
  while ( pos != string::npos ) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}


Jogo::Jogo()
{}

Jogo::Jogo(list<Crianca>& lc2) : criancas(lc2)
{}

void Jogo::insereCrianca(const Crianca &c1)
{
	criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
	return criancas;
}


string Jogo::escreve() const
{
	string output;

	for(auto it = criancas.begin(); it != criancas.end(); it++)
	{
		output += it->escreve() + "\n";
	}

	return output;
}


Crianca& Jogo::perdeJogo(string frase)
{
	unsigned int npalavras = numPalavras(frase);

	unsigned long indexToRemove;
	list<Crianca> temp = criancas; //vetor temporário porque nao quero afetar a lista original

	while(temp.size() > 1)
	{
		indexToRemove = (npalavras % temp.size()) + 1; //tratar da pessoa que se salvou
		auto it = temp.begin();

		advance(it,indexToRemove);
		temp.erase(it);
	}

	return temp.front();
}


list<Crianca>& Jogo::inverte()
{
	/*
		list<Crianca> l1;
		list<Crianca>::iterator it = criancas.begin();
		list<Crianca>::iterator ite = criancas.end();
		while ( it != ite )
		{
			Crianca *c = new Crianca(*it);
			l1.push_front(*c);
			it ++;
		}
		criancas = l1;
		*/
	criancas.reverse();
	return this->criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
	list<Crianca> out;
	for(auto it = criancas.begin(); it != criancas.end(); it++)
	{
		if(it->getIdade() > id)
		{
			out.push_back(*it);
			criancas.erase(it);
		}
	}

	return out;
}


void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
	criancas = l1;
}


bool Jogo::operator==(Jogo& j2)
{
	if(this->criancas.size() != j2.criancas.size())
		return false;

	auto it1 = this->criancas.begin();
	auto it2 = j2.criancas.begin();

	for( ; it1 != criancas.end(); it1++, it2++)
	{
		if(!(*it1 == *it2))
			return false;
	}

	return true;
}


list<Crianca> Jogo::baralha() const
{
	// a alterar
	list<Crianca> res;
	return res;
}
