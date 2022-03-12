#include "trivia_arch.h"
using namespace std;

//Laura Cornwell Engram - CS163
//
//This program is to interact with a client, drawing on trivia data within an ADT.
//
//This file implements functions for an ADT, the classes trivia_arch, which manage each trivia category and
//a list of trivia questions, respectively.

//Constructors
trivia_arch::trivia_arch()
{
	head = NULL;		//Pointer to trivia archive.

}

//Destructor
trivia_arch::~trivia_arch()
{
	cat_node * target = NULL;	//Target pointer to delete node.
	if (head)
		target = head;
	while (target)
	{
		if (target->ihead)
		{			
			indv_node * itarget = target->ihead;
			while (itarget->link)	
			{
				indv_node * icurrent = itarget->link;
				if (itarget->question)
					delete [] itarget->question;
				if (itarget->answer)
					delete [] itarget->answer;
				itarget->question = NULL;
				itarget->answer = NULL;
				delete itarget;
				itarget = icurrent;
			}
			if (itarget->question)
				delete [] itarget->question;
			if (itarget->answer)
				delete [] itarget->answer;
			itarget->question = NULL;
			itarget->answer = NULL;
			delete itarget;
			itarget = NULL;
		}
		delete [] target->cat;
		target->cat = NULL;
		cat_node * current = NULL;
		if (target->link)
		{
			cat_node * current = target->link;
			delete target; 
			target = current;
		}
		else
		{
			delete target;
			target = NULL;
		}
	}
	head = NULL;
}


//Method to enter a trivia item
int trivia_arch::add_quest(char quest[], char answer[], char category[])
{
	cat_node * current = NULL;		//Category traversal pointer
	indv_node * icurrent = NULL;		//Question/answer traversal pointer
	cat_node * target = head;	//Pointer target for new categorynodes.
	int returncode = 0;  	//1000 = category, question, and answer all entered.
				// 100 = a new category was entered
				// +10 for each cat_node traversed
				//  +1 for each indv_node traversed
	
	while (target && (strcmp(target->cat, category) != 0))
	{
		current = target;
		target = target->link;
		returncode += 10;
	}
	if (!target)
	{
		target = new cat_node; 
		target->link = NULL; 	
		target->cat = new char[strlen(category) + 1];
		strcpy(target->cat, category);
		if (!head)
			head = target;
		else
			current->link = target;
		current = target;
		returncode += 100;
	}
	indv_node * itarget = target->ihead;	//Pointer target for new q&a nodes.
	while (itarget)
	{
		icurrent = itarget;
	       	itarget = itarget->link;
		++returncode;
 	}
	itarget = new indv_node;
	itarget->link = NULL;
	itarget->question = new char[strlen(quest) + 1];
	strcpy(itarget->question, quest);
	itarget->answer = new char[strlen(answer) + 1];
	strcpy(itarget->answer, answer);
	if (!(target->ihead))
	{
		current->ihead = itarget;
		returncode += 1000;
	}
	else
	{
		icurrent->link = itarget;
		returncode += 1000;
	}
	return returncode;
}

