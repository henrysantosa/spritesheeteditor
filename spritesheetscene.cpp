#include "spritesheetscene.h"

SpriteSheetScene::SpriteSheetScene(SpriteSheet::Frame& frame)
   : frame(frame)
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

    if(width == 0 || height == 0)
       return;

    auto rectangle = addRect(x, y, width, height, outlinePen);

//    rectangle->setFlag(QGraphicsItem::ItemIsMovable);
//    rectangle->setFlag(QGraphicsItem::ItemIsSelectable);
//    rectangle->setFlag(QGraphicsItem::ItemIsFocusable);

    frame.addNewBox(std::to_string(frame.getSize()), *rectangle);
}

void SpriteSheetScene::removeBox(SpriteSheet::Box &box)
{
   removeItem(box.boxRect);
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
