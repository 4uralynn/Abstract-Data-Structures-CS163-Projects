#include "stackq.h"
using namespace std;

//Laura Cornwell Engmram - CS163
//
//This program is designed to implement two stack objects and a queue in 
//ordering and displaying trivia questions and answers. The resulting ADT
//with member functions will simulate the 2 piles of used trivia cards, being
//those that were answered correctly, and those that were discarded, alongside
//a "queue" deck of questions to be read and answered.
//
//This file implements stack class and queue class functions for the ADT. The stack
//will allow for trivia objects to be displayed or added or removed from the 
//top of the stack, based on whether they were answerd correctly or not. 
//The queue will prepare trivia questions to display to the client.

//Stack constructor
stack::stack()
{
	head = NULL;
	top_index = 0;	
} 
//Stack destructor
stack::~stack()
{
	stacknode * target = NULL;
	if (!head) return;
	if (!head->next) {
		for (int i = 0; i <= top_index; ++i) {
			delete [] head->array[i].question;
			delete [] head->array[i].answer;
			head->array[i].played = 0;
			head->array[i].question = NULL;
			head->array[i].answer = NULL;
		}
		delete [] head->array;
	       	head->array = NULL;
		delete head;
		head = NULL;
		return;
	}
	while (head) {
		for (int i = 0; i <= top_index; ++i) {
			delete [] head->array[i].question;
			delete [] head->array[i].answer;
			head->array[i].played = 0;
			head->array[i].question = NULL;
			head->array[i].answer = NULL;
		}
		target = head;
		head = head->next;
		delete [] target->array;
		target->array = NULL;
		target->next = NULL;
		delete target;
		target = NULL;
	} 

}
//Wrapper function for recursive push function
int stack::push(trivia & item)
{
	return push(head, item);
}
//Push stack member function, to add a new trivia item to the stack
int stack::push (stacknode *& head, trivia & item)
{
	if (strlen(item.question) == 0 || strlen(item.answer) == 0 || item.played == false)
		return 0;
	if (!head) {
		head = new stacknode;
		head->array = new trivia[MAX];
	}
	if (top_index < MAX) {
		head->array[top_index].question = new char[strlen(item.question) + 1];
		strcpy(head->array[top_index].question, item.question); 
		head->array[top_index].answer = new char[strlen(item.answer) + 1];
		strcpy(head->array[top_index].answer, item.answer);
		head->array[top_index].played = item.played;
		delete [] item.question;
		item.question = NULL;
		delete [] item.answer;
		item.answer = NULL;
	        ++top_index;	
		item.played = false;	
		return top_index;
	}
	if (top_index == MAX) {
		stacknode * temp = NULL;
		temp = new stacknode;
		temp->next = head;
		head = temp;
		head->array = new trivia[MAX];
		top_index = 0;
		return (push(head, item));
	}
	return 0;	
}
//Pop stack member function
int stack::pop()
{
	stacknode * temp = NULL;

	if (!head) return 0;
	if (head) {
		if (top_index > 0) --top_index;
		if (top_index >= 0) {
			delete [] head->array[top_index].question;
			head->array[top_index].question = NULL;
			delete [] head->array[top_index].answer;
			head->array[top_index].answer = NULL;
			head->array[top_index].played = false;
		}
		if (top_index == 0) {
			
			if (head->next) {
				temp = head->next;
				top_index = MAX;
			}
			delete [] head->array;
			head->array = NULL;
			head->next = NULL;
			delete head;
			head = temp;		
		}
	}
	return 1;
}

//Pop stack member function, passing a trivia item.
int stack::pop(trivia & output)
{
	stacknode * temp = NULL;

	if (!head) return 0;
	if (head) {
		if (top_index > 0) {
			output.question = new char[strlen(head->array[top_index].question) + 1];
			strcpy(output.question, head->array[top_index].question);
			output.answer = new char[strlen(head->array[top_index].answer) + 1];
			strcpy(output.answer, head->array[top_index].answer);
			output.played = head->array[top_index].played;
			delete [] head->array[top_index].question;
			head->array[top_index].question = NULL;
			delete [] head->array[top_index].answer;
			head->array[top_index].answer = NULL;
			head->array[top_index].played = false;
			--top_index;
		}
		if (top_index == 0) {
			
			if (head->next) {
				temp = head->next;
				top_index = MAX - 1;
			}
			delete [] head->array;
			head->array = NULL;
			head->next = NULL;
			delete head;
			head = temp;		
		}
	}
	return 1;
}

//Display stack member function to dispaly all trivia questions
int stack::display()
{
	if (!head) return 0;
	if (head) {
		for (int i = 0; i < top_index; ++i) {
			cout << endl << head->array[i].question << "\n\t+ "
			     << head->array[i].answer << endl;
			if (head->array[i].played) cout << "\t\t(played)" << endl;
			else cout << "\t\t(not yet played)" << endl;
		}
		if (!head->next) return (top_index); 
	}
	return (display(head->next) + (top_index));
}

