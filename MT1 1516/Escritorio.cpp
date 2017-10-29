#include "Escritorio.h"
#include <iostream>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }



//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }

bool Impressora::imprime(Documento doc1) {
	return false;
}
//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }
bool ImpressoraPB::imprime(Documento doc1){
	int nrpaginas = doc1.getNumPaginas();

	if(nrpaginas < numPagImprimir)
	{
		numPagImprimir = numPagImprimir - nrpaginas;
		docsImpressos.push_back(doc1);
		return true;
	}
	else
		return false;
}


//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo) return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}
bool ImpressoraCores::imprime(Documento doc1)
{
	int nrpaginas = doc1.getNumPaginas();
	float nrpaginaspreto = doc1.getPercentagemPreto();
	float nrpaginasamarelo = doc1.getPercentagemAmarelo();

	if((nrpaginas*nrpaginaspreto < numPagImprimirPreto) && (nrpaginas*nrpaginasamarelo < numPagImprimirAmarelo))
	{
		numPagImprimirAmarelo -= nrpaginas*nrpaginasamarelo; //Like Rui said in his repo
		numPagImprimirPreto -= nrpaginas*nrpaginaspreto; //we're updating the n. of pages both yellow and black
		return true;
	}

	else
		return false;
}



//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }

int Escritorio::numImpressorasSemResponsavel() const{
	int counter = 0;

	for (size_t i = 0; i< funcionarios.size(); i++)
	{
		counter += funcionarios.at(i).getImpressoras().size();
	}

	return impressoras.size() - counter;
}

vector<Impressora *> Escritorio::retiraImpressoras(int ano1)
{
	vector<Impressora *> impressremovida;

	for(size_t i = 0; i<impressoras.size(); i++)
	{
		if(impressoras.at(i)->getAno() < ano1)
		{
			impressremovida.push_back(impressoras.at(i));
			impressoras.erase(impressoras.begin() + i);
			i--;
		}
	}

	return impressremovida;
}

