#ifndef HITBOXLIST_H
#define HITBOXLIST_H

#include <QObject>
#include <QListWidget>
#include <QKeyEvent>

#include "spritesheetmodel.h"

class HitboxList : public QListWidget
{
   Q_OBJECT

public:
    HitboxList(SpriteSheet::Frame& frame);

public slots:
    void addToList(SpriteSheet::Box& box);

private:
    SpriteSheet::Frame& frame;

protected:
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // HITBOXLIST_H
