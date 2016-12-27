#ifndef BOXLISTWIDGET_H
#define BOXLISTWIDGET_H

#include <QObject>
#include <QListWidget>
#include <QKeyEvent>

#include "spritesheetmodel.h"

class BoxListWidget : public QListWidget
{
   Q_OBJECT

public:
    BoxListWidget(SpriteSheet::Frame& frame);

public slots:
    void addToList(SpriteSheet::Box& box);

private:
    SpriteSheet::Frame& frame;

protected:
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // BOXLISTWIDGET_H
