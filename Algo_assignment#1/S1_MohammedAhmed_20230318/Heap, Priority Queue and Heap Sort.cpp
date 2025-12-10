#include "bits/stdc++.h"
using namespace std;

// Heap
class MaxHeap
{
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int i)
    {
        while (i > 0 && heap[parent(i)] < heap[i])
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i)
    {
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < heap.size() && heap[left] > heap[largest])
            largest = left;

        if (right < heap.size() && heap[right] > heap[largest])
            largest = right;

        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insert(int value)
    {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int ExtractMin()
    {
        if (heap.empty())
        {
            throw runtime_error("Heap is empty!");
            return -1;
        }
        int level = heap.size() / 2;
        int left_subtree_start = level - 1;
        int min_val = heap[left_subtree_start];
        int index = 0;
        for (int i = left_subtree_start; i < heap.size(); i++)
        {
            if (heap[i] < min_val)
                min_val = heap[i];
            index = i;
        }
        heap[index] = heap.back();
        heap.pop_back();
        return min_val;
    }

    bool isEmpty()
    {
        return heap.empty();
    }

    int size()
    {
        return heap.size();
    }

    void display()
    {
        if (heap.empty())
        {
            cout << "Heap is empty!" << endl;
            return;
        }

        for (int val : heap)
            cout << val << " ";
        cout << endl;
    }

    int getLevels(int n)
    {
        if (n == 0)
            return 0;
        return floor(log2(n)) + 1;
    }

    void displayTree()
    {
        if (heap.empty())
        {
            cout << "Heap is empty!" << endl;
            return;
        }

        int n = heap.size();
        int totalLevels = 1 + log2(n);

        int index = 0;

        for (int level = 0; level < totalLevels; level++)
        {
            int nodesInLevel = 1 << level;
            int spaces = (1 << (totalLevels - level));

            for (int s = 0; s < spaces; s++)
                cout << " ";

            for (int j = 0; j < nodesInLevel && index < n; j++, index++)
            {
                cout << heap[index];

                for (int s = 0; s < (1 << (totalLevels - level + 1)); s++)
                    cout << " ";
            }
            cout << "\n\n";
        }
    }

    int ExtractMax()
    {
        if (heap.empty())
            throw runtime_error("Heap is empty!");

        int maxValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);

        return maxValue;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////

// Priority Queue
class PriorityQueue
{
private:
    MaxHeap heap;
    unordered_map<int, queue<int>> Values_Map;

public:
    void insert(int value, int priority)
    {
        heap.insert(priority);
        Values_Map[priority].push(value);
    }

    pair<int, int> extractHighestPriority()
    {
        if (heap.isEmpty())
            cout << "Queue is empty!";

        int highestPriority = heap.ExtractMax();
        int value = Values_Map[highestPriority].front();
        Values_Map[highestPriority].pop();

        if (Values_Map[highestPriority].empty())
            Values_Map.erase(highestPriority);

        return {value, highestPriority};
    }

    bool isEmpty()
    {
        return heap.isEmpty();
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////

// Heap Sort

void heapSort(vector<int> &arr)
{
    MaxHeap h;

    for (int val : arr)
    {
        h.insert(val);
    }

    for (int i = (int)arr.size() - 1; i >= 0; --i)
    {
        arr[i] = h.ExtractMax();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    // Test MaxHeap structure and operations
    {
        cout << "=== TESTING MAX HEAP ===" << endl;
        MaxHeap maxHeap;

        cout << "\nInserting elements: 50, 30, 70, 10, 60, 90, 20" << endl;
        maxHeap.insert(50);
        maxHeap.insert(30);
        maxHeap.insert(70);
        maxHeap.insert(10);
        maxHeap.insert(60);
        maxHeap.insert(90);
        maxHeap.insert(20);

        cout << "Heap elements: ";
        maxHeap.display();
        cout << "Heap Structure after insertions:" << endl;
        maxHeap.displayTree();

        //  Extract Max
        cout << "\nExtracting maximum element:" << endl;
        try
        {
            int maxVal = maxHeap.ExtractMax();
            cout << "Extracted max: " << maxVal << endl;
            maxHeap.display();

            cout << "Heap after ectractMax:" << endl;
            maxHeap.displayTree();
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }

        //  Extract Min
        cout << "\nExtracting minimum element:" << endl;
        try
        {
            int minVal = maxHeap.ExtractMin();
            cout << "Extracted min: " << minVal << endl;
            maxHeap.display();

            cout << "Heap after ectractMin:" << endl;
            maxHeap.displayTree();
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }

        cout << "\n"
             << string(50, '=') << endl;
        cout << "=== TESTING PRIORITY QUEUE ===" << endl;
    }
    //=======================================================
    // Test Priority Queue operations
    {
        PriorityQueue pq;

        cout << "\n6. Inserting tasks with priorities:" << endl;
        // first value is task, second is priority
        pq.insert(101, 3);
        pq.insert(102, 5);
        pq.insert(103, 1);
        pq.insert(104, 5);
        pq.insert(105, 7);
        pq.insert(106, 2);

        cout << "Inserted: (101,P3), (102,P5), (103,P1), (104,P5), (105,P7), (106,P2)" << endl;

        cout << "\nExtracting by highest priority:" << endl;
        while (!pq.isEmpty())
        {
            auto [value, priority] = pq.extractHighestPriority();
            cout << "Task: " << value << ", Priority: " << priority << endl;
        }

        cout << "\n"
             << string(50, '=') << endl;
        cout << "=== TESTING HEAP SORT ===" << endl;
    }
    //=======================================================
    // Test 8: Heap Sort
    {
        vector<int> arr = {10, 3, 5, 30, 2, 8, 15};

        cout << "Original array:\n";
        for (int x : arr)
            cout << x << " ";
        cout << "\n";

        heapSort(arr);

        cout << "\nSorted array (descending):\n";
        for (int x : arr)
            cout << x << " ";
        cout << "\n";
    }
    cout << "\n=== ALL TESTS COMPLETED ===" << endl;

    return 0;
}