#include <iostream>
#include <cctype>
#include <cstring>

//Laura Cornwell Engmram - CS163
//
//This program is designed to implement two stack objects and a queue in 
//ordering and displaying trivia questions and answers. The resulting ADT
//with member functions will simulate the 2 piles of used trivia cards, being
//those that were answered correctly, and those that were discarded, alongside
//a "queue" deck of questions to be read and answered.
//
//This file will initialize the stack class and queue class for the ADT. The stack
//will allow for trivia objects to be displayed or added or removed from the 
//top of the stack, based on whether they were answerd correctly or not. 
//The queue will prepare trivia questions to display to the client.
//

//constants
const int MAX = 5;

//Structures
struct trivia {			
	char * answer;    	//to be copied from trivia_arch object
	char * question;	//by stack and queue member functions
	bool played;
};

struct stacknode {
	trivia * array;
	stacknode *next;
};

struct qnode {
	trivia item;
	qnode *next;
};

//Classes
class stack {
	public:
		stack(); 
		~stack();
		int push(trivia &); 
		int push (stacknode *& head, trivia &); //Boolen "played" flag will only be modified
		int pop();
		int pop(trivia &);
		int display();
		int display(stacknode *& head);
	private:
		stacknode *head;
		int top_index;

};

class queue {
	public:
		queue();
		~queue();
		int enqueue(const trivia &); 
		int peek();
		int dequeue();
		int dequeue(trivia &);
		int display();
	private:
		qnode *rear;
};
