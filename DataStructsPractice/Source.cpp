#include <iostream>
#include <set>
#include <map>


using namespace std;

typedef int Vertex;
typedef set<Vertex> VertexSet;
typedef map<Vertex, VertexSet> Graph2;

bool isMinHeap(int arr[]);
bool isMaxHeap(int arr[]);
//Graph2 createComp(unsigned v);
//Graph2 createCyc(unsigned v);
//Graph2 createWheel(unsigned v);

int main() {
	
	int notheap[7] = { 10,4,78,1,32,34,26 };
	int isaMaxArr[7] = { 19,2,12,1,0, 4, 8 };
	int isaMinArr[7] = { 1,2,4,6,7,5,8 };

	int c;
	cout << "1 is for heaps, 2 is for graphs: ";
	cin >> c;
	switch (c) {
	case 1:
		cout << isMinHeap(isaMaxArr) << endl;
		cout << isMinHeap(isaMinArr) << endl;
		cout << isMinHeap(notheap) << endl;

		cout << isMaxHeap(isaMaxArr) << endl;
		cout << isMaxHeap(isaMinArr) << endl;
		cout << isMaxHeap(notheap) << endl;
		break;
	case 2:
		cout << "hi" << endl;
	}
	
	//isheap(isaheap);

	//Graph2 comp = createComp(5);

	system("pause");
	return 0;

}
bool isMinHeap(int arr[]) {
	int s = sizeof(arr) / sizeof(int) - 1;
	for (int i = 0; i <= (arr[1] - 2) / 2; ++i) {
		if (arr[2 * i] < arr[i]) return false;
		if (arr[2 * i + 1] < arr[i]) return false;
	}
	return true;
	//left child is located at 2*k, right child is located at 2*k+1, parent is located at k/2 where k is some element
}

bool isMaxHeap(int arr[]) {
	int s = sizeof(arr) / sizeof(int) - 1;
	for (int i = 0; i <= (arr[1] - 2) / 2; ++i) {
		if (arr[2 * i] > arr[i]) return false;
		if (arr[2 * i + 1] > arr[i]) return false;
	}
	return true;
}
//Graph2 createComp(unsigned v) {
//	Graph2 g;
//	
//}
