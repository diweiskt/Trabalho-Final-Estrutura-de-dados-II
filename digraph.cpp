#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>

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
            std::cout << "\x1b[31mErro ao gerar arquivo do grafo.'\x1b[0m\n";
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
            std::cout << "\x1b[32m\nImagem gerada com sucesso: " << arquivoPng << "\x1b[0m\n";
        }
        else if(tipoSaida == 3){
            std::string arquivoPdf = nomeArquivoOriginal + ".pdf";
            comando = "dot -Tpdf " + arquivoDot + " -o " + arquivoPdf;
            std::cout << "\x1b[32m\nDocumento gerado com sucesso: " << arquivoPdf << "\x1b[0m\n";
        }

        if(!comando.empty()){
            std::system(comando.c_str());
        }
    }

    std::vector<node *> encontrarMenorCaminho(const T& start, const T& end)
    {
        std::vector<node *> path;

        auto pstart = find(start);
        if (!pstart)
            return path;

        auto pend = find(end);
        if (!pend)
            return path;

        std::queue<node*> q;
        std::unordered_set<node*> queued;
        std::unordered_map<node*, node*> origin;
        q.push(pstart);
        queued.insert(pstart);
        origin[pstart] = nullptr;
        bool found = false;

        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            if (current == pend){
                found = true;
                break;
            }
            for (auto adj : current->links) {
                if (queued.count(adj) == 0) {
                    q.push(adj);
                    queued.insert(adj);
                    origin[adj] = current;
                }
            }            
        }
        if(found) {
            auto p = pend;
            while(p){
                path.push_back(p);
                p = origin[p];
            }
        }
        std::reverse(path.begin(), path.end());

        return path;
    }

    void exibirCaminhoDestacado(const std::string& nomeArquivoOriginal, int tipoSaida, const std::vector<node*>& path) {
        std::string arquivoDot = nomeArquivoOriginal + "_caminho.dot";
        std::ofstream dot(arquivoDot);

        if(!dot){
            std::cout << "\x1b[31m[Erro] ao gerar arquivo do caminho.'\x1b[0m\n";
            return;
        }

        dot << "digraph{\n";

        for(auto p : path){
            if(p == path.front()){
                dot << "\t\"" << p->value << "\" [style=filled, fillcolor=limegreen];\n";
            }
            else if(p == path.back()){
                dot << "\t\"" << p->value << "\" [style=filled, fillcolor=tomato];\n";
            }
            else{
                dot << "\t\"" << p->value << "\" [style=filled, fillcolor=lightgreen];\n";
            }
        }

        for(const auto& [key, node_obj] : graph){
            if(!node_obj.links.empty()){
                for(const auto& link : node_obj.links){
                    bool ehAresta = false;
                    for(size_t i = 0; i + 1 < path.size(); ++i){
                        if(path[i]->value == key && path[i+1]->value == link->value){
                            ehAresta = true;
                            break;
                        }
                    }

                    if(ehAresta){
                        dot << "\t\"" << key << "\" -> \"" << link->value << "\" [color=red, penwidth=2.0];\n";
                    }
                    else{
                        dot << "\t\"" << key << "\" -> \"" << link->value << "\";\n";
                    }
                }
            }
            else{
                bool estaNoCaminho = false;
                for(auto p : path){
                    if(p->value == key)
                        estaNoCaminho = true;
                }
                if(!estaNoCaminho){
                    dot << "\t\"" << key << "\";\n";
                }
            }
        }
        dot << "}\n";
        dot.close();

        std::string comando = "";

        if(tipoSaida == 1){
            comando = "dot -Tx11 " + arquivoDot;
        }
        else if(tipoSaida == 2){
            std::string arquivoPng = nomeArquivoOriginal + "_caminho.png";
            comando = "dot -Tpng " + arquivoDot + " -o " + arquivoPng;
            std::cout << "\x1b[32m\nImagem gerada com sucesso: " << arquivoPng << "\x1b[0m\n";
        }
        else if(tipoSaida == 3){
            std::string arquivoPdf = nomeArquivoOriginal + "_caminho.pdf";
            comando = "dot -Tpdf " + arquivoDot + " -o " + arquivoPdf;
            std::cout << "\x1b[32m\nDocumento gerado com sucesso: " << arquivoPdf << "\x1b[0m\n";
        }

        if(!comando.empty()){
            std::system(comando.c_str());
        }
    }
};
}
