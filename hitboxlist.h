#ifndef HITBOXLIST_H
#define HITBOXLIST_H

#include <QObject>
#include <QListWidget>

#include "spritesheetmodel.h"

class HitboxList : public QListWidget
{
   Q_OBJECT

public:
    HitboxList(SpriteSheetModel& model);

public slots:
    void updateList();

private:
    SpriteSheetModel& model;
};

#endif // HITBOXLIST_H
