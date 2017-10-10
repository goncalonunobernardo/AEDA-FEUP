#include "zoo.h"

/* VETERINÁTRIO */
Veterinario::Veterinario(string nome, int cod) : nome(nome), codOrdem(cod) {}

string Veterinario::getNome() const {
	return nome;
}

/* ANIMAL */
int Animal::maisJovem = -1; //Initializing, because initially none
							//of them is younger.


Animal::Animal(string nome, int idade) : nome(nome), idade(idade) 
{
	vet = NULL; // ain't no vet in here
	if (maisJovem == -1) // none of them is younger
		maisJovem = idade;
	else if (idade<maisJovem)
		maisJovem = idade;

}
int Animal::getMaisJovem()
{
	return maisJovem;
}
string Animal::getNome() const {
	return nome;
}
string Animal::getInformacao() const
{
	string inf;
	inf = nome + ", " + to_string(idade); //sem vets

	return inf;
}

//VOADOR
Voador::Voador(int vmax, int amax) : velocidade_max(vmax), altura_max(amax){}

string Voador::getInformacao() const
{
	string inf;
	inf = to_string(velocidade_max) + ", " + to_string(altura_max);

	return inf;
}

//ZOO
void Zoo::adicionaAnimal(Animal *a1)
{
	animais.push_back(a1);
}
int Zoo::numAnimais() const
{
	return animais.size();
}

int Zoo::numVeterinarios() const
{
	return veterinarios.size();
}

string Zoo::getInformacao() const
{
	string inf;

	for (unsigned int i = 0; i < animais.size(); i++)
	{
		inf += animais.at(i)->getInformacao();
		inf += "\n";
	}
	return inf;
}

//CAO
Cao::Cao(string nome, int idade, string raca) : Animal(nome, idade), raca(raca) {}

bool Cao::eJovem() const
{
	if (idade < 5)
		return true;

	return false;

}
string Cao::getInformacao() const
{
	string inf;
	inf = Animal::getInformacao() + ", " + raca;

	return inf;
}

//MORCEGO
Morcego::Morcego(string nome, int idade, int vmax, int amax) :Animal(nome, idade), Voador(vmax, amax)
{
}

bool Morcego::eJovem() const
{
	if (idade<4)
		return true;

	return false;
}

string Morcego::getInformacao() const
{
	string inf;
	inf = Animal::getInformacao() + ", " + Voador::getInformacao();
	return inf;
}