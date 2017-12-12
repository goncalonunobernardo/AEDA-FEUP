#include "Jogo.h"

BinaryTree<Circulo> & Jogo::getJogo() {
	return jogo;
}

void Circulo::mudaEstado()
{
	if(estado == true){
		estado = false;
		return;
	}
	else if(estado == false)
		estado = true;
}
void Circulo::incNvisitas()
{
	nVisitas++;
}

BinaryTree<Circulo> Jogo::iniciaJogo(int pos, int niv, vector<int>& pontos, vector<bool>&estados)
{
	Circulo c1(pontos.at(pos), estados.at(pos));

	if(niv==0) return BinaryTree<Circulo> (c1);

	BinaryTree<Circulo> filhoEsquerdo = iniciaJogo(2*pos+1, niv-1, pontos, estados);
	BinaryTree<Circulo> filhoDireito = iniciaJogo(2*pos+2, niv-1, pontos, estados);

	return BinaryTree<Circulo> (c1,filhoEsquerdo,filhoDireito);
}
ostream &operator << (ostream &os, Circulo &c1)
{
	// a alterar
	return os;
}



Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{
	jogo = iniciaJogo(0,niv,pontos,estados);
}


string Jogo::escreveJogo()
{
	BTItrLevel<Circulo> it(jogo);
	Circulo circulo;
	string jogo;
	string t = "true" , f = "false";

	// Iterate though the tree (by level) and add the info. to the string
	while (!it.isAtEnd()){
		circulo = it.retrieve();

		jogo += to_string(circulo.getPontuacao()) + "-";
		jogo += (circulo.getEstado() ? t : f) + "-";
		jogo += to_string(circulo.getNVisitas()) + "\n";

		it.advance();
	}

	return jogo;
}


int Jogo::jogada()
{
	int score = 1;
	int n = 1;
	BTItrLevel<Circulo> it(jogo);

	while(!it.isAtEnd())
	{
		Circulo & circulo = it.retrieve();

		if(circulo.getPontuacao() != n)
		{
			it.advance();
			continue;
		}

		if(circulo.getEstado())
			n = n*2+1;
		else
			n*=2;

		score = circulo.getPontuacao();
		circulo.mudaEstado();
		circulo.incNvisitas();
	}


	return score;
}



int Jogo::maisVisitado()
{
	BTItrLevel<Circulo> it(jogo);
	int nVis = 0;

	if(it.isAtEnd())
		return 0;

	it.advance(); //skip the rooterino

	while(!it.isAtEnd())
	{
		if(it.retrieve().getNVisitas() > nVis)
			nVis = it.retrieve().getNVisitas();

		it.advance();
	}

	return nVis;
}




