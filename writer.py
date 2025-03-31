from PyQt6.QtCore import QThread, pyqtSignal
from pynput.keyboard import Controller, Key
import random
import time

class Profile:
    def __init__(self, minTimeDelay=100000, maxTimeDelay=200000, chanceChar=150, minTimeChar=100000, maxTimeChar=6000000,
                 chanceWord=30, minTimeWord=100000, maxTimeWord=4000000, chanceToFailWriting=70, chanceToSeeError=3):
        self.minTimeDelay = minTimeDelay
        self.maxTimeDelay = maxTimeDelay
        self.chanceChar = chanceChar
        self.minTimeChar = minTimeChar
        self.maxTimeChar = maxTimeChar
        self.chanceWord = chanceWord
        self.minTimeWord = minTimeWord
        self.maxTimeWord = maxTimeWord
        self.chanceToFailWriting = chanceToFailWriting
        self.chanceToSeeError = chanceToSeeError

class WriteTask(QThread):
    finished = pyqtSignal()
    
    def __init__(self, text, profile):
        super().__init__()
        self.keyboard = Controller()
        self.text = text
        self.profile = profile

    def write_char(self, c):
        if c == '\n':
            self.keyboard.press(Key.enter)
            self.keyboard.release(Key.enter)
        elif c == ' ':
            self.keyboard.press(Key.space)
            self.keyboard.release(Key.space)
        elif c == '\t':
            self.keyboard.press(Key.tab)
            self.keyboard.release(Key.tab)
        else:
            self.keyboard.press(c)
            self.keyboard.release(c)

    def delete_char(self):
        self.keyboard.press(Key.backspace)
        self.keyboard.release(Key.backspace)

    def run(self):
        self.ecrire_texte()
        self.finished.emit()

    def random_between(self, min_val, max_val):
        return random.randint(min_val, max_val)

    def potential_small_break_time(self, chance, min_time, max_time):
        if self.random_between(0, chance) == 0:
            time.sleep(self.random_between(min_time, max_time) / 1000000.0)

    def write_with_potential_error(self, chance, c):
        if self.random_between(0, chance) == 0:
            errorChar = chr(ord(c) + self.random_between(-5, 5))
            
            case = self.random_between(0, 2)
            if case == 0:  # Add an extra character
                self.write_char(errorChar)
                self.write_char(c)
                return 1
            elif case == 1:  # Replace the character
                self.write_char(errorChar)
                return 0
                # Case 2 jumps the character
            return -1
        # Write correctly   
        self.write_char(c)
        return 404

    def ecrire_mot(self, word):
        madeMistake = False
        sumOfError = 0
        rand_speed = self.random_between(self.profile.minTimeDelay, self.profile.maxTimeDelay)

        for c in word:
            if self.isInterruptionRequested():  # Check for interruption inside the loop
                print("Writing interrupted")
                return
            self.potential_small_break_time(self.profile.chanceChar, self.profile.minTimeChar, self.profile.maxTimeChar)

            nbMoreChar = self.write_with_potential_error(self.profile.chanceToFailWriting, c)
            if nbMoreChar != 404:
                madeMistake = True
                sumOfError += nbMoreChar

            time.sleep(rand_speed / 1000000.0)

        self.write_char(' ')

        if madeMistake:
            return sumOfError
        return 404

    def supprimer_mot(self, word_length):
        """Simule la suppression d'un mot en effaçant les caractères un par un."""
        rand_speed = self.random_between(self.profile.minTimeDelay * 2, self.profile.maxTimeDelay)  # Temps entre chaque suppression

        for _ in range(word_length + 1):
            self.delete_char()  # Efface le caractère précédent
            time.sleep(rand_speed / 1_000_000.0)  # Pause pour simuler le temps d'effacement


    def ecrire_texte(self):
        """Simule l'écriture d'un texte avec des erreurs et corrections possibles."""
        mots = self.text.split(" ")

        for mot in mots:
            self.potential_small_break_time(self.profile.chanceWord, self.profile.minTimeWord, self.profile.maxTimeWord)
            nb_more_char = self.ecrire_mot(mot)
            
            if self.isInterruptionRequested():  # Check for interruption inside the loop
                print("Writing interrupted")
                return
            if nb_more_char != 404:
                if self.random_between(0, self.profile.chanceToSeeError) == 0:
                    print ("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")
                    self.supprimer_mot(len(mot) + nb_more_char)
                    self.ecrire_mot(mot)

