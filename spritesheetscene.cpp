#include "spritesheetscene.h"

SpriteSheetScene::SpriteSheetScene(SpriteSheetModel& model)
   : model(model)
{
}

void SpriteSheetScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    auto downPos = event->buttonDownScenePos(event->button());
    auto upPos   = event->scenePos();

    auto width = abs(upPos.x() - downPos.x());
    auto height = abs(upPos.y() - downPos.y());

    auto x = std::min(upPos.x(), downPos.x());
    auto y = std::min(upPos.y(), downPos.y());

    QPen outlinePen(Qt::red);
    auto rectangle = addRect(x, y, width, height, outlinePen);

    model.addNewHitbox(*rectangle);

//    if(model.hitboxes.size() > 1)
//    {
//        int index = 0;
//        auto toRemove = model.hitboxes[index];
//        model.hitboxes.erase(model.hitboxes.begin() + index);
//        removeItem(toRemove);
//    }
}

void SpriteSheetScene::loadImage(QString path)
{
    QGraphicsPixmapItem* pixmap;

    QImageReader reader(path);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();

    image = newImage;
    pixmap = this->addPixmap(QPixmap::fromImage(newImage));
}
