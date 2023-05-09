#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int cmd = 0;
    FILE *arq;
    string fname;

    vector<map<string, int>> joao;
    map<string, int> nameToIndex;

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
                if (nameToIndex.count(fname))
                    cout << "arquivo ja carregado" << endl;
                else
                {
                    nameToIndex.insert(pair<string, int>("ola", nameToIndex.size()));
                    joao.push_back(nameToIndex);
                    vector<map<string, int>>::iterator it;
                    it = joao.begin();
                    auto it1 = it->begin();
                    cout << it1->first << " " << it1->second << endl;
                }
                // map<string, int> reg;
                // reg = ("Ola", 2);
                // carregar as informações do csv no modelo
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