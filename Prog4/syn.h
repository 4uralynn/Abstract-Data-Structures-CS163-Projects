#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

//Laura Cornwell Engmram - CS163
//
//This program is designed to implement a binary search tree (BST) to store and search Modern C++ syntax
//by concept and description, within a table ADT. The client will need to use the syntax class, a structure 
//of arrays, for entering information for the name of the concept, description, code example, and type of syntax.
//
// This file is to initialize syntax class, its functions and data, for use in the BST.


//Classes

class syntax {
	public:
		syntax();
		~syntax();
		int addname(char * input);
		int adddesc(char * input);
		int addcode(char * input);
		int addtype(char * input);
		int display();
		int copy(syntax & output);
		int rmname();
		int rmdesc();
		int rmcode();
		int rmtype();
		int remove();
		int alphacmp(syntax & input);
		int retrievename(char *& output);
		bool matchname(char * input);
		
	private:
		char * name;
		char * desc;
		char * code;
		char * type;
};
