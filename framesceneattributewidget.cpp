#include "framesceneattributewidget.h"

namespace SpriteSheet
{

FrameSceneAttributeWidget::FrameSceneAttributeWidget(SpriteSheet::Sheet& sheet, std::string curId, QWidget *parent)
   : sheet(sheet)
   , QWidget(parent)
{
   QLabel *curBoxLabel = new QLabel(tr("Current Box:"));
   curBoxComboBox = std::make_unique<QComboBox>();
   curBoxComboBox->setEditable(true);
   curBoxComboBox->setInsertPolicy(QComboBox::InsertAlphabetically);

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

   QLabel *boxTypeLabel = new QLabel(tr("Box Type:"));
   boxTypeBox = std::make_unique<QComboBox>();
   boxTypeBox->setEditable(false);
   boxTypeBox->addItem("Hitbox", Box::BoxType::HITBOX);
   boxTypeBox->addItem("Hurtbox", Box::BoxType::HURTBOX);
   boxTypeBox->setInsertPolicy(QComboBox::InsertAlphabetically);

   deleteBoxButton = std::make_unique<QPushButton>("Delete", this);

   QVBoxLayout *boxLayout = new QVBoxLayout;
   QHBoxLayout *hboxLayout = new QHBoxLayout;

   boxLayout->addLayout(hboxLayout);
   boxLayout->addWidget(curBoxLabel);
   boxLayout->addWidget(curBoxComboBox.get());
   boxLayout->addWidget(widthLabel);
   boxLayout->addWidget(boxWidthSpinBox.get());
   boxLayout->addWidget(heightLabel);
   boxLayout->addWidget(boxHeightSpinBox.get());
   boxLayout->addWidget(xPosLabel);
   boxLayout->addWidget(boxXPosSpinBox.get());
   boxLayout->addWidget(yPosLabel);
   boxLayout->addWidget(boxYPosSpinBox.get());
   boxLayout->addWidget(boxTypeLabel);
   boxLayout->addWidget(boxTypeBox.get());
   boxLayout->addWidget(deleteBoxButton.get());

   setLayout(boxLayout);

   setMinimumWidth(200);
   setWindowTitle(tr("Frame Attributes"));

   setupSignalAndSlots();

   switchFrame(curId);
}

void FrameSceneAttributeWidget::setupSignalAndSlots()
{
   QObject::connect(curBoxComboBox.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
                    this, [this](int index){
      auto curFrame = sheet.getFrame(curFrameGuid);
      if(curFrame != nullptr)
      {
         auto curBox = curFrame->findBox(curBoxComboBox->itemText(index).toStdString());
         if(curBox != nullptr)
         {
            switchBox(*curBox);
         }
      }
   });

   QObject::connect(boxTypeBox.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
                    [&](int index){
      emit switchBoxType((Box::BoxType)(index));
   });

   QObject::connect(boxXPosSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [&](double xPos){
      auto curFrame = sheet.getFrame(curFrameGuid);
      if(curFrame != nullptr)
      {
         auto curBox = curFrame->findBox(curBoxGuid);
         if(curBox != nullptr)
         {
            auto& rect = curBox->boxRect->rect();
            rect.setX(xPos);
            curBox->boxRect->setRect(rect);
         }
      }
   });

   QObject::connect(boxYPosSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [&](double yPos){
      auto curFrame = sheet.getFrame(curFrameGuid);
      if(curFrame != nullptr)
      {
         auto curBox = curFrame->findBox(curBoxGuid);
         if(curBox != nullptr)
         {
            auto& rect = curBox->boxRect->rect();
            rect.setY(yPos);
            curBox->boxRect->setRect(rect);
         }
      }
   });

   QObject::connect(boxWidthSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [&](double width){
      auto curFrame = sheet.getFrame(curFrameGuid);
      if(curFrame != nullptr)
      {
         auto curBox = curFrame->findBox(curBoxGuid);
         if(curBox != nullptr)
         {
            auto& rect = curBox->boxRect->rect();
            rect.setWidth(width);
            curBox->boxRect->setRect(rect);
         }
      }
   });

   QObject::connect(boxHeightSpinBox.get(), static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [&](double height){
      auto curFrame = sheet.getFrame(curFrameGuid);
      if(curFrame != nullptr)
      {
         auto curBox = curFrame->findBox(curBoxGuid);
         if(curBox != nullptr)
         {
            auto& rect = curBox->boxRect->rect();
            rect.setHeight(height);
            curBox->boxRect->setRect(rect);
         }
      }
   });

   QObject::connect(deleteBoxButton.get(), &QPushButton::released,
                    this, &FrameSceneAttributeWidget::deleteBox);
}

void FrameSceneAttributeWidget::switchFrame(std::string& guid)
{
   Frame* curFrame = sheet.getFrame(guid);

   if(curFrame == nullptr)
      return;

   curFrameGuid = curFrame->guid;

   curBoxComboBox->clear();
   for(const auto& box : curFrame->boxes)
   {
      curBoxComboBox->addItem(tr(box->guid.c_str()));
   }

   if(curFrame->boxes.size() > 0)
   {
      switchBox(**(curFrame->boxes.begin()));
   }
}

void FrameSceneAttributeWidget::switchBox(std::string& guid)
{
   Frame* frame = sheet.getFrame(curFrameGuid);
   if(frame != nullptr)
   {
      Box* curBox = frame->findBox(guid);
      if(curBox != nullptr)
      {
         switchBox(*curBox);
      }
   }
}

void FrameSceneAttributeWidget::switchBox(Box& box)
{
   curBoxGuid = box.guid;
   boxXPosSpinBox->setValue(static_cast<double>(box.sRect.x));
   boxYPosSpinBox->setValue(static_cast<double>(box.sRect.y));
   boxWidthSpinBox->setValue(static_cast<double>(box.sRect.width));
   boxHeightSpinBox->setValue(static_cast<double>(box.sRect.height));
   boxTypeBox->setCurrentIndex(boxTypeBox->findData(box.type));
}

void FrameSceneAttributeWidget::deleteBox()
{
   Frame* curFrame = sheet.getFrame(curFrameGuid);
   if(curFrame != nullptr)
   {
      curFrame->boxes.erase(std::remove_if(curFrame->boxes.begin(), curFrame->boxes.end(), [this](const auto& box){
         return box->guid == curBoxGuid;
      }), curFrame->boxes.end());

      emit boxDeleted();

      switchFrame(curFrameGuid);
   }
}

void FrameSceneAttributeWidget::addNewBox(Box &box)
{
   curBoxComboBox->addItem(tr(box.guid.c_str()));
   curBoxComboBox->setCurrentIndex(curBoxComboBox->findText(tr(box.guid.c_str())));
   switchBox(box);
}

}
