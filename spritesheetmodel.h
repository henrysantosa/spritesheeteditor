#ifndef SPRITESHEETMODEL_H
#define SPRITESHEETMODEL_H

#include <QObject>
#include <QVector>
#include <QGraphicsRectItem>

#include <memory>

struct Hitbox
{
   Hitbox(std::string guid, QGraphicsRectItem& hitboxRect);
   ~Hitbox() = default;
   std::string guid;
   QGraphicsRectItem* hitboxRect;
};

class SpriteSheetModel : public QObject
{
   Q_OBJECT

public:
   SpriteSheetModel();
   ~SpriteSheetModel() = default;

   void serialize();
   int getSize();

   void removeHitbox(const std::string& guid);

public slots:
   void addNewHitbox(std::string& guid, QGraphicsRectItem& hitboxRect);

signals:
   void hitboxAdded(Hitbox& hitbox);
   void hitboxRemoved(Hitbox& hitbox);

private:
   int size;
   std::map<std::string, std::unique_ptr<Hitbox>> hitboxes;
};

#endif // SPRITESHEETMODEL_H
