#ifndef REVERSEPOLISH_H
#define REVERSEPOLISH_H
#include <iostream>
#include <string>
#include <queue>
using namespace std;


class reversePolish
{
private:
    string infix;
    string checkIfHigherOrEqualOrder(string char_to_check, string top_of_stack);
    struct node{
        string key;
        node* left;
        node* right;
    };
    node* root;
public:
    reversePolish();
    ~reversePolish();
    queue<string> infix_to_postfix(string infix);
    string postfix_string(queue<string> infix);

};

#endif // REVERSEPOLISH_H
