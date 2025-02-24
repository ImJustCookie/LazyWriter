#include "Window.hpp"
#include <QMessageBox>
#include <QTextEdit>

#include "writer.cpp"
using namespace writer;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    inputField = new QTextEdit(this);
    inputField->setPlaceholderText("Enter or paste your paragraph here...");
    inputField->setFixedHeight(150); 
    inputField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    button = new QPushButton("Show Text", this);
    connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    QStringList options = { "Neuneu", "Normal", "HyperActif"};
    QComboBox* combo = new QComboBox(this);
    combo->addItems(options);
    connect( combo, &QComboBox::currentTextChanged, this, &MainWindow::selectChanged);

    layout->addWidget(inputField);
    layout->addWidget(button);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle("Qt Input and Button Window");
}

void MainWindow::onButtonClicked() {
    string text = inputField->toPlainText().toStdString();
    ecrireMoinsBetement(text);
}

void MainWindow::selectChanged() {
    QString text = inputField->toPlainText();
    QMessageBox::information(this, "Input Text", "You entered: " + text);
}