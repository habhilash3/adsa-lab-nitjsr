/*
Set1 Q1. Implement a function to convert an infix arithmetic expression involving the operators +, -, /, *, (, ) and
         single digit constant integer operands to postfix expression. Assume usual precedence of operators in
         the order of /, *, + and -. Parentheses ( ) are used to override the precedence of operators.
*/

#include <stdio.h>
#include <ctype.h>
#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top >= MAX - 1) {
        printf("Operator Stack Overflow!\n");
        return;
    }
    stack[++top] = c;
}

char pop() {
    if (top < 0) {
        printf("Operator Stack Underflow!\n");
        return '\0';
    }
    return stack[top--];
}

int precedence(char op) {
    switch (op) {
        case '/':
        case '*': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void infixToPostfix(char *infix, char *postfix) {
    int i = 0, k = 0;
    char c;

    while ((c = infix[i++]) != '\0') {
        if (c == ' ') continue;  // Ignore spaces
        if (isdigit(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = pop();
            }
            pop(); // remove '('
        } else if (isOperator(c)) {
            while (top != -1 && precedence(stack[top]) >= precedence(c)) {
                postfix[k++] = pop();
            }
            push(c);
        }
    }

    while (top != -1) {
        postfix[k++] = pop();
    }
    postfix[k] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression: ");
    scanf("%[^\n]", infix); // Read expression with spaces

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}
