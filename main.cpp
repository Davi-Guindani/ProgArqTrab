#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
    int cmd = 0;
    FILE *arq;
    string fname;
    map<string, int> joao;
    joao["oi"] = 10;
    joao["ola"] = 8;
    map<string, int>::iterator it = joao.begin();
    while (it != joao.end())
    {
        cout << it->first;
        cout << it->second;
        it++;
    }
    

    // while (cmd != 4)
    // {
    //     cout << "Digite 1 para ler um arquivo CSV" << endl
    //          << "Digite 2 para acessar o relatorio de uma crianca" << endl
    //          << "Digite 3 para acessar o relatorio de um quesito" << endl
    //          << "Digite 4 para sair" << endl;
    //     cin >> cmd;
    //     switch (cmd)
    //     {
    //     case 1:
    //         cout << "Digite o nome do arquivo csv sem a extensao: ";
    //         cin >> fname;
    //         fname += ".csv";
    //         arq = fopen(fname.c_str(), "r");
    //         if (arq == NULL)
    //             cout << "erro abrindo o arquivo" << endl;
    //         else
    //         {
    //             // map<string, int> reg;
    //             // reg = ("Ola", 2);
    //             // carregar as informações do csv no modelo
    //         }

    //         break;
    //     case 2:
    //         // relatar criança
    //         break;
    //     case 3:
    //         // relatar quesito
    //         break;
    //     case 4:
    //         // sair
    //         fclose(arq);
    //         break;

    //     default:
    //         break;
    //     }
    // }
    return 0;
}