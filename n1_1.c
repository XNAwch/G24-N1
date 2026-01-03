#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct nd{
    char c;
    struct nd *next;
}node;
node *top=NULL;

void push(char x){ //Add a value
    node *n=malloc(sizeof(node));
    n->c=x;
    n->next=top;
    top=n;
}

char pop(){ //Delete a value
    if(top==NULL) return '\0';
    char p;
    node *n=top;
    top=top->next;
    p=n->c;
    free(n);
    return p;
}

char stacktop(){ //Check what's on the top
    if(top== NULL) return '\0';
    return top->c;
}

int checkpr(char temp){ //Check priority
    if(temp=='^') return 3;
    if(temp=='*'||temp=='/') return 2;
    if(temp=='+'||temp=='-') return 1;
    return 0;
}

void checkoper(char ck){ //Check operator
    if(ck=='(') push(ck);
    else if(ck==')'){
        while(top != NULL && stacktop() != '(') printf("%c",pop());
        pop();
    }else{
        while(top != NULL && stacktop() != '(' && (checkpr(stacktop()) > checkpr(ck) || (checkpr(stacktop()) == checkpr(ck) && ck != '^'))) printf("%c",pop());
        push(ck);
    } 
}

void main(){
    char ch,con;
    int i=1;
    printf("Infix to Postfix:\n");
    do{
        printf("Enter Infix %d: ",i);
        while((ch=getchar()) != '\n' && ch != EOF){
        if(isspace(ch)) continue;
        if(isalnum(ch)) printf("%c",ch);
        else checkoper(ch);
        }
        while(top != NULL) printf("%c",pop());
        printf("\n");
        printf("Enter to continue, or '.' to stop");
        i++;
    }while(con=getchar() != '.');
}