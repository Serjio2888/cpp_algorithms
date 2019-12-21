#ifndef LISTGRAPH1_H
#define LISTGRAPH1_H

#include <vector>
#include <algorithm>
#include <queue>

#include "graph.h"

class CListGraph : public IGraph
{
public:
    explicit CListGraph( int size );
    explicit CListGraph(const IGraph& g);
    
    virtual ~CListGraph() {}
    
    void AddEdge(int from, int to) override;
    
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
    

private:
    std::vector< std::vector<int> > graph;
    int vertices_count;
};

#endif 