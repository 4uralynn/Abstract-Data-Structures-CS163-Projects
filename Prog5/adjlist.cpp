#include "adjlist.h"
using namespace std;

//Laura Cornwell Engmram - CS163
//
// This program is designed to implement a simple graph to store trail heads and their connecting trails
// along with their distance and difficulty level. The graph is a table ADT. The client will need to use the adjacency class 
// along with its prebuild function, for entering information vertex names, which will form the main structure of the graph
// once the build function is called. After the build function is called, the prebuilt list is deleted.
//
// This file implements the table ADT public member functions for the graph. The functions that will be tested by the client 
// rely on the character arrays and int data types to move data within the ADT, the client, and each vertex, which is a separate class.
// The arrays and int data types are the only arguments for public member functions. New vertices are entered in a the 
// first as a list of character arrays, which then are copied to individual vertices. The build function cannot be used until
// the prebuild function has at least one vertex name in it's list, and the build function can only be used once, until the
// destroy function is used. 

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


//Method to prebuild LLL of vertex names to be used in adjacency list
int table::prebuild(char * input)
{
	if (!input) return 0;
	buildnode * toadd = new buildnode;
	toadd->data = new char[strlen(input) + 1];
	for (int i = 0; i <= strlen(input); ++i) {
		toadd->data[i] = toupper(input[i]); 
	}
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


//Method to build an adjacency from prebuilt list of vertex names
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
int table::insertedge(char * v1, char * v2, int miles, int diff)
{
	vertex * one = NULL;
	vertex * two = NULL;

	int returnvalue = 0;
	if (!list) return returnvalue;
	for (int i = 0; i <= strlen(v1); ++i) v1[i] = toupper(v1[i]);
	for (int i = 0; i <= strlen(v2); ++i) v2[i] = toupper(v2[i]);
	for (int i = 0; i < tablesize; ++i) {
		if (list[i].matchname(v1)) one = (list + i);
		if (list[i].matchname(v2)) two = (list + i);
	}
	if (one && two) {
		one->addedge(two, miles, diff);
		two->addedge(one, miles, diff);
		returnvalue = 1;
	}

	return returnvalue;
}

//Method to display entire adjacency list
int table::display()
{
	int returnvalue = 0;
	if (!list) return returnvalue;
	for (int i = 0; i < tablesize; ++i) {
		returnvalue += list[i].display();
		returnvalue += 100;
	}
	return returnvalue;
}

//Method to completely delete the adjacency list
int table::destroy()
{
	int returnvalue = 0;
	if (!list) return returnvalue;
	for (int i = 0; i < tablesize; ++i) {
		returnvalue = list[i].remove();
		++returnvalue;
	}
	delete [] list; list = NULL;
	if (visited) {
		delete [] visited; visited = NULL;
	}
	tablesize = 0;
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
