/*

Alumno: Juan Pablo Chávez Leal
Matrícula: A01705408

*/
#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <iostream>
#include <queue>
#include <algorithm>

//Creación de plantilla y clase
template <class T> class BST;
template <class T>
class Node {
private:
	T value;
	Node *left, *right;

	Node<T>* succesor();

public:
	Node(T);
	Node(T, Node<T>*, Node<T>*);

	void add(T);
	void remove(T);
	bool find(T);

	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	void postorder(std::stringstream&) const;
	void levelorder(std::stringstream&) const;
	void ancestors(std::stringstream&,T) const;

	friend class BST<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *izq, Node<T> *der)
	: value(val), left(izq), right(der) {}

template <class T>
void Node<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			left->add(val);
		} 
		else {
			left = new Node<T>(val);
		}
	} 
	else {
		if (right != 0) {
			right->add(val);
		} 
		else {
			right = new Node<T>(val);
		}
	}
}

template <class T>
void Node<T>::ancestors(std::stringstream &aux, T val) const {
    if (value != val) {
        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << value;

        if (val < value && left != nullptr) {
            left -> ancestors(aux, val);
        }
        if (val > value && right != nullptr) {
            right -> ancestors(aux, val);
        }
    }
}

template <class T>
bool Node<T>::find(T val) {
	if (val == value) {
		return true;
	} 
	else if (val < value) {
		return (left != 0 && left -> find(val));
	} 
	else if (val > value) {
		return (right != 0 && right -> find(val));
	}
	return -1;
}

template <class T>
void Node<T>::remove(T val) {
	Node<T> * succ, *old;

	if (val < value) {
		if (left != 0) {
			if (left->value == val) {
				old = left;
				succ = left->succesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				left = succ;
				delete old;
			} else {
				left->remove(val);
			}
		}
	} 
	else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				succ = right->succesor();
				if (succ != 0) {
					succ -> left = old -> left;
					succ -> right = old -> right;
				}
				right = succ;
				delete old;
			} 
			else {
				right -> remove(val);
			}
		}
	}
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		aux << " ";
		right -> inorder(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left -> preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right -> preorder(aux);
	}
}

template <class T>
void Node<T>::postorder(std::stringstream &aux) const {
    if (left != 0) {
        left -> postorder(aux);
        aux << " ";
    }
    if (right != 0) {
        right->postorder(aux);
        aux << " ";
    }
    aux << value;
}

template <class T>
void Node<T>::levelorder(std::stringstream &aux) const {
    std::queue<const Node<T>*> cola;
    cola.push(this);

    while (!cola.empty()) {
        const Node<T>* current = cola.front();
        cola.pop();
        aux << current -> value;

        if (current -> left != nullptr) {
            cola.push(current ->left);
        }
        if (current->right != nullptr) {
            cola.push(current-> right);
        }
		if(!cola.empty()){
			aux<< " ";
		}
    }
}

template <class T>
class BST {
private:
	Node<T> *root;
	int findlevel(const Node<T>* node,const T& val,int) const;

public:
	BST();
	bool empty() const;
	void add(T);
	bool find(T) const;
	std::string inorder() const;
	std::string preorder() const;
	std::string postorder() const;
	std::string visit() const;
	int height() const;
	int height_calc(const Node<T>* node) const;
	int whatlevelamI(const T& val) const;
	std::string ancestors(T) const;
	bool ancestors_aux(const Node<T>* node,const T& val, std::stringstream& aux) const;

};
template<class T>
int BST<T>::whatlevelamI(const T& val)const{
	return findlevel(root,val,1);
}

template <class T>
BST<T>::BST() : root(0) {}

template<class T>
int BST<T>::findlevel(const Node<T>* node, const T& target, int level) const {
	if(node == 0){
		return -1;
	}

    if (target == node->value) {
        return level; 
    } else if (target < node->value) {
        int leftLevel = findlevel(node->left, target, level + 1);
        if (leftLevel != -1) {
            return leftLevel;
        }
    } else {
        int rightLevel = findlevel(node->right, target, level + 1);
        if (rightLevel != -1) {
            return rightLevel;
        }
    }

    return -1;
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template <class T>
bool BST<T>::find(T val) const {
	if (root != 0) {
		return root -> find(val);
	} else {
		return false;
	}
}

template<class T>
void BST<T>::add(T val) {
	if (root != 0) {
		if (!root -> find(val)) {
			root -> add(val);
		}
	} 
	else {
		root = new Node<T>(val);
	}
}

template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::postorder() const{
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

template<class T>
std::string BST<T>::visit() const{
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	aux<<"\n";
	aux << "[";
	if (!empty()) {
		root -> inorder(aux);
	}
	aux << "]";
	aux <<"\n";
	aux << "[";
	if (!empty()) {
		root -> postorder(aux);
	}
	aux << "]";
	aux<<"\n";
		aux << "[";
	if (!empty()) {
		root -> levelorder(aux);
	}
	aux << "]";


	return aux.str();
}

template <class T>
int BST<T>::height() const {
    return height_calc(root);
}

template <class T>
int BST<T>::height_calc(const Node<T>* node) const {
    if (node == 0) {
        return 0;
    }
    int leftHeight = height_calc(node->left);
    int rightHeight = height_calc(node->right);
    return std::max(leftHeight, rightHeight) + 1;
}

template <class T>
bool BST<T>::ancestors_aux(const Node<T>* node, const T& target, std::stringstream& result) const {
    if (node == 0) {
        return false;
    }

    if (node->value == target || ancestors_aux(node->left, target, result) || ancestors_aux(node -> right, target, result)) {
        if(node -> value != target){
        	result << node -> value << " ";
		}
        return true;
    }

    return false;
}

template <class T>
std::string BST<T>::ancestors(T val) const {
    std::stringstream aux;
	if (!find(val)) {
		return "[]";
	}
    aux << "[";
    root->ancestors(aux, val);
    aux << "]";
    return aux.str();
}




#endif