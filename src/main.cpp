#include <iostream>
#include <string>
#include <unistd.h>
#include <random>
#include <bits/stdc++.h>

#include "lorem.hpp"

using namespace std;


int micro_sec_random(){
    random_device rd;

    mt19937 gen(rd());

    uniform_int_distribution<> dis(50'000, 300'000);

    return dis(gen);

}

void ecrire_betement(string texte){
    for (auto c : texte){
        cout << c;
        cout.flush();
        usleep(micro_sec_random());
    }
    cout << endl;
}


vector<string> splitBySpace(const string& input) {

    istringstream iss(input);
    vector<string> res;
    string x;
    string temp;
    char delim = ' '; 
    while (getline(iss, temp, delim)) {
        res.push_back(temp);

    }
    return res;

}

void ecrire_moins_betement(string texte){
    stringstream wordStream(texte);  
    string word;
    vector<string> listOfWords = splitBySpace(texte);

    for (auto word : listOfWords){
        int rand_speed = micro_sec_random();
        for (auto c : word){
            cout << c;
            cout.flush();
            usleep(rand_speed);
        }
        cout << ' ';
        cout.flush();
    }
    cout << endl;


}



int main() {
    //ecrire_betement(toto);
    ecrire_moins_betement(lorem);
    return 0;
}