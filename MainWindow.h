#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class MainWindow : public QDialog
{
public:
    MainWindow();

private:
    bool isRegexValid();

    QLabel*    m_enterTextLabel;
    QLineEdit* m_textBox;
    QPushButton* m_computeBtn;
};

#endif // MAINWINDOW_H