//Recursive implementation for displaying the stacks
int stack::display(stacknode *& head)
{
	int nodecount = 100;

	if (!head) return 0;
	if (!head->next) {
		for (int i = 0; i < MAX; ++i) {
			cout << endl << head->array[i].question << "\n\t+ "
			     << head->array[i].answer << endl;
			if (head->array[i].played) cout << "\t\t(played)" << endl;
			else cout << "\t\t(not yet played)" << endl;
		}
		return (nodecount + MAX);
	}
	else {
		for (int i = 0; i < MAX; ++i) {
			cout << endl << head->array[i].question << "\n\t+ "
			     << head->array[i].answer << endl;
			if (head->array[i].played) cout << "\t\t(played)" << endl;
			else cout << "\t\t(not yet played)" << endl;
		}
		return (display(head->next) + nodecount + MAX);
	}
	return 0;
}
//Queue Constructor
queue::queue()
{
	rear = NULL;	
}
//Queue Destructor
queue::~queue()
{
	qnode * target = NULL;
	if (!rear) return;
	while (rear->next != rear) {
		target = rear->next;
		rear->next = rear->next->next;
	        delete [] target->item.question;
		delete [] target->item.answer;
		target->item.played = 0;
	  	target->item.question = NULL;
	 	target->item.answer = NULL;
		delete target;
		target = NULL;
	}	
	if (rear == rear->next) { 
		rear->next = NULL;
	       	delete [] rear->item.question;
		delete [] rear->item.answer;
		rear->item.played = 0;
		rear->item.question = NULL;
		rear->item.answer = NULL;
		delete rear;
		rear = NULL;
	}
}
//Enqueue queue member function to add a question to the end of the queue
int queue::enqueue(const trivia & input)
{
	qnode * temp = NULL;
	if (strlen(input.question) == 0 || strlen(input.answer) == 0) return 10;
	if (input.played == true) return 0;
	if (!rear) {
		rear = new qnode;
		rear->next = rear;
		rear->item.question = new char[strlen(input.question) + 1];
		strcpy(rear->item.question, input.question);
		rear->item.answer = new char[strlen(input.answer) + 1];
		strcpy(rear->item.answer, input.answer);
		rear->item.played = input.played;
	}
	else {
		temp = rear->next;
		rear->next = new qnode;
		rear = rear->next;
		rear->next = temp;
		rear->item.question = new char[strlen(input.question) + 1];
		strcpy(rear->item.question, input.question);
		rear->item.answer = new char[strlen(input.answer) + 1];
		strcpy(rear->item.answer, input.answer);
		rear->item.played = input.played;
	} 
	return 1;
}

//Peek member function to show a question from the beginning of the queue
int queue::peek()
{
	if (!rear) return 0;
	else {
		cout << endl << rear->next->item.question << endl;
	}
	return 1;
}
//Dequeue function with arguments passed.
int queue::dequeue()
{
	qnode * target = NULL;

	if (!rear) return 0;
	else {
		target = rear->next;
		delete [] target->item.question;
		target->item.question = NULL;
		delete [] target->item.answer;
		target->item.answer = NULL;
		target->item.played = false;
		if (rear == rear->next) {
			rear->next = NULL;
			delete rear;
			rear = NULL;
		}
		else {
			rear->next = rear->next->next;
			delete target;
			target = NULL;
		}
	}
	return 1;
}
//Dequeue passing an argument to push onto the stacks.
int queue::dequeue(trivia & output)
{
	qnode * target = NULL; 

	if (!rear) return 0;
	else {
		target = rear->next;
		output.question = new char[strlen(target->item.question) + 1];
		strcpy(output.question, target->item.question);
		output.answer = new char[strlen(target->item.answer) + 1];
		strcpy(output.answer, target->item.answer);
		output.played = true;
		delete [] target->item.question;
		target->item.question = NULL;
		delete [] target->item.answer;
		target->item.answer = NULL;
		target->item.played = false;
		if (rear == rear->next) {
			rear->next = NULL;
			delete rear;
			rear = NULL;
			return 2;
		}
		else {
			rear->next = rear->next->next;
			delete target;
			target = NULL;
		}
	}
	return 1;
}

//Displaying all items from the queue
int queue::display()
{
	int nodecount = 0;  //counting the amount of elements in the list for test return
	if (!rear) return 0;
	qnode * current = rear->next;
	while (rear != current) {
		cout << endl << current->item.question << "\n\t+ " << current->item.answer << endl;
		if (current->item.played == true) cout << "\t\t(played)";
		else cout << "\t\t(not yet played)";
		++nodecount;
		current = current->next;
	}
	if (current == rear) {
		cout << endl << rear->item.question << "\n\t+ " << rear->item.answer << endl;
		if (rear->item.played == true) cout << "\t\t(played)";
		else cout << "\t\t(not yet played)";
		++nodecount;
	}
	return nodecount;
}
