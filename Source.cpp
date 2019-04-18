
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
# include <fstream>
using namespace std;

// A class that represents an undirected MATRIX
class MATRIX
{
	int V;    // No. of vertices
	list<int> *adj;    // A dynamic array of adjacency lists
public:
	// Constructor and destructor
	MATRIX(int V) { this->V = V; adj = new list<int>[V]; }
	~MATRIX() { delete[] adj; }

	// function to add an edge to MATRIX
	void addEdge(int v, int w);

	// Prints greedy coloring of the vertices
	void greedyColoring(vector<int> tokens);
};

void MATRIX::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);  // Note: the MATRIX is undirected
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
void MATRIX::greedyColoring(vector<int> tokens)
{
	int maxout;
	int maxin = 0;
	for (int i = 0; i<V; i++)
	{
		if (tokens[i] > maxin)
			maxin = tokens[i];
	}

	int** results = new int*[V];
	for (int i = 0; i < V; i++) {
		results[i] = new int[V];

	}

	for (int i = 0; i < V; i++) {
		for (int a = 0; a < V; a++)
			results[a][i] = tokens[a] - 1;


	}
	
	for (int j = 0; j < V; j++) {

		bool *colored = new bool[V];
		for (int cr = 0; cr < V; cr++)
			colored[cr] = false;


		for (int u = 0; u < j; u++) {
			// Process all adjacent vertices and flag their colors
			// as uncolored
			list<int>::iterator i;
			for (i = adj[u].begin(); i != adj[u].end(); ++i)
				if (results[*i][j] != -1)
					colored[results[*i][j]] = true;

			// Find the first colored color
			int cr;
			for (cr = 0; cr < V; cr++)
				if (colored[cr] == false)
					break;

			results[u][j] = cr; // Assign the found color

								// Reset the values back to false for the next iteration
			for (i = adj[u].begin(); i != adj[u].end(); ++i)
				if (results[*i][j] != -1)
					colored[results[*i][j]] = false;

		}

		for (int u = j; u < V; u++)
		{
			// Process all adjacent vertices and flag their colors
			// as uncolored
			list<int>::iterator i;
			for (i = adj[u].begin(); i != adj[u].end(); ++i)
				if (results[*i][j] != -1)
					colored[results[*i][j]] = true;

			// Find the first colored color
			int cr;
			for (cr = 0; cr < V; cr++)
				if (colored[cr] == false)
					break;

			results[u][j] = cr; // Assign the found color

			// Reset the values back to false for the next iteration
			for (i = adj[u].begin(); i != adj[u].end(); ++i)
				if (results[*i][j] != -1)
					colored[results[*i][j]] = false;
		}
			}
	int min = V;
	int max = 0;
	int ind = 0;
	for (int j = 0; j < V; j++) {
		max = 0;
		for (int i = 0; i < V; i++) {

			if (results[i][j] > max)
			max = results[i][j];
			
		}
		if (max < min) {
			min = max;
			ind = j;
			maxout = max + 1;
		}
	}
	ofstream output;
	output.open("output.txt");
	output << maxout - maxin << endl;
	for (int i = 0; i < V; i++)
	output << results[i][ind] + 1 << "  ";
	output.close();
}

int main(int argc, char ** argv)
{
	if (argc < 2) { 
		cerr << "please enter a valid text file as an argument\n"; 
		
	return 1;
	}
	ifstream input(argv[1]);
	string str;
	if (input.is_open()) {

		getline(input, str);
		istringstream iss(str);
		vector<int> tokens{ istream_iterator<int>{iss}, istream_iterator<int>{} };
		int N = tokens[0];
		int M = tokens[1];
		MATRIX g(N);
		
		while (getline(input, str)) {

			istringstream iss(str);
			vector<int> tokens{ istream_iterator<int>{iss}, istream_iterator<int>{} };
			int v = tokens[0];
			int w = tokens[1];
			if (tokens.size() == 2)
				g.addEdge(v - 1, w - 1);
			if (tokens.size() < 2 || (tokens.size() > 2 && tokens.size() != N)) {
				cout << "Invalid input" << endl;
			}
			if (tokens.size() > 2) { 
				g.greedyColoring(tokens);
			}
		}
	}

	else cout << " unable to open file";
	input.close();
	return 0;
}




//for (int i = 0; i < V; ++i) {
//for (int a = 0; a < V; a++)
//	cout << results[a][i] << '\t';
//cout << endl;
//}
//cout << "chevking here  "<< results[1][8] << endl;
// Assign the first color to first vertex
//result[0] = 0;
// Initialize remaining V-1 vertices as unassigned
//for (int u = 1; u < V; u++)
//result[u] = -1;  // no color is assigned to u
// A temporary array to store the colored colors. True
// value of colored[cr] would mean that the color cr is
// assigned to one of its adjacent vertices


//	for (int i = 0; i < V; ++i) {
//	for (int a = 0; a < V; a++)
//	cout << results[a][i]+1 << '\t';
//		cout << "t \n \n \n";
//	}
