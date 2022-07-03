#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct ArrayStack
{
    int top;
    int capacity;
    char* array;
};
struct ArrayStack* createStack(int cap)
{
  struct ArrayStack* stack;
  stack=(struct ArrayStack*) malloc(sizeof(struct ArrayStack));
  stack->top=-1;
  stack->capacity=cap;
  stack->array=(char*)malloc(stack->capacity*sizeof(char));
  return(stack);
}
int isEmpty(struct ArrayStack* stack)
{
    if(stack->top==-1)
        return(1);
    else
        return(0);
}
int isFull(struct ArrayStack* stack)
{
    if(stack->top==stack->capacity-1)
        return(1);
    else
        return(0);
}
void push(struct ArrayStack* stack,char item)
{
    if(!isFull(stack))
    {
        stack->top++;
        stack->array[stack->top]=item;

    }
}
int pop(struct ArrayStack* stack)
{
    char item;
    if(!isEmpty(stack))
    {
       item= stack->array[stack->top];
       stack->top--;
       return(item);
    }
    return(-1);
}
int stackTop(struct ArrayStack* stack){
    int item=stack->array[stack->top];
    return item;
}

int isOperator(char ch ){
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){
        return 1;
    }
    else{
        return 0;
    }
}

int precedence(char ch){
    if(ch=='*'||ch=='/'){
        return 3;
    }
    else if(ch=='+'||ch=='-'){
        return 2;
    }
    else{
        return 0;
    }
}

char* infixtopostfix(char* infix){
   struct ArrayStack * stack;
   int l=strlen(infix);
   stack=createStack(l);
   char * postfix=(char *)malloc((l+1)*sizeof(char));
   int i=0;
   int j=0;
   
   while(infix[i]!='\0'){
      if(!isOperator(infix[i])){
         postfix[j]=infix[i];
         i++;
         j++;
      }
      else if(precedence(infix[i])>precedence(stackTop(stack))){
          push(stack,infix[i]);
          i++;
      }
      else{
          postfix[j]=pop(stack);
          j++;
      }
   }
   while(!isEmpty(stack)){
       postfix[j]=pop(stack);
       j++;
   }
   postfix[j]='\0';
   return postfix;

}

void main(){
    char infix[]="x-y/z-k*d";
    char* s=infixtopostfix(infix);
    printf("The postfix is %s",s);
}