/*
 * Mail.h
 */

#ifndef SRC_MAIL_H_
#define SRC_MAIL_H_

#include <string>
#include <vector>
using namespace std;


class Mail {
	string sender;
	string receiver;
	string zipCode;
public:
	Mail(string send, string rec, string zcode);
	virtual ~Mail();
	string getZipCode() const;
};


class RegularMail: public Mail {
	unsigned int weight;
public:
	RegularMail(string send, string rec, string code, unsigned int w);
};


class GreenMail: public Mail {
	string type;  // "envelope", "bag", "box"
public:
	GreenMail(string send, string rec, string code, string t);
};

template <class T>
unsigned int numberDifferent (const vector<T> & v1){

	vector<T> tempv;

	for(auto i= 0; i<v1.size(); i++)
	{
		bool found = false;
		if(tempv.size()>0)
		{
			for(auto j = 0; j<tempv.size(); j++)
			{
				if(v1.at(i) == tempv.at(j))
				{
					found = true;
					break;
				}
			}
		}
		if(!found)
			tempv.push_back(v1.at(i));
	}
	return (unsigned int)tempv.size();
}

#endif /* SRC_MAIL_H_ */
