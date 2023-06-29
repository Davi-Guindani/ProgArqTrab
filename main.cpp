#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

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

bool isNumber(const string& s) //Funcao para verificar se uma string e um numero inteiro positivo
{
    for (char const &ch : s) {
        if (std::isdigit(ch) == 0) 
            return false;
    }
    return true;
}

void lerArquivoCSV(const string& nomeArquivo, unordered_map<string, vector<Registro>>& registros, unordered_map<string, vector<Ocorrencia>>& ocorrencias) {
    ofstream log("log.txt", ios::app); // Abre o arquivo de log em modo de anexação
    ifstream arquivo(nomeArquivo + ".csv"); //abre o arquivo 
    string linha; // usado para armazenar cada linha do arquivo
    unordered_set<string> criancas;
    int numeroLinha = 0,tamanhoVet=0;

    if (!arquivo.is_open()) { //Verifica  se foi possivel abrir o arquivo
        log << "Erro: O arquivo " << nomeArquivo << " não pode ser aberto." << endl;
        log.close();
        cout << "Erro: O arquivo " << nomeArquivo <<  " do lote de arquivos não pôde ser aberto." << endl;

    }else{

        while (getline(arquivo, linha)) { //usado para percorrer todas as linhas do arquivo
        istringstream iss(linha); //istringstream permite ler os dados como um fluxo de entrada
        string nome;
        getline(iss, nome, ',');//armazena o nome, como todas as criancas comecam com o nome e logo depois tem uma virgula, ele armazena tudo ate a primeira virgula na variavel nome
        string entrada,execucoes;
        numeroLinha++;
        if (!nome.empty()) { //verifica se o nome nao esta vazio, evita de armazenar linhas vazias ou invalidas
            if (criancas.count(nome) > 0) {// verifica se existe nome duplicado no arquivo
                log << "Erro no arquivo " << nomeArquivo << ", linha " << numeroLinha << ": Criança duplicada." << endl;
                log.close();
                arquivo.close();
                cout << "Erro: Criança duplicada. A leitura do arquivo " << nomeArquivo << " foi cancelada na linha " << numeroLinha << ". Os dados anteriores a essa linha estão disponiveis no registro." << endl;
                return;
            }
            criancas.insert(nome);
            Registro registro;
            registro.entradas.reserve(6); // Numero maximo de entradas 
            while (getline(iss, entrada, ',')) {//como feito em nome,  agora armazeno as entradas
                if(!entrada.empty()){//verifica se nao esta vazio
                    tamanhoVet = registro.entradas.size();
                    if(tamanhoVet == 0 && !isNumber(entrada)){// Se a entrada for a primeira e nao for um numero armazena no vetor
                        registro.entradas.push_back(entrada);
                    }else if(!isNumber(entrada) && !isNumber(registro.entradas[tamanhoVet-1])){ // se a entrada nao for um numero e a entrada anterior tambem nao for um numero imprime erro
                        log << "Erro no arquivo " << nomeArquivo << ", linha " << numeroLinha << ": Entrada invalida." << endl;
                        log.close();
                        arquivo.close();
                        cout << "Erro: Entrada invalida. A leitura do arquivo " << nomeArquivo << " foi cancelada na linha " << numeroLinha << endl;
                        return;
                    }else{
                        registro.entradas.push_back(entrada);
                    }
                }                     
            }
            string data = nomeArquivo.substr(0, nomeArquivo.find_first_of('.')); //armazena o nome do arquivo ate o ponto, eliminando a extensao
            registro.data = data; // extrai a data do nome do arquivo e atribui ao registro

            registros[nome].push_back(registro); //adiciona 'registro' ao mapa 'registros', usa o nome como chave agrupando todos os registros de uma mesma crianca
        }
    }

    arquivo.close(); // fecha o arquivo

    for (auto& it : registros) { // percorre o mapa, cada iteracao obtem um par chave-valor, chave eh o nome da crianca e valor o vetor de registros associados a ela
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
    }
    /* foram criandos 2 mapas um de registro para funcao gerarRelatorioPorCrianca e outro de ocorrencias para funcao gerarRelatorioPorQuesito */
}

void lerCSVEmLote(const string& nomeArquivo,unordered_map<string, vector<Registro>>& registros, unordered_map<string, vector<Ocorrencia>>& ocorrencias){
    ifstream arquivo(nomeArquivo+".txt");
    string linha;
    int numeroLinha = 0;

    ofstream log("log.txt", ios::app); // Abre o arquivo de log em modo de anexação
    if (!arquivo.is_open()) {
        log << "Erro: O arquivo " << nomeArquivo << " não pode ser aberto." << endl;
        log.close();
        cout << "Erro: O arquivo de entrada não pôde ser aberto." << endl;
        return;
    }
    while(getline(arquivo, linha)){
        lerArquivoCSV(linha,registros,ocorrencias);
    }
    cout << "Operacao finalizada com sucesso." << endl;
}


void gerarRelatorioPorCrianca(const string& nomeCrianca, const unordered_map<string, vector<Registro>>& registros) {
    auto it = registros.find(nomeCrianca); //usa o iterador para procurar em "registros" usando o nome da crianca como chave

    if (it != registros.end()) { //se encontrar o nome da crianca
        const vector<Registro>& registrosCrianca = it->second; // aponta pros registros da crianca em questao

        for (const Registro& registro : registrosCrianca) {
             if (!registro.data.empty()) {
		        cout << "Data: " << registro.data << endl;
		    }

            for (size_t i = 0; i < registro.entradas.size(); i += 2) { //percorre o vetor de 2 em 2 ja que sao pares de valores quesito e quantidade
                string quesito = registro.entradas[i]; 
                int quantidade = stoi(registro.entradas[i + 1]); // transforma o valor das entradas em inteiro "string to integer"

               cout << quesito << ": " << quantidade << endl; // imprime cada quesito da crianca em questao
            }

            cout << endl;
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
   					 if (!data.empty()) {
				        cout << "Data: " << data ;
				    }
				cout << "\nQuantidade: " << ocorrencia.quantidade << endl;    
				    
			
			cout << endl;
		    }
} else 
    cout << "Quesito nao encontrado." << endl;

}

void salvarDados(const unordered_map<string, vector<Registro>>& registros, const unordered_map<string, vector<Ocorrencia>>& ocorrencias) {
    ofstream arquivo("indice.dat"); // Abrir o arquivo em modo texto

    if (arquivo.is_open()) {
        // Salvar registros
        for (const auto& it : registros) {
            const string& crianca = it.first;
            const vector<Registro>& registrosCrianca = it.second;

            arquivo << crianca;

            for (const Registro& registro : registrosCrianca) {
                for (const string& entrada : registro.entradas) {
                    arquivo << "," << entrada;
                }
            }

            arquivo << endl;
        }

        arquivo << endl;

        // Salvar ocorrencias
        for (const auto& it : ocorrencias) {
            const string& quesito = it.first;
            const vector<Ocorrencia>& ocorrenciasQuesito = it.second;

            arquivo << quesito;

            for (const Ocorrencia& ocorrencia : ocorrenciasQuesito) {
                arquivo << "," << ocorrencia.crianca << "," << ocorrencia.quantidade;
            }

            arquivo << endl;
        }

        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo indice.dat" << endl;
    }
}

void carregarDados(unordered_map<string, vector<Registro>>& registros, unordered_map<string, vector<Ocorrencia>>& ocorrencias) {
    ifstream arquivo("indice.dat"); // Abrir o arquivo em modo texto

    registros.clear(); // Limpar registros existentes
    ocorrencias.clear(); // Limpar ocorrencias existentes

    if (arquivo.is_open()) {
        string linha;

        // Carregar registros
        while (getline(arquivo, linha) && !linha.empty()) {
            istringstream iss(linha);
            string crianca;
            getline(iss, crianca, ',');

            Registro registro;
            string entrada;
            while (getline(iss, entrada, ',')) {
                registro.entradas.push_back(entrada);
            }

            registros[crianca].push_back(registro);
        }

        // Carregar ocorrencias
        while (getline(arquivo, linha)) {
            istringstream iss(linha);
            string quesito;
            getline(iss, quesito, ',');

            Ocorrencia ocorrencia;
            string crianca;
            while (getline(iss, crianca, ',')) {
                string quantidade;
                getline(iss, quantidade, ',');
                ocorrencia.crianca = crianca;
                ocorrencia.quantidade = stoi(quantidade);
                ocorrencias[quesito].push_back(ocorrencia);
            }
        }

        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo indice.dat" << endl;
    }
}


int main() {
	//Declaracao dos mapas
	unordered_map<string, vector<Registro>> registros; 
	unordered_map<string, vector<Ocorrencia>> ocorrencias;
	
	int opcao;
	do {
        opcao = 0;
	    cout << "Menu:\n"
	              << "1 - Ler novo arquivo CSV\n"
	              << "2 - Gerar relatorio por crianca\n"
	              << "3 - Gerar relatorio por quesito\n"
	              << "4 - Processar arquivos CSV em lote\n"
	              << "5 - Salvar dados\n"
	              << "6 - Carregar dados\n"
	              << "7 - Encerrar o programa\n"
	              << "Digite a opcao: ";
	    cin >> opcao;
	
	    switch (opcao) {
	        case 1: {
	            string nomeArquivo;
	            cout << "Digite o nome do arquivo (sem a extensao): ";
	            cin >> nomeArquivo;
	            lerArquivoCSV(nomeArquivo, registros, ocorrencias);
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
                string nomeArquivo;
	            cout << "Digite o nome do arquivo txt (sem a extensao): ";
	            cin >> nomeArquivo;
	            lerCSVEmLote(nomeArquivo, registros, ocorrencias);
	            break;
	        }
	        case 5: {
	        	salvarDados(registros, ocorrencias);
	            break;
	        }
	        case 6: {
	        	carregarDados(registros, ocorrencias);
	            break;
	        }
	        case 7:
	            cout << "Encerrando o programa..." << endl;
	            break;
	        default:
	            cout << "Opcao invalida." << endl;
	            break;
	    }
	
	    cout << endl;
	} while (opcao != 7);
	
	return 0;
}
