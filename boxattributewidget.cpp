#include "boxattributewidget.h"

#include <sstream>

using namespace SpriteSheet;

BoxAttributeWidget::BoxAttributeWidget(SpriteSheet::Sheet& sheet)
   : sheet(sheet)
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

   QLabel *xOffsetLabel = new QLabel(tr("x offset:"));
   boxXOffsetSpinBox = std::make_unique<QDoubleSpinBox>();
   boxYPosSpinBox->setRange(-INT_MAX/2, INT_MAX/2);
   boxYPosSpinBox->setSingleStep(1.0);

   QLabel *yOffsetLabel = new QLabel(tr("y offset:"));
   boxYOffsetSpinBox = std::make_unique<QDoubleSpinBox>();
   boxYPosSpinBox->setRange(-INT_MAX/2, INT_MAX/2);
   boxYPosSpinBox->setSingleStep(1.0);

   QLabel *nextFrameLabel = new QLabel(tr("Next frame GUID:"));
   boxNextFrameComboBox = std::make_unique<QComboBox>();

   QLabel *frameLenLabel = new QLabel(tr("Number of frames:"));
   boxFrameLenSpinBox = std::make_unique<QDoubleSpinBox>();
   boxFrameLenSpinBox->setRange(1.0, INT_MAX);
   boxFrameLenSpinBox->setSingleStep(1.0);

   boxPrevFrameButton = std::make_unique<QPushButton>("Previous Frame", this);
   boxNextFrameButton = std::make_unique<QPushButton>("Next Frame", this);

   deleteFrameButton = std::make_unique<QPushButton>("Delete", this);

   saveSpriteSheetButton = std::make_unique<QPushButton>("Save", this);

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
   boxLayout->addWidget(xOffsetLabel);
   boxLayout->addWidget(boxXOffsetSpinBox.get());
   boxLayout->addWidget(yOffsetLabel);
   boxLayout->addWidget(boxYOffsetSpinBox.get());
   boxLayout->addWidget(nextFrameLabel);
   boxLayout->addWidget(boxNextFrameComboBox.get());
   boxLayout->addWidget(frameLenLabel);
   boxLayout->addWidget(boxFrameLenSpinBox.get());
   boxLayout->addWidget(boxPrevFrameButton.get());
   boxLayout->addWidget(boxNextFrameButton.get());
   boxLayout->addWidget(deleteFrameButton.get());
   boxLayout->addWidget(saveSpriteSheetButton.get());
   setLayout(boxLayout);

   // Trick to resolve overloaded signal
   // http://stackoverflow.com/questions/16794695/connecting-overloaded-signals-and-slots-in-qt-5
   QObject::connect(boxCurFrameComboBox.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
                    this, &SpriteSheet::BoxAttributeWidget::setNewFrame);
   QObject::connect(boxWidthSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxWidth);
   QObject::connect(boxHeightSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxHeight);
   QObject::connect(boxXPosSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxXPos);
   QObject::connect(boxYPosSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxYPos);

   QObject::connect(boxXOffsetSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxXOffset);
   QObject::connect(boxYOffsetSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxYOffset);

   QObject::connect(boxNextFrameComboBox.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxNextFrame);
   QObject::connect(boxFrameLenSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    this, &SpriteSheet::BoxAttributeWidget::updateBoxFrameLen);

   QObject::connect(boxPrevFrameButton.get(), &QPushButton::released,
                    this, &SpriteSheet::BoxAttributeWidget::switchPrevFrame);
   QObject::connect(boxNextFrameButton.get(), &QPushButton::released,
                    this, &SpriteSheet::BoxAttributeWidget::switchNextFrame);

   QObject::connect(deleteFrameButton.get(), &QPushButton::released,
                    this, &SpriteSheet::BoxAttributeWidget::deleteFrame);

   QObject::connect(saveSpriteSheetButton.get(), &QPushButton::released,
                    this, &SpriteSheet::BoxAttributeWidget::saveSpriteSheet);

   setMinimumWidth(300);
   setWindowTitle(tr("Box Attributes"));

   if(sheet.frames.begin() != sheet.frames.end())
   {
      buildGuidList();

      switchFrame(nullptr, *(sheet.frames.begin()->second));
   }
}

void BoxAttributeWidget::addNewFrame(Frame &frame)
{
   boxCurFrameComboBox->addItem(tr(frame.guid.c_str()));
}

void BoxAttributeWidget::setNewFrame(int item)
{
   auto& oldFrame = sheet.frames[curBoxGuid];

   try
   {
      auto& newFrame = sheet.frames.at(boxCurFrameComboBox->itemText(item).toStdString());
      switchFrame(oldFrame.get(), *newFrame);
   }
   catch(const std::out_of_range& ex)
   {
      buildGuidList();
   }
}

