/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name){

	vector<Mail *> tempmail;

	for(unsigned int i = 0; i < postmen.size(); i++)
	{
		if(postmen.at(i).getName() == name)
		{
			tempmail = postmen.at(i).getMail();
			postmen.erase(postmen.begin() + i);
		}

	}

	return tempmail;
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance)
{
	//adding moneyzz to balancezz
	unsigned int cntbalance = 0;
	for(unsigned int i = 0; i < mailToSend.size(); i++ )
	{
		cntbalance += mailToSend.at(i)->getPrice();
	}
	//Getting the balance into the actual variable
	balance = cntbalance;

	//Taking care of correspondence
	string zipcode;
	vector<Mail *> mail;

	while(mailToSend.size() != 0){
		zipcode = mailToSend.at(0)->getZipCode();

		if(zipcode >= firstZipCode && zipcode <= lastZipCode) 		//If in range of zipcode
			addMailToDeliver(mailToSend.at(0));
		else											//Not so much
			mail.push_back(mailToSend.at(0));

		//Eliminating index of mailsToSend
		mailToSend.erase(mailToSend.begin());
	}

	return mail;
}

Postman PostOffice::addMailToPostman(Mail *m, string name)
{
	for(unsigned int i= 0; i<postmen.size(); i++)
	{
		if(postmen.at(i).getName() == name)
		{//add the mail
			postmen.at(i).addMail(m);
		 //return the postman
			return postmen.at(i);
		}

	}

	throw (NoPostmanException(name));
}
