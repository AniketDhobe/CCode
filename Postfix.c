#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack{
    char data;
    struct stack * next;
} STRUCT;

int push (STRUCT ** root, char data)
{
    STRUCT * my_stack = (STRUCT *)malloc(sizeof(STRUCT));
    my_stack->data = data;
    my_stack->next = *root;
    *root = my_stack;
}

char pop (STRUCT ** root)
{
    STRUCT * my_stack = *root;
    char ret_val = my_stack->data;
    *root = (*root)->next;
    return ret_val;
}

char peek (STRUCT * root)
{
    return root->data;
}

int isempty (STRUCT * root)
{
    return !(root);
}

int isOperand(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int precidence(char ch)
{
    switch (ch)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
}

int main() 
{
	//code
	char buf[256], *ch = buf; 
	int i = 0;
	STRUCT * my_stack;
	scanf("%s", buf);
	int length = strlen(buf);
	for(i = 0; i < length; i++){
	    if(isOperand(*(ch))) {
	        printf("%c", *(ch));
	    }
	    else if(*ch == '('){
	        push(&my_stack,*ch);
	    }
	    else if(isempty(my_stack) || peek(my_stack) == '('){
	        push(&my_stack,*ch);
	    }
	    else if(*ch == ')'){
	        while(peek(my_stack) != '(') {
	            printf("%c",pop(&my_stack));
	        }
	        pop(&my_stack);
	    }
	    else {
	        if(precidence(*ch) > precidence(peek(my_stack))){
	            push(&my_stack, *ch);
	        } else {
	            while(!isempty(my_stack) &&
	                    (precidence(*ch) <= precidence(peek(my_stack))) &&
	                    (peek(my_stack) != '(')){
	                printf("%c",pop(&my_stack));
	            }
	            push(&my_stack, *ch);
	        }
	    }
	    ch++;
	    
	}
	while(!isempty(my_stack)){
	    printf("%c",pop(&my_stack));
	}
	// printf("%s\n", buf);
	
}
