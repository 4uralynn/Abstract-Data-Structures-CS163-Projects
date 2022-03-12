#include "trivia_arch.h"
#include "stackq.h"
using namespace std;

//Laura Cornwell Engram - CS163
//
//This program is designed to implement two stack objects and a queue in 
//ordering and displaying trivia questions and answers. The resulting ADT
//with member functions will simulate the 2 piles of used trivia cards, being
//those that were answered correctly, and those that were discarded, alongside
//a "queue" deck of questions to be read and answered.
//
//This file is the main file for testing the ADT. The user must manually enter the
//inputs for the ADT trivia categories, questions, and answers. Once entered, the pool
//of trivia objects in the archive remains available to draw on while testing the
//stacks and queues.  Feedback from the member functions are displayed after each test
//in the menu. The integers represent either success or failure with a 1 or 0 respectively,
//or will return the amount of trivia elements stored in the data structure.
//Tests for stacks are pushing onto the stack, popping off, and displaying the total
//contents of the stack. For the queue, tests include enqueue, dequeue, viewing the 
//first entry in the queue (peek), and displaying all objects in the queue.
//
//The "start" function makes use of the trivia_arch class to manage new trivia. This is 
//to test with. The trivia could be supplied to the queue member functions by the client 
//another way in other scenarios. The main files for implementing the stacks and queues
//are "stackq.h" and "gamemech.cpp".

//Prototypes
void start(trivia_arch & object);

//Main function to test stack and queue ADTs
int main()
{
	stack a_stack; 		//Stack of trivia objects answered correctly
	stack f_stack;		//Stack of trivia objects discarded.
	queue queue;		//Queue of questions to the user
	trivia_arch object;  	//Trivia archive object for input of trivia questions and answers
	trivia obj;		//Trivia object to store trivia and whether or not it has been played
	obj.question = new char[200];  //Reusable arrays for new questions
	obj.answer = new char[200];    //and answers
	char input;		//Input for testing menu
	char cat[25];		//Resusable array to manage categories from the trivia_arch
	srand(time(0));	
	do {
		do {
			cout << endl << " ____________________ \n|                    |\n" 	
			     << "| ADP TESTING CLIENT |Tests:                          \n" 
			     << "|____________________|------------------------------- \n" 
			     << "|                |     (E)nqueue   |     P(u)sh      |\n" 
			     << "| (I)nput Trivia |-----------------+-----------------+\n" 
			     << "|________________|     (D)equeue   |      P(o)p      |\n"
			     << "|     Qui(t)     |-----------------+-----------------+\n"
			     << "+================|     (P)eek      | Display (S)tack |\n"
			     << "                 |-----------------+----------------- \n"
			     << "Enter the        | Display (Q)ueue |/\ncorresponding     "
			     << "-----------------\ncharacter:       ";

			cin.width(1);
			cin >> input;
			cin.ignore(100, '\n');	
		}while('I' != toupper(input) && 'E' != toupper(input) && 'D' != toupper(input) &&
		       'P' != toupper(input) && 'U' != toupper(input) && 'O' != toupper(input) &&
		       'S' != toupper(input) && 'Q' != toupper(input) && 'T' != toupper(input));
		if ('I' == toupper(input)) start(object);
		if ('E' == toupper(input)) {
			cout << "\nEnter a category to que a random question: ";
			cin.width(25);
			cin >> cat;
			cin.ignore(100, '\n');
			cout << "\n\nThe following question will be entered into the queue:\n";
			object.display_random(cat, obj.answer, obj.question);
			int test1 = queue.enqueue(obj);
			cout << "\n\nEnqueue Method::Test Result: " << test1 << endl;
		}	
		if ('Q' == toupper(input)) {
			int test2 = queue.display();
			cout << "\n\nDisplay Queue Method::Test Result: " << test2 << endl;
		}
		if ('P' == toupper(input)) {
			int test3 = queue.peek();
			cout << "\n\nPeek (at front of) Queue::Test Results: " << test3 << endl;
		}
		if ('D' == toupper(input)) {
			delete [] obj.question;
			obj.question = NULL;
			delete [] obj.answer;
			obj.answer = NULL;
			int test4;
			do {
				cout << "Would you like to be provided with a copy of what "
					"you are removing? ";
				cin.width(1);
				cin >> input;
				cin.ignore(100, '\n');
			}while(!('Y'== toupper(input)) && !('N' == toupper(input)));
			if ('Y' == toupper(input)) {
				test4 = queue.dequeue(obj);
				cout << "\n\n" << obj.question << "\n\t+ " << obj.answer << endl;
				if (obj.played == true) cout << "\t\t(played)";
				else cout << "\t\t(not yet played)";
				cout << "\n\nYou must immediately push this object to the stack, "
					"to reset the played \nmarker and allow you to enqueue.";
			}
			if ('N' == toupper(input)) test4 = queue.dequeue();
			cout << "\n\nDequeue Method::Test Result: " << test4 << endl;
		}
		if ('U' == toupper(input)) {
			//provide conditional for right or wrong answer to go to separate stacks.
			int test5 = a_stack.push(obj);
			cout << "\n\nPush (to stack) Method::Test Result: " << test5 << endl;
			obj.question = new char[200]; 
			obj.answer = new char[200];    
		}
		if ('O' == toupper(input)) { 
			int test6 = a_stack.pop();
			cout << "\n\nPop (from stack) Method::Test Result: " << test6 << endl;
		}
		if ('S' == toupper(input)) {
			int test7 = a_stack.display();
			cout << "\n\nDisplay Stack Method::Test Result: " << test7 << endl;
		}
	}while (!('T' == toupper(input)));
	return 0;
}

//Client function to use the trivia archive ADT and inject the relevant
//contents into the queue.
void start(trivia_arch & object)
{
	char cat[25];         	//Input for trivia categories.
	char question[200];	//Input for trivia questions
	char answer[200];	//Input for trivia answers
	do {		//loop stands in for preivoud tests 1, 2, & 3
		cout << "\nEnter the category of trivia: ";
		cin.width(25);
		cin >> cat;
		cin.ignore(100, '\n');
		cout << "Enter a trivia question:  ";
		cin.get(question, 200, '\n');
		cin.ignore(100, '\n');
		cout << "Now enter the answer: ";
		cin.get(answer, 200, '\n');
		cin.ignore(100, '\n');
		
		object.add_quest(question, answer, cat);	
		
		do {
			cout << "\nWould you like to enter another piece of trivia?  ";
			cin.width(2);
			cin >> answer;
			cin.ignore(100, '\n');
		}while(!('Y' == toupper(answer[0])) && !('N' == toupper(answer[0])));
	}while('Y' == toupper(answer[0]));

}