//Method to disply questions of a particular category
int trivia_arch::display_cat(char input[])
{
	cat_node * current = head;		//Category traversal pointer
	indv_node * icurrent = NULL;		//Question/answer traversal pointer
	int returncode = 0;		//100 completed successfully
					//+10 for each category displayed
					// +1 for each Q&A displayed

	if (!head) return 0;
	while (current->link && strcmp(input, current->cat) != 0)
	{
		current = current->link;
		returncode += 10;	
	}
	if (strcmp(input, current->cat) != 0) return 0;
	cout << "\nCATEGORY: " << current->cat << endl;
	icurrent = current->ihead;
	if (!icurrent) return returncode;
	if (icurrent)
	{
		cout << "\n+ " << icurrent->question << "\n   - "
		     << icurrent->answer << endl;
		++returncode;
		returncode += 100;
	}
	while (icurrent->link)
	{
		icurrent = icurrent->link;
		cout << "\n+ " << icurrent->question << "\n   - "
		     << icurrent->answer << endl;

		++returncode;
	}
	return returncode;
	
}
//Method to remove a trivia category
bool trivia_arch::remove_cat(char input[]) 
{
	cat_node * current = NULL;		//Category traversal pointer
	indv_node * icurrent = NULL;		//Question/answer traversal pointer.
	cat_node * target = head;	//Pointer target to remove category  nodes.

	if (!head) return false;
	while (target->link && strcmp(input, target->cat) != 0)
	{
		current = target;
		target = target->link;
	}
	if (strcmp(input, target->cat) != 0) return false;
	icurrent = target->ihead;
	if (!icurrent) return false;
	while (icurrent->link)
	{		
		target->ihead = icurrent->link;
		delete [] icurrent->question;
		icurrent->question = NULL;
		delete [] icurrent->answer;
		icurrent->answer = NULL;
		icurrent->link = NULL;
		delete icurrent;
		icurrent = target->ihead;
	}
	if (!icurrent->link)
	{
		delete target->ihead;
		target->ihead = NULL;
	}
	if (head == target)
	{
		head = target->link;
		target->link = NULL;
		delete target;
		target = NULL;
		return true;
	}
	else if (!target->link)
	{
		current->link = NULL;
		delete target;
		target = NULL;
		return true;
	}
	else
	{
		current->link = target->link;
		target->link = NULL;
		delete target;
		target = NULL;
		return true;
	}
	
	return false;

}
//Method to display all trivia questions
int trivia_arch::display_all()
{
	cat_node * current = head;		//Category traversal pointer
	indv_node * icurrent = NULL;		//Question/answer traversal pointer
	int returncode = 0;		//100 completed successfully
					//+10 for each category displayed
					// +1 for each Q&A displayed
	if (!head) return 0;
	while (current)
	{
		icurrent = current->ihead;
		cout << "\nCATEGORY: " << current->cat << endl;
		while (icurrent)
		{
			cout << "+ " << icurrent->question << "\n   - "
			     << icurrent->answer << endl;
			icurrent = icurrent->link;
			++returncode;
		}
		current = current->link;
		returncode += 10;
	}
	returncode += 100;
	return returncode;
}
//Method to display a random question from a particular category
int trivia_arch::display_random(char input[], char answer[], char question[])
{
	cat_node * current = head;
	indv_node * icurrent = NULL;
	int returncode = 0;
	int num = rand();
	int count = 0;

	if (!head) return 0;
	else returncode += 10;
	while (current->link && strcmp(input, current->cat) != 0)
	{
		current = current->link;
		returncode += 10;	
	}
	if (strcmp(input, current->cat) != 0) return 0;
	icurrent = current->ihead;
	if (!icurrent) return returncode;
	else ++returncode;
	while (icurrent)
	{
		++count;
		icurrent = icurrent->link;
	}
	icurrent = current->ihead;
	int var = num % count;
	for (int i = 0; i != var && icurrent; ++i)
	{
		icurrent = icurrent->link;
		++returncode;
	}
	if (icurrent)
	{

		cout << "\n" << icurrent->question << endl;
		strcpy(answer, icurrent->answer);
		strcpy(question, icurrent->question);
		returncode += 100;
	}
	return returncode;
}
//Method to match a given answer with the most recently displayed trivia
bool trivia_arch::match_answer(char answer[], char question[]) 	
{
	cat_node * current = head;
	indv_node * icurrent = NULL;
	bool matchflag = false;

	if (!head) return false;
	while (current && matchflag == false)
	{
		icurrent = current->ihead; 
		if (icurrent && !strcmp(icurrent->question, question) 
				&& !strcmp(icurrent->answer, answer))
			matchflag = true;
		while (icurrent && strcmp(icurrent->question, question) != 0)
		{
			icurrent = icurrent->link;

			if (icurrent && !strcmp(icurrent->question, question) 
					&& !strcmp(icurrent->answer, answer))
				matchflag = true;
		}
		current = current->link;
	}
	return matchflag;

}
