#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "BST.h"


class PalavraSignificado {
      string palavra;
      string significado;
public:
       PalavraSignificado(string p, string s): palavra(p), significado(s) {}
       string getPalavra() const { return palavra; }
       string getSignificado() const { return significado; }
       void setSignificado(string sig) { significado = sig; }
       bool operator < (const PalavraSignificado &ps1) const;
       bool operator == (const PalavraSignificado &ps1) const;
};

class Dicionario
{
      BST<PalavraSignificado> palavras;
public:
      Dicionario(): palavras(PalavraSignificado("","")){};
      BST<PalavraSignificado> getPalavras() const;
      void lerDicionario(ifstream &fich);
      string consulta(string palavra) const;
      bool corrige(string palavra, string significado);
      void imprime() const;
};


// a alterar
class PalavraNaoExiste
{
private:
	PalavraSignificado p_antes;
	PalavraSignificado p_depois;
public:
	PalavraNaoExiste(const PalavraSignificado& panterior, const PalavraSignificado& pdepois) : p_antes(panterior), p_depois(pdepois) {}
	string getPalavraAntes() const { return p_antes.getPalavra();}
	string getSignificadoAntes() const { return p_antes.getSignificado();}
	string getPalavraApos() const { return p_depois.getPalavra();}
	string getSignificadoApos() const { return p_depois.getSignificado(); }
};



#endif
