#include <iostream>
#include <set>
#include <map>
#include <random>

using namespace std;

typedef int Vertex;
typedef set<Vertex> VertexSet;
typedef map<Vertex, VertexSet> Graph2;

Graph2 makeCycle(unsigned v);
Graph2 makeComplete(unsigned v);
Graph2 makeWheel(unsigned v);

bool isWheel(const Graph2 &g);
void show(const Graph2 &g);

unsigned nonHeapPos(const unsigned a[], unsigned els);

int main() {

	int c, numErrs = 0;
	Graph2 test{ {0,{1,4,5}}, {1,{0,2,5}}, {2,{1,3,5}}, {3,{2,4,5}}, {4,{0,3,5}}, {5,{0,1,2,3,4}} };
	const unsigned maxheap1[]{ 0,25,20,12,19,12,5,6 };
	const unsigned maxheap2[]{ 0,19,2,12,1,0, 4, 8 };

	const unsigned minheap1[]{ 0,10,20,30,40,50,60 };
	const unsigned minheap2[]{ 0,1,2,4,6,7,5,8 };

	const unsigned notheap1[]{ 0,50,30,20,50,20,30, 10 };
	
	cout << "------------------------------------------------------------" << endl;
	cout << "Which graph do you want to test?" << endl;
	cout << "1 for Wheel, 2 for Complete, 3 for Cycle, 4 for heap: ";


	while (cin >> c) {
		switch (c) {
		case 1:
			cout << "Testing premade wheel graph: " << isWheel(test) << endl << endl;
			for (int i = 0; i < 200; i++) {
				int s = rand() % 100 + 4;
				Graph2 whee = makeWheel(s);
				//show(whee);
				if (!(isWheel(whee))) numErrs++;
			}
			cout << "ERRORS FOR WHEEL: " << numErrs << endl;
			break;
		case 2:
			for (int i = 0; i < 200; i++) {
				int s = rand() % 100 + 5;
				Graph2 comp = makeComplete(s);
				//show(comp);
				if (isWheel(comp)) numErrs++;
			}
			cout << "ERRORS FOUND FOR COMPLETE: " << numErrs << endl;
			break;
		case 3:
			for (int i = 0; i < 200; i++) {
				int s = rand() % 100 + 4;
				Graph2 cyc = makeCycle(s);
				//show(cyc);
				if (isWheel(cyc)) numErrs++;
			}
			cout << "ERRORS FOUND FOR CYCLE: " << numErrs << endl;
			break;
		case 4:
			//sizeof(notheap) / sizeof(int) - 1
			cout << "should be 0: " << nonHeapPos(maxheap1, 8) << endl << endl;
			cout << "should be 0: " << nonHeapPos(maxheap2, 8) << endl << endl;
		    cout << "should be 1: " << nonHeapPos(minheap1, 8) << endl << endl;
		    cout << "should be 1: " << nonHeapPos(minheap2, 8) << endl << endl;
			cout << "should be 2: " << nonHeapPos(notheap1, 8) << endl << endl;
			break;
		default: cout << "fucked" << endl;
		}
		numErrs = 0;
	}

	system("pause");
	return 0;

}

unsigned nonHeapPos(const unsigned a[], unsigned els) {
	cout << "The array looks like this: " << endl;
	for (int k = 1; k < els; k++) {
		cout << a[k]<< " ";
	}
	cout << endl << "********************" << endl;
	for (int i = 1; i < els; ++i) {
		//a[i] is parent, a[2*i] is left child, a[2*i+1] is right child
		//this checks for a min heap
		cout << "Parent (i) " << a[i] << " and left child (2*i) " << a[2 * i] << " and right child (2*i+1) " << a[2 * i + 1] << endl;
		if (2 * i > els || 2 * i + 1 > els) return 0;
		if (a[i] < a[2 * i] || a[i] < a[2 * i + 1]) return i;

	}
}











//bool isMinHeap(int arr[]) {
//	int s = sizeof(arr) / sizeof(int) - 1;
//	for (int i = 0; i <= (arr[1] - 2) / 2; ++i) {
//		if (arr[2 * i] < arr[i]) return false;
//		if (arr[2 * i + 1] < arr[i]) return false;
//	}
//	return true;
//	//left child is located at 2*k, right child is located at 2*k+1, parent is located at k/2 where k is some element
//}


Graph2 makeCycle(unsigned v) {
	Graph2 gr;
	for (int i = 0; i < v - 1; ++i) {
		gr[i].insert(i + 1);
		gr[i + 1].insert(i);

	}
	gr[v - 1].insert(0);
	gr[0].insert(v - 1);

	return gr;
	//perfect
}

Graph2 makeWheel(unsigned v) {
	Graph2 gr = makeCycle(v - 1);
	for (int i = 0; i < v - 1; ++i) {
		gr[i].insert(v - 1);
		gr[v - 1].insert(i);

	}
	return gr;
}

Graph2 makeComplete(unsigned v) {
	Graph2 g;
	for (int i = 0; i < v; ++i) {
		for (int k = 0; k < v; ++k) {
			if (k != i) {
				g[i].insert(k);
				g[k].insert(i);
			}
		}
	}
	return g;
}

bool isWheel(const Graph2 &g) {
	int edges = 0;

	for (auto itr = g.begin(); itr != g.end(); itr++) {
		if (itr->second.size() < 3) return false;
		for (auto neighbor = itr->second.begin(); neighbor != itr->second.end(); neighbor++) {
			auto it = g.find(*neighbor);
			if (it->second.find(itr->first) != it->second.end()) edges++;
			else return false;
		}
	}

	edges = edges / 2;
	if (edges == 2 * (g.size() - 1)) return true;
	return false;
}


void show(const Graph2 &g) {
	for (auto itr = g.begin(); itr != g.end(); ++itr) {
		cout << itr->first << " and { ";
		for (Vertex v : itr->second) {
			cout << v << " ";
		}
		cout << "}" << endl;
	}
}