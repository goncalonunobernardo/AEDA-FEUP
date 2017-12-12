#include <iostream>
#include <string>
#include <fstream>
#include "Dicionario.h"
#include "BST.h"

using namespace std;


BST<PalavraSignificado> Dicionario::getPalavras() const
{ return palavras; }



bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const
{

	return (palavra < ps1.palavra);
}

bool PalavraSignificado::operator == (const PalavraSignificado &ps1) const
{
	return (palavra == ps1.palavra);
}

void Dicionario::lerDicionario(ifstream &fich)
{
	string pal, significado;

	while(!fich.eof())
	{
		getline(fich, pal);
		getline(fich, significado);

		PalavraSignificado p1(pal,significado);
		palavras.insert(p1);
	}
}


string Dicionario::consulta(string palavra) const
{
    BSTItrIn<PalavraSignificado> it(palavras);
    PalavraSignificado panterior("","");
    PalavraSignificado pdepois("","");

    while(!it.isAtEnd())
    {
    	pdepois = it.retrieve();

    	if(it.retrieve().getPalavra() == palavra)
    		return(pdepois.getSignificado());
    	else if(pdepois.getPalavra() > palavra)
    		throw(PalavraNaoExiste(panterior,pdepois));

    	panterior = it.retrieve();

    	it.advance();
    }
	return "";
}


bool Dicionario::corrige(string palavra, string significado)
{
		BSTItrIn<PalavraSignificado> it(palavras);

		while (!it.isAtEnd())
		{
			if (it.retrieve().getPalavra() == palavra)
			{
				palavras.remove(PalavraSignificado(palavra,""));
				palavras.insert(PalavraSignificado(palavra,significado));
				return true;
			}
			it.advance();
		}

		palavras.insert(PalavraSignificado(palavra,significado));
		return false;
}


void Dicionario::imprime() const
{
	BSTItrIn<PalavraSignificado> it(palavras);

	while(!it.isAtEnd())
	{
		cout << it.retrieve().getPalavra()<< endl <<it.retrieve().getSignificado() << endl;
		it.advance();

	}
}
