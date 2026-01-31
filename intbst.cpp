// intbst.cpp
// Implements class IntBST
// Dan Iacob, 1/30/26

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(nullptr) {	
}

// destructor deletes all nodes
IntBST::~IntBST() {
	clear(root);
	root = nullptr;
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
	if(!n){
		return;
	}
	clear(n->left);
	clear(n->right);
	delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
	if(root){
		return insert(value, root);
	} else{
		root = new Node(value);
		return true;
	}
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
	if(!n) {
		return false;
	}
	if(n->info == value) {
		return false;
	}
	if(value < n->info) {
		if(n->left) {
			return insert(value, n->left);
		} else {
        	        n->left = new Node(value);
                	n->left->parent = n;
			return true;
        	}
	} else {
                if(n->right) {
			return insert(value, n->right);
		} else {
        	        n->right = new Node(value);
                	n->right->parent = n;
			return true;
        	}
	}
}

// print tree data pre-order
void IntBST::printPreOrder() const {
	printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
	if(!n) {
                return;
        }
        cout << n->info << " ";
        printPreOrder(n->left);
	printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
	printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
	if(!n){
		return;
	}
	printInOrder(n->left);
	cout << n->info << " ";
	printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
	printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
	if(!n){
		return;
	}
	printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
	return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
	if(!n) {
		return 0;
	}
	return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
	return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
	if(!n) {
                return 0;
        }
        return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
	if(!n){
                return nullptr;
        }
	if(n->info == value) {
		return n;
	} else if(value < n->info) {
		return getNodeFor(value, n->left);
	} else {
		return getNodeFor(value, n->right);
	}
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
	return getNodeFor(value, root) != nullptr;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
	Node* n = getNodeFor(value, root);
	if (!n){
		return nullptr;
	}
	if (n->left) {
        	n = n->left;
        	while (n->right){
			n = n->right;
		}
        	return n;
	}
	Node* par = n->parent;
	while (par && n == par->left) {
	        n = par;
	        par = par->parent;
	}
	return par;
}
// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
	Node* pred = getPredecessorNode(value);
	if(pred) {
		return pred->info;
	} else {
		return 0;
	}
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
	Node* n = getNodeFor(value, root);
        if (!n){
                return nullptr;
        }
        if (n->right){
                n = n->right;
                while (n->left){
                        n = n->left;
                }
                return n;
        }
        Node* par = n->parent;
        while (par && n == par->right) {
                n = par;
                par = par->parent;
        }
        return par;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
	Node* succ = getSuccessorNode(value);
	if(succ) {
                return succ->info;
        } else {
                return 0;
        }
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
	Node* a = getNodeFor(value, root);
	if(!a){
		return false;
	}
	if(a->left == nullptr){
		replace(a, a->right);
		delete a;
		return true;
	}

	if(a->right == nullptr){
		replace(a, a->left);
		delete a;
		return true;
	}

	Node* temp = a->right;
	while(temp && temp->left){
		temp = temp->left;
	}
	Node* b = temp;

	if(b->parent != a){
		replace(b, b->right);
		b->right = a->right;
		b->right->parent = b;
	}

	replace(a, b);
	b->left = a->left;
	b->left->parent = b;

	delete a;
	return true;	
}

void IntBST::replace(Node* c, Node* d) {
	if(c->parent == nullptr){
		root = d;
	}else if (c == c->parent->left){
		c->parent->left = d;
	}else{
		c->parent->right = d;
	}
	if(d != nullptr){
		d->parent = c->parent;
	}
}
