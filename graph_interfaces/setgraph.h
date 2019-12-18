
#include <cstdlib>
#include <unordered_map>
#include <vector>


struct IGraph {
    virtual ~IGraph() {}
        
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};


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