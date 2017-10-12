#include "zoo.h"

/* VETERINÁTRIO */
Veterinario::Veterinario(string nome, int cod) : nome(nome), codOrdem(cod) {}

string Veterinario::getNome() const {
	return nome;
}
string Veterinario::getInformacao() const {
	return nome + ", " + to_string(codOrdem);
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
	if (vet != nullptr) //EMPTY
		return this->nome + ", " + to_string(this->idade) + ", " + this->vet->getInformacao();

	inf = nome + ", " + to_string(this ->idade); //sem vets

	return inf;
}
void Animal::setVet(Veterinario *v) {
	this->vet = v;
}

Veterinario *Animal::getVet() const {
	return vet;
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

void Zoo::alocaVeterinarios(istream &isV)
{
	string temp, nome, codigostr;

	while (!isV.eof()) {
		getline(isV, nome);
		getline(isV, codigostr);
		Veterinario* tempVet = new Veterinario(nome, stoi(codigostr)); //We are using NEW because it talks about allocating memory
						//Therefore, we should allocate a certain size of bytes to a new memory block.
		veterinarios.push_back(tempVet);
	}

	//GIVING VETS TO PUPPIES & BATS
	for(unsigned int i = 0; i < animais.size(); i++)
		animais.at(i)->setVet(veterinarios.at(i%veterinarios.size())); //EVEN DISTRIBUTION & DISTRIBUTING VETS TO MORE THAN 1 ANIMAL

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