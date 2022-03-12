#include "bst.h"
using namespace std;

//Laura Cornwell Engmram - CS163
//
//This program is designed to implement a binary search tree (BST) to store and search Modern C++ syntax
//by concept and description, within a table ADT. The client will need to use the syntax class, a structure 
//of arrays, for entering information for the name of the concept, description, code example, and type of syntax.
//
// This file implements the table ADT public member functions for the BST, which will be used by the client. The functions 
// rely on the syntax class to move data between the ADT and the client, as arguments. New concepts are entered in a the 
// syntax class. Searches for match and retrieval require separate arrays provided by the client, entered in as arguments.

//Constructor
table::table()
{
	root = NULL;
}

//Destructor
table::~table()
{
	delete_tree(root);
}

//Method to Add a new concept and display all entered.
int table::add_and_display(syntax & input)
{
	int returnvalue = 0;
	if (add_and_display(root, input) > 0) 
		returnvalue = add_and_display(root);
	return returnvalue;
}

//Recursive implementation for display
int table::add_and_display(node *& root)
{
	if (!root) { 
		return 0;
	}
	int total = 1;  	//total amount of concepts
	total += add_and_display(root->left);
	root->data.display();
	total += add_and_display(root->right);
	return total;
}

//Recursive implementation to add
int table::add_and_display(node *& root, syntax & input)
{
	int pos = 0;		//to tract hierarchal position
	int returnvalue = 0;

	if (!root) {
		root = new node; input.copy(root->data);
		root->left = root->right = NULL;
		return 1;	
	}
	pos = root->data.alphacmp(input);
	if (pos == 0) returnvalue = 0;
	if (pos > 0) returnvalue = add_and_display(root->left, input);
	if (pos < 0) returnvalue = add_and_display(root->right, input);
	return returnvalue;
	
}

//Method to retrieve a concept by name, output as an argument
int table::retrieve_by_name(char * input, syntax & output)
{
	return retrieve_by_name(root, input, output);
}

//Recursive implementation to retrieve by name
int table::retrieve_by_name(node * root, char * input, syntax & output)
{
	int returnvalue = 0;
	if (!root) return 0;
	returnvalue += retrieve_by_name(root->left, input, output);
        if (root->data.matchname(input)) {
		root->data.copy(output);
		returnvalue = 1;	
	}
	returnvalue += retrieve_by_name(root->right, input, output);

	return returnvalue;
}

//Method to remove a concept by its name
int table::remove_by_name(char * input)
{
	return remove_by_name(root, input);
}

//Recursive implementation to remove by name
int table::remove_by_name(node *& root, char * input)
{
	int returnvalue = 0;
	char * todelete = new char[strlen(input) + 1];	//to pass into syntax method to retrieve concept name
	strcpy(todelete, input);
	if (!root) {
		delete [] todelete; todelete = NULL;
		return 0;
	}
	if (root->data.matchname(input)) {
		if (!root->left && !root->right) {
			root->data.remove();
			delete root; root = NULL;
			delete [] todelete; todelete = NULL;
			return 1;

		}
		else if (!root->left && root->right) {
			node * hold = root->right;
			delete root; root = hold;
			delete [] todelete; todelete = NULL;
			return 1;
		}
		else if (!root->right && root->left) {
			node * hold = root->left;
			delete root; root = hold;
			delete [] todelete; todelete = NULL;
			return 1;
		}
		else {
	          	node * hold = root->right;
			subtree_min(root->right, hold);
			hold->data.retrievename(todelete);
			root->data.remove();
			hold->data.copy(root->data);
			hold = NULL;
			++returnvalue;
		}

	}
	
	returnvalue += remove_by_name(root->left, todelete);
	returnvalue += remove_by_name(root->right, todelete);
	delete [] todelete; todelete = NULL;
	return returnvalue;

}

//Method find the minimum value in a subtree
int table::subtree_min(node *& root, node *& minimum)
{
	int pos = 0; 	//hierarchy comparison

	if (!root) return 0;
	subtree_min(root->left, minimum);
	pos = root->data.alphacmp(minimum->data);
	if (pos < 0) minimum = root;
	subtree_min(root->right, minimum);
        return 1;
}

//Method to find the height of the tree
int table::height()
{
	return height(root);
}

//Recursive implementation to find the height of the tree
int table::height(node *& root)
{
	if (!root) return 0;
	if (!root->left && !root->right) return 1;
	int left = height(root->left) + 1;	//height of left side
	int right = height(root->right) + 1;	//heigh of right side
	if (left > right) return left;
	if (left < right) return right;
	return right;	
}

//Method for finding the efficiency of the tree
int table::efficiency()
{
	return efficiency(root);
}

//Recursive efficiency
int table::efficiency(node * root)
{	
	if (!root) return 0;	
	int balance = efficiency(root->left);	//balance factor of tree
	int left = height(root->left); 		//height of the left side
	int right = height(root->right);	//height of the right side
	balance = left - right;
	balance += efficiency(root->right);
	return balance;
}

//Method to display a range of concepts, from letter to letter
int table::displayrange(char first, char last)
{
	return displayrange(root, first, last);
}

//Recursive implementation to display a range of concepts
int table::displayrange(node * root, char first, char last)
{
	if (!root) return 0;
	if (first > last) return 0;
	int total = 1;
	total += displayrange(root->left, first, last);
	char * compare = NULL;  		//to retrive name from syntax class
	root->data.retrievename(compare);
	if (toupper(compare[0]) >= toupper(first) && 
	    toupper(compare[0]) <= toupper(last)) {
		root->data.display();
	}
	delete [] compare; compare = NULL;
	total += displayrange(root->right, first, last);
	return total;
}


//Deletes the entire tree. Recursive destructor call.
void table::delete_tree(node *& root)
{
	if (!root) return;
	if (!root->left && !root->right) {
		root->data.remove();
		delete root; root = NULL;
		return;
	}
	else if (!root->left && root->right) {
		node * hold = root->right;
		delete root; root = hold;
	}
	else if (!root->right && root->left) {
		node * hold = root->left;
		delete root; root = hold;
	}
	delete_tree(root->left);
	delete_tree(root->right);
	delete root; root = NULL;
 	return;
}
