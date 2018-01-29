#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


//#ifndef pa3_H
//#define pa3_H
#include <string>
using namespace std;

class Stack{
	private:
		struct item{
			string name;
			int value;
			item* prev;
		};

		item* stackPointer;

	public:
		void Push(string name, int value);
		void Pop();
		void ReadItem(item* read);
		void Print();

		Stack();
		~Stack();
};









#endif // HEADER_H_INCLUDED
