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



