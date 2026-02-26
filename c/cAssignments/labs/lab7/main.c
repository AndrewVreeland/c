

// Arup Guha
// 6/20/07
// Written in COP 3502 to illustrate an array implementation of a stack.
// modified by Tanvir Ahmed 6/1/2020
// Modified by Adam Betinsky on 2/3/2025 to save time while doing Lab #7
// UPDATED ON 2/4/2025 to allow for a character stack instead of an integer stack
// Updated again on 10/2/2025 to account for issues encountered by students
// Lab #7: Stack Implementation Skeleton Code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //needed for isdigit
// The array will store the items in the stack, first in
// index 0, then 1, etc. top will represent the index
// to the top element in the stack. If the stack is
// empty top will be -1.
#define SIZE 100
#define EMPTY -1
typedef struct stack
{
    char items[SIZE];
    int top;
} stack;
// Provided functions
void initialize(struct stack *stackPtr);
int full(struct stack *stackPtr);
int push(struct stack *stackPtr, char value);
int empty(struct stack *stackPtr);
char pop(struct stack *stackPtr);
int peek(struct stack *stackPtr);
//---------------------------------------------
// Functions you need to complete (in addition to main)
int checkBalance(char exp[]);
int priority(char ch);
int isOperator(char ch);
char *infixToPostfix(char infix[]);
int isParentheses(char ch1);
int main()
{
    return 0;
}
void initialize(struct stack *stackPtr)
{
    stackPtr->top = -1;
}
// If the push occurs, 1 is returned. If the
// stack is full and the push can't be done, 0 is
// returned.
int push(struct stack *stackPtr, char value)
{
    // Check if the stack is full.
    if (full(stackPtr))
        return 0;
    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->items[stackPtr->top + 1] = value;
    (stackPtr->top)++;
    return 1;
}
// Returns true iff the stack pointed to by stackPtr is full.
int full(struct stack *stackPtr)
{
    return (stackPtr->top == SIZE - 1);
}
// Returns true iff the stack pointed to by stackPtr is empty.
int empty(struct stack *stackPtr)
{
    return (stackPtr->top == -1);
}
// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is popped and returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
char pop(struct stack *stackPtr)
{
    char retval;
    // Check the case that the stack is empty.
    if (empty(stackPtr))
        return 'I';
    // Retrieve the item from the top of the stack, adjust the top and return
    // the item.
    retval = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;
    return retval;
}
// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
int peek(struct stack *stackPtr)
{
    // Take care of the empty case.
    if (empty(stackPtr))
        return EMPTY;
    // Return the desired item.
    return stackPtr->items[stackPtr->top];
}
/*
 * -------------------------------------------------------------------
 *
 * This marks the start of the functions you must complete
 */
int main()
{
    char inFixExpression[SIZE];

    printf("\n Enter Expression: ");
    scanf("%[^\n]s", inFixExpression);

    if (checkBalance(inFixExpression))
    {
        char *postfixExpression = infixToPostfix(infixToPostfix);
        printf(" The postfix is %s\n", postfixExpression);

        free(postfixExpression);
    }

    return 0;
}
int checkBalance(char exp[])
{
    stack workingStack;
    initialize(&workingStack);
    printf("\n Checking balance...\n");
    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (exp[i] == '[' || exp[i] == '(' || exp[i] == '{')
        {
            push(&workingStack, exp[i]);
        }
        else if (exp[i] == ']')
        {
            char poppedValue = pop(&workingStack);
            if (poppedValue == 'I' || poppedValue != '[')
            {
                printf("INVALID for ]!!!\n");
                return 0;
            }
        }
        else if (exp[i] == ')')
        {
            char poppedValue = pop(&workingStack);
            if (poppedValue == 'I' || poppedValue != '(')
            {
                printf("INVALID for )!!!\n");
                return 0;
            }
        }
        else if (exp[i] == '}')
        {
            char poppedValue = pop(&workingStack);
            if (poppedValue == 'I' || poppedValue != '{')
            {
                printf("INVALID for }!!!\n");
                return 0;
            }
        }
    }
    if (pop(&workingStack) != 'I')
    {
        printf("INVALID. you have extra!!!\n");
    }
    else
    {
        printf("VALID\n");
        return 1;
    }
}
int priority(char ch)
{
    if (ch == '^')
    {
        return 3;
    }
    else if (ch = '%' || ch == '*' || ch == '/')
    {
        return 2;
    }
    else if (ch == '+' || ch == '-')
    {
        return 1;
    }
    else if (ch == '(' || ch == '[' || ch == '{')
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
int isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char *infixToPostfix(char infix[])
{
    stack workingStack;
    initialize(&workingStack);
    int infixLength = strlen(infix);
    char *postFixExpression = malloc(sizeof(char) * (infixLength + 1) * 2);

    int postfixIndex = 0;

    for (int i = 0; i < infixLength; i++)
    {
        if (isdigit(infix[i]))
        {
            while (isdigit(infix[i]))
            {
                postFixExpression[postfixIndex] = infix[i];
                i++;
                postfixIndex++;
            }
            i--;
            postFixExpression[++postfixIndex] = ' ';
            postFixExpression++;
        }
        else if (isOperator(infix[i]))
        {
            if (empty(&workingStack))
            {
                push(&workingStack, infix[i]);
            }
            else if (priority(infix[i]) > priority(pee(&workingStack)))
            {
                push(&workingStack, infix[i]);
            }
            else
            {
                while (!empty(&workingStack) && priority(infix[i]) <= priority(peek(&workingStack)) && !isParentheses(peek(&workingStack)))
                {
                    postFixExpression[postfixIndex++] == pop(&workingStack);
                    postFixExpression[postfixIndex++] = ' ';
                }
                push(&workingStack, infix[i]);
            }
        }
        else if (infix[i] == '(' || infix[i] == ')')
        {
            if (infix[i] == '(')
            {
                push(&workingStack, infix[i]);
            }
            else
            {
                while (peek(&workingStack) != '(')
                {
                    postFixExpression[postfixIndex++] = pop(&workingStack);
                    postFixExpression[postfixIndex++] = ' ';
                }
                pop(&workingStack);
            }
        }

        // TODO check this code here 
        while (peek(&workingStack) != 'I')
        {
            postFixExpression[postfixIndex++] = pop(&workingStack);
            if(peek(&workingStack) != 'I')
            {
                postFixExpression[postfixIndex++] = ' ';
            }
        }
        postFixExpression[postfixIndex] = '\0';

        return postFixExpression;
    }
}

int isParentheses(char ch)
{
    if (ch == '[' || ch == '(' || ch == '{' || ch == '}' || ch == ']' || ch == ')')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
