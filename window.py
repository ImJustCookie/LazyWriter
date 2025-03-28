from PyQt5.QtCore import Qt, QThreadPool
from PyQt5.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QTextEdit, QPushButton, QComboBox, QSizePolicy
from writer import Profile, WriteTask
from time import sleep


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.currentProfile = Profile(
            100000, 200000, 150, 100000, 6000000, 30, 100000, 4000000, 70, 3)

        self.setMinimumSize(400, 520)

        centralWidget = QWidget(self)
        layout = QVBoxLayout(centralWidget)
        subLayout = QHBoxLayout()

        # Input field setup
        self.inputField = QTextEdit(self)
        self.inputField.setPlaceholderText("Enter or paste your paragraph here...")
        self.inputField.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.inputField.setStyleSheet(
            "QTextEdit {"
            "  background-color: #f7f7f7;"
            "  border: 1px solid #ccc;"
            "  font-size: 14px;"
            "  padding: 10px;"
            "  border-radius: 5px;"
            "}"
        )

        # Button setup
        self.button = QPushButton("Write Text!", self)
        self.button.setFixedSize(150, 40)
        self.button.setStyleSheet(
            "QPushButton {"
            "  background-color: #4CAF50;"
            "  color: white;"
            "  border: none;"
            "  border-radius: 5px;"
            "  font-size: 16px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #45a049;"
            "}"
        )
        self.button.clicked.connect(self.onButtonClicked)

        # Mode selection combobox setup
        options = ["Neuneu", "Normal", "HyperActif"]
        self.select = QComboBox(self)
        self.select.addItems(options)
        self.select.setFixedSize(140, 40)
        self.select.setCurrentIndex(1)
        self.select.setStyleSheet(
            "QComboBox {"
            "  background-color: #f7f7f7;"
            "  color : black;"
            "  border: 1px solid #ccc;"
            "  font-size: 14px;"
            "  border-radius: 5px;"
            "}"
            "QComboBox:hover {"
            "  border-color: #4CAF50;"
            "}"
        )
        self.select.currentTextChanged.connect(self.selectChanged)

        # Layout management
        subLayout.addWidget(self.select, 0, Qt.AlignLeft)
        subLayout.addWidget(self.button, 0, Qt.AlignRight)
        
        subLayout.setSpacing(20)
        layout.addLayout(subLayout)
        layout.setContentsMargins(20, 20, 20, 20)
        layout.addWidget(self.inputField)

        centralWidget.setLayout(layout) 
        self.setCentralWidget(centralWidget)

        self.setWindowTitle("LazyWriter")

        # Create QThreadPool
        self.thread_pool = QThreadPool()

    def onButtonClicked(self):
        text = self.inputField.toPlainText()
        print(self.select.currentText())
        self.button.setDisabled(True)
        sleep(3)

        # Create and submit the task to the thread pool
        task = WriteTask(text, self.currentProfile, self.onWritingFinished)
        self.thread_pool.start(task)

    def onWritingFinished(self):
        print("Writing finished!")
        self.button.setDisabled(False)

    def selectChanged(self):
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

    def closeEvent(self, event):
        self.thread_pool.clear()
        event.accept()