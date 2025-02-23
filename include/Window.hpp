
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QComboBox>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();
    void selectChanged();

private:
    QLineEdit *inputField;
    QPushButton *button;
    QComboBox *select;
};

#endif // MAINWINDOW_HPP
