
#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {

private:

    int nelem;
    BSNode<T>* root;

    // Busqueda recursiva
    BSNode<T>* search(BSNode<T>* n, T e) const {

        if (n == nullptr) {
            throw std::runtime_error("Element not found!");
        }

        if (e == n->elem) {
            return n;
        }

        if (e < n->elem) {
            return search(n->left, e);
        }

        return search(n->right, e);
    }

    // Insercion recursiva
    BSNode<T>* insert(BSNode<T>* n, T e) {

        if (n == nullptr) {
            return new BSNode<T>(e);
        }

        if (e == n->elem) {
            throw std::runtime_error("Element already exists!");
        }

        if (e < n->elem) {
            n->left = insert(n->left, e);
        } else {
            n->right = insert(n->right, e);
        }

        return n;
    }

    // Recorrido inorden
    void print_inorder(std::ostream& out, BSNode<T>* n) const {

        if (n != nullptr) {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }

    // Devuelve el elemento maximo
    T max(BSNode<T>* n) const {

        if (n->right == nullptr) {
            return n->elem;
        }

        return max(n->right);
    }

    // Elimina el elemento maximo
    BSNode<T>* remove_max(BSNode<T>* n) {

        if (n->right == nullptr) {
            BSNode<T>* aux = n->left;
            delete n;
            return aux;
        }

        n->right = remove_max(n->right);

        return n;
    }

    // Eliminacion recursiva
    BSNode<T>* remove(BSNode<T>* n, T e) {

        if (n == nullptr) {
            throw std::runtime_error("Element not found!");
        }

        if (e < n->elem) {
            n->left = remove(n->left, e);
        }
        else if (e > n->elem) {
            n->right = remove(n->right, e);
        }
        else {

            // Caso 1: no tiene hijo izquierdo
            if (n->left == nullptr) {
                BSNode<T>* aux = n->right;
                delete n;
                return aux;
            }

            // Caso 2: no tiene hijo derecho
            if (n->right == nullptr) {
                BSNode<T>* aux = n->left;
                delete n;
                return aux;
            }

            // Caso 3: tiene dos hijos
            n->elem = max(n->left);
            n->left = remove_max(n->left);
        }

        return n;
    }

    // Liberacion recursiva de memoria
    void delete_cascade(BSNode<T>* n) {

        if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:

    // Constructor
    BSTree() {
        nelem = 0;
        root = nullptr;
    }

    // Devuelve el numero de elementos
    int size() const {
        return nelem;
    }

    // Busqueda publica
    T search(T e) const {
        return search(root, e)->elem;
    }

    // Operador []
    T operator[](T e) const {
        return search(e);
    }

    // Insercion publica
    void insert(T e) {
        root = insert(root, e);
        nelem++;
    }

    // Operador <<
    friend std::ostream& operator<<(
        std::ostream& out,
        const BSTree<T>& bst
    ) {
        bst.print_inorder(out, bst.root);
        return out;
    }

    // Eliminacion publica
    void remove(T e) {
        root = remove(root, e);
        nelem--;
    }

    // Destructor
    ~BSTree() {
        delete_cascade(root);
    }

};

#endif

