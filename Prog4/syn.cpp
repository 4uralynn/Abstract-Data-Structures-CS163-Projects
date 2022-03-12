#include "syn.h"
using namespace std;

//Laura Cornwell Engmram - CS163
//
//This program is designed to implement a binary search tree (BST) to store and search Modern C++ syntax
//by concept and description, within a table ADT. The client will need to use the syntax class, a structure 
//of arrays, for entering information for the name of the concept, description, code example, and type of syntax.
//
// This file implements the syntax class public member functions, which will be used by both the BST table ADT and the client. 
// Arrays are used in most cases are arguments to add information to a syntax class object. For copy a syntax class object must
// be provided to be copied into, and one must be included in the function to compare two syntax objects. Other functions
// are basic opertations to add, remove, display, and retrieve data from the class.


//Syntax Class Member Functions
//Constructor
syntax::syntax()
{
	name = NULL;
	desc =  NULL;
	code = NULL;
	type = NULL;
}

//Destructor
syntax::~syntax()
{
	remove();
}

//Add Name to Syntax Data Type
int syntax::addname(char * input)
{
	if (!input) return 0;
	name = new char[strlen(input) + 1];
	strcpy(name, input);
	return 1;
}

//Add Syntax Description
int syntax::adddesc(char * input) 
{
	if (!input) return 0;
	desc = new char[strlen(input) + 1];
	strcpy(desc, input);
	return 1;
}

//Add Syntax Code Example
int syntax::addcode(char * input)
{
	if (!input) return 0;
	code = new char[strlen(input) + 1];
	strcpy(code, input);
	return 1;
}

//Add Syntax Type
int syntax::addtype(char * input)
{
	if (!input) return 0;
	type = new char[strlen(input) + 1];
	strcpy(type, input);
	return 1;
}

//Display Syntax
int syntax::display()
{
	if (!name || !desc || !code || !type) return 0;
	cout << "\n\nNAME:\t" << name << endl << desc << "\n\nCODE:\n" << code << 
		"\n\nTYPE:\t" << type << endl;
	return 1;
}

//Make a Copy of the Syntax Data Type
int syntax::copy(syntax & output)
{
	if (!name || !desc || !code || !type) return 0;
	output.addname(name);
	output.adddesc(desc);
	output.addcode(code);
	output.addtype(type);
	return 1;
}

//Remove Syntax Name
int syntax::rmname()
{
	if (!name) return 0;
	delete [] name;
	name = NULL;
	return 1;
}

//Remove Syntax Description
int syntax::rmdesc()
{
	if (!desc) return 0;
	delete [] desc;
	desc = NULL;
	return 1;
}

//Remove Syntax Code
int syntax::rmcode()
{
	if (!code) return 0;
	delete [] code;
	code = NULL;
	return 1;
}

//Remove Syntax Type
int syntax::rmtype()
{
	if (!type) return 0;
	delete [] type;
	type = NULL;
	return 1;
}

//Remove All Data From the Syntax Data Type
int syntax::remove()
{
	int returnvalue = 0;
	if (name) {
		rmname();
		++returnvalue;
	}
	if (desc) {	
		rmdesc();
		++returnvalue;
	}
	if (code) {
		rmcode();
		++returnvalue;
	}
	if (type) {
		rmtype();
		++returnvalue;
	}
	return returnvalue;
}

//Match Input to Syntax Name
bool syntax::matchname(char * input)
{
	char * match = NULL;
	bool returnvalue = false;

	match = new char[strlen(name) + 1];
	strcpy(match, name);
	for (int i = 0; i < strlen(input); ++i) {
		toupper(match[i]);
		toupper(input[i]);
	}
	if (strcmp(match, input) == 0) returnvalue = true;
	delete [] match; match = NULL;
	
	return returnvalue;
}

//Retrieve the name of the object
int syntax::retrievename(char *& output)
{
	if (!name) return 0;
	if (output) {
		delete [] output; output = NULL;
	}
	output = new char[strlen(name) + 1];
	strcpy(output, name);
	return 1;
}

//Compare the names of two syntax class objects, alphabetically
int syntax::alphacmp(syntax & input) 
{
	int pos = 0;

	for (int i = 0; i < strlen(name); ++i) {
		if (pos == 0) {
			if (toupper(input.name[i]) > toupper(name[i])) pos = -1;
			if (toupper(input.name[i]) < toupper(name[i])) pos = 1;
		}
		else i = strlen(name);
	}
	return pos;	
}
