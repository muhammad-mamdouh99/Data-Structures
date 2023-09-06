#include <iostream>
#include <cassert>

using namespace std;

class Vector {
private:
    int *arr = nullptr;
    int size = 0;
public:
    Vector(int size) :
            size(size) {
        if (size < 0)
            size = 1;
        arr = new int[size]{};
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
        // Add element to the end of the vector
        // 1) Create a new array of bigger size
        int *arr2 = new int[size + 1]{};
        // 2) Copy old data
        for (int i = 0; i < size; ++i)
            arr2[i] = arr[i];
        // 3) add the new element and increase size
        arr2[size++] = val;
        // 4) Change the pointers
        swap(arr, arr2);
        // 5) remove the useless data
        delete[] arr2;
    }
};

int main() {
    int n = 4;
    Vector v(n);
    for (int i = 0; i < n; ++i)
        v.set(i, i);

    v.push_back(15);
    v.push_back(17);
    v.push_back(19);
    v.print();  // 0 1 2 3 15 17 19
    return 0;
}

