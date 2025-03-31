from PyQt6.QtCore import QThread, pyqtSignal
from pynput.keyboard import Controller, Key
import random
import time

class Profile:
    """the class for storing the parameters of the writer :
    
    - min_time_delay/max_time_delay: the delay between two characters (in microseconds)
    
    - chance_char: the chance to make take a small break between 2 chars, it is done like so 1/x = chance to take a break
    - min_time_char/max_time_char: the delay of the small break between characters(in microseconds)
    
    - chance_word: the chance to make take a small break between 2 words, it is done like so 1/x = chance to take a break
    - min_time_word/max_time_word: the delay of the small break between words(in microseconds)
    
    - chance_to_fail_writing = the chance to fail writing the current char, it is done like so 1/x = chance to make mistake
    - chance_to_see_error = the chance to see that it has made a mistake in the word, it is done like so 1/x = chance to realize the mistake

    """
    def __init__(self, min_time_delay=100_000, max_time_delay=200_000, chance_char=150, min_time_char=100_000, max_time_char=6_000_000,
                 chance_word=30, min_time_word=100_000, max_time_word=4_000_000, chance_to_fail_writing=70, chance_to_see_error=3):
        self.min_time_delay = min_time_delay
        self.max_time_delay = max_time_delay
        self.chance_char = chance_char
        self.min_time_char = min_time_char
        self.max_time_char = max_time_char
        self.chance_word = chance_word
        self.min_time_word = min_time_word
        self.max_time_word = max_time_word
        self.chance_to_fail_writing = chance_to_fail_writing
        self.chance_to_see_error = chance_to_see_error

class WriteTask(QThread):
    """the class that inherits Qthread to create a thread that write
    the given text according to the given profile
    """
    finished = pyqtSignal() # initialize the signal to send to the main thread when finished
    
    def __init__(self, text, profile):
        super().__init__()
        self.keyboard = Controller()
        self.text = text
        self.profile = profile

    def run(self):
        """the method that is ran 
        when starting the Qthreads
        """
        self.write_text()
        self.finished.emit()


    def write_char(self, c):
        """Small utility methods
        used to write a char
        using the pynput module
        """
        if c == '\n': #return of line
            self.keyboard.press(Key.enter)
            self.keyboard.release(Key.enter)
        elif c == ' ': #space
            self.keyboard.press(Key.space)
            self.keyboard.release(Key.space)
        elif c == '\t': #tabulation
            self.keyboard.press(Key.tab)
            self.keyboard.release(Key.tab)
        else:
            self.keyboard.press(c)
            self.keyboard.release(c)

    def delete_char(self):
        """Small utility method
        used to delete a char
        using the pynput module
        """
        self.keyboard.press(Key.backspace)
        self.keyboard.release(Key.backspace)


    def random_between(self, min_val, max_val):
        """encapsulation method for obtaining a random int
        between 2 given int"""
        return random.randint(min_val, max_val)

    def potential_small_break_time(self, chance, min_time, max_time):
        """method used to take a small break when called"""
        if self.random_between(0, chance) == 0:
            time.sleep(self.random_between(min_time, max_time) / 1_000_000.0)

    def write_with_potential_error(self, chance, c):
        """the method for writing a single char given the chance
        to fail there is 3 type of error it can make :
        - case 0 : writes an extra character
        - case 1 : replaces the correct character
        - case 2 : forgets to write the correct character
        """
        if self.random_between(0, chance) == 0:
            error_char = chr(ord(c) + self.random_between(-5, 5))
            
            case = self.random_between(0, 2)
            if case == 0:  # Add an extra character
                self.write_char(error_char)
                self.write_char(c)
                return 1
            elif case == 1:  # Replace the character
                self.write_char(error_char)
                return 0
                # Case 2 jumps the character
            return -1
        # Write correctly   
        self.write_char(c)
        return 

    def write_word(self, word):
        """the methods used for writing a full word, according to the current profile
        of the Qthread
        """
        made_mistake = False
        sum_of_error = 0
        rand_speed = self.random_between(self.profile.min_time_delay, self.profile.max_time_delay)

        for c in word:
            
            if self.isInterruptionRequested():  # Check for interruption inside the loop
                print("Writing interrupted")
                return
            
            self.potential_small_break_time(self.profile.chance_char, self.profile.min_time_char, self.profile.max_time_char)

            nb_more_char = self.write_with_potential_error(self.profile.chance_to_fail_writing, c)
            if nb_more_char : # if not none then no error has been made
                made_mistake = True
                sum_of_error += nb_more_char

            time.sleep(rand_speed / 1_000_000.0)

        self.write_char(' ')

        if made_mistake:
            return sum_of_error
        return 

    def delete_word(self, word_length):
        """method for simulating the suppression of the previous word
        of length = word_length"""
        rand_speed = self.random_between(self.profile.min_time_delay * 2, self.profile.max_time_delay)  # Temps entre chaque suppression

        for _ in range(word_length + 1):
            self.delete_char()  # Efface le caractère précédent
            time.sleep(rand_speed / 1_000_000.0)  # Pause pour simuler le temps d'effacement


    def write_text(self):
        """method for simulating the writing of the entire text, according to the 
        current profile"""
        words = self.text.split(" ")

        for word in words:
            self.potential_small_break_time(self.profile.chance_word, self.profile.min_time_word, self.profile.max_time_word)
            nb_more_char = self.write_word(word)
            
            if self.isInterruptionRequested():  # Check for interruption inside the loop
                print("Writing interrupted")
                return
            
            if nb_more_char :# if not none then no error has been made
                if self.random_between(0, self.profile.chance_to_see_error) == 0:
                    self.delete_word(len(word) + nb_more_char)
                    self.write_word(word)

