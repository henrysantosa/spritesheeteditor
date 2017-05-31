#include "framesceneattributewidget.h"

namespace SpriteSheet
{

FrameSceneAttributeWidget::FrameSceneAttributeWidget(SpriteSheet::Sheet& sheet, QWidget *parent)
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

   setLayout(boxLayout);

   setMinimumWidth(200);
   setWindowTitle(tr("Frame Attributes"));

   setupSignalAndSlots();
}

void FrameSceneAttributeWidget::setupSignalAndSlots()
{
   QObject::connect(boxTypeBox.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
                    [&](int index){
      emit switchBoxType((Box::BoxType)(index));
   });

//TODO: Implement
}

void FrameSceneAttributeWidget::addNewBox(Box &box)
{
//TODO: Implement
}

}
