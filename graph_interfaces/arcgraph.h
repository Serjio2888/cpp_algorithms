
struct IGraph {
    virtual ~IGraph() {}
        
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

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
