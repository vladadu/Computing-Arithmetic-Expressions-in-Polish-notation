//Adumitracesei Vlad Year 1 Group 2
#include<iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
using namespace std;



class Node // we implement a class node to store a token and be able to build a tree
{
	Node *left; //we have pointers to it's left right node(this will help us build the tree)
	Node *right;
public:     //we have multiple constructors for different situations 
	Node  (string token):           caracter(token),  left(nullptr),   right(nullptr)   {}
	Node  ():                       caracter(""),     left(nullptr),   right(nullptr)   {}
	Node  (Node *new_node):         caracter(""),     left(nullptr),   right(nullptr)   {}
	~Node() {}
	string gettoken()
	{
		return caracter;
	}
	Node* getleft()
	{
		return this->left;
	}
	Node* getright()
	{
		return this->right;
	}
	void set_left(Node *new_left)
	{
		left = new_left;
	}
	void set_right(Node *new_right)
	{
		right = new_right;
	}
	void set_token(string &new_token)
	{
		caracter = new_token;
	}
private:
	string caracter;

};


class Tree //The tree class that we build with the help of a stack and a root node
{
	Node *root;
public:
	Tree(string str)
	{
		Node *curr;
		stack<Node *>rstack;
		string token = prs(str);
		root = new Node();

		curr = root;//here we set the current nod to the root node
		while (token.size() != 0)//here we star building the tree 
		{

			if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')//here we check if it is a operator the we go left on the tree and so on 
			{
				curr->set_token(token);
				curr->set_left(new Node(curr));
				curr->set_right(new Node(curr));
				rstack.push(curr->getright());
				curr = curr->getleft();
			}
			else // here we have the digit part where we pop the digit from the stack 
			{
				curr->set_token(token);
				if (rstack.size())
				{
					curr = rstack.top();
					rstack.pop();
				}
				
			}
			token = prs(str);

		}
	}
	string prs(string &str)//for the parser we just break the string in substrings and cut the string that we take from the inital string.
	{                      //so next time when we call the parser it will take the next substring and so on.
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == ' ')
			{
				string aux = str.substr(0, i);
				if (str.size() >= i + 1)
					str = str.substr(i + 1, string::npos);
				else
					return string("");
				return aux;
			}
			else if (i == str.size() - 1)
			{
				string aux = str.substr(0, i + 1);
				str = str.substr(i + 1, string::npos);
				return aux;
			}
		}
		return str;
	}
	void ex_print(Node* current)//here is the print function that prints the string in inorder.
	{
		if (current)
		{
			if (current->getright())
			{
				cout << '(';
				ex_print(current->getleft());
				cout << ' ' << current->gettoken() << ' ';
				ex_print(current->getright());
				cout << ')';
			}
			else if (current->getleft())
			{
				cout << '(';
				cout << current->gettoken();
				ex_print(current->getleft());
				cout << ')';
			}
			else
				std::cout << current->gettoken();
		}
	}
	double cal(Node *root)//this is a recursiv function that calculates tha value of the nodes
	{
		if (root->gettoken()[0] == '+')    return cal(root->getleft()) + cal(root->getright());
		if (root->gettoken()[0] == '-')    return cal(root->getleft()) - cal(root->getright());
		if (root->gettoken()[0] == '*')    return cal(root->getleft()) * cal(root->getright());
		if (root->gettoken()[0] == '/')    return cal(root->getleft()) / cal(root->getright());
		return stod(root->gettoken());
	}
	Node* getroot()
	{
		return root;
	}
};






int main()
{   ifstream my_file("test.txt");
    string file_txt;
    getline(my_file,file_txt);
    my_file.close();
	Tree test(file_txt);
    cout <<"Infix notation: ";
	test.ex_print(test.getroot());
	cout << "\n";
    cout<<"Tree value: ";
	cout << test.cal(test.getroot());
}
