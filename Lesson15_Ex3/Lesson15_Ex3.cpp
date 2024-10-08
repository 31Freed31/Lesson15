#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename K, typename V>
struct KeyValuePair {
    K key;
    V value;

    KeyValuePair(K k, V v) : key(k), value(v) {}
};

template <typename K, typename V>
class Registry {
private:
    vector<KeyValuePair<K, V>> data;

public:
    void add(const K& key, const V& value) {
        data.push_back(KeyValuePair<K, V>(key, value));
    }

    void remove(const K& key) {
        data.erase(remove_if(data.begin(), data.end(), [&](const KeyValuePair<K, V>& pair) {
            return pair.key == key;
            }), data.end());
    }

    void print() const {
        if (data.empty()) {
            cout << "Registry is empty!" << endl;
        }
        else {
            for (const auto& pair : data) {
                cout << "Key: " << pair.key << ", Value: " << pair.value << endl;
            }
        }
    }

    void find(const K& key) const {
        bool found = false;
        for (const auto& pair : data) {
            if (pair.key == key) {
                cout << "Key: " << pair.key << ", Value: " << pair.value << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No elements found with key: " << key << endl;
        }
    }
};

int main() {
    Registry<int, string> registry;
    string command;

    while (true) {
        cout << "Enter command (add, remove, print, find, exit): ";
        cin >> command;

        if (command == "add") {
            int key;
            string value;
            cout << "Enter key (int): ";
            cin >> key;
            cout << "Enter value (string): ";
            cin >> value;
            registry.add(key, value);
        }
        else if (command == "remove") {
            int key;
            cout << "Enter key to remove (int): ";
            cin >> key;
            registry.remove(key);
        }
        else if (command == "print") {
            registry.print();
        }
        else if (command == "find") {
            int key;
            cout << "Enter key to find (int): ";
            cin >> key;
            registry.find(key);
        }
        else if (command == "exit") {
            break;
        }
        else {
            cout << "Invalid command!" << endl;
        }
    }
    return 0;
}
