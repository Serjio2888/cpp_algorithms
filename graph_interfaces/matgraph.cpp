#include "matgraph.h"

MatrixGraph::MatrixGraph(size_t _size) : matrix_(std::vector<std::vector<bool> >(_size)) {
    for (auto & i : matrix_) {
        i = std::vector<bool> (_size, false);
    }
}

MatrixGraph::MatrixGraph(const IGraph& gr) : matrix_(gr.VerticesCount()) {
    for ( size_t i = 0; i < matrix_.size(); ++i ) {
        std::vector<int> next_vertices = gr.GetNextVertices(i);
        for ( const auto & next : next_vertices ) {
            AddEdge(i, next);
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    matrix_[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    int amount = 0;

    std::vector<bool> visited(matrix_.size(), false);

    for ( size_t i = 0; i < matrix_.size(); ++i ) {
        for ( size_t j = 0; j < matrix_[i].size(); ++j ) {
            if ( matrix_[i][j] ) {
                if ( !visited[i] ) {
                    ++amount;
                    visited[i] = true;
                }
                if ( !visited[j] ) {
                    ++amount;
                    visited[j] = true;
                }
            }
        }
    }
    return amount;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    auto result = std::vector<int>();

    for ( size_t i = 0; i < matrix_[vertex].size(); ++i ) {
        if ( matrix_[vertex][i] ) {
            result.push_back(i);
        }
    }

    return result;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    auto result = std::vector<int>();

    for ( size_t i = 0; i < matrix_.size(); ++i ) {
        if ( matrix_[i][vertex] ) {
            result.push_back(i);
        }
    }

    return result;
}

