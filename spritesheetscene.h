#ifndef SPRITESHEETSCENE_H
#define SPRITESHEETSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QImageReader>

#include <cmath>
#include <algorithm>

#include "spritesheetmodel.h"

class SpriteSheetScene : public QGraphicsScene
{
Q_OBJECT

public:
    SpriteSheetScene(SpriteSheetModel& model);
    void loadImage(QString path);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public slots:
    void removeHitbox(Hitbox& hitbox);

private:
    SpriteSheetModel& model;
    QImage image;
};

#endif // SPRITESHEETSCENE_H
