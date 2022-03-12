#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

//Laura Cornwell Engmram - CS163
//
// This program is designed to implement a simple graph to store trail heads and their connecting trails
// along with their distance and difficulty level. The graph is a table ADT. The client will need to use the adjacency class 
// along with its prebuild function, for entering information vertex names, which will form the main structure of the graph
// once the build function is called. After the build function is called, the prebuilt list is deleted.
//
// This file is to initialize the vertex class used within the graph ADT. Its functions and data and basic operations
// support the graph ADT class, but allow each vertex to manage itself for better organization. The class includes a
// node structure for use as an edge list for each vertex. To improve the functionality of the ADT, the edge list itself
// needs to have functions that will retrieve the vertex pointers at traveral, so that the ADT can match them with the
// its visited array and avoid circular paths.

//Structures
struct vertex {
	int num;
	node * head;
};

struct node { 		//Node for the edge list of each vertex
	int * data = NULL;
	node * link = NULL;
};
		int num;		//Name of the vertex
		node * head;		//Beginning of the edge list.

		//Recursive function to display a vertex's edge list
		int display(node *& head) {
			if (!head) return 0;
			cout << head->data->name << " [" << head->miles << " miles, " 
			     << head->diff << " difficulty]";
			if (!head->link) {
				cout << endl;
				return 1;
			}
			else cout << ", ";
			return display(head->link) + 1;
		}

		//Recursive function to remove all edges from a vertex
		int rmedges(node *& head) {
			if (!head) return 0;
			int returnvalue = rmedges(head->link) + 1;
			head->data = NULL;
			delete head; head = NULL;
			return returnvalue;
		}

};
