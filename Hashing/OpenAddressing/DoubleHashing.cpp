#include <iostream>
using namespace std;

class HashTable {
    static const int SIZE = 10;      // table size
    static const int EMPTY = -1;     // empty slot
    static const int DELETED = -2;   // deleted slot

    int table[SIZE];
    int count;

public:
    HashTable() {
        count = 0;
        for (int i = 0; i < SIZE; i++)
            table[i] = EMPTY;
    }

    // Primary hash function
    int hash1(int key) {
        return key % SIZE;
    }

    // Secondary hash function (non-zero, coprime with SIZE)
    int hash2(int key) {
        return 7 - (key % 7);
    }

    // Insert using Double Hashing
    void insert(int key) {
        if (count == SIZE) {
            cout << "Hash Table Full\n";
            return;
        }

        for (int i = 0; i < SIZE; i++) {
            int index = (hash1(key) + i * hash2(key)) % SIZE;

            if (table[index] == EMPTY || table[index] == DELETED) {
                table[index] = key;
                count++;
                cout << "Inserted " << key << " at index " << index << endl;
                return;
            }
        }
    }

    // Search key
    bool search(int key) {
        for (int i = 0; i < SIZE; i++) {
            int index = (hash1(key) + i * hash2(key)) % SIZE;

            if (table[index] == EMPTY)
                return false;

            if (table[index] == key)
                return true;
        }
        return false;
    }

    // Delete key
    void remove(int key) {
        for (int i = 0; i < SIZE; i++) {
            int index = (hash1(key) + i * hash2(key)) % SIZE;

            if (table[index] == EMPTY) {
                cout << "Key not found\n";
                return;
            }

            if (table[index] == key) {
                table[index] = DELETED;
                count--;
                cout << "Deleted " << key << endl;
                return;
            }
        }
        cout << "Key not found\n";
    }

    // Display table
    void display() {
        cout << "\nHash Table:\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << " : ";
            if (table[i] == EMPTY)
                cout << "-";
            else if (table[i] == DELETED)
                cout << "D";
            else
                cout << table[i];
            cout << endl;
        }
    }

    // Load factor
    double loadFactor() {
        return (double)count / SIZE;
    }
};

int main() {
    HashTable ht;

    ht.insert(23);
    ht.insert(43);
    ht.insert(13);
    ht.insert(27);
    ht.insert(33);

    ht.display();

    cout << "\nSearch 27: " << (ht.search(27) ? "Found" : "Not Found") << endl;
    cout << "Search 99: " << (ht.search(99) ? "Found" : "Not Found") << endl;

    ht.remove(27);
    ht.display();

    cout << "\nLoad Factor: " << ht.loadFactor() << endl;

    return 0;
}
