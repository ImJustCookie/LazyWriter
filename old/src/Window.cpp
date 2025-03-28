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

    setMinimumSize(400, 520); // Prevent too small windows

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QHBoxLayout *subLayout = new QHBoxLayout();

    // Input field setup
    inputField = new QTextEdit(this);
    inputField->setPlaceholderText("Enter or paste your paragraph here...");
    // inputField->setFixedHeight(400);
    inputField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Adding a bit of custom styling to the QTextEdit
    inputField->setStyleSheet(
        "QTextEdit {"
        "  background-color: #f7f7f7;"
        "  border: 1px solid #ccc;"
        "  font-size: 14px;"
        "  padding: 10px;"
        "  border-radius: 5px;"
        "}"
    );

    // Button setup
    button = new QPushButton("Write Text!", this);
    button->setFixedSize(150, 40);
    button->setStyleSheet(
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
    );
    connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    // Mode selection combobox setup
    QStringList options = { "Neuneu", "Normal", "HyperActif"};
    select = new QComboBox(this);
    select->addItems(options);
    select->setFixedSize(140,40);
    select->setCurrentIndex(1);
    select->setStyleSheet(
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
    );
    connect(select, &QComboBox::currentTextChanged, this, &MainWindow::selectChanged);

    // Layout management
    subLayout->addWidget(select,0,Qt::AlignLeft);
    subLayout->addWidget(button,0,Qt::AlignRight);
    subLayout->setSpacing(20);
    layout -> addLayout(subLayout);
    layout->setContentsMargins(20, 20, 20, 20); // Add some padding around the central widgets
    layout->addWidget(inputField);


    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    setWindowTitle("LazyWriter");
}

void MainWindow::onButtonClicked() {
    string text = inputField->toPlainText().toStdString();
    cout << select->currentText().toStdString() << endl;
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
            30'000,
            70'000,
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