void BoxAttributeWidget::buildGuidList()
{
   boxCurFrameComboBox->clear();

   for(const auto& it : sheet.frames)
   {
      Frame curFrame = *(it.second);
      addNewFrame(curFrame);
   }
}

void BoxAttributeWidget::updateBoxWidth(double width)
{
   auto rect = sheet.frames[curBoxGuid]->boxRect->rect();
   rect.setWidth(width);
   sheet.frames[curBoxGuid]->boxRect->setRect(rect);
}

void BoxAttributeWidget::updateBoxHeight(double height)
{
   auto rect = sheet.frames[curBoxGuid]->boxRect->rect();
   rect.setHeight(height);
   sheet.frames[curBoxGuid]->boxRect->setRect(rect);
}

void BoxAttributeWidget::updateBoxXPos(double xPos)
{
   auto rect = sheet.frames[curBoxGuid]->boxRect->rect();
   rect.setX(xPos);
   sheet.frames[curBoxGuid]->boxRect->setRect(rect);
}

void BoxAttributeWidget::updateBoxYPos(double yPos)
{
   auto rect = sheet.frames[curBoxGuid]->boxRect->rect();
   rect.setY(yPos);
   sheet.frames[curBoxGuid]->boxRect->setRect(rect);
}

void BoxAttributeWidget::updateBoxXOffset(double xOffset)
{
   sheet.frames[curBoxGuid]->xOffset = xOffset;
}

void BoxAttributeWidget::updateBoxYOffset(double yOffset)
{
   sheet.frames[curBoxGuid]->yOffset = yOffset;
}

void BoxAttributeWidget::updateBoxFrameLen(double frameLen)
{
   sheet.frames[curBoxGuid]->setFrameLen(frameLen);
}

void BoxAttributeWidget::updateBoxNextFrame(int entry)
{
   QString value = boxNextFrameComboBox->itemText(entry);
   sheet.frames[curBoxGuid]->setNextFrameGuid(value.toStdString());
}

void BoxAttributeWidget::switchNextFrame()
{
   auto& oldFrame = sheet.frames[curBoxGuid];
   auto& nextFrameGuid = oldFrame->getNextFrameGuid();

   if(nextFrameGuid.length() == 0)
   {
      return;
   }

   auto nextFrameIterator = sheet.frames.find(nextFrameGuid);
   if(nextFrameIterator == sheet.frames.end())
      return;
   else
   {
      auto& frame = nextFrameIterator->second;
      switchFrame(oldFrame.get(), *frame);
   }
}

void BoxAttributeWidget::switchPrevFrame()
{
   //TODO
}

void BoxAttributeWidget::deleteFrame()
{
   sheet.removeFrame(curBoxGuid);

   if(sheet.frames.begin() != sheet.frames.end())
   {
      switchFrame(nullptr, *(sheet.frames.begin()->second));
   }
}

void BoxAttributeWidget::saveSpriteSheet()
{
   try
   {
      sheet.serialize();
   }
   catch (const std::exception& ex)
   {
      QErrorMessage *error = new QErrorMessage(this);

      std::stringstream stream;
      stream << "Failed to serialize spritesheet: " << ex.what() << ".";
      error->showMessage(tr(stream.str().c_str()));
   }
}

void BoxAttributeWidget::switchFrame(const Frame* oldFrame, Frame &newFrame)
{
   if(oldFrame != nullptr)
   {
      oldFrame->boxRect->setPen(QPen(Qt::red));
   }

   curBoxGuid = newFrame.guid;

   newFrame.boxRect->setPen(QPen(Qt::blue));
   boxWidthSpinBox->setValue(newFrame.boxRect->rect().width());
   boxHeightSpinBox->setValue(newFrame.boxRect->rect().height());
   boxXPosSpinBox->setValue(newFrame.boxRect->rect().x());
   boxYPosSpinBox->setValue(newFrame.boxRect->rect().y());
   boxXOffsetSpinBox->setValue(newFrame.xOffset);
   boxYOffsetSpinBox->setValue(newFrame.yOffset);
   boxFrameLenSpinBox->setValue(newFrame.getFrameLen());

   boxNextFrameComboBox->clear();
   for(const auto& keyvalue : sheet.frames)
   {
      boxNextFrameComboBox->addItem(tr(keyvalue.first.c_str()));
   }

   auto index = boxCurFrameComboBox->findText(tr(curBoxGuid.c_str()));
   if(index != -1)
   {
      boxCurFrameComboBox->setCurrentIndex(index);
   }

   index = boxNextFrameComboBox->findText(tr(newFrame.getNextFrameGuid().c_str()));
   if(index != -1)
   {
      boxNextFrameComboBox->setCurrentIndex(index);
   }
}
