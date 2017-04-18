#include <QPen>
#include <QPainter>
#include <QTime>
#include <QtMath>
#include "Automaton.h"
#include "Canvas.h"
#include "State.h"

#include <QDebug>

Automaton::Automaton(Canvas* canvas) :
    QWidget(canvas),
    m_states{},
    m_transitions{}
{
    qsrand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));

    auto s1 = new State(1);
    auto s2 = new State(2);
    auto s3 = new State(3);

    m_transitions[std::make_pair(s1, 'a')] = s2;
    m_transitions[std::make_pair(s2, 'b')] = s3;
    m_transitions[std::make_pair(s3, 'c')] = s1;

    m_states.push_back(State::Ptr(s1));
    m_states.push_back(State::Ptr(s2));
    m_states.push_back(State::Ptr(s3));

    for (const auto& state : m_states)
    {
        state->paintedAt(findNewStatePaintLocation());
    }

    for (const auto& sourceItr : m_transitions)
    {
        qDebug() << "from state "
                 << sourceItr.first.first->getGuid()
                 << "with isPAinted = " << sourceItr.first.first->isPainted()
                 << " to state "
                 << sourceItr.second->getGuid()
                 << " via symbol "
                 << sourceItr.first.second;
    }
}

QSize Automaton::sizeHint() const
{
    return
    {
        500,
        500
    };
}

void Automaton::paintEvent(QPaintEvent*)
{
    QPen pen;
    pen.setColor(QColor(Qt::red));
    pen.setWidth(1);

    QPainter painter(this);

    painter.setPen(pen);

    painter.setRenderHint(QPainter::Antialiasing);

    /*painter.drawEllipse(QPoint(40, 40), 20, 20);

    painter.drawEllipse(QPoint(80, 80), 20, 20);

    painter.drawEllipse(QPoint(120, 190), 20, 20);

    painter.drawLines(QVector<QPoint>{ {40, 40}, {80, 80}, {80, 80}, {120, 190} });

    painter.drawText(60, 60, "dwed");*/

    for (const auto& state : m_states)
    {
        painter.drawEllipse(state->getPaintLocation(), 5, 5);
    }
}

bool Automaton::isPaintLocationSuitable(const QPoint& location) const
{
    for (const auto& state : m_states)
    {
        if (!state->isPainted())
        {
            continue;
        }

        if (qFabs(state->getPaintLocation().manhattanLength() - location.manhattanLength()) < 10)
        {
            return false;
        }
    }

    return true;
}

QPoint Automaton::getRandomPaintLocation() const
{
    return
    {
        qrand() % 480,
        qrand() % 480
    };
}

QPoint Automaton::findNewStatePaintLocation() const
{
    QPoint result(getRandomPaintLocation());
    while (!isPaintLocationSuitable(result))
    {
        qDebug() << "point " << result << " was not good";
        result = getRandomPaintLocation();
    }

    return result;
}
