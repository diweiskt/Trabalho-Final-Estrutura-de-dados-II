// Diwei V. Nicolay - 193014

#include "digraph.cpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int menu(){
    int opcao;
    while (true) {
        cout << "\n======================================================\n"
             << "\x1b[31m1\x1b[0m. Exibir Grafo Completo\n"
             << "\x1b[31m2\x1b[0m. Encontrar Menor Caminho\n"
             << "\x1b[31m3\x1b[0m. Calcular o Diâmetro do Grafo\n"
             << "\x1b[31m4\x1b[0m. Identificar Roteadores Críticos\n"
             << "\x1b[31m0\x1b[0m. Sair\n"
             << "======================================================\n"
             << "Escolha uma opção: ";
        cin >> opcao;
        cout << endl;
        cin.ignore(); 
        if (opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 0) {
            return opcao;
        }
        cout << "\x1b[31mOpção inválida. Tente novamente.\n";
    }
}

int subMenuSaida(const string& titulo){
    int subOpcao;
    cout << "\x1b[36m\n" << titulo << "\x1b[0m\n"
         << "\x1b[31m1\x1b[0m. Tela\n"
         << "\x1b[31m2\x1b[0m. Imagem (PNG)\n"
         << "\x1b[31m3\x1b[0m. Documento (PDF)\n"
         << "Opção: ";
    cin >> subOpcao;
    cin.ignore();
    return subOpcao;
}

void path(UPF::digraph<string>& rede, const string& nomeArquivoOriginal){
    string origem,destino;

    cout << "Digite o IP de Origem: ";
    cin >> origem;
    cout << "Digite o IP de Destino: ";
    cin >> destino;

    auto path = rede.encontrarMenorCaminho(origem, destino);
    if (path.empty()) {
        cout << "\n\x1b[31mNenhum caminho encontrado\x1b[0m\n";
    }
    else {
        cout << "\n\x1b[32mCaminho encontrado (" << path.size() - 1 << " saltos):\x1b[0m\n";

        bool primeiro = true;

        for (auto p : path){
            if(!primeiro)
                cout << "\x1b[32m -> \x1b[0m";
            cout << "\x1b[32m" << p->value << "\x1b[0m";
            primeiro = false;
        }
        cout << "\n";

        int subOpcao = subMenuSaida("Selecione o formato de saída do Graphviz:");

        if(subOpcao >= 1 && subOpcao <= 3){
            rede.exibirCaminhoDestacado(nomeArquivoOriginal, subOpcao, path);
        }
        else{
            cout << "\x1b[31m\nOpção Inválida.\x1b[0m\n";
        }
    }
}


int main(int argc, char* argv[]){

    if(argc != 2){
        cout << "\x1b[31m[Erro] Você não passou um caminho de um arquivo de log de traceroute\x1b[0m\n";
        return 1;
    }

    ifstream arq;
    arq.open(argv[1]);
    if(!arq){
        cout << "\x1b[31m[Erro] Não foi possivel abrir o arquivo \x1b[34m'" << argv[1] << "'\x1b[0m\n";
        return 1;
    }

    UPF::digraph<string> rotas;
    string linha;
    getline(arq, linha);

    while(getline(arq,linha)){
        stringstream ss(linha);
        string prb_id, probe_src, dst_addr, hop, hop_from, hop_to, rtt;

        getline(ss, prb_id, ',');
        getline(ss, probe_src, ',');
        getline(ss, dst_addr, ',');
        getline(ss, hop, ',');
        getline(ss, hop_from, ',');
        getline(ss, hop_to, ',');
        getline(ss, rtt, ',');

        if(hop_to=="*"||hop_from==""||hop_to==""){
            continue;
        }
        rotas.insert_node(hop_from);
        rotas.insert_node(hop_to);
        rotas.insert_link(hop_from, hop_to);
    }

    arq.close();

    cout << "\n\x1b[32mGrafo de roteamento inicializado!\x1b[0m\n"
         << "Vértices únicos (IPs): " << rotas.qtdVertices()
         << " | Arestas: " << rotas.qtdArestas() << "\n";

    int opcao;

    do {
        opcao = menu();
        int subOpcao;

        switch (opcao) {
        case 1:
            subOpcao =  subMenuSaida("Selecione o formato de saída do Graphviz:");

            if(subOpcao >= 1 && subOpcao <= 3){
                rotas.exibirGrafoCompleto(argv[1], subOpcao);
            }
            else{
                cout << "\x1b[31m\nOpção Inválida.\x1b[0m\n";
            }
            break;
        case 2:
            path(rotas, argv[1]);
            break;
        case 3:
            rotas.calcularDiametroGrafo();
            break;
        case 4:
            //identificarRoteadoresCriticos();
            break;
        case 0:
            cout << "\x1b[31mEncerrando analisador de rotas.\x1b[0m\n\n";
            break;
        }
    } while (opcao != 0);

    return 0;
}