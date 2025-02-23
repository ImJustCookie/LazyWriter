#include <iostream>
#include <string>
#include <unistd.h>
#include <random>
#include <bits/stdc++.h>
#include <functional>

#include <QApplication>
#include <QDialog>
#include <QPushButton>

#include "lorem.hpp"
#include "Window.hpp"

// DELAY BETWEEN 2 CHARS
#define MIN_TIME_DELAY 100'000 //in micro seconds (1'000'000 equals 1 sec)
#define MAX_TIME_DELAY 200'000

//SMALL BREAK PARAMETERS BETWEEN WORDS
#define CHANCE_CHAR 150 //1 in 150
#define MIN_TIME_CHAR 100'000
#define MAX_TIME_CHAR 6'000'000

//SMALL BREAK PARAMETERS BETWEEN WORDS
#define CHANCE_WORD 30 //1 in 30
#define MIN_TIME_WORD 100'000
#define MAX_TIME_WORD 4'000'000

//VALUE FOR CHANCE OF FAILURE WHEN WRITING
#define CHANCE_TO_FAIL_WRITING 70 //1 in 70

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



int ecrireMot(string word){
    bool madeMistake = false;
    int sumOfError =0;
    int nbMoreChar = 404;
    int rand_speed = randomBetween(MIN_TIME_DELAY, MAX_TIME_DELAY);//temps entre chaque caratere pour chaque mot

    for (auto c : word){
        potentialSmallBreakTime(CHANCE_CHAR, MIN_TIME_CHAR, MAX_TIME_CHAR);//chance et temps de pause intermot

        nbMoreChar = writeWithPotentialError(CHANCE_TO_FAIL_WRITING, c);
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
    int rand_speed = randomBetween(MIN_TIME_DELAY * 2, MAX_TIME_DELAY);//temps entre chaque mot pour le 
    for (int i=0; i< word_length+1 ;i++){
        cout << '\b' << ' ' << '\b';
        cout.flush();
        usleep(rand_speed);
    }
}


void ecrireMoinsBetement(string texte){
    stringstream wordStream(texte); 
    string word;
    int nbMoreChar;
    bool madeMistake;
    vector<string> listOfWords = splitBySpace(texte);

    for (auto word : listOfWords){
        potentialSmallBreakTime(CHANCE_WORD, MIN_TIME_WORD, MAX_TIME_WORD);//chance et temps de pause extramot
        nbMoreChar = ecrireMot(word);
        if (nbMoreChar != 404){
            if (randomBetween(0,3)==0){
                supprimerMot(word.length() + nbMoreChar);
                ecrireMot(word);

            }
        }
    }
    cout << endl;


}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(400, 200);
    window.show();
    return app.exec();
}

// int main() {

//     ecrireMoinsBetement(lorem);
//     return 0;
// }


// OLD
void ecrireBetement(string texte){
    for (auto c : texte){
        cout << c;
        cout.flush();
        usleep(randomBetween(MIN_TIME_DELAY, MAX_TIME_DELAY));
    }
    cout << endl;
}
