#include "boxattributewidget.h"

#include <sstream>

using namespace SpriteSheet;

FrameAttributeWidget::FrameAttributeWidget(SpriteSheet::Sheet& sheet)
   : sheet(sheet)
{
   QLabel *curFrameLabel = new QLabel(tr("Current Frame:"));
   frameCurFrameComboBox = std::make_unique<QComboBox>();
   frameCurFrameComboBox->setEditable(true);
   frameCurFrameComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);

   QLabel *widthLabel = new QLabel(tr("Width:"));
   frameWidthSpinBox = std::make_unique<QDoubleSpinBox>();
   frameWidthSpinBox->setRange(1.0, INT_MAX);
   frameWidthSpinBox->setSingleStep(1.0);

   QLabel *heightLabel = new QLabel(tr("Height:"));
   frameHeightSpinBox = std::make_unique<QDoubleSpinBox>();
   frameHeightSpinBox->setRange(1.0, INT_MAX);
   frameHeightSpinBox->setSingleStep(1.0);

   QLabel *xPosLabel = new QLabel(tr("x:"));
   frameXPosSpinBox = std::make_unique<QDoubleSpinBox>();
   frameXPosSpinBox->setRange(1.0, INT_MAX);
   frameXPosSpinBox->setSingleStep(1.0);

   QLabel *yPosLabel = new QLabel(tr("y:"));
   frameYPosSpinBox = std::make_unique<QDoubleSpinBox>();
   frameYPosSpinBox->setRange(1.0, INT_MAX);
   frameYPosSpinBox->setSingleStep(1.0);

   QLabel *xOffsetLabel = new QLabel(tr("x offset:"));
   frameXOffsetSpinBox = std::make_unique<QDoubleSpinBox>();
   frameYPosSpinBox->setRange(-INT_MAX/2, INT_MAX/2);
   frameYPosSpinBox->setSingleStep(1.0);

   QLabel *yOffsetLabel = new QLabel(tr("y offset:"));
   frameYOffsetSpinBox = std::make_unique<QDoubleSpinBox>();
   frameYPosSpinBox->setRange(-INT_MAX/2, INT_MAX/2);
   frameYPosSpinBox->setSingleStep(1.0);

   QLabel *nextFrameLabel = new QLabel(tr("Next frame GUID:"));
   nextFrameComboBox = std::make_unique<QComboBox>();

   QLabel *frameLenLabel = new QLabel(tr("Number of frames:"));
   frameLenSpinBox = std::make_unique<QDoubleSpinBox>();
   frameLenSpinBox->setRange(1.0, INT_MAX);
   frameLenSpinBox->setSingleStep(1.0);

   boxPrevFrameButton = std::make_unique<QPushButton>("Previous Frame", this);
   frameNextFrameButton = std::make_unique<QPushButton>("Next Frame", this);

   deleteFrameButton = std::make_unique<QPushButton>("Delete", this);

   saveSpriteSheetButton = std::make_unique<QPushButton>("Save", this);

   frameGuidLineEdit = std::make_unique<QLineEdit>(this);
   frameGuidLineEdit->setPlaceholderText("New GUID");
   frameGuidEditButton = std::make_unique<QPushButton>("Apply", this);

   QVBoxLayout *boxLayout = new QVBoxLayout;
   QHBoxLayout *hboxLayout = new QHBoxLayout;

   boxLayout->addWidget(curFrameLabel);
   boxLayout->addWidget(frameCurFrameComboBox.get());
   hboxLayout->addWidget(frameGuidLineEdit.get());
   hboxLayout->addWidget(frameGuidEditButton.get());
   boxLayout->addLayout(hboxLayout);
   boxLayout->addWidget(widthLabel);
   boxLayout->addWidget(frameWidthSpinBox.get());
   boxLayout->addWidget(heightLabel);
   boxLayout->addWidget(frameHeightSpinBox.get());
   boxLayout->addWidget(xPosLabel);
   boxLayout->addWidget(frameXPosSpinBox.get());
   boxLayout->addWidget(yPosLabel);
   boxLayout->addWidget(frameYPosSpinBox.get());
   boxLayout->addWidget(xOffsetLabel);
   boxLayout->addWidget(frameXOffsetSpinBox.get());
   boxLayout->addWidget(yOffsetLabel);
   boxLayout->addWidget(frameYOffsetSpinBox.get());
   boxLayout->addWidget(nextFrameLabel);
   boxLayout->addWidget(nextFrameComboBox.get());
   boxLayout->addWidget(frameLenLabel);
   boxLayout->addWidget(frameLenSpinBox.get());

   boxLayout->addWidget(boxPrevFrameButton.get());
   boxLayout->addWidget(frameNextFrameButton.get());
   boxLayout->addWidget(deleteFrameButton.get());
   boxLayout->addWidget(saveSpriteSheetButton.get());
   setLayout(boxLayout);

   setMinimumWidth(300);
   setWindowTitle(tr("Box Attributes"));

   setupSignalAndSlots();

   if(sheet.frames.begin() != sheet.frames.end())
   {
      buildGuidList();

      switchFrame(nullptr, *(sheet.frames.begin()->second));
   }
}

