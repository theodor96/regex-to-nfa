#include "MainWindow.h"

MainWindow::MainWindow() :
    QDialog(),
    m_enterTextLabel(new QLabel(this)),
    m_textBox(new QLineEdit(this)),
    m_computeBtn(new QPushButton(this))
{
    // setup the main window
    this->setWindowTitle("RegexToNFA");
    this->setFixedSize(200, 150);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // setup the label
    m_enterTextLabel->setText("Enter a REGEX in the textbox below:");
    m_enterTextLabel->move(10, 30);

    // setup the textbox
    m_textBox->setGeometry(10, 60, 180, 20);

    // setup the button
    m_computeBtn->setText("Compute the NFA");
    m_computeBtn->move(50, 100);

    // check when the regex becomes valid, activate the button
    this->connect(m_textBox, &QLineEdit::textChanged, this, [=]
    {
        m_computeBtn->setEnabled(isRegexValid());
    });

    // when button is clicked (so regex is implicitly valid), magic happens
    this->connect(m_computeBtn, &QPushButton::clicked, this, [=]
    {
        this->close();
    });
}

bool MainWindow::isRegexValid()
{
    // this validation method is rather naive
    // and does not take into account the actual validity
    // of the string as a regex, but it's good to prevent mistakes

    static QString C_ACCEPTED_CHARACTERS("()+*");

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