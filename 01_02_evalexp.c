/*
Set1 Q2. Implement a function to read an arithmetic expression (as given in the previous problem) from the
         command line ( C:\> in Windows and $ in Linux) and display the computed value of the expression.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>s
#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top >= MAX - 1) {
        printf("Operator Stack Overflow!\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop() {
    if (top < 0) {
        printf("Operator Stack Underflow!\n");
        exit(1);
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
        if (isdigit(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = pop();
            }
            if (top == -1) {
                printf("Error: Mismatched parentheses\n");
                exit(1);
            }
            pop(); // remove '('
        } else if (isOperator(c)) {
            while (top != -1 && precedence(stack[top]) >= precedence(c)) {
                postfix[k++] = pop();
            }
            push(c);
        } else {
            printf("Error: Invalid character '%c'\n", c);
            exit(1);
        }
    }

    while (top != -1) {
        if (stack[top] == '(') {
            printf("Error: Mismatched parentheses\n");
            exit(1);
        }
        postfix[k++] = pop();
    }
    postfix[k] = '\0';
}

int evaluatePostfix(char *postfix) {
    int valStack[MAX];
    int valTop = -1;
    int i = 0;
    char c;

    while ((c = postfix[i++]) != '\0') {
        if (isdigit(c)) {
            if (valTop == MAX - 1) {
                printf("Value Stack Overflow!\n");
                exit(1);
            }
            valStack[++valTop] = c - '0';  // convert char to int
        } else {
            if (valTop < 1) {
                printf("Value Stack Underflow!\n");
                exit(1);
            }
            int val2 = valStack[valTop--];
            int val1 = valStack[valTop--];
            switch (c) {
                case '+': valStack[++valTop] = val1 + val2; break;
                case '-': valStack[++valTop] = val1 - val2; break;
                case '*': valStack[++valTop] = val1 * val2; break;
                case '/': valStack[++valTop] = val1 / val2; break;
            }
        }
    }
    return valStack[valTop];
}

int main(int argc, char *argv[]) {
    char postfix[MAX];

    if (argc != 2) {
        printf("Usage: %s <expression>\n", argv[0]);
        return 1;
    }

    infixToPostfix(argv[1], postfix);
    printf("Postfix Expression: %s\n", postfix);
    printf("Result: %d\n", evaluatePostfix(postfix));

    return 0;
}
