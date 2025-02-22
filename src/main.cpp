#include <iostream>
#include <string>
#include <unistd.h>
#include <random>
#include <bits/stdc++.h>

#include "lorem.hpp"

using namespace std;


int randomBetween(int min, int max){
    random_device rd;

    mt19937 gen(rd());

    uniform_int_distribution<> dis(min, max);

    return dis(gen);

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

void potentialSmallBreakTime(int chance, int min, int max){
    if (randomBetween(0,chance)==0){
        usleep(randomBetween(min,max));
    }
}




void ecrireMot(string word){
    int rand_speed = randomBetween(100'000,200'000);
    for (auto c : word){
        potentialSmallBreakTime(80, 0, 6'000'000);
        cout << c;
        cout.flush();
        usleep(rand_speed);
    }
    cout << ' ';
    cout.flush();
}


void ecrireBetement(string texte){
    for (auto c : texte){
        cout << c;
        cout.flush();
        usleep(randomBetween(100'000,200'000));
    }
    cout << endl;
}

void ecrireMoinsBetement(string texte){
    stringstream wordStream(texte);  
    string word;
    vector<string> listOfWords = splitBySpace(texte);

    for (auto word : listOfWords){
        potentialSmallBreakTime(30, 0, 4'000'000);
        ecrireMot(word);
    }
    cout << endl;


}



int main() {
    //ecrire_betement(lorem);
    ecrireMoinsBetement(lorem);
    return 0;
}