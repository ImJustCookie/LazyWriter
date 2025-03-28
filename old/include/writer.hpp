#pragma once 

#include <string>
#include <vector>

using namespace std;

namespace writer{

    struct Profile;

    static void ecrireMoinsBetement(string texte, Profile profile);
    static void ecrireBetement(string texte, Profile profile);

    static vector<string> splitBySpace(const string& input);
    static int randomBetween(int min, int max);
    static void potentialSmallBreakTime(int chance, int min, int max);
    static int writeWithPotentialError(int chance, char c);
    static int ecrireMot(string word, Profile profile);
    static void supprimerMot(int word_length, Profile profile);

};



