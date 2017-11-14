#include "reversepolish.h"
#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

reversePolish::reversePolish()
{
}
reversePolish::~reversePolish()
{
}

queue<string> reversePolish::infix_to_postfix(string infix){
// Ta funkcja zamienia obiekt klasy string notacji konwencjonalnej na kolejkę obiektów klasy string w Odwrotnej Notacjii Polskiej
    stack <string> stack_of_operators;
    queue <string> postfix2;
    string numbers = "y.1234567890";
    string operators = "+-/*^";
    int number_of_left_parentheses = 0;
    int number_of_right_parentheses = 0;
    string::size_type pos = 0;
    string replacement = "           ";
    for (int i = 0; i < infix.length(); i++){
        if (infix.substr(i, 1)!=" "){
            if (infix.substr(i, 1)=="-" && infix.substr(i-1, 1) == "("){
                pos = infix.find_first_not_of(numbers, i+1);
                postfix2.push(infix.substr(i, pos - i));
                infix.replace(i, pos - i, replacement.substr(0, pos - i));
            }
            else if (infix.find_first_of(numbers, i)==i){
                pos = infix.find_first_not_of(numbers, i);
                postfix2.push(infix.substr(i, pos - i));
                infix.replace(i, pos - i, replacement.substr(0, pos - i));
            }
            else if (infix.find_first_of(operators, i)==i || infix.find("sin", i)==i || infix.find("cos", i)==i || infix.find("tan", i)==i || infix.find("exp", i)==i || infix.find("log", i)==i){
                if (!stack_of_operators.empty()){
                while (!stack_of_operators.empty() && (((checkIfHigherOrEqualOrder(infix.substr(i, 1), stack_of_operators.top())=="higher"
                        || checkIfHigherOrEqualOrder(infix.substr(i, 1), stack_of_operators.top())=="equal")
                        && (infix.substr(i, 1)=="-" || infix.substr(i, 1) == "/" || infix.substr(i, 1) == "^" || infix.substr(i, 1)=="*" || infix.substr(i, 1) == "+"))
                        ||

                        ((checkIfHigherOrEqualOrder(infix.substr(i, 1), stack_of_operators.top())=="higher" ) &&
                        (infix.substr(i, 1)=="*" || infix.substr(i, 1) == "+"))

                                                       ) && stack_of_operators.top()!="("

                       ){

                        postfix2.push(stack_of_operators.top());

                        stack_of_operators.pop();
                }
                }

                if (infix.find("sin", i)==i || infix.find("cos", i)==i || infix.find("tan", i)==i || infix.find("exp", i)==i || infix.find("log", i)==i){
                    stack_of_operators.push(infix.substr(i, 3));
                    infix.replace(i, 3, replacement.substr(0, 3));
                }
                else
                    stack_of_operators.push(infix.substr(i, 1));
            }

            else if (infix.find_first_of('(', i)==i){
                stack_of_operators.push(infix.substr(i, 1));
                number_of_left_parentheses +=1;
            }

            else if (infix.find_first_of(')', i)==i){
                number_of_right_parentheses+=1;
                while (!stack_of_operators.empty() && stack_of_operators.top()!= "("){
                    postfix2.push(stack_of_operators.top());
                    stack_of_operators.pop();
                }
                if (!stack_of_operators.empty()){
                    stack_of_operators.pop();
                }
                if (number_of_right_parentheses > number_of_left_parentheses){
                    postfix2.push ("Cos poszlo nie tak");
                    return postfix2;
                }
            }
            else {
                postfix2.push ("Cos poszlo nie tak");
                return postfix2;
            }
        }
    }
    if (number_of_left_parentheses!=number_of_right_parentheses){
        postfix2.push ("Cos poszlo nie tak");
        return postfix2;
    }

    while (!stack_of_operators.empty()){
        postfix2.push(stack_of_operators.top());
        stack_of_operators.pop();
    }

return postfix2;
}

string reversePolish::postfix_string(queue<string> postfix3){
// Ta funkcja zamienia kolejkę obiektów klasy string na jeden obiekt klasy string
    string postfix;
    if (postfix3.back()=="Cos poszlo nie tak"){
        return postfix = "Coś poszło nie tak";
    }
    while (!postfix3.empty()){
        postfix += postfix3.front();
        postfix += " ";
        postfix3.pop();
    }
    return postfix;
}



string reversePolish::checkIfHigherOrEqualOrder(string string_to_check, string top_of_stack){
// Ta funkcja sprawdza czy dany string znajdujący się na szczycie stosu jest wyższego rzędu niż obecnie rozważany
    string operators = "()sctle^*/+-";
    int levels [12] = {5, 5, 4, 4, 4, 4, 4, 3, 2, 2, 1, 1};
    int string_to_check_level = 6;
    int top_of_stack_level = 6;
    string higher_or_equal = "lower";
    for (int i = 0; i < 12; i++){
        if (string_to_check.find_first_of( operators.substr(i, 1), i)==i){
            string_to_check_level = levels[i];
        }
        if (top_of_stack. find_first_of (operators.substr(i, 1))==i){
            top_of_stack_level = levels[i];
        }
    }
    if (string_to_check_level < top_of_stack_level){
        higher_or_equal = "higher";
    }
    else if (string_to_check_level == top_of_stack_level){
        higher_or_equal = "equal";
    }
    return higher_or_equal;
}




