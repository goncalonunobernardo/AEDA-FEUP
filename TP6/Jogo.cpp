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
	// a alterar
	Crianca *c1 = new Crianca();
	return *c1;
}


list<Crianca>& Jogo::inverte()
{
	// a alterar
	return criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
	// a alterar
		list<Crianca> res;
		return res;
}


void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
	criancas = l1;
}


bool Jogo::operator==(Jogo& j2)
{
	// a alterar
	return true;
}


list<Crianca> Jogo::baralha() const
{
	// a alterar
	list<Crianca> res;
	return res;
}
