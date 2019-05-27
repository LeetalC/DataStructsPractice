#include <iostream>
#include <set>
#include <map>
#include <random>

using namespace std;

typedef int Vertex;
typedef set<Vertex> VertexSet;
typedef map<Vertex, VertexSet> Graph2;

Graph2 makeCycle(unsigned v);
bool isWheel(const Graph2 &g);

Graph2 makeComplete(unsigned v);

Graph2 makeWheel(unsigned v);
void show(const Graph2 &g);

int main() {

	int c;
	cout << "Which graph do you want to test?" << endl;
	cout << "1 for Wheel, 2 for Complete, 3 for Cycle." << endl;

	while (cin >> c) {
		switch (c) {
		case 1:
			for (int i = 0; i < 5; i++) {
				int s = rand() % 5 + 4;
				Graph2 whee = makeWheel(s);
				show(whee);
				cout << "Is whee a wheel?: " << isWheel(whee) << endl;
			}
			cout << endl;
			break;
		case 2:
			for (int i = 0; i < 5; i++) {
				int s = rand() % 5 + 1;
				Graph2 comp = makeComplete(s);
				show(comp);
				cout << "Is complete a wheel?: " << isWheel(comp) << endl;
			}
			break;
		case 3:
			for (int i = 0; i < 25; i++) {
				int s = rand() % 30 + 4;
				Graph2 cyc = makeCycle(s);
				show(cyc);
				cout << "Is cyc a wheel?: " << isWheel(cyc) << endl;
				cout << endl;
			}
			break;
		default: cout << "fucked" << endl;
		}
	}

	system("pause");
	return 0;

}

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
	//perfect
}

