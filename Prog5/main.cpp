#include "adjlist.h"
using namespace std;

//Laura Cornwell Engmram - CS163
//
// This program is designed to implement a simple graph to store trail heads and their connecting trails
// along with their distance and difficulty level. The graph is a table ADT. The client will need to use the adjacency class 
// along with its prebuild function, for entering information vertex names, which will form the main structure of the graph
// once the build function is called. After the build function is called, the prebuilt list is deleted.
//
// This is the client program that will test the graph ADT and all member functions. The client will need to provide
// the names of the vertices in the form of character arrays, as well as distance in mile between trails, and difficulty 
// in the form of int data.


int main()
{
	int test = 0;
	char input;
	char toadd[151];
	table bigtable;

	do {
		do {
			cout << endl << " ____________________ \n|                    |\n" 	
			     << "| ADP TESTING CLIENT |Tests:                          \n" 
			     << "|____________________|------------------------------- \n" 
			     << "|  (A)dd Trail   |       (B)uild Adjacency List      |\n" 
			     << "|    Vertices    |-----------------+-----------------+\n" 
			     << "|________________|        (I)nsert Connection        |\n"
			     << "|     (Q)uit     |-----------------+-----------------+\n"
			     << "+================|    Destr(O)y    | (D)isplay List  |\n"
			     << "                 |-----------------+----------------- \n"
			     << "Enter the        \ncorresponding     "
			     << "\ncharacter:       ";

			cin.width(1);
			cin >> input;
			cin.ignore(100, '\n');	
		}while('A' != toupper(input) && 'B' != toupper(input) && 'I' != toupper(input) &&
		       'Q' != toupper(input) && 'O' != toupper(input) && 'D' != toupper(input));
	
		if ('A' == toupper(input)) {
		        do {
				cout << "\n\nWhat is the name of the trail vertex to add?  ";
				cin.get(toadd, 150, '\n');
				cin.ignore(150, '\n');
				bigtable.prebuild(toadd);
				cout << "\n\nWould you like to add another vertex?  ";
				cin.width(1);
				cin >> input;
				cin.ignore(100, '\n');
			}while('Y' == toupper(input));
		        
		}
		if ('B' == toupper(input)) {
			if (bigtable.exists()) {
				cout << "\n\nERROR: You must destroy the current list before building a new one!";
			}
			if (!bigtable.pbexists()) {
				cout << "\n\nERROR: Cannot build list until vertices are added!";
			}
			else {
				test = bigtable.build();
				cout << "\n\nBuild Adjacency List--Test Result: " << test << endl;	
			}
		}

		if ('I' == toupper(input)) {
			char toadd2[151];
			int miles = 0;
			int diff = 0;
			cout << "\n\nEnter two trail vertices to connect...\nFirst:  ";
			cin.get(toadd, 150, '\n');
			cin.ignore(150, '\n');
			cout << "\nSecond:  ";
			cin.get(toadd2, 150, '\n');
			cin.ignore(150, '\n');
			do {
				cout << "\n\nEnter the distance of the trail in miles:  ";
				cin >> miles;
			}while(isalpha(miles));
			do {
				cout << "\n\nEnter the difficulty of the trail:  ";
				cin >> diff;
			}while(diff > 10 || diff < 1 || isalpha(diff));
			test = bigtable.insertedge(toadd, toadd2, miles, diff);
			cout << "\n\nInsert Connection/Edge--Test Result: " << test << endl;	
		}

		if ('D' == toupper(input)) {

			test = bigtable.display();
			cout << "\n\nDisplay List--Test Result: " << test << endl;	
		}
		
		if ('O' == toupper(input)) {
			test = bigtable.destroy();
			cout << "\n\nDestroy--Test Result: " << test << endl;	
			}

	}while (!('Q' == toupper(input)));

	return 0;
}

