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

	int c, numErrs = 0;
	//premade wheel
	Graph2 test{ {0,{1,4,5}}, {1,{0,2,5}}, {2,{1,3,5}}, {3,{2,4,5}}, {4,{0,3,5}}, {5,{0,1,2,3,4}}};
    cout << "Is this a wheel?: " << isWheel(test) << endl << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "Which graph do you want to test?" << endl;
	cout << "1 for Wheel, 2 for Complete, 3 for Cycle." << endl;


	while (cin >> c) {
		switch (c) {
		case 1:
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
		default: cout << "fucked" << endl;
		}
		numErrs = 0;
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