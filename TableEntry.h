
#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>
using namespace std;
template <typename V>
class TableEntry {
public:

    string key;
    V value;

    // Constructor sin parametros
    TableEntry() : key(""), value() {}

    // Constructor solo con clave
    TableEntry(string key) : key(key), value() {}

    // Constructor con clave y valor
    TableEntry(string key, V value) : key(key), value(value) {}

    // Comparacion por clave
    friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key == te2.key;
    }

    // Desigualdad por clave
    friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key != te2.key;
    }

    // Impresion de la entrada
    friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te) {
        out << "('" << te.key << "' => " << te.value << ")";
        return out;
    }
};

#endif

