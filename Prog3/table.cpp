#include "table.h"
using namespace std;

//Laura Cornwell Engmram - CS163
//
//This program is designed to implement a hash function to store and search websites by term and description, within
//a table ADT. The client will need to prepare term and description arrays, or utilize the exernal file for entering
//information into the ADT.
//
// This file implements the table ADT public member functions, which will be used by the client. The functions mostly
// utilitize the "entry" structure to move data between the ADT and the client, as well as certain arrays, most importantly
// that for the term or keyword array. New keywords are copied from the entry structure, which is ultimately fed into the hash
// function. But searches will require separate arrays, which again will be hasshed to index the correct location on the table
// ADT.

//Constructor
table::table(int size)
{
	tablesize = size;
	hashtable = new node*[size];
       	for (int i = 0; i < size; ++i) hashtable[i] = NULL;
}

//Destructor
table::~table()
{
	node * target = NULL;

	for (int i = 0; i < tablesize; ++i) {
		while (hashtable[i]) {
			delete [] hashtable[i]->data.term;
			delete [] hashtable[i]->data.description;
			hashtable[i]->data.term = NULL;
			hashtable[i]->data.description = NULL;
			removesites(hashtable[i]->data.head);
			target = hashtable[i];
			hashtable[i] = hashtable[i]->link;
			delete target;
			target = NULL;
		}
	}
	delete [] hashtable;
	hashtable = NULL;
}


//Function to Add a Term with List of Websites
int table::addterm(const entry & input)
{
	int returntype =  0;
	char * key = NULL;
	key = new char[strlen(input.term) + 1];
   	strcpy(key, input.term); 
    	int hash = hashfunction(key);
    	returntype = addterm(hashtable[hash], key, input);
	delete [] key; key = NULL;
	return returntype;
}

int table::addterm(node *&  head, char * key, const entry & input)
{
	if (!input.head || !input.term) return 0;
    	if (!head) { 
		head = new node; 
		head->link = NULL; 
		head->data.term = new char[strlen(input.term) +1]; 
		head->data.description = new char[strlen(input.description) +1]; 
		strcpy(head->data.term, key); 
		strcpy(head->data.description, input.description);
		addsites(head->data.head, input.head);
		return 1;
	}
    	if (head && strcmp(head->data.term, input.term) != 0) return addterm(head->link, key, input);
    	return 0;
}

//Copy site list from  entry to entry
int table::addsites(snode *& target, snode * head)
{
	if (!head || target) return 0;
	if (!head->next) {
		target = new snode;
		target->site = new char[strlen(head->site) + 1];
		strcpy(target->site, head->site);
		target->next = NULL;
		return 1;
	}
	else {
		target = new snode;
		target->site = new char[strlen(head->site) + 1];
		strcpy(target->site, head->site);
		target->next = NULL;
	       	return addsites(target->next, head->next);
	}
}


//Function to display the data matching the keyword
int table::displaymatch(char * key)
{
	int hash = hashfunction(key);
	return displaymatch(hashtable[hash], key);
}


int table::displaymatch(node * head, char * key)
{
	if (!head) return 0;
	if (!head->link) {
		if (strcmp(key, head->data.term) == 0) {
			cout << "\n\nKeyword:\t" << key << "\nDescription:\t" << head->data.description << "\n\nWebsites:";
			return displaymatch(head, head->data.head, key) + 1; 
			
		}
		else return 0;
	}
	else {
		if (strcmp(key, head->data.term) == 0) {
			cout << "\n\nKeyword:\t" << key << "\nDescription:\t" << head->data.description << "\n\nWebsites:";
			return displaymatch(head, head->data.head, key) + 1;
		        	
		}
		else return displaymatch(head->link, key);
	}
	return 0;
}

int table::displaymatch(node * heada, snode * head, char * key)
{
	if (!head) {
		cout << "\n\t[No websites to show]" << endl;
		return 0;
	}
	if (!head->next) {
		cout << "\n\t" << head->site << endl;
		return 10;
	}
	else {
		cout << "\n\t" << head->site;
		return displaymatch(heada, head->next, key) + 10;
	}
	return 0;
}

