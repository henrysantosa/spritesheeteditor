#include "boxattributewidget.h"

using namespace SpriteSheet;

BoxAttributeWidget::BoxAttributeWidget(SpriteSheet::Frame& frame)
   : frame(frame)
{
   QVBoxLayout *boxLayout = new QVBoxLayout;

   QLabel *widthLabel = new QLabel(tr("Width:"));
   boxWidthSpinBox = std::make_unique<QDoubleSpinBox>();
   boxWidthSpinBox->setRange(1.0, INT_MAX);
   boxWidthSpinBox->setSingleStep(1.0);

   QLabel *heightLabel = new QLabel(tr("Height:"));
   boxHeightSpinBox = std::make_unique<QDoubleSpinBox>();
   boxHeightSpinBox->setRange(1.0, INT_MAX);
   boxHeightSpinBox->setSingleStep(1.0);

   QLabel *xPosLabel = new QLabel(tr("x:"));
   boxXPosSpinBox = std::make_unique<QDoubleSpinBox>();
   boxXPosSpinBox->setRange(1.0, INT_MAX);
   boxXPosSpinBox->setSingleStep(1.0);

   QLabel *yPosLabel = new QLabel(tr("y:"));
   boxYPosSpinBox = std::make_unique<QDoubleSpinBox>();
   boxYPosSpinBox->setRange(1.0, INT_MAX);
   boxYPosSpinBox->setSingleStep(1.0);

   boxLayout->addWidget(widthLabel);
   boxLayout->addWidget(boxWidthSpinBox.get());
   boxLayout->addWidget(heightLabel);
   boxLayout->addWidget(boxHeightSpinBox.get());
   boxLayout->addWidget(xPosLabel);
   boxLayout->addWidget(boxXPosSpinBox.get());
   boxLayout->addWidget(yPosLabel);
   boxLayout->addWidget(boxYPosSpinBox.get());
   setLayout(boxLayout);

   // Trick to resolve overloaded signal
   // http://stackoverflow.com/questions/16794695/connecting-overloaded-signals-and-slots-in-qt-5
   QObject::connect(boxWidthSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxWidth);
   QObject::connect(boxHeightSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxHeight);
   QObject::connect(boxXPosSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxXPos);
   QObject::connect(boxYPosSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxYPos);

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

void BoxAttributeWidget::updateBoxWidth(double width)
{
   auto rect = frame.boxes[curBoxGuid]->boxRect->rect();
   rect.setWidth(width);
   frame.boxes[curBoxGuid]->boxRect->setRect(rect);
}

void BoxAttributeWidget::updateBoxHeight(double height)
{
   auto rect = frame.boxes[curBoxGuid]->boxRect->rect();
   rect.setHeight(height);
   frame.boxes[curBoxGuid]->boxRect->setRect(rect);
}

void BoxAttributeWidget::updateBoxXPos(double xPos)
{
   auto rect = frame.boxes[curBoxGuid]->boxRect->rect();
   rect.setX(xPos);
   frame.boxes[curBoxGuid]->boxRect->setRect(rect);
}

void BoxAttributeWidget::updateBoxYPos(double yPos)
{
   auto rect = frame.boxes[curBoxGuid]->boxRect->rect();
   rect.setY(yPos);
   frame.boxes[curBoxGuid]->boxRect->setRect(rect);
}
