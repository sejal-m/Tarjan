#include <bits/stdc++.h>
using namespace std;
 
class Graph
{
    int V;   
    vector<int> *adj;    
public:
  
    Graph(int V)
    {
        this->V = V;
        adj = new vector<int>[V];
    }
    ~Graph()
    {
        delete [] adj;
    }

    void addEdge(int u, int v);
    void findArticulationPoint(int u, bool visited[],
            int disc[], int low[], int& time, int parent,
            bool isAP[]);
    void tarjanArticulationPoints();
};

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u); 
}

void Graph::findArticulationPoint(int u, bool visited[],int disc[], int low[], int& time, int parent,bool isAP[])
{ 
    int children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;
 
    for (auto v : adj[u]) {
 
        if (!visited[v]) {
            children++;
            findArticulationPoint(v, visited, disc, low, time, u, isAP);
 
            low[u] = min(low[u], low[v]);
 
            if (parent != -1 && low[v] >= disc[u])
                isAP[u] = true;
        }
        else if (v != parent)
            low[u] = min(low[u], disc[v]);
    }
    if (parent == -1 && children > 1)
        isAP[u] = true;
}
 
void Graph::tarjanArticulationPoints()
{
    int disc[V] = { 0 };
    int low[V];
    bool visited[V] = { false };
    bool isAP[V] = { false };
    int time = 0, par = -1;
 
    for (int u = 0; u < V; u++)
        if (!visited[u])
            findArticulationPoint(u, visited, disc, low,
                   time, par, isAP);

    for (int u = 0; u < V; u++)
        if (isAP[u] == true)
            cout << u << " ";
}
 
int main()
{
     
    cout << "Articulation points in given graph \n";
    ifstream infile("tarjan_input.txt");
    int n;
    infile>>n;
    Graph G(n);

    int a, b;
    while (infile >> a >> b)
        G.addEdge(a, b); 

    G.tarjanArticulationPoints();

    infile.close();
    return 0;
}