Graph2 makeComplete(unsigned v) {
	Graph2 g;
	for(int i = 0; i < v; ++i){
		for (int k = 0; k < v; ++k) {
			if (k != i) {
				g[i].insert(k);
				g[k].insert(i);
			}
		}
	}
	return g;
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

bool isWheel(const Graph2 &g) {
	int s = g.size(); //number of verts in the graph
	int edges = 0; //going to find the number of edges in the graph. a wheel has 2(s-1) edges, soif s = 5, then this graph should have 2*4 edges == 8 edges.
	auto center = g.begin();
	bool centerFound = false;

    //find the vertex with the largest adjacency list, equal to the size of the graph, minus itself
	//this is also used for obvious removals
	for (auto max = g.begin(); max != g.end(); max++) {
		if (max->second.size() < 3) return false;
		if (max->second.size() == s - 1) {
			center = max;
			centerFound = true;
		}
	}

	if (centerFound) {
		for (auto itr = g.begin(); itr != g.end(); itr++) {	//for every element in the map (vertex) 
			for (auto neighbor = itr->second.begin(); neighbor != itr->second.end(); neighbor++) {	//for every element in the set of vertex
				auto it = g.find(*neighbor); //we start with vertex 0, which has 1,3,and 4 as neighbors. g.find(1) is found so we go to it
				if (it->second.find(itr->first) != it->second.end()) { //does vertex 1 contain 0 in it's set? if so, add an edge
					edges++; //this will find all existing edges and counts them twice
				}
				else return false;	//there existed a set without a match, this is not a wheel.

			}
		}
		edges = edges / 2;
		if (edges == 2 * (s - 1)) return true;
	}

	return false;
}



//incorrect is wheel


//int i = 0; // the value of the vertex we're working with
	//int s = g.size(); //size of the graph

	//for (auto itr = g.begin(); itr != g.end(); ++itr) {
	//	auto is = itr->second;
	//	if (itr->first == 0) {	//checking to see if 0's match up
	//		if (!(is.find(i + 1) != is.end() &&
	//			is.find(s - 1) != is.end() &&
	//			is.find(s - 2) != is.end())) return false;
	//	}
	//	else if (itr->first == s - 1) {	//checking to see if last element contains all other elements.
	//		for (int k = 0; k < s - 1; ++k) {
	//			if (!(is.find(k) != is.end())) return false;
	//		}
	//	}
	//	else {	//checking to see if any other element has 
	//		if (!(is.find(i + 1) != is.end() &&
	//			is.find(i - 1) != is.end() &&
	//			is.find(s - 1) != is.end())) return false;
	//	}
	//	i++;
	//}
	//return true;




//--------------old


//void maxHeapify(int arr[], int k, int size); //where k is the value up until which the data is not sorted.
//void minHeapify(int arr[]);
//
//

//
//void show(const Graph2 &g);
//bool isMinHeap(int arr[]);
//bool isMaxHeap(int arr[]);
////Graph2 createComp(unsigned v);
////Graph2 createCyc(unsigned v);
////Graph2 createWheel(unsigned v);
//
//int main() {
//	
//	
//	system("pause");
//	return 0;
//
//}
//bool isMinHeap(int arr[]) {
//	int s = sizeof(arr) / sizeof(int) - 1;
//	for (int i = 0; i <= (arr[1] - 2) / 2; ++i) {
//		if (arr[2 * i] < arr[i]) return false;
//		if (arr[2 * i + 1] < arr[i]) return false;
//	}
//	return true;
//	//left child is located at 2*k, right child is located at 2*k+1, parent is located at k/2 where k is some element
//}
//
//bool isMaxHeap(int arr[]) {
//	int s = sizeof(arr) / sizeof(int) - 1;
//	for (int i = 0; i <= (arr[1] - 2) / 2; ++i) {
//		if (arr[2 * i] > arr[i]) return false;
//		if (arr[2 * i + 1] > arr[i]) return false;
//	}
//	return true;
//}
//
////void maxHeapify(int arr[], int k, int size) {
//////a center heap has the property where each node has a child that is smaller than itself. (left/right)
//////the parent is located at k/2, left child is at 2*k and rigth child is at 2*k+1
////	
////	int temp;
////	int parent = size / 2 - 1;
////	int current = parent;
////	for(int i = 0; )
////
////}
//
//Graph2 makeWheel(unsigned v) {
//	
//
//
//}
//Graph2 makeCycle(unsigned v) {
//	Graph2 g;
//	for (unsigned i = 0; i < v-1; ++i) {
//		
//		g[i].insert(i + 1);
//		g[i + 1].insert(i);
//
//	}
//	g[v - 1].insert(0);
//	g[0].insert(v - 1);
//	return g;
//}
//
//Graph2 makeWheel(unsigned v) {
//	Graph2 g = makeCycle(v);
//	for (unsigned i = 0; i < v - 1; ++i) {
//			
//	}
//}
//
//
//Graph2 makeComplete(unsigned v) {
//	Graph2 g;
//	for (unsigned i = 0; i < v; ++i) {
//	}
//}
//
//void show(const Graph2 &g) {
//	for (auto itr = g.begin(); itr != g.end(); itr++) {
//		cout << itr->first << endl;
//		for (auto it = itr->second.begin(); it != itr->second.end(); it++) {
//			cout << *it << " ";
//		}
//		cout << endl;
//	}
//
//}
//
////Graph2 createComp(unsigned v) {
////	Graph2 g;
////	
////}
//
////old code
///*int notAHeapArr[7] = { 10,4,78,1,32,34,26 };
//	int isaMaxArr[7] = { 19,2,12,1,0, 4, 8 };
//	int isaMinArr[7] = { 1,2,4,6,7,5,8 };
//
//	int c;
//	cout << "1 is for heaps, 2 is for graphs: ";
//	cin >> c;
//	switch (c) {
//	case 1:
//		cout << isMinHeap(isaMaxArr) << endl;
//		cout << isMinHeap(isaMinArr) << endl;
//		cout << isMinHeap(notAHeapArr) << endl;
//
//		cout << isMaxHeap(isaMaxArr) << endl;
//		cout << isMaxHeap(isaMinArr) << endl;
//		cout << isMaxHeap(notAHeapArr) << endl;
//		break;
//	case 2:
//		Graph2 g = makeCycle(7);
//		show(g);
//		//maxHeapify(notAHeapArr, (sizeof(notAHeapArr) / sizeof(int) - 1));
//
//	}
//
//	//isheap(isaheap);
//
//	//Graph2 comp = createComp(5);
//*/