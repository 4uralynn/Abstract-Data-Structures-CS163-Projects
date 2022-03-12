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
	count = display(list[0], list[0].head);
	for (int i = 0; i < tablesize; ++i) {
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
