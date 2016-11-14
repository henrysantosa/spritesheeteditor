#include "hitboxlist.h"

HitboxList::HitboxList(SpriteSheetModel& model)
   : model(model)
{
}

void HitboxList::updateList()
{
   new QListWidgetItem(tr("Oak"), this);
   new QListWidgetItem(tr("Fir"), this);
   new QListWidgetItem(tr("Pine"), this);
}
