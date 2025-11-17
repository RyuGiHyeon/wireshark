/********************************************************************************
** Form generated from reading UI file 'packet_format_json_group_box.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACKET_FORMAT_JSON_GROUP_BOX_H
#define UI_PACKET_FORMAT_JSON_GROUP_BOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PacketFormatJSONGroupBox
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *dupKeysCheckBox;
    QCheckBox *valuesCheckBox;
    QCheckBox *bytesCheckBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QGroupBox *PacketFormatJSONGroupBox)
    {
        if (PacketFormatJSONGroupBox->objectName().isEmpty())
            PacketFormatJSONGroupBox->setObjectName("PacketFormatJSONGroupBox");
        PacketFormatJSONGroupBox->resize(400, 199);
        verticalLayout = new QVBoxLayout(PacketFormatJSONGroupBox);
        verticalLayout->setObjectName("verticalLayout");
        dupKeysCheckBox = new QCheckBox(PacketFormatJSONGroupBox);
        dupKeysCheckBox->setObjectName("dupKeysCheckBox");
        dupKeysCheckBox->setChecked(false);

        verticalLayout->addWidget(dupKeysCheckBox);

        valuesCheckBox = new QCheckBox(PacketFormatJSONGroupBox);
        valuesCheckBox->setObjectName("valuesCheckBox");
        valuesCheckBox->setChecked(true);

        verticalLayout->addWidget(valuesCheckBox);

        bytesCheckBox = new QCheckBox(PacketFormatJSONGroupBox);
        bytesCheckBox->setObjectName("bytesCheckBox");

        verticalLayout->addWidget(bytesCheckBox);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(PacketFormatJSONGroupBox);

        QMetaObject::connectSlotsByName(PacketFormatJSONGroupBox);
    } // setupUi

    void retranslateUi(QGroupBox *PacketFormatJSONGroupBox)
    {
        PacketFormatJSONGroupBox->setWindowTitle(QCoreApplication::translate("PacketFormatJSONGroupBox", "GroupBox", nullptr));
        PacketFormatJSONGroupBox->setTitle(QCoreApplication::translate("PacketFormatJSONGroupBox", "Packet Format", nullptr));
#if QT_CONFIG(tooltip)
        dupKeysCheckBox->setToolTip(QCoreApplication::translate("PacketFormatJSONGroupBox", "<html><head/><body><p>Avoid duplicate keys in the JSON by using a list for sibling fields with the same key</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        dupKeysCheckBox->setText(QCoreApplication::translate("PacketFormatJSONGroupBox", "No duplicate keys", nullptr));
#if QT_CONFIG(tooltip)
        valuesCheckBox->setToolTip(QCoreApplication::translate("PacketFormatJSONGroupBox", "<html><head/><body><p>Export a name/value pair for each field with the field value</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        valuesCheckBox->setText(QCoreApplication::translate("PacketFormatJSONGroupBox", "Values", nullptr));
#if QT_CONFIG(tooltip)
        bytesCheckBox->setToolTip(QCoreApplication::translate("PacketFormatJSONGroupBox", "<html><head/><body><p>Export a name/value pair for each field with the hex bytes of its packet data</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bytesCheckBox->setText(QCoreApplication::translate("PacketFormatJSONGroupBox", "Raw Bytes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PacketFormatJSONGroupBox: public Ui_PacketFormatJSONGroupBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PACKET_FORMAT_JSON_GROUP_BOX_H
