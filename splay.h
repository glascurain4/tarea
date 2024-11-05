/*
 *      Author: Gabriel Lascurain
*/

#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <sstream>

template <class T>
class SplayTree;

template <class T>
class Node {
private:
    T value;
    Node *left, *right;

    Node* splay(Node* root, T val);
    Node* rightRotate(Node* x);
    Node* leftRotate(Node* x);
    Node* add(Node* root, T val);
    Node* remove(Node* root, T val);
    bool find(Node* root, T val);

    // Recorridos de árbol
    void inorder(std::ostringstream &out);
    void preorder(std::ostringstream &out);

public:
    Node(T val) : value(val), left(0), right(0) {}
    friend class SplayTree<T>;
};

// Función para recorrido inorder
template <class T>
void Node<T>::inorder(std::ostringstream &out) {
    if (left) left->inorder(out);
    out << value << " ";
    if (right) right->inorder(out);
}

// Función para recorrido preorder
template <class T>
void Node<T>::preorder(std::ostringstream &out) {
    out << value << " ";
    if (left) left->preorder(out);
    if (right) right->preorder(out);
}

template <class T>
Node<T>* Node<T>::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

template <class T>
Node<T>* Node<T>::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

template <class T>
Node<T>* Node<T>::splay(Node* root, T val) {
    if (root == 0 || root->value == val) return root;

    if (val < root->value) {
        if (root->left == 0) return root;
        if (val < root->left->value) {
            root->left->left = splay(root->left->left, val);
            root = rightRotate(root);
        } else if (val > root->left->value) {
            root->left->right = splay(root->left->right, val);
            if (root->left->right != 0) root->left = leftRotate(root->left);
        }
        return root->left == 0 ? root : rightRotate(root);
    } else {
        if (root->right == 0) return root;
        if (val > root->right->value) {
            root->right->right = splay(root->right->right, val);
            root = leftRotate(root);
        } else if (val < root->right->value) {
            root->right->left = splay(root->right->left, val);
            if (root->right->left != 0) root->right = rightRotate(root->right);
        }
        return root->right == 0 ? root : leftRotate(root);
    }
}

template <class T>
Node<T>* Node<T>::add(Node* root, T val) {
    if (root == 0) return new Node(val);
    root = splay(root, val);
    if (root->value == val) return root;

    Node* newNode = new Node(val);
    if (val < root->value) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = 0;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = 0;
    }
    return newNode;
}

template <class T>
Node<T>* Node<T>::remove(Node* root, T val) {
    if (root == 0) return 0;
    root = splay(root, val);
    if (root->value != val) return root;

    Node* temp;
    if (root->left == 0) {
        temp = root->right;
    } else {
        temp = splay(root->left, val);
        temp->right = root->right;
    }
    delete root;
    return temp;
}

template <class T>
bool Node<T>::find(Node* root, T val) {
    if (root == 0) return false;
    root = splay(root, val);
    return root->value == val;
}

template <class T>
class SplayTree {
private:
    Node<T> *root;
    int count;

    // Helper para formatear la salida sin espacio al final
    std::string formatOutput(std::ostringstream &out) {
        std::string result = out.str();
        if (!result.empty() && result.back() == ' ') {
            result.pop_back();  // Elimina el espacio final
        }
        return result;
    }

public:
    SplayTree() : root(0), count(0) {}

    void add(T val) {
        root = root ? root->add(root, val) : new Node<T>(val);
        count++;
    }

    void remove(T val) {
        if (root && root->find(root, val)) {
            root = root->remove(root, val);
            count--;
        }
    }

    bool find(T val) {
        if (root) {
            root = root->splay(root, val);
            return root->value == val;
        }
        return false;
    }

    int size() {
        return count;
    }

    std::string inorder() {
        std::ostringstream out;
        if (root) root->inorder(out);
        return "[" + formatOutput(out) + "]";
    }

    std::string preorder() {
        std::ostringstream out;
        if (root) root->preorder(out);
        return "[" + formatOutput(out) + "]";
    }
};

/*
template <class T> class Splay;
class Node {
private:
	T value;
	Node *left, *right;
	int level, balance;
	Node<T>* predecesor();
public:
Node(T);
Node(T, Node<T>*, Node<T>*, int, int);
};

class AVL {
private:
Node<T> *root;

public:
AVL();
void add(T);
void remove(T);
bool find(T);
int size();
};
*/

#endif