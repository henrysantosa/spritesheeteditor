#include "hitboxlist.h"

HitboxList::HitboxList(SpriteSheetModel& model)
   : model(model)
{
}

void HitboxList::addToList(Hitbox& hitbox)
{
   new QListWidgetItem(tr(hitbox.guid.c_str()), this);
}

void HitboxList::keyPressEvent(QKeyEvent *event)
{
   if(event->key() == Qt::Key_Delete)
   {
      auto selected = this->selectedItems();
      foreach(QListWidgetItem* item, selected)
      {
         model.removeHitbox(item->text().toStdString());
         delete this->takeItem(this->row(item));
      }
   }
}
