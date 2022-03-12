#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

//Laura Cornwell Engmram - CS250 - Homework 9
//
// This program is designed to implement a simple graph to store vertices and their edges. The the user can detect of their
// implementation is complete, connected, or neither.

//Structures
struct vertex {
	int num = 0;
	struct node * head = NULL;
};

struct node { 		//Node for the edge list of each vertex
	vertex * data = NULL;
	node * link = NULL;
};

//Class
class table {
	public:
		table(); 
		~table();
		int prebuild(int input); 	//To easily input all vertices at once which will be used in the build function
		int build();
		int insertedge(int v1, int v2);
		int display();
		int display(vertex & input, node *& head);
		int display(vertex & input, node *& head, int & index);
		int destroy();
		int destroy(node *& head);
		bool pbexists();
		bool exists();
	private:
		struct buildnode {   		//Special node for assembling all vertices to be used in building the graph
			int data = 0; 		//Dynamically allocated array for name of vertex
			buildnode * link = NULL;
		};
		vertex * list;			//Dynamically allocated array of vertices making up adjacency list
		bool * visited;			//Visited array, fully set up, but currently low functionality
		buildnode * head;		//Beginning of LLL of vertex names use
		int tablesize;			

		//Recursively build the adjacency list based on vertices entered
		int build(buildnode *& head, int index) {
			if (!list) {
				if (!head) return 0;
				tablesize = build(head->link, index) + 1;
			}
			else {
				if (!head) return 0;
				list[index].num = head->data;;
				++index;
				build(head->link, index);
			}
			return tablesize;
		}

		//Recursively remove LLL leftover from prebuild method		
		int rmprebuild(buildnode *& head) {
			if (!head) return 0;
			head->data = 0;
			rmprebuild(head->link);
			delete head; head = NULL;
			return 1;
		}
};


//Constructor
table::table()
{
	list = NULL;
	visited = NULL;
	head = NULL;
	tablesize = 0;
}

//Destructor
table::~table()
{
	rmprebuild(head);
	destroy();
}


//Method to prebuild LLL of vertex values to be used in adjacency list
int table::prebuild(int input)
{
	if (!input) return 0;
	buildnode * toadd = new buildnode;
	toadd->data = input;
	if (!head) {
		head = toadd;
		head->link = NULL;
	}
	else {
		toadd->link = head;
		head = toadd;
	}
	return 1;
}


//Method to build an adjacency from prebuilt list of vertex values
int table::build()
{
	if (list) return 0;
	int index = 0;
	build(head, index);
	list = new vertex[tablesize];
	visited = new bool[tablesize];
	for (int i = 0; i < tablesize; ++i) {
		visited[i] = false;
	}
	build(head, index);
	rmprebuild(head);
	return tablesize;
}

//Method to insert a new edge between two vertices
int table::insertedge(int v1, int v2)
{
	vertex * one = NULL;
	vertex * two = NULL;
	node * temp1 = NULL;
	node * temp2 = NULL;

	int returnvalue = 0;
	if (!list) return returnvalue;
	for (int i = 0; i < tablesize; ++i) {
		if (list[i].num == v1) one = (list + i);
		if (list[i].num == v2) two = (list + i);
	}
	if (one && two) {
		temp1 = new node; temp1->data = two;
		if (!one->head) temp1->link = NULL;
		else temp1->link = one->head;
		one->head = temp1;
	       	temp2 = new node; temp2->data = one;	
		if (!two->head) temp2->link = NULL;
		else temp2->link = two->head;
		two->head = temp2;
		returnvalue = 1;
	}

	return returnvalue;
}

