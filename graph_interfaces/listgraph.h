#include <vector>
#include <vector>
#include <algorithm>
#include <queue>

struct IGraph {
    virtual ~IGraph() {}
        
        // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};



class CListGraph : public IGraph
{
public:
    explicit CListGraph( int size );
    
    virtual ~CListGraph() {}
    
    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;
    
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
    

private:
    std::vector< std::vector<int> > graph;
    int vertices_count;
};