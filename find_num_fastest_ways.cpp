#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <assert.h>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;
    
    virtual int VerticesCount() const  = 0;
    
    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
};

class CListGraph : public IGraph
{
public:
    explicit CListGraph( int size ) : vertices_count( size )
    {
        graph.resize(size);
    }
    
    virtual ~CListGraph() {}
    
    void AddEdge(int from, int to) override
    {
        graph[from].push_back(to);
        graph[to].push_back(from);
    }
    
    int VerticesCount() const override
    {
        return vertices_count;
    }
    
    std::vector<int> GetNextVertices(int vertex) const override
    {
        std::vector<int> result;
        result.resize(graph[vertex].size());
        
        std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
        return result;
    }

private:
    std::vector< std::vector<int> > graph;
    int vertices_count;
};

void WaysSearch(const IGraph& graph, int start, int end)
{
    std::queue<int> q;
    std::vector<std::pair<int, int>> states(graph.VerticesCount(), std::pair<int,int>(0,0));  // (0, 0)

    q.push(start);
    states[start].first = 1;
    states[start].second = 1;

    while(!q.empty()) {
        int current = q.front();
        int depth = states[current].first + 1;
        q.pop();

        std::vector <int> vertices = graph.GetNextVertices(current);

        for (int i : vertices) {
            if (states[i].first == 0) {
                states[i].first = depth;
                states[i].second = states[current].second;
                q.push(i);
            } else
            if (states[i].first == depth) {
                states[i].second += states[current].second;
            }
        }
    }
    std::cout << states[end].second;
}

void printer(int vertex)
{
    std::cout << "*fs: " << vertex << std::endl;
}

int main(int argc, const char * argv[]) {
    int verticas, edges = 0;
    std::cin >> verticas;
    std::cin >> edges;
    
    IGraph* graph = new CListGraph(verticas);
    int from, to = 0;
    for (int i = 0; i < edges; ++i) {
        std::cin >> from >> to;
        graph->AddEdge(from, to);
    }

    int start, end = 0;
    std::cin >> start >> end;

    WaysSearch(*graph, start, end);
    
    delete graph;
    return 0;
}