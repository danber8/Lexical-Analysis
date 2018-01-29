#include <string>
#include <iostream>
#include <cstdlib>
#include "pa3.h"
#include <fstream>
#include <cmath>
#include <sstream>
using namespace std;


Stack::Stack(){     //constructor
	stackPointer = NULL;    //points to the top of the stack
}

Stack::~Stack(){            //deconstructor
	item* p1;       //2 pointers
	item* p2;

	p1 = stackPointer;
	while (p1 != NULL){
		p2 = p1;
		p1 = p1->prev;
		p2->prev = NULL;
		delete p2;
	}
}

void Stack::Push(string name, int value){       //adds elements to the stack
	item* n = new item;

	n->name = name;
	n->value = value;

	if (stackPointer == NULL){
		stackPointer = n;
		stackPointer->prev = NULL;
	}
	else{
		n->prev = stackPointer;
		stackPointer = n;

	}
}

void Stack::ReadItem(item* r){      //other methods use this to print out a stack

	cout <<r->name << "\t";
	//cout << "Value: " << r->value << "\n";

}

void Stack::Pop(){          //removes the top element off the stack
	if (stackPointer == NULL){
		cout << "There is nothing on the stack\n";
	}
	else{
		item* p = stackPointer;
		ReadItem(p);
		stackPointer = stackPointer->prev;
		p->prev = NULL;
		delete p;
	}
}

void Stack::Print(){            //prints out the stack in filo order
	item *p = stackPointer;

	while (p != NULL){
		ReadItem(p);
		p = p->prev;
	}
}


int main(){
	Stack Keywords;
	Stack Identifiers;
	Stack Constants;
	Stack Operators;
	Stack Delimiters;           //I created a bunch of stacks to put my elements in
	Stack SyntaxErrors;

	string potentialWords;
	string potentialNumbers;        //the strings store potential elements before they go into the stacks
	string punctuation;
	string mathsymbols;
	string potentialIdentifiers;
	bool plusplus;
	bool minusminus;

	int loopCounter = 0;            //counts the number of for loops


	cout << "INPUT> Please enter the name of the input file: \n";

    string userinput;       //asks the user for the name of the file
    cin>>userinput;

    userinput += ".txt";            //adds .txt to the file name
    ifstream infile;
    infile.open(userinput.c_str());         //opens the file

    if(infile.fail()){
        cerr<<"File not found, system exiting";         //the system exits if the file is not found
        return 0;
    }
    else{
        char data;
        while (!infile.eof()){      //eof means end of file
			infile >> data;
			cout << data;           //prints out the text document to the screen

			if (isalpha(data) && isupper(data)){        //if the char is part of the alphabet and uppercase, it is a keyword, so add it to the keyword string

				potentialWords += data;


                if(potentialWords == "BEGIN"){      //check for specific cases
                    Keywords.Push("BEGIN", 0);
                    potentialWords = "";
                }

                if(potentialWords == "END"){
                    Keywords.Push("END", 0);
                    potentialWords = "";
                }
			}
			else if(isalpha(data) && islower(data)){        //checks for lower case letters and adds them to a string
                potentialIdentifiers += data;
			}

			else if (isdigit(data)){            //checks for numbers
				potentialNumbers += data;
			}

			else if (data == ','){
				Delimiters.Push(",", 0);        //adds commas to their stack
				if(potentialNumbers != ""){                 //numbers can come before commas so if the number string isn't empty, add it to its stack
                    Constants.Push(potentialNumbers,0);
                    potentialNumbers = "";
				}

				else if(potentialIdentifiers != ""){        //identifiers also can come before commas
				    string s;
                    stringstream ss;
                    ss<<data;
                    ss>>s;
                    Identifiers.Push(potentialIdentifiers, 0);
                    potentialIdentifiers = "";
				}
			}
			else if(data == '='){
                Operators.Push("=",0);      //adds BEGIN to stack
                if(potentialWords == "BEGIN"){
                    Keywords.Push(potentialWords,0);
                    potentialWords = "";
                }
                else{                                   //checks if begin is spelled wrong
                    SyntaxErrors.Push(potentialWords,0);
                }
                if(potentialIdentifiers != ""){
                    Identifiers.Push(potentialIdentifiers,0);       //adds possible identifiers to its stack
                }
                potentialWords = "";        //resets identifiers and keywords
                potentialIdentifiers = "";
			}
            else if(data == '+'){
                mathsymbols += "+";                 //identifiers can come before order of operations sighs so check if the identifier string isn't empty
                if(potentialIdentifiers != ""){             //if it isn't empty, add it to its respective stack
                    Identifiers.Push(potentialIdentifiers,0);
                }
                potentialWords = "";
                potentialIdentifiers = "";
            }                                               //be sure to reset the strings after adding them to the stack
            else if(data == '*'){
                mathsymbols += "*";
                if(potentialIdentifiers != ""){
                    Identifiers.Push(potentialIdentifiers,0);
                }
                potentialWords = "";
                potentialIdentifiers = "";
            }
            else if(data == '/'){
                mathsymbols += "/";
                if(potentialIdentifiers != ""){
                    Identifiers.Push(potentialIdentifiers,0);
                }
                potentialWords = "";
                potentialIdentifiers = "";
            }
            else if(data == '-'){
                mathsymbols += "-";
                if(potentialIdentifiers != ""){
                    Identifiers.Push(potentialIdentifiers,0);
                }
                potentialWords = "";
                potentialIdentifiers = "";
            }
			else if (data == ';'){
				Delimiters.Push(";", 0);
                if(potentialIdentifiers != ""){      //identifiers can also come before semicolons so do the same thing you did for order of operations signs
                    Identifiers.Push(potentialIdentifiers,0);
                }
                potentialWords = "";
			}
            else if(data == ')' && mathsymbols!= ""){       //plus plus or minus minus increments can come before ')'
                Operators.Push(mathsymbols, 0);
                if(punctuation == "++"){
                    plusplus = true;
                    potentialWords = "";
                }
                else if(punctuation == "--"){
                    minusminus = true;
                }
                punctuation = "";
                potentialWords = "";
            }
			else if (data == '('){
                if(potentialWords == "FOR"){        //CHecks for FOR keywords
                Keywords.Push(potentialWords,0);
                potentialWords = "";
                loopCounter++;          //counts the number of fors
                }
                else if(potentialWords == "BEGIN"){         //checks for BEGIN again
                Keywords.Push(potentialWords,0);
                potentialWords = "";
                }

                else{
                    SyntaxErrors.Push(potentialWords,0);        //checks for misspelled keywords
                }

                potentialWords = "";
			}
			else if(potentialWords!= ""){
                if(potentialWords == "BEGIN"){
                    Keywords.Push(potentialWords,0);
                    potentialWords = "";
                }
                else if(potentialIdentifiers == "FOR"){
                    Keywords.Push(potentialWords,0);
                    potentialWords = "";
                }
			}
        }
        infile.close();
    }

    cout<<"\nOUTPUT> The depth of nested loop(s) is "<<loopCounter;
    cout<<"\nKeywords: ";
    Keywords.Print();
    cout<<"\nConstants: ";
    Constants.Print();
    cout<<"\nIdentifiers: ";
    Identifiers.Print();                //print out what the user wants
    cout<<"\nSyntax Errors: ";
    SyntaxErrors.Print();

    cout<<"\nOperators: ";
    Operators.Print();
    cout<<"\nDelimiters: ";
    Delimiters.Print();

    cout<<"\n";

	system("PAUSE");
	return 0;
}
