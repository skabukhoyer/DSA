
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include<iterator>
#include<climits>
using namespace std;
struct node
{
	int pathWeight;
	vector<int> p;
};
vector<vector<int>> paths;
void findNewPath(vector<vector<int>> &graph, int u, int d, bool visited[], vector<int> &path, int &path_index)
{
	int V = graph.size();
	visited[u] = true;
	path[path_index] = u;
	path_index++;
	if (u == d)
	{
		for (int i = path_index; i < V; i++)
			path[i] = -1;
		paths.push_back(path);
	}
	else
	{

		for (int i = 0; i < V; i++)
			if (graph[u][i] != 0 && (!visited[i]))
				findNewPath(graph, i, d, visited, path, path_index);
	}
	path_index--;
	visited[u] = false;
}
void printPaths(vector<vector<int>> &graph)
{
	int V = graph.size();
	bool *visited = new bool[V];
	vector<int> path(V);
	int path_index;
	for (int i = 0; i < V; i++)
	{
		for (int j = i + 1; j < V; j++)
		{
			path_index = 0;
			for (int i = 0; i < V; i++)
			{
				visited[i] = false;
				path[i] = -1;
			}
			findNewPath(graph, i, j, visited, path, path_index);
		}
	}
}
void sort_weight(vector<struct node> &out, int n)
{
	struct node temp;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (out[j].pathWeight > out[j + 1].pathWeight)
			{
				temp = out[j];
				out[j] = out[j + 1];
				out[j + 1] = temp;
			}
		}
	}
}

void sort_path(vector<struct node> &out, int l, int u)
{
	struct node temp;
	//int n1 = l + 1;
	int n2 = u - l + 1;
    int n1=l+n2;
	for (int i = 0; i < n2 - 1; i++)
	{
		for (int j = l; j < n1 - i - 1; j++)
		{
			stringstream ss1, ss2;
			copy(out[j].p.begin(), out[j].p.end(), ostream_iterator<int>(ss1, ""));
			string s1 = ss1.str();
			// s = s.substr(0, s.length()-1);  // get rid of the trailing space
			copy(out[j + 1].p.begin(), out[j + 1].p.end(), ostream_iterator<int>(ss2, ""));
			string s2 = ss2.str();

			if (s1 > s2)
			{
				temp = out[j];
				out[j] = out[j + 1];
				out[j + 1] = temp;
			}
		}
	}
}
void lexicographical_sort(vector<struct node> &out, int n)
{
	int i = 0, w = 0;
	int lower, upper;
	while (i < n)
	{
		lower = i;
		upper = lower + 1;
		w = out[i].pathWeight;
		while (upper < n && out[upper].pathWeight == w)
		{
			upper++;
		}
		sort_path(out, lower, upper - 1);
        //cout<<lower<<"\t"<<upper-1<<endl;
		i = upper;
	}
}
int main()
{
	int V, E;
	cin >> V >> E;
	int K;
	vector<vector<int>> graph(V, vector<int>(V, 0));
	// for (int i = 0; i < V; i++)
	// {
	//     graph.push_back(edge);
	// }
	int u, v, w;
	for (int i = 1; i <= E; i++)
	{
		cin >> u >> v >> w;
		graph[u][v] = graph[v][u] = w;
	}
	cin>>K;
	// for(int i=0;i<V;i++){
	//     for(int j=0;j<V;j++)
	//         cout<<graph[i][j]<<" ";
	//     cout<<endl;
	// }
	printPaths(graph);
	int n = paths.size();
	// for (int i = 0; i < n; i++)
	// {

	//     for (int j = 0; j < V; j++)
	//     {
	//         if (paths[i][j] == -1)
	//             break;
	//         else
	//             cout << paths[i][j] << " ";
	//     }
	//     cout << endl;
	// }
	vector<struct node> out(n);
	int weight;
	for (int i = 0; i < n; i++)
	{
		vector<int> x;
		weight = 0;
		int j = 0, prev = -1;
		do
		{
			if (paths[i][j] == -1)
				break;
			if (j != 0)
			{
				weight += graph[prev][paths[i][j]];
			}
			x.push_back(paths[i][j]);
			prev = paths[i][j];
			j++;
		} while (j < V);
		out[i].pathWeight = weight;
		out[i].p = x;
		//cout<<weight<<endl;
	}
	sort_weight(out, n);
	// for (int i = 0; i < n; i++)
	// {
	// 	cout << i << ": " << out[i].pathWeight << "--> ";
	// 	for (int j = 0; j < out[i].p.size(); j++)
	// 	{
	// 		cout << out[i].p[j] << " ";
	// 	}
	// 	cout << endl;
	// }
	lexicographical_sort(out, n);
	
	int m=min(K,n);
	for(int i=0;i<m;i++){
		cout<<out[i].pathWeight<<"--> ";
		for (int j = 0; j < out[i].p.size(); j++)
		{
			cout << out[i].p[j] << " ";
		}
		cout << endl;
	}
	return 0;
}