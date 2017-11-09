/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
#include <sstream>
using namespace std;


unsigned Jogo::numPalavras(string frase)
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
{
	// a alterar
}

Jogo::Jogo(list<Crianca>& lc2)
{
	// a alterar
}

void Jogo::insereCrianca(const Crianca &c1)
{
	// a alterar
}

list<Crianca> Jogo::getCriancasJogo() const
{
	// a alterar
	list<Crianca> res;
	return res;
}


string Jogo::escreve() const
{
	// a alterar
	string res;
	return res;
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
	// a alterar
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
