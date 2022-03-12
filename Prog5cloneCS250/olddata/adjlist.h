#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

//Laura Cornwell Engmram - CS163
//
// This program is designed to implement a simple graph to store vertices and their edges. The the user can detect of their
// implementation is complete, connected, or neither.
//
// This file is to initialize the graph table ADT class along with its data structure for the buildnodes. The buildnodes
// are used to implement a LLL to hold names of the vertices before the final build function is called. This helps the
// client easily set up the correct size array of vectors without giving the client access to the private data members and
// nodes for the ADT. To improve this ADT in the future, the vertex class would need to be updated so that the vertex pointers
// in the edge list are retrievable, or matched with the vertices in the adjacency list. A separate function would need to be
// used to call the vertex function and match it to the adjacency list.
	

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

