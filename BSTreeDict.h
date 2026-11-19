
#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {

private:

    BSTree<TableEntry<V>>* tree;

public:

    // Constructor
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    // Destructor
    ~BSTreeDict() {
        delete tree;
    }

    // Devuelve el numero de entradas
    int entries() override {
        return tree->size();
    }

    // Inserta una pareja clave-valor
    void insert(std::string key, V value) override {

        TableEntry<V> entry(key, value);

        try {
            tree->search(entry);
            throw std::runtime_error(
                "Key '" + key + "' already exists!"
            );
        }
        catch (const std::runtime_error& e) {

            if (std::string(e.what()) ==
                "Key '" + key + "' already exists!") {
                throw;
            }

            tree->insert(entry);
        }
    }

    // Busca el valor asociado a una clave
    V search(std::string key) override {

        try {
            return tree->search(TableEntry<V>(key)).value;
        }
        catch (const std::runtime_error&) {
            throw std::runtime_error(
                "Key '" + key + "' not found!"
            );
        }
    }

    // Elimina una pareja clave-valor
    V remove(std::string key) override {

        V value = search(key);

        tree->remove(TableEntry<V>(key));

        return value;
    }

    // Operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Operador de salida
    friend std::ostream& operator<<(
        std::ostream& out,
        const BSTreeDict<V>& bs
    ) {
        out << *bs.tree;
        return out;
    }

};

#endif

