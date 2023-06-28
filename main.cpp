#include <iostream>
#include <string>
#include <Windows.h>
#include "multiset.h"
#include "multiset.cpp"

using namespace std;


void menu();

template<typename T>
void performSetOperations();

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int type;
    cout << "Congratulations!\nTo work with a set, you need to enter the type of elements\n\t1 = int\n\t2 = float\n\t3 = double\n\t4 = string\nEnter a number: ";
    cin >> type;
    if (type == 1) {
        performSetOperations<int>();
    }
    else if (type == 2) {
        performSetOperations<float>();
    }
    else if (type == 3) {
        performSetOperations<double>();
    }
    else if (type == 4) {
        performSetOperations<string>();
    }
    else cout << "Invalid type!" << endl;

    return 0;
}

void menu() {
    cout << "**************************************************** ************" << endl;
    cout << "Possible operations on sets:" << endl;
    cout << "1 = Including a new element in the set" << endl;
    cout << "2 = Checking whether an element belongs to a set" << endl;
    cout << "3 = Set data output" << endl;
    cout << "4 = Union of two sets" << endl;
    cout << "5 = Clear set" << endl;
    cout << "6 = End of work" << endl;
    cout << "**************************************************** ************" << endl;
    cout << "Enter the set mode: ";
}
template<typename T>
void performSetOperations() {
    int n;
    cout << "Enter the size of the set: ";
    cin >> n;
    Multiset<T> set;
    for (int i = 0; i < n; i++) {
        T value;
        cout << "Enter " << i + 1 << " element: ";
        cin >> value;
        set.insert(value);
    }

    int variant = 0;
    while (variant != 6) {
        menu();
        cin >> variant;
        if (variant == 1) {
            T value;
            cout << "Enter the element: ";
            cin >> value;
            set.insert(value);
        }
        else if (variant == 2) {
            T value;
            cout << "Enter the element: ";
            cin >> value;
            cout << "Searching for " << value << ": " << (set.search(value) ? "Found" : "Not found") << endl;
        }
        else if (variant == 3) {
            if (!set.empty()) {
                typename Multiset<T>::MultisetIterator it(set.begin());
                while (it != set.end()) {
                    cout << it->data << "; ";
                    ++it;
                }
                cout << it->data << ".";
                cout << endl;
            }
            else cout << "Set is empty" << endl;
        }
        else if (variant == 4) {
            int n2;
            cout << "To begin with, you need to create a new set with which we will combine sets" << endl;
            cout << "Enter the size of the second set: ";
            cin >> n2;
            Multiset<T> set2;
            for (int i = 0; i < n2; i++) {
                T value;
                cout << "Enter " << i + 1 << " element: ";
                cin >> value;
                set2.insert(value);
            }
            Multiset<T> unionSet = set.unionSet(set2);
            cout << "Contents of merged vertices: ";
            typename Multiset<T>::MultisetIterator it(unionSet.begin());
            while (it != unionSet.end()) {
                cout << it->data << "; ";
                ++it;
            }
            cout << it->data << ".";
            cout << endl;
            string saveToFirst;
            cout << "Would you like to save the data of the merged set to the first set?\nEnter YES or NO: "; cin >> saveToFirst;
            if (saveToFirst == "YES" || saveToFirst == "Yes" || saveToFirst == "yes" || saveToFirst == "YES" || saveToFirst == "yes" || saveToFirst == "Yes") {
                set = unionSet;
            }
            unionSet.clear();
            set2.clear();
        }
        else if (variant == 5) {
            if (!set.empty()) {
                set.clear();
                cout << "Set cleared" << endl;
            }
            else cout << "The array is already empty!" << endl;
        }
    }
    if (!set.empty()) set.clear();
}