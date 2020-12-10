#include <cstring>
#pragma once

using namespace std;
class BinaryTreeNode{
 public:
  BinaryTreeNode(char*, int);
  void setLeft(BinaryTreeNode*);
  void setRight(BinaryTreeNode*);
  void setNext(BinaryTreeNode*);
  BinaryTreeNode* getLeft();
  BinaryTreeNode* getRight();
  BinaryTreeNode* getNext();
  char* getChar();
  int getDigits();
 private:
  BinaryTreeNode* left;
  BinaryTreeNode* right;
  BinaryTreeNode* next;
  char* charn;
  int digits;
};
