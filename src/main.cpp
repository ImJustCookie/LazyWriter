#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;


void ecrire_betement(string texte){
    for (auto c : texte){
        cout << c;
        cout.flush();
        usleep(100'000);
    }
    cout << endl;
}


int main() {

    string toto ="miam miam \ndes chocolats";

    ecrire_betement(toto);
    return 0;
}