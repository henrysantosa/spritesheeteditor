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
    HitboxList(SpriteSheetModel& model);

public slots:
    void addToList(Hitbox& hitbox);

private:
    SpriteSheetModel& model;

protected:
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // HITBOXLIST_H
