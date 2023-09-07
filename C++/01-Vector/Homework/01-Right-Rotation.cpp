#include <iostream>
#include <cassert>

using namespace std;

class Vector {
private:
    int *arr = nullptr;
    int size = 0;           // user size
    int capacity = 0;       // actual size

    void expand_capacity() {
        // Add element to the end of the vector
        // 1) Create a new array of double capacity
        capacity *= 2;
        cout << "Expand capacity to " << capacity << "\n";
        int *arr2 = new int[capacity]{};
        // 2) Copy old data
        for (int i = 0; i < size; ++i)
            arr2[i] = arr[i];
        // 3) Change the pointers
        swap(arr, arr2);
        // 4) remove the useless data
        delete[] arr2;
    }

public:
    Vector(int size) :
            size(size) {
        if (size < 0)
            size = 1;
        capacity = size * 2;
        arr = new int[capacity]{};
    }

    ~Vector() {
        delete[] arr;
        arr = nullptr;
    }

    // Operations:
    int get(int idx) {
        assert(0 <= idx && idx < size);
        return arr[idx];
    }

    void set(int idx, int val) {
        assert(0 <= idx && idx < size);
        arr[idx] = val;
    }

    void print() {
        for (int i = 0; i < size; ++i)
            cout << arr[i] << " ";
        cout << "\n";
    }

    int find(int val) {
        for (int i = 0; i < size; ++i)
            if (arr[i] == val)
                return i;
        return -1;  // -1 for NOT found
    }

    int get_front() {
        return arr[0];
    }

    int get_back() {
        return arr[size - 1];
    }

    void push_back(int val) {
        if (size == capacity)
            expand_capacity();
        arr[size++] = val;
    }

    void insert(int idx, int val) {
        assert(0 <= idx && idx < size);
        if (size == capacity)
            expand_capacity();
        // Shift all the data to the right first
        for (int i = size - 1; i >= idx; --i)
            arr[i + 1] = arr[i];
        arr[idx] = val;
        size++;
    }

    void right_rotate() {
        // Make sure your code doesn't expand capacity or goes beyond limit
        int last_element = arr[size - 1];
        // right shift first size-1 elements
        for (int i = size - 1; i > 0; --i)
            arr[i] = arr[i - 1];
        arr[0] = last_element;
    }
};

int main() {
    int n = 5;
    Vector v(n);
    for (int i = 0; i < n; ++i)
        v.set(i, i + 1);
    v.print();
    v.right_rotate();
    v.print();
    return 0;
}


