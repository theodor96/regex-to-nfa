#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "Canvas.h"
#include "Utils.h"

class QLabel;
class QLineEdit;
class QPushButton;

class MainWindow : public QDialog
{
public:
    SMART_ALIASES(MainWindow);
    NO_COPY_NO_MOVE(MainWindow);

    MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    bool isRegexValid();

    QLabel*      m_enterText;
    QLineEdit*   m_textBox;
    QPushButton* m_computeBtn;
    Canvas::Ptr  m_canvas;
};

#endif // MAINWINDOW_H