//Function to load terms and associated data from an external file
int table::loadfromfile()
{
	ifstream file_in;
	ifstream char_in;
	int count = 0;
	int sites = 0;
	entry newentry;
		
	file_in.open("terms.csv");
	char_in.open("term.csv");
	if (!file_in || file_in.eof()) return 0;
	while (file_in && !file_in.eof())
	{	
		count = loadfromfile(char_in);
		file_in >> sites; file_in.ignore(1, ',');
		count = loadfromfile(char_in);	
		newentry.term = new char[count];
		file_in.get(newentry.term, (count - 1), ','); file_in.ignore(1, ',');
		count = loadfromfile(char_in);	
		newentry.description = new char[count];
		file_in.get(newentry.description, (count - 1), ','); file_in.ignore(1, ',');
		int nodecount = 0;
		loadfromfile(newentry.head, char_in, file_in, sites, nodecount);
		snode * current = NULL;
		addterm(newentry);
		delete [] newentry.term; newentry.term = NULL;
		delete [] newentry.description; newentry.description = NULL;
		removesites(newentry.head); 
		file_in.peek();
	}
	file_in.close();
	char_in.close();
	return 1;
}

int table::loadfromfile(ifstream &file_in)
{
	char slot;
	int count = 1;

	if (!file_in || file_in.eof()) return 0;
	while (file_in && !file_in.eof() && !(slot  == ',')) {
		file_in >> slot;
		if (file_in.peek() == ' ') ++count;
		++count;
	}
	return count;
}

int table::loadfromfile(snode *& head, ifstream & char_in, ifstream & file_in, int sites, int &nodecount)
{	
	int count = 0;
	
	if (head) return 0;
	if (sites == nodecount) return nodecount;
	head = new snode; 
	count = loadfromfile(char_in);
	head->site = new char[count];
	file_in.get(head->site, (count - 1), ','); file_in.ignore(1, ',');
	++nodecount;
	return loadfromfile(head->next, char_in, file_in, sites, nodecount);
}

//Remove site list from an entry
int table::removesites(snode *& head)
{
	if (!head) return 0;
	if (!head->next) {
		delete [] head->site; head->site = NULL;
		delete head;
		head = NULL;
		return 1;
	}
	else {
		delete [] head->site; head->site = NULL;
		removesites(head->next);
		delete head; head = NULL;
	}
	return 1;
}

//Funtion to add a site to a term
int table::addsitetoterm(char * website, char * key)
{
	int hash = hashfunction(key);
	return addsitetoterm(hashtable[hash], website, key);
}

int table::addsitetoterm(node * head, char * website, char * key)
{
	if (!head) return 0;
	if (!head->link) {
		if (strcmp(key, head->data.term) == 0) {
			return addsitetoterm(head->data.head, website) + 1; 
			
		}
		else return 0;
	}
	else {
		if (strcmp(key, head->data.term) == 0) {
			return addsitetoterm(head->data.head, website) + 1; 
		}
		else return addsitetoterm(head->link, website, key);
	}

}

int table::addsitetoterm(snode *& head, char * website)
{
	if (!head) {
		head = new snode;
		head->next = NULL;
		head->site = new char[strlen(website) + 1];
		strcpy(head->site, website);
		return 1;
	}
	return addsitetoterm(head->next, website);
}

//Funtion to remove a term and all data
int table::remove(char * key)
{
	int hash = hashfunction(key);
	return remove(hashtable[hash], key);
}

int table::remove(node *& head, char * key)
{
	node * target = NULL;

	if (!head) return 0;
	if (!head->link) {
		if (strcmp(key, head->data.term) == 0) {
			removesites(head->data.head); 
			delete [] head->data.term; head->data.term = NULL;
			delete [] head->data.description; head->data.description = NULL;
			delete head;
			head = NULL;
			return 1;
		}
		else return 0;
	}
	if (!head->link->link) {
		if (strcmp(key, head->data.term) == 0) {
			removesites(head->data.head); 
			delete [] head->data.term; head->data.term = NULL;
			delete [] head->data.description; head->data.description = NULL;
			target = head;
			head = head->link;
			delete target;
			target = NULL;
			return 1;
		}
		if (strcmp(key, head->link->data.term) == 0) {
			removesites(head->link->data.head); 
			delete [] head->link->data.term; head->link->data.term = NULL;
			delete [] head->link->data.description; head->link->data.description = NULL;
			delete head->link;
			head->link = NULL;
			return 1;
		}
		else return 0;
	}
	else {
		if (strcmp(key, (head->link->data.term)) == 0) {
			removesites(head->link->data.head);
			target = head->link;
			head->link = head->link->link;
			delete [] target;
			delete target;
		       	target = NULL;
			return 1;	
		}
		else return remove(head->link, key);
	}
}

