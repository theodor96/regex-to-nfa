#ifndef CANVAS_H
#define CANVAS_H

#include <QDialog>

class Canvas : public QDialog
{
public:
    Canvas();
    Canvas(const Canvas&) = delete;
    Canvas& operator=(const Canvas&) = delete;
    Canvas(Canvas&&) = delete;
    Canvas& operator=(Canvas&&) = delete;
};

#endif // CANVAS_H