void FrameAttributeWidget::setupSignalAndSlots()
{
   // Trick to resolve overloaded signal
   // http://stackoverflow.com/questions/16794695/connecting-overloaded-signals-and-slots-in-qt-5
   QObject::connect(frameCurFrameComboBox.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
                    this, &SpriteSheet::FrameAttributeWidget::setNewFrame);
   QObject::connect(frameGuidEditButton.get(), &QPushButton::released,
                    this, &SpriteSheet::FrameAttributeWidget::editFrameName);

//   QObject::connect(frameWidthSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
//                    this, &SpriteSheet::FrameAttributeWidget::updateFrameWidth);
   QObject::connect(frameWidthSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [&](double width){
      auto rect = sheet.frames[curFrameGuid]->boxRect->rect();
      rect.setWidth(width);
      sheet.frames[curFrameGuid]->boxRect->setRect(rect);
   });

   QObject::connect(frameHeightSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [&](double height){
      auto rect = sheet.frames[curFrameGuid]->boxRect->rect();
      rect.setHeight(height);
      sheet.frames[curFrameGuid]->boxRect->setRect(rect);
   });

   QObject::connect(frameXPosSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [&](double xPos){
      auto rect = sheet.frames[curFrameGuid]->boxRect->rect();
      rect.setX(xPos);
      sheet.frames[curFrameGuid]->boxRect->setRect(rect);
   });

   QObject::connect(frameYPosSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [&](double yPos){
      auto rect = sheet.frames[curFrameGuid]->boxRect->rect();
      rect.setY(yPos);
      sheet.frames[curFrameGuid]->boxRect->setRect(rect);
   });

   QObject::connect(frameXOffsetSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [&](double xOffset){sheet.frames[curFrameGuid]->xOffset = xOffset;});

   QObject::connect(frameYOffsetSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [&](double yOffset){sheet.frames[curFrameGuid]->yOffset = yOffset;});

   QObject::connect(nextFrameComboBox.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
                    [&](int entry){
      QString value = nextFrameComboBox->itemText(entry);
      sheet.frames[curFrameGuid]->setNextFrameGuid(value.toStdString());
   });

   QObject::connect(frameLenSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [&](double frameLen){sheet.frames[curFrameGuid]->setFrameLen(frameLen);});

   QObject::connect(boxPrevFrameButton.get(), &QPushButton::released,
                    this, &SpriteSheet::FrameAttributeWidget::switchPrevFrame);

   QObject::connect(frameNextFrameButton.get(), &QPushButton::released,
                    this, &SpriteSheet::FrameAttributeWidget::switchNextFrame);

   QObject::connect(deleteFrameButton.get(), &QPushButton::released,
                    this, &SpriteSheet::FrameAttributeWidget::deleteFrame);

   QObject::connect(saveSpriteSheetButton.get(), &QPushButton::released,
                    this, &SpriteSheet::FrameAttributeWidget::saveSpriteSheet);
}

