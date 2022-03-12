#include "bst.h"
using namespace std;

//Laura Cornwell Engmram - CS163
//
//This program is designed to implement a binary search tree (BST) to store and search Modern C++ syntax
//by concept and description, within a table ADT. The client will need to use the syntax class, a structure 
//of arrays, for entering information for the name of the concept, description, code example, and type of syntax.
//
// This is the client program that will test the BST and the member functions. The client will need to provide
// the concepts, but arrays and syntax class are available to use to trasfer data to the ADT.


int main()
{
	int test = 0;
	char input;
	syntax object;
	char toadd[151];
	table bigtable;

	do {
		do {
			cout << endl << " ____________________ \n|                    |\n" 	
			     << "| ADP TESTING CLIENT |Tests:                          \n" 
			     << "|____________________|------------------------------- \n" 
			     << "|                |  (A)dd Concept  | Remo(v)e Concept|\n" 
			     << "|                |-----------------+-----------------+\n" 
			     << "|________________|   (R)etrieve    |  (E)fficiency   |\n"
			     << "|     (Q)uit     |-----------------+-----------------+\n"
			     << "+================|    (H)eight     | (D)isplay Range |\n"
			     << "                 |-----------------+----------------- \n"
			     << "Enter the        \ncorresponding     "
			     << "\ncharacter:       ";

			cin.width(1);
			cin >> input;
			cin.ignore(100, '\n');	
		}while('A' != toupper(input) && 'V' != toupper(input) && 'R' != toupper(input) &&
		       'Q' != toupper(input) && 'E' != toupper(input) && 'H' != toupper(input) &&
		       'D' != toupper(input));
	
		if ('A' == toupper(input)) {
		        cout << "\n\nWhat is the name of the syntax concept to add?  ";
			cin.get(toadd, 50, '\n');
			cin.ignore(100, '\n');
			object.addname(toadd);
		        cout << "\n\nProvide a description of this concept:  ";
			cin.get(toadd, 150, '\n');
			cin.ignore(150, '\n');
			object.adddesc(toadd);
		        cout << "\n\nPlease provide an example of the code:  ";
			cin.get(toadd, 150, '\n');
			cin.ignore(150, '\n');
			object.addcode(toadd);
		        cout << "\n\nWhat type of syntax is this?  ";
			cin.get(toadd, 50, '\n');
			cin.ignore(100, '\n');
			object.addtype(toadd);

			test = bigtable.add_and_display(object);
			cout << "\n\nAdd and Display All Concepts--Test Result: " << test << endl;	
			object.remove();
		}
		if ('R' == toupper(input)) {
			cout << "\n\nWhat concept are you looking for?  ";
			cin.get(toadd, 50, '\n');
			cin.ignore(100, '\n');
			
			test = bigtable.retrieve_by_name(toadd, object);
			cout << "\n\nThis concept was retrieved:  ";
			object.display();
			cout << "\n\nRetrieve By Matching Name--Test Result: " << test << endl;	
			object.remove();
		}

		if ('H' == toupper(input)) {
			test = bigtable.height();
			cout << "\n\nFind the Tree Height--Test Result: " << test << endl;	
		}

		if ('V' == toupper(input)) {
			cout << "\n\nEnter the concept you'd like to remove: ";
			cin.get(toadd, 50, '\n');
			cin.ignore(100, '\n');

			test = bigtable.remove_by_name(toadd);
			cout << "\n\nRemove Concept--Test Result: " << test << endl;	
		}
		
		if ('E' == toupper(input)) {
			test = bigtable.efficiency();
			cout << "\n\nEfficiency--Test Result: " << test << endl;	
			}

		if ('D' == toupper(input)) {
			char first, last;
			cout << "\n\nEnter the first letter of range: ";
			cin >> first;
			cin.ignore(100, '\n');
			cout << "\n\nEnter the last letter in range: ";
			cin >> last;
			cin.ignore(100, '\n');
			test = bigtable.displayrange(first, last);
			cout << "\n\nDisplay Range--Test Result: " << test << endl;	
		}

	}while (!('Q' == toupper(input)));

	return 0;
}

