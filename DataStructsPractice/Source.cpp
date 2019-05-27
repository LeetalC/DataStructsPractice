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
				/*does vertex 1 contain 0 in it's set? if so, add an edge*/
				if (it->second.find(itr->first) != it->second.end()) edges++; //this will find all existing edges and counts them twice
				else return false;	//there existed a set without a match, this is not a wheel.
			}
		}
		edges = edges / 2;
		if (edges == 2 * (s - 1)) return true;
	}
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
