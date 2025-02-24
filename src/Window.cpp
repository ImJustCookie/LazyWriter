#include "Window.hpp"

#include <QMessageBox>
#include <QTextEdit>
#include <QtCore/qfuture.h>
#include <QtConcurrent/qtconcurrentrun.h>

#include "writer.cpp"
using namespace writer;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    currentProfile = 
        new Profile{
            100'000,
            200'000,

            150,
            100'000,
            6'000'000,

            30,
            100'000,
            4'000'000,

            70,
            3,
        };

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    inputField = new QTextEdit(this);
    inputField->setPlaceholderText("Enter or paste your paragraph you want to write here...");
    inputField->setFixedHeight(150); 
    inputField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    button = new QPushButton("Write Text!", this);
    connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    QStringList options = { "Neuneu", "Normal", "HyperActif"};
    select = new QComboBox(this);
    select->addItems(options);
    select->setCurrentIndex(1);
    connect( select, &QComboBox::currentTextChanged, this, &MainWindow::selectChanged);
    

    layout->addWidget(inputField);
    layout->addWidget(button);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle("LazyWriter");
}

void MainWindow::onButtonClicked() {
    string text = inputField->toPlainText().toStdString();
    cout << select->currentText().toStdString() <<endl;
    cout.flush();
    QFuture<void> t1 = 
    QtConcurrent::run([=]() {
    ecrireMoinsBetement(text, *currentProfile);
    });
}

void MainWindow::selectChanged() {
    int optionSelected = select->currentIndex();
    switch (optionSelected)
    {
    case 0: //bete

        *currentProfile = {
            100'000,
            200'000,

            150,
            100'000,
            3'000'000,

            30,
            100'000,
            2'000'000,

            15,
            20,

        };
        break;
    
    case 1://normal

        *currentProfile = {
            100'000,
            200'000,

            150,
            100'000,
            6'000'000,

            30,
            100'000,
            4'000'000,

            70,
            3,

        };
        break;
    
    case 2://fort

        *currentProfile = {
            60'000,
            150'000,

            150,
            100'000,
            3'000'000,

            30,
            100'000,
            2'000'000,

            150,
            2,

        };
        break;

    }
}