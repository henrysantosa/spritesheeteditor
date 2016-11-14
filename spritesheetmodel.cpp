#include "spritesheetmodel.h"

SpriteSheetModel::SpriteSheetModel()
   : hitboxes()
{
}

void SpriteSheetModel::serialize()
{
}

void SpriteSheetModel::addNewHitbox(QGraphicsRectItem& hitbox)
{
   hitboxes.push_back(&hitbox);
   emit hitboxAdded(hitbox);
}
