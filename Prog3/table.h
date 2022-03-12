#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
using namespace std;

//Laura Cornwell Engmram - CS163
//
//This program is designed to implement a hash function to store and search websites by term and description, within
//a table ADT. The client will need to prepare term and description arrays, or utilize the exernal file for entering
//information into the ADT.
//
// This file is to initialize the data structure and class to create the table ADT for use in implementation.

//Structures
struct snode {
	char * site;			//Array per site.
	snode * next = NULL;
};

struct entry {			
	char * term = NULL;   		//keyword 
	char * description = NULL;	//Keyword description	
	snode * head = NULL;     	//list of websited
};

struct node {
	entry data;
	node * link = NULL;
};

//Classes
class table {
	public:
		table(int size = 181); 
		~table();
		int addterm(const entry & input);
		int addterm(node *& head, char * key, const entry & input);
		int addsites(snode *&, snode *);
		int displaymatch(char * key);
		int displaymatch(node * head, char * key);
		int displaymatch(node * heada, snode * head, char * key);
		int loadfromfile();
		int loadfromfile(ifstream &file_in);
		int loadfromfile(snode *& head, ifstream & char_in, 
				ifstream & file_in, int sites, int &nodecount);
		int removesites(snode *& head);
		int addsitetoterm(char * website, char * key);
		int addsitetoterm(node * head, char * website, char * key);
		int addsitetoterm(snode *& head, char * website);
		int remove(char * key);
		int remove(node *& head, char * key);
		int retrievematch(char * key, entry &);
		int retrievematch(node * head, char * key, entry &);
		int rmtermwithsite(char * website);
		int rmtermwithsite(node * head, char * website);
		bool rmmatchingsites(snode *& head, char * website);
		int displayall();
		int displayall(node * head);
	private:
		node ** hashtable;
		int tablesize;	
		//Hash Function
		int hashfunction(char *key) const
		{
		    long hash = 0;

		    for (int i = 0; i < strlen(key); ++i) {
			key[i] = toupper(key[i]);
			hash *= 10;
			hash += key[i];
		    }
		    return hash % tablesize;

		};
};

