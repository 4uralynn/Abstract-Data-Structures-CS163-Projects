#include "syn.h"
using namespace std;

//Laura Cornwell Engmram - CS163
//
//This program is designed to implement a hash function to store and search websites by term and description, within
//a table ADT. The client will need to prepare term and description arrays, or utilize the exernal file for entering
//information into the ADT.
//
// This file is to initialize the data structure for nodes, and class itself to create the BST table ADT, which
// will be implemented in its *.cpp file.

//Structures
struct node {
	class syntax data;
	node * left = NULL;
	node * right = NULL;
};

//Class
class table {
	public:
		table(); 
		~table();
		int add_and_display(syntax & input);
		int add_and_display(node *& root);
		int add_and_display(node *& root, syntax & input);
		int retrieve_by_name(char * input, syntax & output);
		int retrieve_by_name(node * root, char * input, syntax & output);
		int remove_by_name(char * input);
		int remove_by_name(node *& root, char * input);
		int subtree_min(node *& root, node *& minimum);
		int height();
		int height(node *& root);
		int efficiency();
		int efficiency(node * root);
		int displayrange(char first, char last);
		int displayrange(node * root,  char first, char last);
		void delete_tree(node *& root);
	private:
		node * root;
};

