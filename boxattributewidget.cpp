#include "boxattributewidget.h"

using namespace SpriteSheet;

BoxAttributeWidget::BoxAttributeWidget(SpriteSheet::Frame& frame)
   : frame(frame)
{
   QVBoxLayout *boxLayout = new QVBoxLayout;

   QLabel *curFrameLabel = new QLabel(tr("Current Frame:"));
   boxCurFrameComboBox = std::make_unique<QComboBox>();

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

   QLabel *nextFrameLabel = new QLabel(tr("Next frame GUID:"));
   boxNextFrameComboBox = std::make_unique<QComboBox>();

   QLabel *frameLenLabel = new QLabel(tr("Number of frames:"));
   boxFrameLenSpinBox = std::make_unique<QDoubleSpinBox>();
   boxFrameLenSpinBox->setRange(1.0, INT_MAX);
   boxFrameLenSpinBox->setSingleStep(1.0);

   boxLayout->addWidget(curFrameLabel);
   boxLayout->addWidget(boxCurFrameComboBox.get());
   boxLayout->addWidget(widthLabel);
   boxLayout->addWidget(boxWidthSpinBox.get());
   boxLayout->addWidget(heightLabel);
   boxLayout->addWidget(boxHeightSpinBox.get());
   boxLayout->addWidget(xPosLabel);
   boxLayout->addWidget(boxXPosSpinBox.get());
   boxLayout->addWidget(yPosLabel);
   boxLayout->addWidget(boxYPosSpinBox.get());
   boxLayout->addWidget(nextFrameLabel);
   boxLayout->addWidget(boxNextFrameComboBox.get());
   boxLayout->addWidget(frameLenLabel);
   boxLayout->addWidget(boxFrameLenSpinBox.get());
   setLayout(boxLayout);

   // Trick to resolve overloaded signal
   // http://stackoverflow.com/questions/16794695/connecting-overloaded-signals-and-slots-in-qt-5
   QObject::connect(boxCurFrameComboBox.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
                    this, &SpriteSheet::BoxAttributeWidget::setNewBox);
   QObject::connect(boxWidthSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxWidth);
   QObject::connect(boxHeightSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxHeight);
   QObject::connect(boxXPosSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxXPos);
   QObject::connect(boxYPosSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxYPos);
   QObject::connect(boxNextFrameComboBox.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxNextFrame);
   QObject::connect(boxFrameLenSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxFrameLen);

   this->setMinimumWidth(300);
   setWindowTitle(tr("Box Attributes"));
}

void BoxAttributeWidget::addNewFrame(Box &box)
{
   boxCurFrameComboBox->addItem(tr(box.guid.c_str()));
}

void BoxAttributeWidget::setNewBox(int item)
{
   curBoxGuid = boxCurFrameComboBox->itemText(item).toStdString();

   boxWidthSpinBox->setValue(frame.boxes[curBoxGuid]->boxRect->rect().width());
   boxHeightSpinBox->setValue(frame.boxes[curBoxGuid]->boxRect->rect().height());
   boxXPosSpinBox->setValue(frame.boxes[curBoxGuid]->boxRect->rect().x());
   boxYPosSpinBox->setValue(frame.boxes[curBoxGuid]->boxRect->rect().y());
   boxFrameLenSpinBox->setValue(frame.boxes[curBoxGuid]->getFrameLen());

   boxNextFrameComboBox->clear();
   for(const auto& keyvalue : frame.boxes)
   {
      boxNextFrameComboBox->addItem(tr(keyvalue.first.c_str()));
   }
   int pos = boxNextFrameComboBox->findText(tr(frame.boxes[curBoxGuid]->getNextFrameGuid().c_str()));
   if(pos != -1)
   {
      boxNextFrameComboBox->setCurrentIndex(pos);
   }

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

void BoxAttributeWidget::updateBoxFrameLen(double frameLen)
{
   frame.boxes[curBoxGuid]->setFrameLen(frameLen);
}

void BoxAttributeWidget::updateBoxNextFrame(int entry)
{
   QString value = boxNextFrameComboBox->itemText(entry);
   frame.boxes[curBoxGuid]->setNextFrameGuid(value.toStdString());
}

