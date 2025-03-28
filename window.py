from PyQt6.QtCore import Qt, QThreadPool
from PyQt6.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QTextEdit,\
    QPushButton, QComboBox, QSizePolicy, QSplitter, QLabel
from writer import Profile, WriteTask
from time import sleep


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.currentProfile = Profile(
            100000, 200000, 150, 100000, 6000000, 30, 100000, 4000000, 70, 3)
        self.currentTask = None
        
        self.setMinimumSize(520, 520)
        self.setWindowTitle("LazyWriter")

        self.createTextInput()
        self.createStartButton()
        self.createStopButton()
        self.createSelectMenu()
        
        splitter = QSplitter(Qt.Orientation.Horizontal)
        
        button_widget = QWidget()
        button_layout = QHBoxLayout(button_widget)
        button_layout.addWidget(self.startButton, 0, Qt.AlignmentFlag.AlignRight)
        button_layout.addWidget(self.stopButton, 0, Qt.AlignmentFlag.AlignLeft)

        main_widget = QWidget()
        main_layout = QVBoxLayout(main_widget)
        main_layout.addWidget(button_widget)
        main_layout.addWidget(self.inputField)
        
        side_widget = QWidget()
        side_layout = QVBoxLayout(side_widget)
        side_title = QLabel("Parameters")
        side_title.setObjectName("title")
        side_layout.setSpacing(0)
        side_layout.addWidget(side_title, 0, Qt.AlignmentFlag.AlignTop)
        side_layout.addWidget(self.select, 0, Qt.AlignmentFlag.AlignAbsolute | Qt.AlignmentFlag.AlignTop)
        side_widget.setFixedWidth(150)
        
        
        splitter.setSizes([400, 200]) 
        splitter.addWidget(main_widget)
        splitter.addWidget(side_widget)
        
        self.setCentralWidget(splitter)

        # Create QThreadPool
        self.thread_pool = QThreadPool()

    def onStopButtonClicked(self):
        if self.currentTask and self.currentTask.isRunning():
            self.currentTask.stop()
            self.currentTask.wait()
            self.currentTask = None  # Clear reference


    def onButtonClicked(self):
        text = self.inputField.toPlainText()
        print(self.select.currentText())
        self.startButton.setDisabled(True)
        sleep(3)

        if self.currentTask and self.currentTask.isRunning():
            self.currentTask.stop()
            self.currentTask.wait()

        self.currentTask = WriteTask(text, self.currentProfile)
        self.currentTask.finished.connect(self.onWritingFinished)
        self.currentTask.start()  # Start the thread
        

    def onWritingFinished(self):
        print("Writing finished!")
        self.startButton.setDisabled(False)
        self.currentTask = None 

    def onSelectChange(self):
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

    def createTextInput(self):
        self.inputField = QTextEdit(self)
        self.inputField.setObjectName("textField")
        self.inputField.setPlaceholderText("Enter or paste your paragraph here...")
        self.inputField.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)

    def createStartButton(self):
        self.startButton = QPushButton("Write Text!", self)
        self.startButton.setObjectName("startButton")
        self.startButton.setFixedSize(150, 40)
        self.startButton.clicked.connect(self.onButtonClicked)
        
    def createStopButton(self):
        self.stopButton = QPushButton("Stop Writing", self)
        self.stopButton.setObjectName("stopButton")
        self.stopButton.setFixedSize(150, 40)
        self.stopButton.clicked.connect(self.onStopButtonClicked)

    def createSelectMenu(self):
        options = ["Neuneu", "Normal", "HyperActif"]
        self.select = QComboBox(self)
        self.select.setObjectName("selectMenu")
        self.select.addItems(options)
        self.select.setFixedSize(130, 30)
        self.select.setCurrentIndex(1)
        self.select.currentTextChanged.connect(self.onSelectChange)
