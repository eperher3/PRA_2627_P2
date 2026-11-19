
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <ostream>
#include <stdexcept>

#include "Dict.h"
#include "TableEntry.h"
#include "../PRA_2627_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

private:

    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    // Funcion hash
    int h(std::string key) {
        int sum = 0;

        for (int i = 0; i < key.length(); i++) {
            sum += static_cast<unsigned char>(key.at(i));
        }

        return sum % max;
    }

public:

    // Constructor
    HashTable(int size) {

        if (size <= 0) {
            throw std::invalid_argument(
                "HashTable size must be positive"
            );
        }

        n = 0;
        max = size;

        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Devuelve la capacidad
    int capacity() {
        return max;
    }

    // Devuelve el numero de entradas
    int entries() override {
        return n;
    }

    // Inserta una pareja clave-valor
    void insert(std::string key, V value) override {

        int pos = h(key);

        TableEntry<V> entry(key);

        if (table[pos].search(entry) != -1) {
            throw std::runtime_error(
                "Key '" + key + "' already exists!"
            );
        }

        table[pos].prepend(TableEntry<V>(key, value));

        n++;
    }

    // Busca una clave y devuelve su valor
    V search(std::string key) override {

        int pos = h(key);

        int index = table[pos].search(
            TableEntry<V>(key)
        );

        if (index == -1) {
            throw std::runtime_error(
                "Key '" + key + "' not found!"
            );
        }

        return table[pos].get(index).value;
    }

    // Elimina una pareja clave-valor
    V remove(std::string key) override {

        int pos = h(key);

        int index = table[pos].search(
            TableEntry<V>(key)
        );

        if (index == -1) {
            throw std::runtime_error(
                "Key '" + key + "' not found!"
            );
        }

        V value = table[pos].remove(index).value;

        n--;

        return value;
    }

    // Sobrecarga del operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(
        std::ostream& out,
        const HashTable<V>& th
    ) {

        out << "HashTable [entries: " << th.n
            << ", capacity: " << th.max << "]\n";

        out << "==============\n";

        for (int i = 0; i < th.max; i++) {

            out << "\n== Cubeta " << i << " ==\n\n";

            out << "List => [\n";

            for (int j = 0; j < th.table[i].size(); j++) {

                out << "  " << th.table[i].get(j) << "\n";
            }

            out << "]\n";
        }

        out << "\n==============\n";

        return out;
    }

};

#endif

