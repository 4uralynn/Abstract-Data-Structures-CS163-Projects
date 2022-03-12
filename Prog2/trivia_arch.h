#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <ctime>

//Laura Cornwell Engram - CS163
//
//This program is to interact with a client, drawing on trivia data within an ADT.
//The client will need to supply character input (question, answer, and/or category)
//to class member functions.
//
//This file maintains an ADT, the class trivia_arch, which manages each trivia category and
//a list of trivia questions, respectively.
//

//Structures
struct indv_node
{
	char * question = NULL;	//Trivia question
	char * answer = NULL;		//Trivia answer
	indv_node * link = NULL;	//Next piece of trivia.
};

struct cat_node
{ 
	char * cat = NULL;
	indv_node * ihead = NULL;	//Beginning list of trivia items.
	cat_node * link = NULL;	//Link to next trivia category
};

//Classes
//To manage a trivia archive
class trivia_arch
{
	public:
		trivia_arch();
		~trivia_arch();
		int add_quest(char quest[], char answer[], char category[]);
		int display_cat(char input[]);
		bool remove_cat(char input[]);
		int display_all();
		int display_random(char input[], char answer[], char question[]);
		bool match_answer(char answer[], char question[]);

	private:
		cat_node * head;  	//Beginning of list of trivia categories
};
		
