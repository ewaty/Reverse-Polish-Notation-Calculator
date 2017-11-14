#ifndef BET_H
#define BET_H
#include <string>
#include <queue>
using namespace std;

class BET {

private:
    struct node{
        string key;
        node* left;
        node* right;
    };
    node* root;
    node* create_leaf_private(string key);
    node* build_tree(queue<string> postfix);
    node* join_subtrees(string key, node *left, node *right);
    double getValue( node* root, double value );

public:
    BET(queue<string> postfix);
    ~BET();
    double getValue_publc(double value);

};

#endif // BET_H
