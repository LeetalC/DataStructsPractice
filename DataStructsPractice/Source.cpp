#include <iostream>
#include <set>
#include <map>


using namespace std;

typedef int Vertex;
typedef set<Vertex> VertexSet;
typedef map<Vertex, VertexSet> Graph2;


void maxHeapify(int arr[], int k, int size); //where k is the value up until which the data is not sorted.
void minHeapify(int arr[]);


Graph2 makeCycle(unsigned v);
void show(const Graph2 &g);
bool isMinHeap(int arr[]);
bool isMaxHeap(int arr[]);
//Graph2 createComp(unsigned v);
//Graph2 createCyc(unsigned v);
//Graph2 createWheel(unsigned v);

int main() {
	
	int notAHeapArr[7] = { 10,4,78,1,32,34,26 };
	int isaMaxArr[7] = { 19,2,12,1,0, 4, 8 };
	int isaMinArr[7] = { 1,2,4,6,7,5,8 };

	int c;
	cout << "1 is for heaps, 2 is for graphs: ";
	cin >> c;
	switch (c) {
	case 1:
		cout << isMinHeap(isaMaxArr) << endl;
		cout << isMinHeap(isaMinArr) << endl;
		cout << isMinHeap(notAHeapArr) << endl;

		cout << isMaxHeap(isaMaxArr) << endl;
		cout << isMaxHeap(isaMinArr) << endl;
		cout << isMaxHeap(notAHeapArr) << endl;
		break;
	case 2:
		Graph2 g = makeCycle(7);
		show(g);
		//maxHeapify(notAHeapArr, (sizeof(notAHeapArr) / sizeof(int) - 1));

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

//void maxHeapify(int arr[], int k, int size) {
////a max heap has the property where each node has a child that is smaller than itself. (left/right)
////the parent is located at k/2, left child is at 2*k and rigth child is at 2*k+1
//	
//	int temp;
//	int parent = size / 2 - 1;
//	int current = parent;
//	for(int i = 0; )
//
//}

Graph2 makeCycle(unsigned v) {
	Graph2 g;
	for (unsigned i = 0; i < v-1; ++i) {
		
		g[i].insert(i + 1);
		g[i + 1].insert(i);

	}
	g[v - 1].insert(0);
	g[0].insert(v - 1);
	return g;
}

Graph2 makeWheel(unsigned v) {
	Graph2 g = makeCycle(v);
	for (unsigned i = 0; i < v - 1; ++i) {
			
	}
}


Graph2 makeComplete(unsigned v) {
	Graph2 g;
	for (unsigned i = 0; i < v; ++i) {
	}
}

void show(const Graph2 &g) {
	for (auto itr = g.begin(); itr != g.end(); itr++) {
		cout << itr->first << endl;
		for (auto it = itr->second.begin(); it != itr->second.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}

}
//Graph2 createComp(unsigned v) {
//	Graph2 g;
//	
//}
