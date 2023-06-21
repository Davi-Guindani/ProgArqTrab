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
            registro.entradas.reserve(6); // Número máximo de entradas 

            while (getline(iss, entrada, ',')) { //como feito em nome,  agora armazeno as entradas
                if (!entrada.empty()) //verifica se nao esta vazio
                    registro.entradas.push_back(entrada); //armazena no vetor
            }

            string data = nomeArquivo.substr(0, nomeArquivo.find_first_of('.')); //armazena o nome do arquivo ate o ponto, eliminando a extensao
            registro.data = data; // extrai a data do nome do arquivo e atribui ao registro

            registros[nome].push_back(registro); //adiciona 'registro' ao mapa 'registros', usa o nome como chave agrupando todos os registros de uma mesma criança
        }
    }

    arquivo.close(); // fecha o arquivo

    for (auto& it : registros) { // percorre o mapa, cada iteracao obtem um par chave-valor, chave é o nome da crianca e valor o vetor de registros associados a ela
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
    auto it = registros.find(nomeCrianca); //usa o iterador para procurar em "registros" usando o nome da criança como chave

    if (it != registros.end()) { //se encontrar o nome da criança
        const vector<Registro>& registrosCrianca = it->second; // aponta pros registros da criança em questao

        for (const Registro& registro : registrosCrianca) {
             if (!registro.data.empty()) {
		        cout << "Data: " << registro.data << endl;
		    }

            for (size_t i = 0; i < registro.entradas.size(); i += 2) { //percorre o vetor de 2 em 2 ja que sao pares de valores quesito e quantidade
                string quesito = registro.entradas[i]; 
                int quantidade = stoi(registro.entradas[i + 1]); // transforma o valor das entradas em inteiro "string to integer"

               cout << quesito << ": " << quantidade << endl; // imprime cada quesito da criança em questao
            }

            cout << endl;
        }
    } else {
        cout << "Crianca não encontrada." << endl; //caso nao entre no IF imprime isso ai
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
   					 if (!data.empty()) {
				        cout << "Data: " << data ;
				    }
				cout << "Quantidade: " << ocorrencia.quantidade << endl;    
				    
			
			cout << endl;
		    }
} else 
    cout << "Quesito nao encontrado." << endl;

}

void atualizarDados(unordered_map<string, vector<Registro>>& registros, unordered_map<string, vector<Ocorrencia>>& ocorrencias) {
    // Limpar os dados existentes
    registros.clear(); // Limpa o mapa de registros
    ocorrencias.clear(); // Limpa o mapa de ocorrencias

    ifstream arquivo("indice.dat"); // Abre o arquivo "indice.dat" para leitura
    string linha; // Variável para armazenar cada linha do arquivo

    while (getline(arquivo, linha)) { // Lê cada linha do arquivo
        istringstream iss(linha); // Cria um fluxo de string para processar cada linha
        string nome;
        getline(iss, nome, ','); // Extrai o nome da criança separado por vírgula
        string entrada;

        if (!nome.empty()) { // Verifica se o nome não está vazio
            Registro registro; // Cria um objeto Registro para armazenar os dados
            registro.entradas.reserve(6); // Reserva espaço para 6 entradas

            while (getline(iss, entrada, ',')) { // Lê as próximas entradas separadas por vírgula
                if (!entrada.empty()) // Verifica se a entrada não está vazia
                    registro.entradas.push_back(entrada); // Armazena a entrada no vetor de entradas do registro
            }

            registros[nome].push_back(registro); // Adiciona o registro ao mapa de registros usando o nome como chave
        }
    }

    arquivo.close(); // Fecha o arquivo

    for (auto& it : registros) { // Percorre o mapa de registros
        const string& crianca = it.first; // Armazena o nome da criança
        vector<Registro>& registrosCrianca = it.second; // Referência para o vetor de registros da criança

        for (const Registro& registro : registrosCrianca) { // Percorre cada registro da criança
            for (size_t i = 0; i < registro.entradas.size(); i += 2) { // Percorre o vetor de entradas de 2 em 2
                string quesito = registro.entradas[i]; // Armazena o quesito
                int quantidade = stoi(registro.entradas[i + 1]); // Converte a quantidade para inteiro

                Ocorrencia ocorrencia; // Cria um objeto Ocorrencia para agrupar os dados
                ocorrencia.crianca = crianca; // Armazena o nome da criança na ocorrencia
                ocorrencia.datas.push_back(registro.data); // Adiciona a data do registro à ocorrencia
                ocorrencia.quantidade = quantidade; // Armazena a quantidade na ocorrencia

                ocorrencias[quesito].push_back(ocorrencia); // Adiciona a ocorrencia ao mapa de ocorrencias usando o quesito como chave
            }
        }
    }

    cout << "Dados atualizados com sucesso." << endl; // Exibe mensagem de sucesso
}



int main() {
	//Declaracao dos mapas
	unordered_map<string, vector<Registro>> registros; 
	unordered_map<string, vector<Ocorrencia>> ocorrencias;
	
	int opcao;
	do {
	    cout << "Menu:\n"
	              << "1 - Ler novo arquivo CSV\n"
	              << "2 - Gerar relatorio por criança\n"
	              << "3 - Gerar relatorio por quesito\n"
	              << "4 - \n"
	              << "5 - \n"
	              << "6 - Atualizar dados\n"
	              << "7 - Encerrar o programa\n"
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
	            cin >> nomeCrianca;
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
	        case 4: {
			    break;
	        }
	        case 5: {
	            break;
	        }
	        case 6: {
	        	atualizarDados(registros, ocorrencias);
	            break;
	        }
	        case 7:
	            cout << "Encerrando o programa..." << endl;
	            break;
	        default:
	            cout << "Opção inválida." << endl;
	            break;
	    }
	
	    cout << endl;
	} while (opcao != 7);
	
	return 0;
}
