#include <vector>
#include <vector>
#include <algorithm>
#include <queue>


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