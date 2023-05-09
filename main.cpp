#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Registro
{
    map<string, int> entrada;
};

int main()
{
    int cmd = 0;
    FILE *arq;
    string fname;

    // entrada a = {"penalti", 10};
    // entrada b = {"cartao amarelo", 2};
    // vector<Registro> joao;
    // joao.push_back(Registro{a, b});

    // cout << joao[0].teste.quesito << endl;
    // cout << joao[0].teste.qtd << endl;
    map<string, int> criancaParaIndex;
    map<string, int> arquivoParaIndex;
    vector<Registro> criancas; 

    while (cmd != 4)
    {
        cout << "Digite 1 para ler um arquivo CSV" << endl
             << "Digite 2 para acessar o relatorio de uma crianca" << endl
             << "Digite 3 para acessar o relatorio de um quesito" << endl
             << "Digite 4 para sair" << endl;
        cin >> cmd;
        switch (cmd)
        {
        case 1:
            cout << "Digite o nome do arquivo csv sem a extensao: ";
            cin >> fname;

            arq = fopen((fname + ".csv").c_str(), "r");
            if (arq == NULL)
                cout << "erro abrindo o arquivo" << endl;
            else
            {
                if (arquivoParaIndex.count(fname))
                    cout << "arquivo ja carregado" << endl;
                else
                {
                    
                }

                // nameToIndex["ola"] = 0;
                // nameToIndex["oi"] = 1;
                // nameToIndex["dois"] = 2;

                // auto it = segunda.begin() + 2;
                // segunda.insert(it, {"penalti", 2});

                // joao[nameToIndex["ola"]] = {"canto", 10};
                // joao[nameToIndex["oi"]] = {"cartao amarelo", 57};

                // cout << segunda[nameToIndex["ola"]].quesito << " " << segunda[nameToIndex["ola"]].qtd << endl;
                // cout << segunda[nameToIndex["oi"]].quesito << " " << segunda[nameToIndex["oi"]].qtd << endl;
                // cout << segunda[nameToIndex["dois"]].quesito << " " << segunda[nameToIndex["dois"]].qtd << endl;
            }
            fclose(arq);
            break;
        case 2:
            // relatar criança
            break;
        case 3:
            // relatar quesito
            break;
        case 4:
            // sair
            break;

        default:
            break;
        }
    }
    return 0;
}