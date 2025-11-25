#include "DataStructures/PriorityQueue.hpp"
#include <stdexcept>

template <typename T, typename Comparator>
PriorityQueue<T, Comparator>::PriorityQueue(Comparator comp)
    : heap(10), compare(comp)
{
}

template <typename T, typename Comparator>
int PriorityQueue<T, Comparator>::parent(int i)
{
    return (i - 1) / 2;
}

template <typename T, typename Comparator>
int PriorityQueue<T, Comparator>::leftChild(int i)
{
    return 2 * i + 1;
}

template <typename T, typename Comparator>
int PriorityQueue<T, Comparator>::rightChild(int i)
{
    return 2 * i + 2;
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::swap(int i, int j)
{
    T temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::heapifyUp(int index)
{
    while(index > 0 && compare(heap[index], heap[parent(index)]))
    {
        swap(index, parent(index));
        index = parent(index);
    }
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::heapifyDown(int index)
{
    int bestIndex = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if(left < heap.getSize() && compare(heap[left], heap[bestIndex]))
    {
        bestIndex = left;
    }
    if(right < heap.getSize() && compare(heap[right], heap[bestIndex]))
    {
        bestIndex = right;
    }

    if(bestIndex != index)
    {
        swap(index, bestIndex);
        heapifyDown(bestIndex);
    }
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::enqueue(T item)
{
    if(!item)
    {
        throw std::invalid_argument("Cannot insert null item");
    }

    heap.push(item);
    heapifyUp(heap.getSize() - 1);
}

template <typename T, typename Comparator>
T PriorityQueue<T, Comparator>::dequeue()
{
    if(heap.isEmpty())
    {
        return nullptr;
    }

    T best = heap[0];
    heap[0] = heap[heap.getSize() - 1];
    heap.pop();

    if(!heap.isEmpty())
    {
        heapifyDown(0);
    }

    return best;
}

template <typename T, typename Comparator>
T PriorityQueue<T, Comparator>::peek() const
{
    return heap.isEmpty() ? nullptr : heap[0];
}

template <typename T, typename Comparator>
bool PriorityQueue<T, Comparator>::isEmpty() const
{
    return heap.isEmpty();
}

template <typename T, typename Comparator>
int PriorityQueue<T, Comparator>::getSize() const
{
    return heap.getSize();
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::clear()
{
    heap.clear();
}
