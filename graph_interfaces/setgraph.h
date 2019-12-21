#ifndef LISTGRAPH3_H
#define LISTGRAPH3_H

#include <cstdlib>
#include <unordered_map>
#include <vector>

#include "graph.h"

class SetGraph : public IGraph {
public:
    explicit SetGraph(size_t _size);
    explicit SetGraph(const IGraph& g);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::unordered_map<int, std::vector<int> > map_;
};

#endif