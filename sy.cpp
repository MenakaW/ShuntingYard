#include <iostream>
#include <cstring>
#include "BinaryTreeNode.h"

using namespace std;

//struct for node used in stack and queue
//charn is data value, and digits is number of chars in data value
struct Node{
  char* charn;
  Node* next = nullptr;
  int digits;
};


//method prototypes, phew there's alot
void infixToPostfix(char infix[20]);
void enqueue(Node* &tail, Node* n);
Node* dequeue(Node* &head);
void push(Node* &head, Node* n);
Node* pop(Node* &head);
Node* peek(Node* head);
int numDigits(char infix[20], int index);
void printStack(Node* head);
void printQueue(Node* head);
void convertToTree(Node* headPrev);
void treePush(BinaryTreeNode* &head, BinaryTreeNode* &n);
void printTreeStack(BinaryTreeNode* head);
BinaryTreeNode* treePop(BinaryTreeNode* &head);
void printInfix(BinaryTreeNode* head);
void printPostfix(BinaryTreeNode* head);
void printPrefix(BinaryTreeNode* head);

int main(){

  //get the infix equation from the user with no spaces
  char input[20];
  cout << "please enter your mathematical expression with no spaces." << endl;
  cin >> input;
  cin.get();
  cout << input << endl;
  infixToPostfix(input);
  return 0;
  
}

//this method doesn't actually go to postfix like i thought, it just goes through the shunting yard algorithm
void infixToPostfix(char infix[20]){
  
  //create the head pointer for operator stack and head/tail pointers for output queue
  Node* headStack = nullptr;
  Node* headQueue = nullptr;
  Node* tailQueue = nullptr;
  //cycle through user input
  for(int a = 0; a < strlen(infix); a++){
    int b = (int)infix[a];
    //if it's an operator
    if(b==42 || b==40 || b==41 || b==43 || b==45 || b==47 || b==94){
      //create a new node with the operator as the value
      Node* n = new Node;
      char* charn = new char[1];
      charn[0] = infix[a];
      n->charn = charn;
      n->digits = 1;
      //if there's nothing in the stack, add in the operator
      if(headStack==nullptr){
	headStack = n;
      }
      //if it's a plus or minus, it has the lowest weight, so only add it on top if there's a opening brace
      //otherwise keep popping till you reach the ond or a opening brace
      else if(infix[a]=='+'|| infix[a]=='-'){
	if(headStack->charn[0]=='('){
	  push(headStack,n);
	}
	else{
	  while(headStack!=nullptr && headStack->charn[0]!='('){
	    enqueue(tailQueue,pop(headStack));
	  }
	  push(headStack,n);
	}
      }
      //if it's multiplication or division, only put it directly on top for lower weight operations like plus and minus, and of course opening brace
      //else keep popping till you reach a lower weight, an opening brace, or the end
      else if(infix[a]=='*' || infix[a]=='/'){
	if(headStack->charn[0]=='(' || headStack->charn[0]=='+' || headStack->charn[0]=='-'){
	  push(headStack,n);
	}
	else{
	  while(headStack!=nullptr && headStack->charn[0]!='(' && headStack->charn[0]!='+' && headStack->charn[0]!='-'){
	    enqueue(tailQueue, pop(headStack));
	  }
	  push(headStack,n);
	}
      }
      //if it's a closing bracket, keep popping till you see the left bracket then pop out that one too
      else if(infix[a]==')'){
	push(headStack, n);
	while(headStack->charn[0]!='('){
	  if(headStack->charn[0]==')'){
	    pop(headStack);
	  }
	  else{
	    enqueue(tailQueue,pop(headStack));
	  }
	}
	pop(headStack);
      }
      //the exponent '^' always goes on top
      else{
	push(headStack, n);
      }
    }
    //if it's a variable or a number
    else{
      //find out number of digits if it's a number like 32 or 105
      //create a new node with the value
      int digits = numDigits(infix, a);
      char* charn = new char[digits];
      for(int c = 0; c < digits; c++){
	charn[c] = infix[a+c];
	if(c!=0){
	  a++;
	}
      }
      Node* n = new Node;
      n->charn = charn;
      n->digits = digits;
      //add the new node to the queue
      if(headQueue==nullptr){
	headQueue = n;
	tailQueue = n;
      }
      else{
	enqueue(tailQueue, n);
      }
    }
  }
  //now that you've processed the input, pop everything from the stack to the output queue
  while(headStack!=nullptr){
    enqueue(tailQueue,pop(headStack));
  }
  //print out stack and output queue for debugging
  cout << "stack: " << endl;
  printStack(headStack);
  cout << "queue: " << endl;
  printQueue(headQueue);
  //covert the shuntingyard output to a tree
  convertToTree(headQueue);
}

