#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
#include <stack>
#include <math.h>
#include "bet.h"
using namespace std;
BET::BET(queue<string> postfix)
{
    root = BET::build_tree(postfix);
}
BET::~BET(){

}
BET::node* BET::create_leaf_private(string key){
// Ta funkcja tworzy liść którego wskaźniki "left" i "right" są puste
    node* n = new node;
    n -> key = key;
    n -> left = NULL;
    n -> right = NULL;
    return n;
}


BET::node* BET::join_subtrees(string key, node *left, node *right){
// Ta funkcja łączy dwa korzenie poddrzew
    node* n = new node;
    n -> key = key;
    n -> left = left;
    n -> right = right;
    return n;
}

BET::node* BET::build_tree(queue<string> postfix){
// Ta funkcja buduje drzewo i oddaje wskaźnik do jego korzenia
    stack<node*> stack_of_nodes;
    node* right;
    node* left;
    node* root;
    while (!postfix.empty()){
        if (postfix.front().find_first_of("y.0123456789") != string::npos){
            stack_of_nodes.push(create_leaf_private(postfix.front()));
            postfix.pop();
        }
        else if (postfix.front()=="sin" || postfix.front()=="cos" || postfix.front()=="tan" || postfix.front()=="log" || postfix.front()=="exp"){
            left = stack_of_nodes.top();
            stack_of_nodes.pop();
            stack_of_nodes.push(join_subtrees(postfix.front(), left, NULL));
            postfix.pop();
        }
        else {
            right = stack_of_nodes.top();
            stack_of_nodes.pop();
            left = stack_of_nodes.top();
            stack_of_nodes.pop();
            stack_of_nodes.push(join_subtrees(postfix.front(), left, right));
            postfix.pop();
        }

    }
    root = stack_of_nodes.top();
    stack_of_nodes.pop();
return root;
}

double BET::getValue( BET::node* root, double value ) {
// Ta funkcja oblicza wartość funkcji zaisanej na drzewie dla zadanej wartości
             if ( root->key.find_first_of("y0123456789.", 0) != string::npos ) {
                 if (root->key == "y"){
                    return value;
                 }
                 else{
                    return stod(root->key);
                 }
             }
             else {
                double leftVal = getValue(root->left , value);
                double rightVal = 1;
                if (root->right!=NULL){
                    rightVal = getValue(root->right, value);
                }
                switch ( root->key[0] ) {
                   case '+':  return leftVal + rightVal;
                   case '-':  return leftVal - rightVal;
                   case '*':  return leftVal * rightVal;
                   case '/':  return leftVal / rightVal;
                   case '^':  return pow(leftVal, rightVal);
                   case 's':  return sin(leftVal);
                   case 'c':  return cos(leftVal);
                   case 't':  return tan(leftVal);
                   case 'e':  return exp(leftVal);
                   case 'l':  return log10(leftVal);
                }
             }
          }
double BET::getValue_publc(double value){
// Ta funkcja zapewnia dostęp do funkcji getValue
    return getValue(root, value);
}
