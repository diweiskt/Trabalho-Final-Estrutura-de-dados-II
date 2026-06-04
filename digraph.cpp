#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace UPF {

template <typename T>
class digraph {
private:
    struct node {
        T value;
        std::unordered_set<node*> links;
    };

    std::unordered_map<T, node> graph;

    node* find(const T& val)
    {
        auto it = graph.find(val);
        if (it == graph.end()) { // Not found!
            return nullptr;
        }
        return &it->second;
    }

public:
    void insert_node(const T& val)
    {
        if (graph.count(val) != 0)
            return;
        node aux;
        aux.value = val;
        graph[val] = aux;
    }

    void insert_link(const T& from, const T& to)
    {
        auto pfrom = find(from);
        if (!pfrom)
            return;
        auto pto = find(to);
        if (!pto)
            return;

        pfrom->links.insert(pto);
    }

    //funçoes de contagem
    int qtdVertices() const {
        return graph.size();
    }

    int qtdArestas() const {
        int total = 0;
        for (const auto& [key, node] : graph) {
            total += node.links.size();
        }
        return total;
    }
};
}
