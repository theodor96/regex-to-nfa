#ifndef STATE_H
#define STATE_H

#include <QWidget>

class State : public QWidget
{
public:

    State(QWidget* parent, quint16 rx, quint16 ry);

    QSize sizeHint() const override
    {
        return
        {
            500,
            500
        };
    }

protected:

    void paintEvent(QPaintEvent* event) override;

private:

    quint16 m_rx;
    quint16 m_ry;
};

#endif // STATE_H
