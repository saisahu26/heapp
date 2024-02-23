// This program is an implementation for a basic heap data structure
// Author: Nikaansh S.
// Last Edited: 2/14/24
// Idea for heap up and heap down taken from geeks for geeks

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class maxheap {
private:
    int heap[101];
    int size;
    const int MAXSIZE = 101;

public:
    // Function to move an element up in the heap
    void heapup(int index) {
        if (index == 1) {
            return;
        }
        int parent = floor(index / 2);
        if (heap[index] > heap[parent]) {
            swap(heap[index], heap[parent]);
            heapup(parent);
        }
    }

    // Function to move an element down in the heap
    void heapdown(int index) {
        int leftchild = 2 * index;
        int rightchild = 2 * index + 1;

        if (leftchild > size) {
            return;
        }

        int largest = index;
        if (heap[leftchild] > heap[largest]) {
            largest = leftchild;
        }
        if (rightchild <= size && heap[rightchild] > heap[largest]) {
            largest = rightchild;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapdown(largest);
        }
    }

    // Constructor to initialize the heap
    maxheap() : size(0) {}

    // Function to add an item to the heap
    void additem(int value) {
        if (size >= MAXSIZE) {
            cout << "Heap is full" << endl;
            return;
        }
        size++;
        heap[size] = value;
        heapup(size);
    }

    // Function to remove the root element of the heap
    void removeroot() {
        if (size == 0) {
            cout << "Heap is empty" << endl;
            return;
        }
        heap[1] = heap[size];
        size--;
        heapdown(1);
    }

    // Function to remove all elements from the heap
    void removeall() {
        while (size != 0) {
            removeroot();
        }
    }

    // Function to print all elements of the heap in a visual format
    void printall(int current = 1, int depth = 0) {
        if (current > size) {
            return;
        }
        printall(2 * current + 1, depth + 1); // Right child
        for (int i = 0; i < depth; i++) {
            cout << "\t";
        }
        cout << heap[current] << endl; // Current node
        printall(2 * current, depth + 1); // Left child
    }

    // Function to get the size of the heap
    int getsize() {
        return size;
    }

    // Function to get the value of a specific element in the heap
    int getheap(int index) {
        return heap[index];
    }

    // Function to read inputs from a file and add them to the heap
    void addFromFile(string filename) {
        ifstream file(filename); // Open the file
        if (!file) {
            cout << "Could not open file" << endl; // Print error message if file cannot be opened
            return;
        }
        int value;
        while (file >> value && size < MAXSIZE) { // Read numbers from the file until the heap is full
            additem(value);
        }
        file.close(); // Close the file
    }
};

int main() {
    maxheap heap = maxheap(); // Create an instance of the maxheap class
    string input;

    while (true) {
        cout << "Enter add, file, delete, clear, print, quit" << endl;
        cin >> input;
        cout << endl;

        if (input == "add") {
            int newitem;
            cout << "What do you want to add?" << endl;
            cin >> newitem;
            cout << endl;
            heap.additem(newitem);
        }
        else if (input == "file") {
            string filename;
            cout << "Enter filename: ";
            cin >> filename;
            heap.addFromFile(filename); // Add elements from the file to the heap
        }
        else if (input == "delete") {
            heap.removeroot();
        }
        else if (input == "clear") {
            heap.removeall();
        }
        else if (input == "print") {
            heap.printall();
            cout << endl;
        }
        else if (input == "quit") {
            heap.removeall();
            break;
        }
    }

    return 0;
}