void convertToTree(Node* headPrev){
  
  //create a head pointer
  BinaryTreeNode* head = nullptr;
  //cycle through the output queue from shunting yard
  while(headPrev!=nullptr){
    //for every node from output queue, create a new tree node and set the left and right if it's an operator
    Node* n = pop(headPrev);
    BinaryTreeNode* bn = new BinaryTreeNode(n->charn, n->digits);
    char c = bn->getChar()[0];
    //to set left and right, pop the last two tree nodes out of their places and then connect them to the current tree node and then push the tree node
    if(c==42 || c==43 || c==45 || c==47 || c==94){
      bn->setLeft(treePop(head));
      bn->setRight(treePop(head));
    }
    treePush(head, bn);
  }
  //output the tree nodes on the stack
  cout << "tree: " << endl;
  printTreeStack(head);
  //prompt the user to choose one of the three
  cout << "would you like to see infix, prefix, or postfix" << endl;
  char fix[20];
  cin >> fix;
  cin.get();
  if(fix[1]=='n'){
    printInfix(head);
  }
  else if(fix[1]=='r'){
    printPrefix(head);
  }
  else if(fix[1]=='o'){
    printPostfix(head);
  }
  else{
    cout << "invalid type" << endl;
  }
}

//print out the current head before recursively calling for left and right
void printPrefix(BinaryTreeNode* head){
  if(head!=nullptr){
    for(int a = 0; a < head->getDigits(); a++){
      cout << head->getChar()[a];
    }
    printPrefix(head->getLeft());
    printPrefix(head->getRight());
  }
}

//use parenthesis to mark each layer of the print-> basically each time theres an operator, you want to encompass them with parenthesis
void printInfix(BinaryTreeNode* head){
  if(head!=nullptr){
    char c = head->getChar()[0];
    if(c==42 || c==43 || c==45 || c==47 || c==94){
      cout << "(";
    }
    printInfix(head->getLeft());
    for(int a = 0; a < head->getDigits(); a++){
      cout << head->getChar()[a];
    }
    printInfix(head->getRight());
    if(c==42 || c==43 || c==45 || c==47 || c==94){
      cout << ")";
    }
  }
}

//print out the current head after recursively calling the left and right
void printPostfix(BinaryTreeNode* head){
  if(head!=nullptr){
    printPostfix(head->getLeft());
    printPostfix(head->getRight());
    for(int a = 0; a < head->getDigits(); a++){
      cout << head->getChar()[a];
    }
  }
}

//make the head point to the next tree node, and return the old head
BinaryTreeNode* treePop(BinaryTreeNode* &head){
  BinaryTreeNode* temp = head;
  head = temp->getNext();
  temp->setNext(nullptr);
  return temp;
}

//cycle through the treenodes, using next to get to each one
void printTreeStack(BinaryTreeNode* head){
  if(head!=nullptr){
    for(int a = 0; a < head->getDigits(); a++){
      cout << head->getChar()[a];
    }
    cout << endl;
    printTreeStack(head->getNext());
  }
}

//make the input node equal to head, and connect the new head to the old head
void treePush(BinaryTreeNode* &head, BinaryTreeNode* &n){
  if(head==nullptr){
    head = n;
  }
  else{
    BinaryTreeNode* temp = head;
    head = n;
    n->setNext(temp);
  }
}

//start from the head and keep printing until you reach the nullptr at the end
void printQueue(Node* head){
  if(head!=nullptr){
    for(int a = 0; a < head->digits; a++){
      cout << head->charn[a];
    }
    cout << endl;
    printQueue(head->next);
  }
}

//start at the head, and keep printing until you reach the nullptr at the end
void printStack(Node* head){
  if(head!=nullptr){
    cout << head->charn[0] << endl;
    printStack(head->next);
  }
}

//find out the number of digits by counting how many chars until the next operator
int numDigits(char infix[20], int index){
  int count = 0;
  for(int a = index; a < strlen(infix); a++){
    int b = (int)infix[a];
    if(b==42 || b==41 || b==40 || b==43 || b==45 || b==47 || b==94){
      break;
    }
    count++;
  }
  return count;
}

//add the node onto the end by connecting the old tail to the input node and making input node the new tail
void enqueue(Node* &tail, Node* n){
  Node* temp = tail;
  tail = n;
  temp->next = tail;
  tail->next = nullptr;
}

//make new head equal to the one after the old head, and then return the old head
Node* dequeue(Node* &head){
  Node* temp = head;
  head = temp->next;
  temp->next = nullptr;
  return temp;
}

//make new head equal to input node and then connect new head to the old head
void push(Node* &head, Node* n){
  if(head==nullptr){
    head = n;
  }
  else{
    Node* temp = head;
    n->next = temp;
    head = n;
  }
}

//make new head equal to the one after old head and then return the old head
Node* pop(Node* &head){
  Node* temp = head;
  head = temp->next;
  temp->next = nullptr;
  return temp;
}

//return the head
Node* peek(Node* head){
  return head;
}
