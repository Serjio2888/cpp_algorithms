#include "graph.h"


class PairGraph : public IGraph {
 public:
    explicit PairGraph(size_t vertices_count);

    void AddEdge(int from, int to) override;

    size_t VerticesCount() const override { return v_count_; }

    void GetNextVertices(int vertex, std::vector<int> &vertices) const override;

    void GetPrevVertices(int vertex, std::vector<int> &vertices) const override;
 private:
    std::vector<std::pair<int, int>> pair_list_;
    size_t v_count_;
};
