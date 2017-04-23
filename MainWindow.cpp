#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QCloseEvent>
#include "MainWindow.h"
#include "NFA.h"

MainWindow::MainWindow() :
    QDialog(),
    m_enterText(new QLabel(this)),
    m_textBox(new QLineEdit(this)),
    m_computeBtn(new QPushButton(this)),
    m_canvas()
{
    // setup the main window
    this->setWindowTitle("RegexToNFA");
    this->setFixedSize(200, 150);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // setup the label
    m_enterText->setText("Enter a REGEX in the textbox:");
    m_enterText->move(10, 30);

    // setup the textbox
    m_textBox->setGeometry(10, 60, 180, 20);

    // setup the compute button
    m_computeBtn->setText("Compute the NFA");
    m_computeBtn->move(20, 100);

    // check when the regex becomes valid, activate the compute button
    this->connect(m_textBox, &QLineEdit::textChanged, this, [=]
    {
        m_computeBtn->setEnabled(isRegexValid());
    });

    // when compute button is clicked (so regex is implicitly valid), magic happens
    this->connect(m_computeBtn, &QPushButton::clicked, this, [=]
    {
        m_canvas = Canvas::Ptr(new Canvas(NFA::FromRegex(m_textBox->text().toStdString())));
        m_canvas->show();
    });
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (m_canvas)
    {
        m_canvas->close();
    }

    event->accept();
}

bool MainWindow::isRegexValid()
{
    // this validation method is rather naive
    // and does not take into account the actual validity
    // of the string as a regex, but it's good to prevent mistakes

    static QString C_ACCEPTED_CHARACTERS("|()+*.");

    for (const auto& itr : m_textBox->text())
    {
        if (itr.isLetter())
        {
            if (!itr.isLower())
            {
                return false;
            }

            continue;
        }

        if (!C_ACCEPTED_CHARACTERS.contains(itr))
        {
            return false;
        }
    }

    return true;
}
