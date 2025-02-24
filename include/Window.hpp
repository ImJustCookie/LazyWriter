#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QComboBox>
#include <QTextEdit>
#include "writer.hpp"


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    writer::Profile* currentProfile;

private slots:
    void onButtonClicked();
    void selectChanged();

private:
    QTextEdit *inputField;
    QPushButton *button;
    QComboBox *select;


};

