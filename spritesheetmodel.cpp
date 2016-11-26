#include "spritesheetmodel.h"

Hitbox::Hitbox(std::string guid, QGraphicsRectItem& hitboxRect)
   : guid(guid)
   , hitboxRect(&hitboxRect)
{
}

SpriteSheetModel::SpriteSheetModel()
   : hitboxes()
   , size(0)
{
}

void SpriteSheetModel::serialize()
{
}

void SpriteSheetModel::addNewHitbox(std::string& guid, QGraphicsRectItem& hitboxRect)
{
   hitboxes[guid] = std::make_unique<Hitbox>(guid, hitboxRect);
   ++size;
   emit hitboxAdded(*hitboxes[guid]);
}

void SpriteSheetModel::removeHitbox(const std::string& guid)
{
   emit hitboxRemoved(*hitboxes[guid]);
   hitboxes.erase(guid);
//   --size; // don't want to overwrite until we figure out how to get GUIDs working
}

int SpriteSheetModel::getSize()
{
   return size;
}
