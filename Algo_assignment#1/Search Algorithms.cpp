#include "bits/stdc++.h"
using namespace std;

// Sequential Search
template <typename T>
int sequential_search_iterative(const vector<T> &arr, const T &target)
{
    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (arr[i] == target)
            return static_cast<int>(i);
    }
    return -1; // not found
}

/////////////////////////////////////////////////////////////////////////////////

// Recursive Sequential Search
int recursive_sequential_search(const int arr[], const int key, const int size, int index = 0)
{
    if (index >= size)
    {
        return -1;
    }
    if (arr[index] == key)
    {
        return index;
    }
    return recursive_sequential_search(arr, key, size, ++index);
}

/////////////////////////////////////////////////////////////////////////////////

// Binary Search Iterative
int binarySearch_Iterative(int arr[], int n, int key)
{
    int left = 0, right = n - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

/////////////////////////////////////////////////////////////////////////////////

// Recursive Binary Search
int binarySearch_Recursive(int array[], int l, int h, int x)
{
    if (l > h)
        return -1;

    int mid = (l + h) / 2;

    if (array[mid] == x)
        return mid;
    else if (array[mid] > x)
        return binarySearch_Recursive(array, l, mid - 1, x);
    else
        return binarySearch_Recursive(array, mid + 1, h, x);
}

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    while (true)
    {
        int choice, n, key;
        cout << "\n=============================================\n";
        cout << " Search Algorithms Menu\n";
        cout << "=============================================\n";
        cout << "1. Sequential Search (Iterative)\n";
        cout << "2. Sequential Search (Recursive)\n";
        cout << "3. Binary Search (Iterative)\n";
        cout << "4. Binary Search (Recursive)\n";
        cout << "5. Exit\n";
        cout << "---------------------------------------------\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        if (choice == 5)
        {
            cout << "Exiting program. Goodbye!\n";
            break;
        }

        cout << "Enter number of elements: ";
        cin >> n;

        if (n <= 0)
        {
            cout << "Invalid tree size! Please enter a positive number greater than 0." << endl;
            continue;
        }

        vector<int> vec(n);
        cout << "Enter " << n << " elements :\n";
        for (int i = 0; i < n; ++i)
            cin >> vec[i];

        cout << "Enter the key to search for: ";
        cin >> key;

        int result = -1;

        switch (choice)
        {
        case 1:
            result = sequential_search_iterative(vec, key);
            cout << "Result (Sequential Iterative): ";
            break;

        case 2:
            result = recursive_sequential_search(vec.data(), key, n);
            cout << "Result (Sequential Recursive): ";
            break;

        case 3:
            sort(vec.begin(), vec.end());
            cout << "\nSorted array for Binary Search -> ";
            for (const auto &val : vec)
                cout << val << " ";
            cout << endl;
            result = binarySearch_Iterative(vec.data(), n, key);
            cout << "Result (Binary Iterative): ";
            break;

        case 4:
            sort(vec.begin(), vec.end());
            cout << "\nSorted array for Recursive Binary Search -> ";
            for (const auto &val : vec)
                cout << val << " ";
            cout << endl;
            result = binarySearch_Recursive(vec.data(), 0, n - 1, key);
            cout << "Result (Binary Recursive): ";
            break;

        default:
            cout << "Invalid choice!\n";
            continue;
        }

        if (result != -1)
            cout << "Key found at index " << result << endl;
        else
            cout << "Key not found.\n";
    }
}