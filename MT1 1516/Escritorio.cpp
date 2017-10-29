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

	if(nrpaginas <= numPagImprimir)
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

	if((nrpaginas*nrpaginaspreto <= numPagImprimirPreto) && (nrpaginas*nrpaginasamarelo <=
			numPagImprimirAmarelo))
	{
		numPagImprimirAmarelo -= nrpaginas*nrpaginasamarelo; //Like Rui said in his repo
		numPagImprimirPreto -= nrpaginas*nrpaginaspreto; //we're updating the n. of pages both yellow and black
		docsImpressos.push_back(doc1);
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

Impressora * Escritorio::imprimeDoc(Documento doc1) const
{
	for(size_t i = 0; i < impressoras.size(); i++)
	{
		if(impressoras.at(i)->imprime(doc1))
			return impressoras.at(i);
	}

	return(new ImpressoraPB("inexistente",0,0));
}

vector<Impressora *> Escritorio::tonerBaixo() const
{
	string tipo;
	vector<Impressora*> impressorasbaixot;

	for(size_t i = 0; i <impressoras.size(); i++)
	{
		tipo = impressoras.at(i)->getTipo();
		if(tipo == "Cores")
		{
			if(impressoras.at(i)->getNumPaginasImprimir() < 20)
				impressorasbaixot.push_back(impressoras.at(i));
		}
			else
			{
				if (impressoras.at(i)->getNumPaginasImprimir() < 30)
					impressorasbaixot.push_back(impressoras.at(i));
			}
		}
	return impressorasbaixot;
}


Documento& Documento::operator+(const Documento &d1)
{
	float bdblack = ((pPreto*numPaginas + d1.getPercentagemPreto()*d1.getNumPaginas())/(numPaginas + d1.getNumPaginas()));
	float bdyellow = (pAmarelo*numPaginas + d1.getPercentagemAmarelo()*d1.getNumPaginas())/(numPaginas + d1.getNumPaginas());

	int pages = numPaginas + d1.getNumPaginas();
	Documento *newdoc = new Documento(pages,bdblack,bdyellow);

	return *newdoc;
}


string Escritorio::operator()(const string & codigo) const
{
	for(size_t i = 0; i< funcionarios.size(); i++)
		for(size_t j = 0; j<funcionarios.at(i).getImpressoras().size(); j++)
			if(funcionarios.at(i).getImpressoras().at(j)->getCodigo() == codigo)
				return funcionarios.at(i).getCodigo();

	return "nulo";
}
