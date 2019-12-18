#include "arcgraph.h"

PairGraph::PairGraph(size_t vertices_count)
: v_count_(vertices_count) {}

void PairGraph::AddEdge(int from, int to) {
  pair_list_.emplace_back(std::make_pair(from, to));
}

void PairGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
  for (const auto& elem : pair_list_) {
    if (elem.first == vertex) {
      vertices.push_back(elem.second);
    }
  }
}

void PairGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
  for (const auto& elem : pair_list_) {
    if (elem.second == vertex) {
      vertices.push_back(elem.first);
    }
  }
}
