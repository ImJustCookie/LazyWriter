#include "Window.hpp"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Enter text here");

    button = new QPushButton("Show Text", this);
    connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    QStringList options = { "Q", "W", "E", "R" };
    QComboBox* combo = new QComboBox(this);
    combo->addItems(options);
    connect( combo, &QComboBox::currentTextChanged, this, &MainWindow::selectChanged);

    // layout-> addWidget(combo);
    layout->addWidget(inputField);
    layout->addWidget(button);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle("Qt Input and Button Window");
}

void MainWindow::onButtonClicked() {
    QString text = inputField->text();
    QMessageBox::information(this, "Input Text", "You entered: " + text);
}

void MainWindow::selectChanged() {
    QString text = inputField->text();
    QMessageBox::information(this, "Input Text", "You entered: " + text);
}