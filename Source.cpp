#include"MaxHeap.h"

int main()
{
	MaxHeap<int, string> heap;

	heap.Insert(pair<int, string>(5, "A"));

	heap.Insert(pair<int, string>(4, "A"));

	heap.Insert(pair<int, string>(5, "A"));

	heap.Insert(pair<int, string>(15, "A"));

	heap.Insert(pair<int, string>(2, "A"));

	heap.Insert(pair<int, string>(6, "A"));

	heap.Insert(pair<int, string>(20, "A"));

	heap.Insert(pair<int, string>(20, "A"));

	heap.Display();

	cout << endl;

	pair<int, string> P = heap.DeleteMax();

	cout << P.first << "  " << P.second << endl << endl;

	heap.Display();

	cout << endl;

	cout << "After invoking Copy Constructor..\n";

	MaxHeap<int, string> heap2 = heap;

	heap2.Display();
}