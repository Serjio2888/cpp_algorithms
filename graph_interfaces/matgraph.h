#ifndef LISTGRAPH2_H
#define LISTGRAPH2_H


#include <vector>
#include <cstdlib>

#include "graph.h"


class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(size_t _size);
    explicit MatrixGraph(const IGraph& g);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector<std::vector<bool> > matrix_;
};

#endif