
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
# include <fstream>
using namespace std;

// A class that represents an undirected graph
class Graph
{
	int V;    // No. of vertices
	list<int> *adj;    // A dynamic array of adjacency lists
public:
	// Constructor and destructor
	Graph(int V) { this->V = V; adj = new list<int>[V]; }
	~Graph() { delete[] adj; }

	// function to add an edge to graph
	void addEdge(int v, int w);

	// Prints greedy coloring of the vertices
	void greedyColoring(vector<int> tokens);
};

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);  // Note: the graph is undirected
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
void Graph::greedyColoring(vector<int> tokens)
{
	int maxin = 0;

	for (int i = 0; i<V; i++)
	{
		if (tokens[i] > maxin)
			maxin = tokens[i];
	} 

	int *result = new int[V];
	for (int i = 0; i < V; i++) {
		result[i] = tokens[i] - 1;
	}




	// Assign the first color to first vertex
	//result[0] = 0;

	// Initialize remaining V-1 vertices as unassigned
	//for (int u = 1; u < V; u++)
		//result[u] = -1;  // no color is assigned to u

						 // A temporary array to store the colored colors. True
						 // value of colored[cr] would mean that the color cr is
						 // assigned to one of its adjacent vertices
	bool *colored = new bool[V];
	for (int cr = 0; cr < V; cr++)
		colored[cr] = false;

	// Assign colors to remaining V-1 vertices
	for (int u = 0; u < V; u++)
	{
		// Process all adjacent vertices and flag their colors
		// as uncolored
		list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (result[*i] != -1)
				colored[result[*i]] = true;

		// Find the first colored color
		int cr;
		for (cr = 0; cr < V; cr++)
			if (colored[cr] == false)
				break;

		result[u] = cr; // Assign the found color

						// Reset the values back to false for the next iteration
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (result[*i] != -1)
				colored[result[*i]] = false;
	}
	int maxout = 0;

	for (int i = 0; i<V; i++)
	{
		if (result[i]+1 > maxout)
			maxout = result[i]+1;
	}


	
	ofstream myfile2;
	myfile2.open("output.txt");
	myfile2 << maxout - maxin << endl;

		// print the result
	for (int u = 0; u < V; u++)
		myfile2 << result[u] + 1 << "  ";


	myfile2.close();
}

       

// Driver program to test above function
int main()
{
	ifstream myfile("input.txt");
	string str;
	if (myfile.is_open()) {

		getline(myfile , str);
		istringstream iss(str);
		vector<int> tokens{ istream_iterator<int>{iss}, istream_iterator<int>{} };
		int V = tokens[0];
		int M = tokens[1];
		Graph g(V);

		//bool reading = true;
		while (getline(myfile, str)) {
			
			//getline(myfile, str);

			istringstream iss(str);
			vector<int> tokens{ istream_iterator<int>{iss}, istream_iterator<int>{} };
			int v = tokens[0];
			int w = tokens[1];
			if (tokens.size() == 2)
				g.addEdge(v - 1, w - 1);
			if (tokens.size() < 2 || (tokens.size() > 2 && tokens.size() != V)) {
				cout << "Invalid input" << endl;
			}
			if (tokens.size() > 2) { // result-Colors
				 // reading = false;
				g.greedyColoring(tokens);
			}
		}
	}

	else cout << " unable to open file";
	
	
	return 0;
}