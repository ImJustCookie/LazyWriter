from time import sleep
from PyQt6.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QTextEdit,\
    QPushButton, QComboBox, QSizePolicy, QSplitter, QLabel
from PyQt6.QtCore import Qt, QThreadPool
from lazy_writer_raphael_senellart.writer import Profile, WriteTask


class MainWindow(QMainWindow):
    """The class that inherit Qt mainwindow to create a ui for the writer"""
    def __init__(self):
        super().__init__()

        self.currentProfile = Profile()
        self.currentTask = None

        self.setMinimumSize(520, 520)
        self.setWindowTitle("LazyWriter ")

        self.createTextInput()
        self.createStartButton()
        self.createStopButton()
        self.createSelectMenu()

        splitter = QSplitter(Qt.Orientation.Horizontal)

        # the widget of the button in a horizontal box
        button_widget = QWidget()
        button_layout = QHBoxLayout(button_widget)
        button_layout.addWidget(self.startButton, 0, Qt.AlignmentFlag.AlignRight)
        button_layout.addWidget(self.stopButton, 0, Qt.AlignmentFlag.AlignLeft)

        # the main widget with the button and text widgets in a vertical box
        main_widget = QWidget()
        main_layout = QVBoxLayout(main_widget)
        main_layout.addWidget(button_widget)
        main_layout.addWidget(self.inputField)

        # the side widget in a vertical box with the parameters
        side_widget = QWidget()
        side_layout = QVBoxLayout(side_widget)
        side_title = QLabel("Parameters")
        side_title.setObjectName("title")
        side_layout.setSpacing(0)
        side_layout.addWidget(side_title, 0, Qt.AlignmentFlag.AlignTop)
        side_layout.addWidget(self.select, 0, Qt.AlignmentFlag.AlignTop)
        side_widget.setFixedWidth(150)

        #the main splitter that takes the main widget and side widget
        splitter.setSizes([400, 200]) 
        splitter.addWidget(main_widget)
        splitter.addWidget(side_widget)

        self.setCentralWidget(splitter)

        # Create the QThreadPool used for writing
        self.thread_pool = QThreadPool()

    def createTextInput(self):
        """method that create the text input"""
        self.inputField = QTextEdit(self)
        self.inputField.setObjectName("textField")
        self.inputField.setPlaceholderText("Enter or paste your paragraph here...")
        self.inputField.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)

    def createStartButton(self):
        """method that create the start button"""

        self.startButton = QPushButton("Write Text!", self)
        self.startButton.setObjectName("startButton")
        self.startButton.setFixedSize(150, 40)
        self.startButton.clicked.connect(self.onStartButtonClicked)

    def createStopButton(self):
        """method that create the stop button"""

        self.stopButton = QPushButton("Stop Writing", self)
        self.stopButton.setObjectName("stopButton")
        self.stopButton.setFixedSize(150, 40)
        self.stopButton.clicked.connect(self.onStopButtonClicked)

    def createSelectMenu(self):
        """method that create the dropdown menu for profiles"""

        options = ["Neuneu", "Normal", "HyperActif"]
        self.select = QComboBox(self)
        self.select.setObjectName("selectMenu")
        self.select.addItems(options)
        self.select.setFixedSize(130, 30)
        self.select.setCurrentIndex(1)
        self.select.currentTextChanged.connect(self.onSelectChange)


    def onStopButtonClicked(self):
        """the method launched by the stop button"""
        if self.currentTask and self.currentTask.isRunning():
            self.currentTask.requestInterruption()  # Request interruption
            self.currentTask.wait()  # Wait for the thread to finish
            self.currentTask = None  # Clear reference

    def onStartButtonClicked(self):
        """the method launched by the start button"""

        text = self.inputField.toPlainText()
        print(self.select.currentText())
        self.startButton.setDisabled(True)
        sleep(3)

        if self.currentTask and self.currentTask.isRunning():
            self.currentTask.stop()
            self.currentTask.wait()

        self.currentTask = WriteTask(text, self.currentProfile)
        self.currentTask.finished.connect(self.onWritingFinished)#connected the eventlistener
        self.currentTask.start()  # Start the thread

    def onWritingFinished(self):
        """ the method called when the writing thread is done"""
        print("Writing finished!")
        self.startButton.setDisabled(False)
        self.currentTask = None 

    def onSelectChange(self):
        """ the method to change the profile according to the selected item in the dropdown"""
        optionSelected = self.select.currentIndex()
        if optionSelected == 0:  # Neuneu
            self.currentProfile = Profile(
                100000, 200000, 150, 100000, 3000000, 30, 100000, 2000000, 15, 20)
        elif optionSelected == 1:  # Normal
            self.currentProfile = Profile(
                100000, 200000, 150, 100000, 6000000, 30, 100000, 4000000, 70, 3)
        elif optionSelected == 2:  # HyperActif
            self.currentProfile = Profile(
                30000, 70000, 150, 100000, 3000000, 30, 100000, 2000000, 150, 2)

