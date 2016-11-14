#ifndef SPRITESHEETMODEL_H
#define SPRITESHEETMODEL_H

#include <QObject>
#include <QVector>
#include <QGraphicsRectItem>

class SpriteSheetModel : public QObject
{
    Q_OBJECT

public:
    SpriteSheetModel();
    ~SpriteSheetModel() = default;

    QVector<QGraphicsRectItem*> hitboxes;
    void serialize();

public slots:
    void addNewHitbox(QGraphicsRectItem& hitbox);

signals:
    void hitboxAdded(QGraphicsRectItem& hitbox);

private:
};

#endif // SPRITESHEETMODEL_H
