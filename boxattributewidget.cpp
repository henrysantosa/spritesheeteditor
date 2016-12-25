#include <QtWidgets>

#include "boxattributewidget.h"
#include "limits.h"

using namespace SpriteSheet;

BoxAttributeWidget::BoxAttributeWidget(SpriteSheet::Frame& frame)
   : frame(frame)
{
   QVBoxLayout *boxLayout = new QVBoxLayout;

   QLabel *widthLabel = new QLabel(tr("Width:"));
   boxWidthSpinBox = std::make_unique<QDoubleSpinBox>();
   boxWidthSpinBox->setRange(0.0, INT_MAX);
   boxWidthSpinBox->setSingleStep(0.1);

   QLabel *heightLabel = new QLabel(tr("Height:"));
   boxHeightSpinBox = std::make_unique<QDoubleSpinBox>();
   boxHeightSpinBox->setRange(0.0, INT_MAX);
   boxHeightSpinBox->setSingleStep(0.1);

   QLabel *xPosLabel = new QLabel(tr("x:"));
   boxXPosSpinBox = std::make_unique<QDoubleSpinBox>();
   boxXPosSpinBox->setRange(0.0, INT_MAX);
   boxXPosSpinBox->setSingleStep(0.1);

   QLabel *yPosLabel = new QLabel(tr("y:"));
   boxYPosSpinBox = std::make_unique<QDoubleSpinBox>();
   boxYPosSpinBox->setRange(0.0, INT_MAX);
   boxYPosSpinBox->setSingleStep(0.1);

   boxLayout->addWidget(widthLabel);
   boxLayout->addWidget(boxWidthSpinBox.get());
   boxLayout->addWidget(heightLabel);
   boxLayout->addWidget(boxHeightSpinBox.get());
   boxLayout->addWidget(xPosLabel);
   boxLayout->addWidget(boxXPosSpinBox.get());
   boxLayout->addWidget(yPosLabel);
   boxLayout->addWidget(boxYPosSpinBox.get());
   setLayout(boxLayout);

   this->setMinimumWidth(300);
   setWindowTitle(tr("Box Attributes"));
}

void BoxAttributeWidget::setNewBox(QListWidgetItem *item)
{
   curBoxGuid = item->text().toStdString();

   boxWidthSpinBox->setValue(frame.boxes[curBoxGuid]->boxRect->rect().width());
   boxHeightSpinBox->setValue(frame.boxes[curBoxGuid]->boxRect->rect().height());
   boxXPosSpinBox->setValue(frame.boxes[curBoxGuid]->boxRect->rect().x());
   boxYPosSpinBox->setValue(frame.boxes[curBoxGuid]->boxRect->rect().y());
}
