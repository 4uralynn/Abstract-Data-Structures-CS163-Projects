#include "trivia_arch.h"
using namespace std;

//Laura Cornwell Engram - CS163
//
//This program is to interact with a client, drawing on trivia data within an ADT.
//
//This file is the main file for testing the ADT. The user must manually enter the
//inputs for the ADT trivia categories, questions, and answers. Test results are
//coded on the bottom. 
//For non-boolean functions with one input or less:
//					100 means the function completed.
//					+10 for every category node added, removed, or displayed
//					 +1 for every Q&A node added, removed or displayed.
//Otherwise:
//				      1000 signals a completed function
//				       100 signals a category was added or edited.
//				       +10 for every category node traversed.
//				       	+1 for every Q&A node traversed.


int main()
{
	srand(time(0));

	cout << endl << "------------------" << endl 
	     << "ADP TESTING CLIENT" << endl 
	     << "------------------" << endl;

	trivia_arch object;   	//Class object to test.
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
		
		int test1 = object.add_quest(question, answer, cat);	
		
		cout << "\nAdd Method::Test Result: " << test1 << endl << endl;
		
		do {
			cout << "\nWould you like to enter another piece of trivia?  ";
			cin.width(2);
			cin >> answer;
			cin.ignore(100, '\n');
		}while(!('Y' == toupper(answer[0])) && !('N' == toupper(answer[0])));
	}while('Y' == toupper(answer[0]));
	/*cout << "\nEnter the next question's category of trivia: ";
	cin.width(25);
	cin >> cat;
	cin.ignore(100, '\n');
	cout << "Enter the question:  ";
	cin.get(question, 200, '\n');
	cin.ignore(100, '\n');
	cout << "Now enter the answer: ";
	cin.get(answer, 200, '\n');
	cin.ignore(100, '\n');
	
	int test2 = object.add_quest(question, answer, cat);
	
	cout << "\nEnter the next question's category of trivia: ";
	cin.width(25);
	cin >> cat;
	cin.ignore(100, '\n');
	cout << "Enter the question:  ";
	cin.get(question, 200, '\n');
	cin.ignore(100, '\n');
	cout << "Now enter the answer: ";
	cin.get(answer, 200, '\n');
	cin.ignore(100, '\n');
	
	int test3 = object.add_quest(question, answer, cat);
	
	cout << "\nEnter the next question's category of trivia: ";
	cin.width(25);
	cin >> cat;
	cin.ignore(100, '\n');
	cout << "Enter the question:  ";
	cin.get(question, 200, '\n');
	cin.ignore(100, '\n');
	cout << "Now enter the answer: ";
	cin.get(answer, 200, '\n');
	cin.ignore(100, '\n');
	
	int test3b = object.add_quest(question, answer, cat);
*/
	int test4 = object.display_all();

	cout << "\nEnter a category of questions to display: ";
	cin.width(25);
	cin >> cat;
	cin.ignore(100, '\n');

	int test5 = object.display_cat(cat);

	cout << "\nEnter a category to remove: ";
	cin.width(25);
	cin >> cat;
	cin.ignore(100, '\n');
	bool test6 = object.remove_cat(cat);
	
	cout << "\nDiplaying what is remaining after using the remove_cat"
		"\nmember function:  \n";
	object.display_all();

	cout << "\nEnter a category to pull a random question from: ";
	cin.width(25);
	cin >> cat;
	cin.ignore(100, '\n');
	int test7 = object.display_random(cat, answer, question);
	
	cout << "\nWhat is the answer to the previous question? ";
	cin.get(answer, 200, '\n');
	cin.ignore(100, '\n');

	bool test8 = object.match_answer(answer, question);

	cout << "Display Method::Test Result: " << test4 << endl;
	cout << "Display Category Method::Test Result: " << test5 << endl;
	cout << "Remove Category Method::Test Result: " << test6 << endl;
	cout << "Display Random Question From Category::Test Result: " << test7 << endl;
	cout << "Match Answer Method::Test Result: " << test8 << endl;

	return 0;
}
