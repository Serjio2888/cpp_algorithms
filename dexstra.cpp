#include <iostream>
#include <vector>
#include <queue>

const int NUM = 50000;

class IGraph {
 public:
    explicit IGraph(size_t verticas);
    void addEdge(int from, int to, int weight);
    void bfs(int from, int to);
    ~IGraph() = default;
 private:
    std::vector<std::vector<std::pair<int, int>>> graph;
};

IGraph::IGraph(size_t verticas) : graph(verticas) {}

void IGraph::addEdge(int from, int to, int weight) {
    graph[from].push_back(std::make_pair(to, weight));
    graph[to].push_back(std::make_pair(from, weight));
}

void IGraph::bfs(int from, int to) {
    std::vector<int> current(graph.size(), NUM);
    current[from] = 0;
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>>q;
    q.push(std::make_pair(0, from));
    int itterator = 0;
    while (!q.empty()) {
        std::pair<int, int> cur = q.top();
        q.pop();
        // if (graph[cur.second] < current[cur])
        for (auto& elem : graph[cur.second]) {
            ++itterator;
            if (current[elem.first] > elem.second + current[cur.second]) {
                current[elem.first] = elem.second + current[cur.second];
                q.push(std::make_pair(current[elem.first], elem.first));
            }
        }
    }
    std::cout << "here is itterator: " << itterator << std::endl;
    std::cout << current[to] << std::endl;
}

int main() {
    int verticas, edge = 0; // N, M
    std::cin >> verticas >> edge;
    IGraph graph(verticas);
    for (int i = 0; i < edge; ++i) {
        int from, to, weight = 0;
        std::cin >> from >> to >> weight;
        graph.addEdge(from, to, weight);
    }
    int from = 0;
    int to = 0;
    std::cin >> from >> to;
    graph.bfs(from, to);
    return 0;
}
