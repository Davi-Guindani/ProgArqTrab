#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Registro {
   string data;
    vector<string> entradas;
};

struct Ocorrencia {
    string crianca;
   vector<string> datas;
    int quantidade;
};

void lerArquivoCSV(const string& nomeArquivo, unordered_map<string, vector<Registro>>& registros, unordered_map<string, vector<Ocorrencia>>& ocorrencias) {
    ifstream arquivo(nomeArquivo + ".csv"); //abre o arquivo 
    string linha; // usado para armazenar cada linha do arquivo

    while (getline(arquivo, linha)) { //usado para percorrer todas as linhas do arquivo
        istringstream iss(linha); //istringstream permite ler os dados como um fluxo de entrada
        string nome;
        getline(iss, nome, ',');//armazena o nome, como todas as criancas comecam com o nome e logo depois tem uma virgula, ele armazena tudo ate a primeira virgula na variavel nome
        string entrada;

        if (!nome.empty()) { //verifica se o nome nao esta vazio, evita de armazenar linhas vazias ou invalidas
            Registro registro;
            registro.entradas.reserve(6); // Numero maximo de entradas

            while (getline(iss, entrada, ',')) { //como feito em nome,  agora armazeno as entradas
                if (!entrada.empty()) //verifica se nao esta vazio
                    registro.entradas.push_back(entrada); //armazena no vetor
            }

            string data (nomeArquivo.substr(0, nomeArquivo.find_first_of('.'))); //armazena o nome do arquivo ate o ponto, eliminando a extensao
            data.insert(2,"/");
            data.insert(5,"/");
            registro.data = data; // extrai a data do nome do arquivo e atribui ao registro

            registros[nome].push_back(registro); //adiciona 'registro' ao mapa 'registros', usa o nome como chave agrupando todos os registros de uma mesma crianca
        }
    }

    arquivo.close(); // fecha o arquivo

    for (auto& it : registros) { // percorre o mapa, cada iteracao obtem um par chave-valor, chave � o nome da crianca e valor o vetor de registros associados a ela
        const string& crianca = it.first; //armazena o nome da crianca
        vector<Registro>& registrosCrianca = it.second; //referencia para o vetor de registros

        for (const Registro& registro : registrosCrianca) { //iteracao sobre cada registro de cada crianca 
            for (size_t i = 0; i < registro.entradas.size(); i += 2) { //percorre o vetor associado a cada uma onde esta cada entrada. Pula de 2 em 2 pois sao pares de informacao aramzenados no vetor
                string quesito = registro.entradas[i]; 
                int quantidade = stoi(registro.entradas[i + 1]);   //stoi converte string pra inteiro

                Ocorrencia ocorrencia; //objeto para agrupar dessa vez por quesito, usa o quesito como chave 
                ocorrencia.crianca = crianca;
                ocorrencia.datas.push_back(registro.data);
                ocorrencia.quantidade = quantidade;

                ocorrencias[quesito].push_back(ocorrencia);
            }
        }
    }
    /* foram criandos 2 mapas um de registro para funcao gerarRelatorioPorCrianca e outro de ocorrencias para funcao gerarRelatorioPorQuesito */
}


void gerarRelatorioPorCrianca(const string& nomeCrianca, const unordered_map<string, vector<Registro>>& registros) {
    auto it = registros.find(nomeCrianca); //usa o iterador para procurar em "registros" usando o nome da crianca como chave

    if (it != registros.end()) { //se encontrar o nome da criança
        const vector<Registro>& registrosCrianca = it->second; // aponta pros registros da criança em questao
        cout << "Relatorio de " << nomeCrianca << ":\n";
        for (const Registro& registro : registrosCrianca) {
            cout << "Data: " << registro.data << endl; // imprime a data que e o nome do arquivo

            for (size_t i = 0; i < registro.entradas.size(); i += 2) { //percorre o vetor de 2 em 2 ja que sao pares de valores quesito e quantidade
                string quesito = registro.entradas[i]; 
                int quantidade = stoi(registro.entradas[i + 1]); // transforma o valor das entradas em inteiro "string to integer"

               cout << quesito << ": " << quantidade << endl; // imprime cada quesito da criança em questao
            }
        }
    } else {
        cout << "Crianca nao encontrada." << endl; //caso nao entre no IF imprime isso ai
    }
}

void gerarRelatorioPorQuesito(const string& quesito, const unordered_map<string, vector<Ocorrencia>>& ocorrencias) {
    auto it = ocorrencias.find(quesito);//usa o iterador para procurar em "ocorrencias" usando o quesito como chave

    if (it != ocorrencias.end()) { //se ele nao estivar no final, entra nesse if
        const vector<Ocorrencia>& ocorrenciasQuesito = it->second; //aponta para as ocorrencias do quesito

       	for (const Ocorrencia& ocorrencia : ocorrenciasQuesito) { //percorre cada ocorrencia no vetor e imprime o nome das criancas
			cout << "Crianca: " << ocorrencia.crianca << endl;
			
			for (const string& data : ocorrencia.datas)
				for (const string& data : ocorrencia.datas)
   					cout << "Data: " << data << ", Quantidade: " << ocorrencia.quantidade << endl;
		}
} else 
    cout << "Quesito nao encontrado." << endl;

}

int main() {
	//Declaracao dos mapas
	unordered_map<string, vector<Registro>> registros; 
	unordered_map<string, vector<Ocorrencia>> ocorrencias;
	int opcao;
	do {
            cout << "Menu:\n"
                    << "1 - Ler novo arquivo CSV\n"
                    << "2 - Gerar relatorio por crianca\n"
                    << "3 - Gerar relatorio por quesito\n"
                    << "4 - Encerrar o programa\n"
                    << "Digite a opcao: ";
            cin >> opcao;
            switch (opcao) {
                case 1: {
                    string nomeArquivo;
                    cout << "Digite o nome do arquivo (sem a extensao): ";
                    cin >> nomeArquivo;
                    lerArquivoCSV(nomeArquivo, registros, ocorrencias);
                    cout << "Arquivo lido e processado com sucesso." << endl;
                    break;
                }
                case 2: {
                    string nomeCrianca;
                    cout << "Digite o nome da crianca: ";
                    cin.ignore(); // Limpar o buffer do teclado
                    getline(cin,nomeCrianca);
                    cout << endl;
                    gerarRelatorioPorCrianca(nomeCrianca, registros);
                    break;
                }
                case 3: {
                    string quesito;
                    cout << "Digite o quesito: ";
                    cin.ignore(); // Limpar o buffer do teclado
                    cin >> quesito;
                    cout << endl;
                    gerarRelatorioPorQuesito(quesito, ocorrencias);
                    break;
                }
                case 4:
                    cout << "Encerrando o programa..." << endl;
                    break;
                default:
                    cout << "Opcao invalida." << endl;
                    break;
            }
            cout << endl;
        }while (opcao != 4);
	return 0;
}
