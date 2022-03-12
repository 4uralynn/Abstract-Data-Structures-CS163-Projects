#include "table.h"
using namespace std;

//Laura Cornwell Engmram - CS163
//
//This program is designed to implement a hash function to store and search websites by term and description, within
//a table ADT. The client will need to prepare term and description arrays, or utilize the exernal file for entering
//information into the ADT.
//
// This is thr client program that to test the table ADT, hash function, and the member functions..


int main()
{
	int test = 0;
	char input;
	entry object;
	object.term = new char[51];
	object.description = new char[101];
	object.head = new snode;
	object.head->next = NULL;
	object.head->site = new char[101];
	table bigtable;

	do {
		do {
			cout << endl << " ____________________ \n|                    |\n" 	
			     << "| ADP TESTING CLIENT |Tests:                          \n" 
			     << "|____________________|------------------------------- \n" 
			     << "|                |    Add (T)erm   |  Rem(o)ve Term  |\n" 
			     << "|  (L)oad File   |-----------------+-----------------+\n" 
			     << "|________________|  Add (W)ebsite  |  Remo(v)e Link  |\n"
			     << "|     (Q)uit     |-----------------+-----------------+\n"
			     << "+================|  Display (K)ey  |(R)etrieve Match |\n"
			     << "                 |-----------------+----------------- \n"
			     << "Enter the        |  Display (A)ll  |/\ncorresponding     "
			     << "-----------------\ncharacter:       ";

			cin.width(1);
			cin >> input;
			cin.ignore(100, '\n');	
		}while('L' != toupper(input) && 'K' != toupper(input) && 'V' != toupper(input) &&
		       'Q' != toupper(input) && 'A' != toupper(input) && 'R' != toupper(input) &&
		       'W' != toupper(input) && 'O' != toupper(input) && 'T' != toupper(input));
	
		if ('L' == toupper(input)) {
			test = bigtable.loadfromfile();
			cout << "\n\nLoad File--Test Result: " << test << endl;	
		}
		if ('W' == toupper(input)) {
			cout << "\n\nWhat term would you like to add a site to?  ";
			cin.get(object.term, 50, '\n');
			cin.ignore(100, '\n');
			cout << "\n\nEnter the site: ";
			cin.get(object.head->site, 100, '\n');
			cin.ignore(100, '\n');
			test = bigtable.addsitetoterm(object.head->site, object.term);
			cout << "\n\nAdd Website--Test Result: " << test << endl;	
		}

		if ('O' == toupper(input)) {
			cout << "\n\nWhat term would you like to remove all information for?  ";
			cin.get(object.term, 50, '\n');
			cin.ignore(100, '\n');
			test = bigtable.remove(object.term);
			cout << "\n\nRemove Term--Test Result: " << test << endl;	
		}

		if ('T' == toupper(input)) {
			cout << "\n\nEnter a new term: ";
			cin.get(object.term, 50, '\n');
			cin.ignore(100, '\n');
			cout << "\n\nEnter the description: ";
			cin.get(object.description, 100, '\n');
			cin.ignore(100, '\n');
			cout << "\n\nEnter a website: ";
			cin.get(object.head->site, 100, '\n');
			cin.ignore(100, '\n');
			test = bigtable.addterm(object);
			cout << "\n\nAdd Term--Test Result: " << test << endl;	
		}

	
		if ('K' == toupper(input)) {
			cout << "\n\nEnter term to lookup: ";
			cin.get(object.term, 50, '\n');
			cin.ignore(100, '\n');

			test = bigtable.displaymatch(object.term);
			cout << "\n\nDisplay Key--Test Result: " << test << endl;	
		}

		if ('A' == toupper(input)) {
			test = bigtable.displayall();
			cout << "\n\nDisplay All--Test Result: " << test << endl;	
		}
		if ('R' == toupper(input)) {
			char response[51];
			delete [] object.term; object.term = NULL;
			delete [] object.description; object.description = NULL;
			delete [] object.head->site; object.head->site = NULL;
			delete object.head; object.head = NULL;
			cout << "\n\nEnter term to match: ";
			cin.get(response, 50, '\n');
			cin.ignore(100, '\n');

			test = bigtable.retrievematch(response, object);
			cout << "\n\nRetrieve Term--Test Result: " << test << endl;	
			if (test > 0) 
				cout << "\n\nAll data for term " << object.term << " has been retrieved.\nNow it will be deleted." << endl;
			delete [] object.term; object.term = NULL;
			delete [] object.description; object.description = NULL;
			bigtable.removesites(object.head);
			object.term = new char[51];
			object.description = new char[101];
			object.head = new snode;
			object.head->next = NULL;
			object.head->site = new char[101];

		}
		if ('V' == toupper(input)) {
			cout << "\n\nRemove terms with the following site: ";
			cin.get(object.head->site, 100, '\n');
			cin.ignore(100, '\n');
			test = bigtable.rmtermwithsite(object.head->site);
			cout << "\n\nRemove Terms Containing Site--Test Result: " << test << endl;	
		}

	}while (!('Q' == toupper(input)));

	delete [] object.term; object.term = NULL;
	delete [] object.description; object.description = NULL;
	delete [] object.head->site; object.head->site = NULL;
	delete object.head; object.head = NULL;

	return 0;
}

