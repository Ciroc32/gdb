#include <iostream>
#include <string>

using namespace std;

int main()
{
    string password = "::blank::";
    string buffer;
    cout << "Entrez le mot de passe :\n";
    cin >> buffer;

    if(buffer == password)
    {
        cout << "Le mot de passe est correct" << endl;
    }
    else
    {
        cout << "Mot de passe incorrect" << endl;
    }
}