#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

struct Registro
{
    string fundamento;
    string qtd;
};

int main()
{
    int cmd = 0;
    ifstream arq;
    string fname;

    map<string, int> criancaParaIndex;
    map<string, int> arqParaIndex;

    vector<vector<map<string, string>>> criancas;
    vector<vector<map<string, string>>>::iterator it1;

    vector<map<string, string>> crianca;
    vector<map<string, string>>::iterator it2;
    
    map<string, string> reg;
    map<string, string>::iterator it3;

    while (cmd != 4)
    {
        string nome;
        string fundamento;
        string qtd;

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
            fname += ".csv";

            arq.open(fname.c_str());
            if (!arq.is_open())
                cout << "erro abrindo o arquivo" << endl;
            else
            {
                fname.erase(fname.end() - 4, fname.end());

                if (!arqParaIndex.count(fname))
                {
                    arqParaIndex[fname] = arqParaIndex.size();
                }

                getline(arq, nome, ',');
                getline(arq, fundamento, ',');
                getline(arq, qtd, ',');

                if (!criancaParaIndex.count(nome))
                {
                    criancaParaIndex[nome] = criancaParaIndex.size();
                }

                reg[fundamento] = qtd;

                crianca.insert(crianca.begin() + arqParaIndex[fname] - 1, reg);
                criancas.insert(criancas.begin() + criancaParaIndex[nome] - 1, crianca);

                for (it1 = criancas.begin(); it1 != criancas.end(); it1++)
                {
                    for (it2 = it1->begin(); it2 != it1->end(); it2++)
                    {
                        for (it3 = it2->begin(); it3 != it2->end(); it3++)
                        {
                            cout << it3->first << " " << it3->second << endl;
                        }
                    }
                }
            }
            arq.close();
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