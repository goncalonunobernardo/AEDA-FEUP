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


void Dicionario::lerDicionario(ifstream &fich)
{
	string palavra, significado;

	//Getting the word through the file
	while(getline(fich,palavra))
	{
		getline(fich, significado); //Get the meaning
		//Removing "\r" from txt files
		if(palavra.at(palavras.size()-1) == '\r')
			palavra.erase(palavras.size()-1);
	}
	return;
}


string Dicionario::consulta(string palavra) const
{
     // a alterar
	return "";
}


bool Dicionario::corrige(string palavra, string significado)
{
	// a alterer
		return true;
}


void Dicionario::imprime() const
{
	// a alterar
     return;
}
