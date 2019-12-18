#include "listgr.h"

CListGraph::CListGraph( int size ) : vertices_count( size )
{
    graph.resize(size);
}

ListGraph::ListGraph(const IGraph& gr) : graph(gr.VerticesCount()) {
    for ( size_t i = 0; i < list_.size(); ++i ) {
        std::vector<int> next_vertices = gr.GetNextVertices(i);
        for ( const auto & next : next_vertices ) {
            AddEdge(i, next);
        }
    }
}

void CListGraph::AddEdge(int from, int to) 
{
    graph[from].push_back(to);
}

std::vector<int> CListGraph::GetNextVertices(int vertex) const
{
    std::vector<int> result;
    result.resize(graph[vertex].size());
    
    std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
    return result;
}

std::vector<int> CListGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> result;
    for ( int i = 0; i < graph.size(); ++i)
    {
        auto& children = graph[i];
        for ( auto child : children)
        {
            if ( child == vertex )
            {
                result.push_back(i);
            }
        }
    }
    return result;
}

int CListGraph::VerticesCount() const
{
    return vertices_count;
}

int main() {
    return 0;
}