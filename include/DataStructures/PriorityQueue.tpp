#include "DataStructures/PriorityQueue.hpp"
#include <stdexcept>

template <typename T, typename Comparator>
PriorityQueue<T, Comparator>::PriorityQueue(Comparator comp)
    : capacity(10), size(0), compare(comp)
{
    heap = new T[capacity];
}

template <typename T, typename Comparator>
PriorityQueue<T, Comparator>::~PriorityQueue()
{
    delete[] heap;
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::resize()
{
    capacity *= 2;
    T *newHeap = new T[capacity];
    for(int i = 0; i < size; i++)
    {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
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

    if(left < size && compare(heap[left], heap[bestIndex]))
    {
        bestIndex = left;
    }
    if(right < size && compare(heap[right], heap[bestIndex]))
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
void PriorityQueue<T, Comparator>::insert(T item)
{
    if(!item)
    {
        throw std::invalid_argument("Cannot insert null item");
    }

    if(size == capacity)
    {
        resize();
    }

    heap[size] = item;
    heapifyUp(size);
    size++;
}

template <typename T, typename Comparator>
T PriorityQueue<T, Comparator>::extract()
{
    if(size == 0)
    {
        return nullptr;
    }

    T best = heap[0];
    heap[0] = heap[size - 1];
    size--;

    if(size > 0)
    {
        heapifyDown(0);
    }

    return best;
}

template <typename T, typename Comparator>
T PriorityQueue<T, Comparator>::peek() const
{
    return size == 0 ? nullptr : heap[0];
}

template <typename T, typename Comparator>
bool PriorityQueue<T, Comparator>::isEmpty() const
{
    return size == 0;
}

template <typename T, typename Comparator>
int PriorityQueue<T, Comparator>::getSize() const
{
    return size;
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::clear()
{
    size = 0;
}
