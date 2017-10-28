/*
 * Postman.cpp
 */
#include "Postman.h"

static unsigned int postmanID = 1;


Postman::Postman(): id(0) {}

Postman::Postman(string name): name(name), id(postmanID) {
	postmanID++;
}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}


bool Postman::operator<(const Postman & p2) const
{
	vector <string> zpc1;
	vector <string> zpc2;

	//Taking care of the first zpc
	for(unsigned int i = 0; i < myMail.size(); i++)
		zpc1.push_back(myMail.at(i)->getZipCode());


	vector <Mail *> otherPostman = p2.getMail();

	//Taking care of the second zpc
	for(unsigned int i = 0; i < otherPostman.size(); i++)
		zpc2.push_back(otherPostman.at(i)->getZipCode());

	//Comparing
	return (numberDifferent(zpc1) < numberDifferent(zpc2));

}