//Function to feed data associated with a term into an argument
int table::retrievematch(char * key, entry & find)
{
	int hash = hashfunction(key);
	return retrievematch(hashtable[hash], key, find);
}

int table::retrievematch(node * head, char * key, entry & find)
{
	if (!head) return 0;
	if (!head->link) {
		if (strcmp(key, head->data.term) == 0) {
			find.term = new char[strlen(key) + 1];
			strcpy(find.term, key);
			find.description = new char[strlen(head->data.description) + 1];
			strcpy(find.description, head->data.description);
			return addsites(find.head, head->data.head);
			
		}
		else return 0;
	}
	else {
		if (strcmp(key, head->data.term) == 0) {
			find.term = new char[strlen(key) + 1];
			strcpy(find.term, key);
			find.description = new char[strlen(head->data.description) + 1];
			strcpy(find.description, head->data.description);
			return addsites(find.head, head->data.head);
		        	
		}
		else return retrievematch(head->link, key, find);
	}
	return 0;
}

//Function to remove all terms that contain a scepecific link
int table::rmtermwithsite(char * website)
{
	int removed = 0;
	int returnvalue = 0;
       	for (int i = 0; i < tablesize; ++i) {
		removed = rmtermwithsite(hashtable[i], website);
		if (removed > 0) returnvalue += removed;
	}
	return returnvalue;
}

int table::rmtermwithsite(node * head, char * website)
{
	int returnvalue = 0;
	if (!head) return 0;
	if (!head->link) {
			if (rmmatchingsites(head->data.head, website) ==  true) {
			 	remove(head->data.term); 
				return 101; 
			}
	}
	else {
			if (rmmatchingsites(head->data.head, website) == true) {
				remove(head->data.term); 
				returnvalue = 1; 
			}
			return rmtermwithsite(head->link, website) + 100 + returnvalue; 

	}
	return 0;
}

bool table::rmmatchingsites(snode *& head, char * website)
{
	if (!head) return false;
	if (!head->next) {
		bool returnvalue = false;
		int count = 0;
		for (int i = 0; head->site[i] != '\0'; ++i) {
			if (head->site[i] == website[0]) {
				for (int j = 0; website[j] != '\0'; ++j) if (website[j] == head->site[i+j]) ++count;
				if (count == strlen(website)) returnvalue = true; 
				count = 0;
			}
		}
		return returnvalue;
	}
	else {
		bool returnvalue = false;
		int count = 0;
		for (int i = 0; head->site[i] != '\0'; ++i) {
			if (head->site[i] == website[0]) {
				for (int j = 0; website[j] != '\0'; ++j) if (website[j] == head->site[i+j]) ++count;
				if (count == strlen(website)) returnvalue = true; 
				count = 0;
			}
		}
		if (returnvalue) return returnvalue;
		return rmmatchingsites(head->next, website);

	}
	return false;
}


//Function to display all data in the hashtable.
int table::displayall()
{
	int indexes = 0;
	int returnvalue = 0;
       	for (int i = 0; i < tablesize; ++i) {
		cout << "\n\nTable index: " << i << endl;
		indexes  = displayall(hashtable[i]);
		if (indexes > 0) returnvalue += indexes;
	}
	return returnvalue;
}


int table::displayall(node * head)
{
	if (!head) return 0;
	if (!head->link) {
			cout << "\n\nKeyword:\t" << head->data.term << "\nDescription:\t" << head->data.description << "\n\nWebsites:";
			displaymatch(head, head->data.head, head->data.term); 
			return 1;
	}
	else {
			cout << "\n\nKeyword:\t" << head->data.term << "\nDescription:\t" << head->data.description << "\n\nWebsites:";
			displaymatch(head, head->data.head, head->data.term);
		        return displayall(head->link) + 1;	
	}
	return 0;
}

