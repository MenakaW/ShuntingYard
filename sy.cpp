#include <iostream>
#include <cstring>

using namespace std;

struct Node{
  char* charn;
  Node* next = nullptr;
  int digits;
};

void infixToPostfix(char infix[20]);
void enqueue(Node* &tail, Node* n);
Node* dequeue(Node* &head);
void push(Node* &head, Node* n);
Node* pop(Node* &head);
Node* peek(Node* head);
int numDigits(char infix[20], int index);
void printStack(Node* head);
void printQueue(Node* head);

int main(){

  char input[20];
  cout << "please enter your mathematical expression with no spaces." << endl;
  cin >> input;
  cin.get();
  cout << input << endl;
  infixToPostfix(input);
  return 0;
  
}

void infixToPostfix(char infix[20]){
  Node* headStack = nullptr;
  Node* headQueue = nullptr;
  Node* tailQueue = nullptr;
  for(int a = 0; a < strlen(infix); a++){
    int b = (int)infix[a];
    if(b==42 || b==40 || b==41 || b==43 || b==45 || b==47 || b==94){
      Node* n = new Node;
      char* charn = new char[1];
      charn[0] = infix[a];
      n->charn = charn;
      n->digits = 1;
      if(headStack==nullptr){
	headStack = n;
	cout << "operator and added to stack head" << endl;
      }
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
      else{
	push(headStack, n);
	cout << "added operator to stack" << endl;
      }
    }
    else{
      int digits = numDigits(infix, a);
      char* charn = new char[digits];
      for(int c = 0; c < digits; c++){
	charn[c] = infix[a];
	if(c!=0){
	  a++;
	}
      }
      Node* n = new Node;
      n->charn = charn;
      n->digits = digits;
      if(headQueue==nullptr){
	headQueue = n;
	tailQueue = n;
	cout << "added operand to queue head" << endl;
      }
      else{
	enqueue(tailQueue, n);
	cout << "added operand to queue" << endl;
      }
    }
  }
  cout << "stack: " << endl;
  printStack(headStack);
  cout << "queue: " << endl;
  printQueue(headQueue);
}

void printQueue(Node* head){
  if(head!=nullptr){
    for(int a = 0; a < head->digits; a++){
      cout << head->charn[a];
    }
    cout << endl;
    printQueue(head->next);
  }
}

void printStack(Node* head){
  if(head!=nullptr){
    cout << head->charn[0] << endl;
    printStack(head->next);
  }
}

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

void enqueue(Node* &tail, Node* n){
  Node* temp = tail;
  tail = n;
  temp->next = tail;
  tail->next = nullptr;
}

Node* dequeue(Node* &head){
  Node* temp = head;
  head = temp->next;
  temp->next = nullptr;
  return temp;
}

void push(Node* &head, Node* n){
  Node* temp = head;
  n->next = temp;
  head = n;
}

Node* pop(Node* &head){
  Node* temp = head;
  head = temp->next;
  temp->next = nullptr;
  return temp;
}

Node* peek(Node* head){
  return head;
}
