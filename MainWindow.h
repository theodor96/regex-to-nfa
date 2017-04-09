#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <memory>

class QLabel;
class QLineEdit;
class QPushButton;

class Canvas;

class MainWindow : public QDialog
{
public:
    MainWindow();

    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow(MainWindow&&) = delete;
    MainWindow& operator=(MainWindow&&) = delete;

private:
    bool isRegexValid();

    QLabel*      m_enterTextLabel;
    QLineEdit*   m_textBox;
    QPushButton* m_computeBtn;

    std::unique_ptr<Canvas> m_canvas;
};

#endif // MAINWINDOW_H
