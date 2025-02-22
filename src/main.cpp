#include <iostream>
#include <string>
#include <unistd.h>
#include <random>
#include <bits/stdc++.h>
#include <functional>



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

int writeWithPotentialError(int chance, char c){
    if (randomBetween(0,chance)==0){

        char errorChar = 'a' + randomBetween(0, 5);
        switch (randomBetween(0,2))
        {
        case 0: //ajoute caractere en trop

            cout << errorChar;
            cout << c;
            return 1;
        
        case 1: //remplace caractere
            cout << errorChar;
            return 0;

        // case 2 saute le caractere
            
        }
        return -1;
    }

    cout << c;
    return 404;
}



int ecrireMot(string word){
    bool madeMistake = false;
    int sumOfError =0;
    int nbMoreChar = 404;
    int rand_speed = randomBetween(100'000,200'000);
    for (auto c : word){
        potentialSmallBreakTime(150, 0, 6'000'000);

        nbMoreChar = writeWithPotentialError(70, c);
        if (nbMoreChar!=404){
            madeMistake = true;
            sumOfError += nbMoreChar;
        }

        cout.flush();
        usleep(rand_speed);
    }
    cout << ' ';
    cout.flush();

    if (madeMistake){
        return sumOfError;
    }
    return 404;
}

void supprimerMot(int word_length){
    int rand_speed = randomBetween(200'000,400'000);
    for (int i=0; i< word_length+1 ;i++){
        cout << '\b' << ' ' << '\b';
        cout.flush();
        usleep(rand_speed);
    }
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
    int nbMoreChar;
    bool madeMistake;
    vector<string> listOfWords = splitBySpace(texte);

    for (auto word : listOfWords){
        potentialSmallBreakTime(30, 0, 4'000'000);
        nbMoreChar = ecrireMot(word);
        if (nbMoreChar != 404){
            if (true){
                supprimerMot(word.length() + nbMoreChar);
                ecrireMot(word);

            }
        }
    }
    cout << endl;


}



int main() {
    //ecrire_betement(lorem);
    ecrireMoinsBetement(lorem);
    return 0;
}