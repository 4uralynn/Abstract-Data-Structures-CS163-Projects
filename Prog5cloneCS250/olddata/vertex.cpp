#include "vertex.h"
using namespace std;

//Laura Cornwell Engmram - CS163
//
// This program is designed to implement a simple graph to store trail heads and their connecting trails
// along with their distance and difficulty level. The graph is a table ADT. The client will need to use the adjacency class 
// along with its prebuild function, for entering information vertex names, which will form the main structure of the graph
// once the build function is called. After the build function is called, the prebuilt list is deleted.
//
// This file implements the vertex class public member functions which will be used by the graph ADT. 
// Arrays and the vertex class itself are both used in most cases are arguments to add information. For copy a vertex class object must
// be provided to be copied into, and one must be included in the function to compare two vertex objects. Basic opertations include insert, 
// inserting into the vertex edgelist, remove, display, and matching data from the class. Other useful function that could be implemented
// in the future is a retrival function for vertex pointers in the edge list. This would allow the adjacency list visited boolean values
// to work correctly so that the graph only shows vertices that haven't already been visited.


//Vertex Class Member Functions
//Constructor
vertex::vertex()
{
	name = NULL;
	head = NULL;
}

//Destructor
vertex::~vertex()
{
	remove();
}

//Add Name to Vertex Data Type
int vertex::addname(char * input)
{
	if (!input) return 0;
	name = new char[strlen(input) + 1];
	strcpy(name, input);
	return 1;
}

//Add Vertex Edge
int vertex::addedge(vertex * input, int miles, int diff) 
{
	if (!input) return 0;
	node * toadd = new node;
	toadd->data = input;
	toadd->miles = miles; toadd->diff = diff;
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

//Display Vertex
int vertex::display()
{
	int returnvalue = 0;
	if (!name) return 0;
	cout << endl << name;
	if (!head) cout << endl;
	else {
		cout << "--->";
		returnvalue = display(head);
	}
	return returnvalue;
}

//Remove Vertex Name
int vertex::rmname()
{
	if (!name) return 0;
	delete [] name;
	name = NULL;
	return 1;
}

//Remove Vertex Edge List
int vertex::rmedges()
{
	return rmedges(head);
}

//Remove All Data From the Vertex Data Type
int vertex::remove()
{
	int returnvalue = 0;
	if (name) {
		rmname();
		++returnvalue;
	}
	if (head) {	
		rmedges();
		++returnvalue;
	}
	return returnvalue;
}

//Match the vertex name with an input
bool vertex::matchname(char * input)
{
	if (strcmp(name, input) == 0) return true;
	return false;
}