//Method to show edge and vertex list
int table::display()
{
	int count = 0;
	int count2 = 0;
	int count3 = -1;
	int returnvalue = 0;
	if (!list) {
	        cout << "\n\nThere is no graph!";	
		return returnvalue;
	}
	else cout << "\n\nHere is your graph's edge and vertex list:\n\n\nE = {";
	for (int i = 0; i < tablesize; ++i) {
		if (list[i].head) cout << "(" << list[i].num;
		returnvalue = display(list[i], list[i].head, i);
		if ((i < (tablesize - 1)) && list[i+1].head) cout << ", ";
	}
	cout << "}\nV = {";
	for (int i = 0; i < tablesize; ++i) {
		cout << list[i].num;
		if (i < (tablesize - 1)) cout << ",";
	}
	cout << "}\n\nThis is a ";
	count = display(list[0], list[0].head);  //Works but segfaults with certain graph configurations
						 //(to identify connected graph)

	for (int i = 0; i < tablesize; ++i) {	//Code to identify complete graph. Could not get this working
		node * current = list[i].head;
		while (current) {
			++count2;
			if (!current->link && count2 == (tablesize - 1)) {
				++count3;
				count2 = 0;
			}
			current = current->link;
		}
	}
	if (count > 0) cout << "connected ";
	if (count3 == (tablesize)) cout << "complete ";
	cout << "graph.";
	return returnvalue;
}

//Method to better organize edge and vertex notation
int table::display(vertex & input, node *& head, int & index)
{
	int returnvalue = 1;
	if (!head) {
		return 0;
	}
	cout << "," << head->data->num;
	if (head->link) cout << "), (" << input.num;
	if (!head->link) cout << ")";

	display(input, head->link, index);
	return returnvalue;
}

//Method to check for connected graph
int table::display(vertex & input, node *& head)
{
	int returnvalue = 0;

	if (!head) return returnvalue;
	for (int i = 0; i < tablesize; ++i) {
		if (visited[i] == false && head->data == (list + i)) {
			visited[i] = true;
			returnvalue = 1 + display(list[i], list[i].head);
		}
	}
	if (!head->link) return returnvalue;
	returnvalue += display(input, head->link);
	for (int i = 0; i < tablesize; ++i) {
		++returnvalue;
		if (visited[i] == false) {
			returnvalue = 0;
			i = tablesize;
		}
		visited[i] = false;
	}
	return returnvalue;
}

//Method to completely delete the adjacency list
int table::destroy()
{
	int returnvalue = 0;
	if (!list) return returnvalue;
	for (int i = 0; i < tablesize; ++i) {
		list[i].num = 0;
		destroy(list[i].head);
		++returnvalue;
	}
	delete [] list; list = NULL;
	if (visited) {
		delete [] visited; visited = NULL;
	}
	tablesize = 0;
	return returnvalue;
}

//Recursive deletion of the adjacency list
int table::destroy(node *& head) 
{
	if (!head) return 0;
	int returnvalue = destroy(head->link) + 1;
	head->data = NULL;
	delete head; head = NULL;
	return returnvalue;
}

//Method to check if prebuild list of vertices still exists
bool table::pbexists()
{
	if (!head) return false;
	return true;
}


//Method to check if the adjacency list exists
bool table::exists()
{
	if (!list) return false;
	return true;
}


int main()
{
	int test = 0;
	int num;
	char input;
	table bigtable;

	do {
		do {
			cout << endl << " ___________________ \n|                   |\n" 	
			     << "|   GRAPH BUILDER   | (Add vertices first, then Build) \n" 
			     << "|___________________|--------------------------------\n" 
			     << "|     (A)dd      |       (B)uild Adjacency List      |\n" 
			     << "|    Vertices    |-----------------+-----------------+\n" 
			     << "|________________|          (I)nsert Edge            |\n"
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
				cout << "\n\nInput vertex data to add:  ";
				cin >> num;
				cin.ignore(100, '\n');
				bigtable.prebuild(num);
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
				cout << "\n\nBuilt " << test << "!" <<  endl;	
			}
		}

		if ('I' == toupper(input)) {
			int diff = 0;
			cout << "\n\nEnter vertices to connect...\nFirst:  ";
			cin >> num;
			cin.ignore(100, '\n');
			cout << "\nSecond:  ";
			cin >> diff;
			cin.ignore(100, '\n');
			test = bigtable.insertedge(num, diff);
		}

		if ('D' == toupper(input)) {

			test = bigtable.display();
		}
		
		if ('O' == toupper(input)) {
			test = bigtable.destroy();
			cout << "\n\nDestroyed: " << test << endl;	
			}

	}while (!('Q' == toupper(input)));

	return 0;
}

