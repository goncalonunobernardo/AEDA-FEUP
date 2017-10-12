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

bool Zoo::removeVeterinario(string nomeV) {
	int indiceVet = -1;

	for (auto i = 0; i < veterinarios.size(); i++)
		if (veterinarios.at(i)->getNome() == nomeV) //going through vet vector to find the name of the removable vet
			indiceVet = i;

	if (indiceVet == -1) // didn't found the vet
		return false;


	//GIVING REMAINING VETS TO PUPPIES & BATS
	for (auto i = 0; i < animais.size(); i++)
		if (animais.at(i)->getVet()->getNome() == nomeV)
			animais.at(i)->setVet(veterinarios.at((indiceVet + 1) % veterinarios.size()));

	//REMOVING THE VET. SO LONG
	veterinarios.erase(veterinarios.begin() + indiceVet);

	return true;
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


/*RESPOSTA À QUESTÃO G) DA FICHA 2 ATRAVÉS DO MIGUELPDUARTE, QUE TÁ DEMASIADO BOA PARA NAOa SER PARTILHADA
QUESTÃO:
Pode o vetor veterinarios ser “vector<Veterinario>” e não “vector<Veterinario *>”?
RESPOSTA:
O vetor de veterinários pode ser um vetor de objetos e não de apontadores pois não usufrui de caraterísticas polimórficas.
* Esta implementação será, porém, menos eficiente e mais volátil, pois grande parte das operações com vetores,
* nomeadamenete o aumento do seu tamanho, quando ultrapassa a capacidade alocada, implica operações de cópia.
* Para além de ser menos eficiente pois tem de haver criação de novos objetos, também é uma situação volátil pois apontadores
* para elementos do vetor podem ficar inválidos, apontando para cópias antigas do objeto.
* Elaboração:
* Objeto está no vetor. Apontador é criado para o objeto no vetor.
* Objeto é copiado quando o vetor precisa de ser realocado. Vetor antigo tem a sua memória desalocada.
* Apontador previamente referido é agora inválido, tendo muitas vezes "undefined behaviour".
*/