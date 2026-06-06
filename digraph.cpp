#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>

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

    void exibirGrafoCompleto(const std::string& nomeArquivoOriginal, int tipoSaida){
        std::string arquivoDot = nomeArquivoOriginal + ".dot";
        std::ofstream dot(arquivoDot);

        if(!dot){
            std::cout << "Erro ao gerar arquivo do grafo.\n";
            return;
        }

        dot << "digraph{\n";
        for (const auto& [key, node] : graph) {
            dot << "\t\"" << key << "\" -> {";
            for (const auto& link : node.links) {
                dot << "\"" << link->value << "\" ";
            }
            dot << "};\n";
        }
        dot << "}\n";
        dot.close();

        std::string comando = "";

        if(tipoSaida == 1){
            comando = "dot -Tx11 " + arquivoDot;
        }
        else if(tipoSaida == 2){
            std::string arquivoPng = nomeArquivoOriginal + ".png";
            comando = "dot -Tpng " + arquivoDot + " -o " + arquivoPng;
            std::cout << "\x1b[32mImagem gerada com sucesso: " << arquivoPng << "\x1b[0m\n";
        }
        else if(tipoSaida == 3){
            std::string arquivoPdf = nomeArquivoOriginal + ".pdf";
            comando = "dot -Tpdf " + arquivoDot + " -o " + arquivoPdf;
            std::cout << "\x1b[32mDocumento gerado com sucesso: " << arquivoPdf << "\x1b[0m\n";
        }

        if(!comando.empty()){
            std::system(comando.c_str());
        }
    }
};
}
