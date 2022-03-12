#include "vertex.h"
using namespace std;

//Laura Cornwell Engmram - CS163
//
// This program is designed to implement a simple graph to store trail heads and their connecting trails
// along with their distance and difficulty level. The graph is a table ADT. The client will need to use the adjacency class 
// along with its prebuild function, for entering information vertex names, which will form the main structure of the graph
// once the build function is called. After the build function is called, the prebuilt list is deleted.
//
// This file is to initialize the graph table ADT class along with its data structure for the buildnodes. The buildnodes
// are used to implement a LLL to hold names of the vertices before the final build function is called. This helps the
// client easily set up the correct size array of vectors without giving the client access to the private data members and
// nodes for the ADT. To improve this ADT in the future, the vertex class would need to be updated so that the vertex pointers
// in the edge list are retrievable, or matched with the vertices in the adjacency list. A separate function would need to be
// used to call the vertex function and match it to the adjacency list.
	

//Class
class table {
	public:
		table(); 
		~table();
		int prebuild(char * input); 	//To easily input all vertex names at once which will be used in the build function
		int build();
		int insertedge(char * v1, char * v2, int miles, int diff);
		int display();
		int destroy();
		bool pbexists();
		bool exists();
	private:
		struct buildnode {   		//Special node for assembling all vertex names to be used in building the graph
			char * data = NULL; 	//Dynamically allocated array for name of vertex
			buildnode * link = NULL;
		};
		vertex * list;			//Dynamically allocated array of vertices making up adjacency list
		bool * visited;			//Visited array, fully set up, but currently low functionality
		buildnode * head;		//Beginning of LLL of vertex names use
		int tablesize;			

		//Recursively build the adjacency list based on names entered
		int build(buildnode *& head, int index) {
			if (!list) {
				if (!head) return 0;
				tablesize = build(head->link, index) + 1;
			}
			else {
				if (!head) return 0;
				list[index].addname(head->data);
				++index;
				build(head->link, index);
			}
			return tablesize;
		}

		//Recursively remove LLL leftover from prebuild method		
		int rmprebuild(buildnode *& head) {
			if (!head) return 0;
			delete [] head->data; head->data = NULL;
			rmprebuild(head->link);
			delete head; head = NULL;
			return 1;
		}
};

