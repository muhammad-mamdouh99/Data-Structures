#include <iostream>
#include <cassert>

using namespace std;

class Vector {
private:
    int *arr = nullptr;
    int size = 0;       // user size.
    int capacity = 0;   // actual size.

    void expand_capacity() {
        // double the actual array size.
        capacity *= 2;
        cout << "Expand capacity to " << capacity << "\n";

        int *temp = new int[capacity]{};
        for (int i = 0; i < size; ++i)
            temp[i] = arr[i];   // copy the data.

        swap(temp, arr);
        delete[] temp;
    }

public:
    Vector(int size) :
            size(size) {
        if (size < 0)
            size = 1;
        capacity = size * 2;
        // The actual size of the array will always be bigger than needed.
        arr = new int[capacity]{};
    }

    ~Vector() {
        delete[] arr;
        arr = nullptr;
    }

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
        return -1;  // -1 for NOT found.
    }

    int get_front() {
        return arr[0];
    }

    int get_back() {
        return arr[size - 1];
    }

    void push_back(int val) {
        // We can't add anymore.
        if (size == capacity)
            expand_capacity();
        arr[size++] = val;
    }

    void insert(int idx, int val) {
        assert(0 <= idx && idx < size);

        // We can't add anymore.
        if (size == capacity)
            expand_capacity();

        // shift all the data to the right first.
        for (int i = size - 1; i >= idx; --i)
            arr[i + 1] = arr[i];

        arr[idx] = val;
        ++size;
    }

    /* Homework Solution. */
    // Problem #1: Right rotation.
    void right_rotate() {
        int last = arr[size - 1];

        // right shift first size - 1 elements.
        for (int i = size - 2; i >= 0; --i)
            arr[i + 1] = arr[i];

        arr[0] = last;
    }

    // Problem #2: Left rotation.
    void left_rotate() {
        int first = arr[0];

        // left shift first size - 1 elements.
        for (int i = 1; i < size; ++i)
            arr[i - 1] = arr[i];

        arr[size - 1] = first;
    }

    // Problem #3: Right rotation with steps.
    void right_rotate(int times) {
        // get rid of all size rotations.
        times %= size;
        while (times--)
            right_rotate();
    }

    // Problem #4: Deleting a position.
    int pop(int idx) {
        assert(0 <= idx && idx < size);
        int val = arr[idx];

        // shift all the data to the left.
        for (int i = idx + 1; i < size; ++i)
            arr[i - 1] = arr[i];

        --size;
        return val;
    }

    // Problem #5: Transposition.
    int find_transposition(int val) {
        for (int i = 0; i < size; ++i) {
            if (arr[i] == val) {
                if (i == 0)
                    return 0;   // special case.

                // shift the element one time to the left.
                swap(arr[i], arr[i - 1]);
                return i - 1;   // the new position.
            }
        }
        return -1;  // -1 for NOT found.
    }

};

int main() {
    int n = 5;
    Vector v(n);
    for (int i = 0; i < n; ++i)
        v.set(i, i);

    v.print();            // 0 1 2 3 4
    v.right_rotate(5 * 1000);
    v.print();            // 0 1 2 3 4
    v.right_rotate(2);
    v.print();            // 3 4 0 1 2
    v.left_rotate();
    v.print();            // 4 0 1 2 3

    int val = v.pop(2);
    cout << val << "\n";    // 1
    v.print();            // 4 0 2 3

    cout << v.find_transposition(3) << "\n";    // 2
    v.print();            // 4 0 3 2
    return 0;
}
