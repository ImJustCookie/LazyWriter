#pragma once 

#include <string>
#include <vector>

using namespace std;

namespace writer{

    static void ecrireMoinsBetement(string texte);
    static void ecrireBetement(string texte);

    static void supprimerMot(string texte);
    static vector<string> splitBySpace(const string& input);
    static int randomBetween(int min, int max);
    static void potentialSmallBreakTime(int chance, int min, int max);
    static int writeWithPotentialError(int chance, char c);
    static int ecrireMot(string word);
    static void supprimerMot(int word_length);

};