void FrameAttributeWidget::addNewFrame(Frame &frame)
{
   frameCurFrameComboBox->addItem(tr(frame.guid.c_str()));
}

void FrameAttributeWidget::setNewFrame(int item)
{
   auto& oldFrame = sheet.frames[curFrameGuid];

   try
   {
      auto& newFrame = sheet.frames.at(frameCurFrameComboBox->itemText(item).toStdString());
      switchFrame(oldFrame.get(), *newFrame);
   }
   catch(const std::out_of_range&)
   {
      buildGuidList();
   }
}

void FrameAttributeWidget::buildGuidList()
{
   frameCurFrameComboBox->clear();

   for(const auto& it : sheet.frames)
   {
      Frame curFrame = *(it.second);
      addNewFrame(curFrame);
   }
}

void FrameAttributeWidget::switchPrevFrame()
{
   //TODO
}

void FrameAttributeWidget::switchNextFrame()
{
   auto& oldFrame = sheet.frames[curFrameGuid];
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

void FrameAttributeWidget::deleteFrame()
{
   sheet.removeFrame(curFrameGuid);

   if(sheet.frames.begin() != sheet.frames.end())
   {
      switchFrame(nullptr, *(sheet.frames.begin()->second));
   }
}

void FrameAttributeWidget::saveSpriteSheet()
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

void FrameAttributeWidget::switchFrame(const Frame* oldFrame, Frame &newFrame)
{
   if(oldFrame != nullptr)
   {
      oldFrame->boxRect->setPen(QPen(Qt::red));
   }

   curFrameGuid = newFrame.guid;

   newFrame.boxRect->setPen(QPen(Qt::blue));
   frameWidthSpinBox->setValue(newFrame.boxRect->rect().width());
   frameHeightSpinBox->setValue(newFrame.boxRect->rect().height());
   frameXPosSpinBox->setValue(newFrame.boxRect->rect().x());
   frameYPosSpinBox->setValue(newFrame.boxRect->rect().y());
   frameXOffsetSpinBox->setValue(newFrame.xOffset);
   frameYOffsetSpinBox->setValue(newFrame.yOffset);
   frameLenSpinBox->setValue(newFrame.getFrameLen());
   frameGuidLineEdit->clear();

   // resets everytime we switch frames, could be optimised
   // need to differentiate between add and switch
   nextFrameComboBox->clear();
   for(const auto& keyvalue : sheet.frames)
   {
      nextFrameComboBox->addItem(tr(keyvalue.first.c_str()));
   }

   auto index = frameCurFrameComboBox->findText(tr(curFrameGuid.c_str()));
   if(index != -1)
   {
      frameCurFrameComboBox->setCurrentIndex(index);
   }

   index = nextFrameComboBox->findText(tr(newFrame.getNextFrameGuid().c_str()));
   if(index != -1)
   {
      nextFrameComboBox->setCurrentIndex(index);
   }

   emit frameSwitched(curFrameGuid);
}

void FrameAttributeWidget::editFrameName()
{
   auto newName = frameGuidLineEdit->text().toStdString();

   if(!newName.empty() && newName != curFrameGuid && sheet.frames.find(curFrameGuid) != sheet.frames.end())
   {
      sheet.frames[newName] = std::move(sheet.frames[curFrameGuid]);
      sheet.frames[newName]->setGuid(newName);
      sheet.frames.erase(curFrameGuid);

      for(auto& framePair: sheet.frames)
      {
         auto& frame = framePair.second;
         if(frame->getNextFrameGuid() == curFrameGuid)
         {
            frame->setNextFrameGuid(newName);
         }
      }

      buildGuidList();

      switchFrame(nullptr, *(sheet.frames[newName]));
   }
}
