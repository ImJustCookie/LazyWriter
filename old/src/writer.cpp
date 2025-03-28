#include <iostream>
#include <string>
#include <unistd.h>
#include <random>
#include <bits/stdc++.h>
#include <functional>

#include "writer.hpp"

using namespace std;


struct writer::Profile {
    // Delay between two characters (in microseconds)
    unsigned int minTimeDelay = 100'000; // 1'000'000 equals 1 sec
    unsigned int maxTimeDelay = 200'000;

    // Small break parameters between characters
    unsigned int chanceChar = 150;      // 1 in 150
    unsigned int minTimeChar = 100'000;
    unsigned int maxTimeChar = 6'000'000;

    // Small break parameters between words
    unsigned int chanceWord = 30;       // 1 in 30
    unsigned int minTimeWord = 100'000;
    unsigned int maxTimeWord = 4'000'000;

    // Chance of failure when writing
    unsigned int chanceToFailWriting = 70; // 1 in 70
    unsigned int chanceToSeeError = 3;
};


int writer::randomBetween(int min, int max){
    random_device rd;

    mt19937 gen(rd());

    uniform_int_distribution<> dis(min, max);

    return dis(gen);

}

vector<string> writer::splitBySpace(const string& input) {

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

void writer::potentialSmallBreakTime(int chance, int min, int max){
    if (writer::randomBetween(0,chance)==0){
        usleep(writer::randomBetween(min,max));
    }
}

int writer::writeWithPotentialError(int chance, char c){
    if (writer::randomBetween(0,chance)==0){

        char errorChar = c + randomBetween(-5, 5);
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



int writer::ecrireMot(string word, Profile profile){
    bool madeMistake = false;
    int sumOfError =0;
    int nbMoreChar = 404;
    int rand_speed = randomBetween(profile.minTimeDelay, profile.maxTimeDelay);//temps entre chaque caratere pour chaque mot

    for (auto c : word){
        potentialSmallBreakTime(profile.chanceChar, profile.minTimeChar, profile.maxTimeChar);//chance et temps de pause intermot

        nbMoreChar = writeWithPotentialError(profile.chanceToFailWriting, c);
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

void writer::supprimerMot(int word_length, Profile profile){
    int rand_speed = randomBetween(profile.minTimeDelay * 2, profile.maxTimeDelay);//temps entre chaque mot pour le 
    for (int i=0; i< word_length+1 ;i++){
        cout << '\b' << ' ' << '\b';
        cout.flush();
        usleep(rand_speed);
    }
}


void writer::ecrireMoinsBetement(string texte, Profile profile){
    stringstream wordStream(texte); 
    string word;
    int nbMoreChar;
    bool madeMistake;
    vector<string> listOfWords = splitBySpace(texte);

    for (auto word : listOfWords){
        potentialSmallBreakTime(profile.chanceWord, profile.minTimeWord, profile.maxTimeWord);//chance et temps de pause extramot
        nbMoreChar = ecrireMot(word, profile);
        if (nbMoreChar != 404){
            if (randomBetween(0,profile.chanceToSeeError)==0){
                supprimerMot(word.length() + nbMoreChar, profile);
                ecrireMot(word, profile);

            }
        }
    }
    cout << endl;


}


// OLD
void writer::ecrireBetement(string texte, Profile profile){
    for (auto c : texte){
        cout << c;
        cout.flush();
        usleep(randomBetween(profile.minTimeDelay, profile.maxTimeDelay));
    }
    cout << endl;
}
