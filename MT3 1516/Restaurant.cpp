/*
 * Restaurant.cpp
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#include "Restaurant.h"
#include <algorithm>
#include <iostream>

using namespace std;

Restaurant::Restaurant() { }

Restaurant::Restaurant(vector< stack<Dish*> >* cl, queue<Dish*>* di, list<Dish*>* dr) {
	if(cl != NULL) clean = *cl;
	if(di != NULL) dirty = *di;
	if(dr != NULL) drying = *dr;
}

void Restaurant::addTable(unsigned int n_places) {
	tables.push_back(Table(n_places));
}

void Restaurant::addTable(Table& t) {
	tables.push_back(t);
}

const Table& Restaurant::getTable(vector<Table>::size_type idx) const {
	return tables[idx];
}

/**
 * Gets the clean dishes stack for a given collection and type.
 * If there is none, adds and returns an empty stack.
 */
stack<Dish*>& Restaurant::getCleanDishStack(string collection, TypeOfDish type) {

	for(vector< stack<Dish*> >::iterator it = clean.begin(); it != clean.end(); ++it) {
		if((*it).empty() || ((*it).top()->getCollection() == collection && (*it).top()->getType() == type)) {
			return *it;
		}
	}

	stack<Dish*> st;
	clean.push_back(st);
	return clean.back();
}

const queue<Dish*>& Restaurant::getDirty() const {
	return dirty;
}

const list<Dish*>& Restaurant::getDrying() const {
	return drying;
}

/**
 * Adds a number of dishes of a collection/type to the respective clean stack.
 */
void Restaurant::addDishes(unsigned int n, string collection, TypeOfDish type) {

	for(size_t i = 0; i < n; i++)
	{
		Dish * d = new Dish(collection, type);
		this->getCleanDishStack(collection,type).push(d);
	}
}

/**
 * Washes a dish, getting if from the dirty queue and putting it in the wet list.
 * Returns the washed dish.
 */
Dish* Restaurant::washDish() {
	Dish* d = dirty.front();	// Get the front dish from the dirty dishes queue
	dirty.pop();				// Remove it from the queue

	//Wash it
	drying.push_back(d);

	return d;
}

/**
 * Clears a table, placing all dishes that are on it in the dirty queue.
 */
void Restaurant::clearTable(vector<Table>::size_type idx) {

	if(tables.size() > idx)
	{
		for(auto p: tables.at(idx).getPlaces())
		{
			while(!(p.empty()))
			{
			dirty.push(p.top());
			p.pop();
			}
		}

		tables.at(idx).clear();
	}

	return;
}

/**
 * Stores in the respective clean stack all drying dishes of a given collection and type.
 */
void Restaurant::storeDryDishes(string collection, TypeOfDish type) {

	for(auto i = drying.begin(); i != drying.end(); i++)
	{
		if(((*i)->getCollection()== collection) && ((*i)->getType() == type))
		{
			this->getCleanDishStack(collection, type).push((*i));
			i = drying.erase(i);

			if(i != drying.begin())
				i--;
		}
	}
}

/**
 * Puts Plates of a given collection in a table.
 * Throws TableNotReadyException when the table is not empty.
 * Throws NotEnoughDishesException when there are not enough clean plates of the collection.
 */
void Restaurant::setupTable(vector<Table>::size_type idx, string collection) {
vector<Dish *> d;

	if(idx >= tables.size() || idx < 0)
		return;
	if(!tables.at(idx).empty())
		throw TableNotReadyException();
	else
	{
		if(getCleanDishStack(collection, Plate).size() < tables.at(idx).size())
			throw NotEnoughDishesException();
		else
		{
			for(size_t i = 0; i < tables.at(idx).size(); i++)
			{
				d.push_back(getCleanDishStack(collection,Plate).top());
				getCleanDishStack(collection,Plate).pop();
			}

			tables.at(idx).putOn(d);
		}
	}
}

bool sortDishes( Dish* d1, Dish* d2)
{
	if(d1->getCollection() == d1->getCollection())
		return d1->getType() < d2->getType();
	else
		return d1->getCollection() < d2->getCollection();
}
/**
 * Picks the dry dishes and groups them.
 * Returns the grouped dishes.
 */
list<Dish*> Restaurant::pickupAndGroupDryDishes() {
	list<Dish*> dry_grouped;

	while(!drying.empty()){
		vector<Dish*> v;
		v.push_back(*drying.begin());
		drying.erase(drying.begin());
		for(auto it=drying.begin();it!=drying.end();it++)
			if(**it==**v.begin()){
				v.push_back(*it);
				it=drying.erase(it);
				if(it!=drying.begin())
					it--;
			}

		for(int i=0;i<v.size();i++)
			dry_grouped.push_back(v.at(i));
	}

	return dry_grouped;
}

/**
 * Stores grouped dishes in the respective clean stacks.
 * Returns the number of stacks that have been updated.
 */
int Restaurant::storeGroupedDishes(list<Dish*> grouped_dishes) {
//RUI'S RESOLUTION
	string collection;
	TypeOfDish type;
	unsigned int dishStackCounter = 0;

	// Iterate through the grouped dishes
	for (auto it=grouped_dishes.begin() ; it!=grouped_dishes.end() ; it++){
		collection = (*it)->getCollection();
		type = (*it)->getType();
		dishStackCounter++;		// Increment the counter
		stack<Dish*> & dishesStack = getCleanDishStack(collection,type);	// Get the stack of the right type of dishes
		while ( ((*it)->getCollection()==collection) && ((*it)->getType()==type)){
			dishesStack.push(*it);
			it++;
			if (it == grouped_dishes.end()) break;
		}
		it--;
	}

	return dishStackCounter;
}

