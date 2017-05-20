#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include <QWidget>
#include <QSize>
#include <QPoint>
#include "Utils.h"

class AutomatonWidget;
class QPaintEvent;

class StateWidget : public QWidget
{
public:
    SMART_ALIASES(StateWidget);
    NO_COPY_NO_MOVE(StateWidget);

    using Guid = qint64;
    static const Guid InvalidGuid = -1;

    StateWidget(AutomatonWidget* parent);

    const QPoint& getLocation() const;
    Guid getGuid() const;
    bool isFinal() const;

    void setGuid(Guid guid);
    void setLocation(const QPoint& location);
    void markAsFinal();

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPoint m_location;
    Guid   m_guid;
    bool   m_isFinal;
};

#endif // STATEWIDGET_H
