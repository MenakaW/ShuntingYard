#include "BinaryTreeNode.h"
#include <iostream>
#include <cstring>

using namespace std;

BinaryTreeNode::BinaryTreeNode(char* charnNew, int digitsNew){
  charn = charnNew;
  digits = digitsNew;
  left = nullptr;
  right = nullptr;
  next = nullptr;
}

void BinaryTreeNode::setLeft(BinaryTreeNode* leftNew){
  left = leftNew;
}

void BinaryTreeNode::setRight(BinaryTreeNode* rightNew){
  right = rightNew;
}

void BinaryTreeNode::setNext(BinaryTreeNode* nextNew){
  next = nextNew;
}

BinaryTreeNode* BinaryTreeNode::getLeft(){
  return left;
}

BinaryTreeNode* BinaryTreeNode::getRight(){
  return right;
}

BinaryTreeNode* BinaryTreeNode::getNext(){
  return next;
}

char* BinaryTreeNode::getChar(){
  return charn;
}

int BinaryTreeNode::getDigits(){
  return digits;
}
