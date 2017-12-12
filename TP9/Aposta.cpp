#include "Aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

bool Aposta::contem(unsigned num) const
{
	for (auto it =numeros.begin();it!=numeros.end();it++){
			if ((*it)==num)
				return true;
		}
		return false;
}


void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
	numeros.clear();

	for(size_t i = 0; i < valores.size(); i++)
	{
		if(numeros.size() == n)
			break;

		if(!contem(valores.at(i)))
			numeros.insert(valores.at(i));
	}
}


unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
	unsigned certos = 0;

	for(auto it = sorteio.begin(); it != sorteio.end(); it++)
	{
		if(contem((*it)))
			certos++;
	}
	return certos;
}
