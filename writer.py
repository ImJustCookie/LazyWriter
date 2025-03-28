from PyQt5.QtCore import QThread, pyqtSignal
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
        self.running = True
        
    def stop(self):
        self.running = False
    
    def write(self, c):
        if c == '\n':
            self.keyboard.press(Key.enter)
            self.keyboard.release(Key.enter)
            
        self.keyboard.press(c)
        self.keyboard.release(c)

    def run(self):
        # Simulate typing text with potential delays and errors
        words = self.text.split(" ")
        for word in words:
            if not self.running:
                return
            self.ecrireMot(word)

        self.finished.emit()

    def randomBetween(self, min_val, max_val):
        return random.randint(min_val, max_val)

    def potentialSmallBreakTime(self, chance, min_time, max_time):
        if self.randomBetween(0, chance) == 0:
            time.sleep(self.randomBetween(min_time, max_time) / 1000000.0)

    def writeWithPotentialError(self, chance, c):
        if self.randomBetween(0, chance) == 0:
            errorChar = chr(ord(c) + self.randomBetween(-5, 5))
            case = self.randomBetween(0, 2)

            if case == 0:  # Add an extra character
                self.write(errorChar)
                self.write(c)
                return 1
            elif case == 1:  # Replace the character
                self.write(errorChar)
                return 0
            return -1
        self.write(c)
        return 404

    def ecrireMot(self, word):
        madeMistake = False
        sumOfError = 0
        rand_speed = self.randomBetween(self.profile.minTimeDelay, self.profile.maxTimeDelay)

        for c in word:
            self.potentialSmallBreakTime(self.profile.chanceChar, self.profile.minTimeChar, self.profile.maxTimeChar)

            nbMoreChar = self.writeWithPotentialError(self.profile.chanceToFailWriting, c)
            if nbMoreChar != 404:
                madeMistake = True
                sumOfError += nbMoreChar

            time.sleep(rand_speed / 1000000.0)

        self.write(' ')

        if madeMistake:
            return sumOfError
        return 404

