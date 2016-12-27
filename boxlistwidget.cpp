#include "boxlistwidget.h"

BoxListWidget::BoxListWidget(SpriteSheet::Frame& frame)
   : frame(frame)
{
}

void BoxListWidget::addToList(SpriteSheet::Box& box)
{
   new QListWidgetItem(tr(box.guid.c_str()), this);
}

void BoxListWidget::keyPressEvent(QKeyEvent *event)
{
   if(event->key() == Qt::Key_Delete)
   {
      auto selected = this->selectedItems();
      foreach(QListWidgetItem* item, selected)
      {
         frame.removeBox(item->text().toStdString());
         delete this->takeItem(this->row(item));
      }
   }
}
