/********************************************************************************
** Form generated from reading UI file 'packet_format_group_box.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACKET_FORMAT_GROUP_BOX_H
#define UI_PACKET_FORMAT_GROUP_BOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PacketFormatTextGroupBox
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *summaryCheckBox;
    QCheckBox *includeColumnHeadingsCheckBox;
    QCheckBox *detailsCheckBox;
    QRadioButton *allCollapsedButton;
    QRadioButton *asDisplayedButton;
    QRadioButton *allExpandedButton;
    QCheckBox *bytesCheckBox;
    QCheckBox *includeDataSourcesCheckBox;
    QCheckBox *timestampCheckBox;

    void setupUi(QGroupBox *PacketFormatTextGroupBox)
    {
        if (PacketFormatTextGroupBox->objectName().isEmpty())
            PacketFormatTextGroupBox->setObjectName("PacketFormatTextGroupBox");
        PacketFormatTextGroupBox->resize(400, 199);
        verticalLayout = new QVBoxLayout(PacketFormatTextGroupBox);
        verticalLayout->setObjectName("verticalLayout");
        summaryCheckBox = new QCheckBox(PacketFormatTextGroupBox);
        summaryCheckBox->setObjectName("summaryCheckBox");
        summaryCheckBox->setChecked(true);

        verticalLayout->addWidget(summaryCheckBox);

        includeColumnHeadingsCheckBox = new QCheckBox(PacketFormatTextGroupBox);
        includeColumnHeadingsCheckBox->setObjectName("includeColumnHeadingsCheckBox");
        includeColumnHeadingsCheckBox->setChecked(true);

        verticalLayout->addWidget(includeColumnHeadingsCheckBox);

        detailsCheckBox = new QCheckBox(PacketFormatTextGroupBox);
        detailsCheckBox->setObjectName("detailsCheckBox");
        detailsCheckBox->setChecked(true);

        verticalLayout->addWidget(detailsCheckBox);

        allCollapsedButton = new QRadioButton(PacketFormatTextGroupBox);
        allCollapsedButton->setObjectName("allCollapsedButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(allCollapsedButton->sizePolicy().hasHeightForWidth());
        allCollapsedButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(allCollapsedButton);

        asDisplayedButton = new QRadioButton(PacketFormatTextGroupBox);
        asDisplayedButton->setObjectName("asDisplayedButton");
        sizePolicy.setHeightForWidth(asDisplayedButton->sizePolicy().hasHeightForWidth());
        asDisplayedButton->setSizePolicy(sizePolicy);
        asDisplayedButton->setChecked(true);

        verticalLayout->addWidget(asDisplayedButton);

        allExpandedButton = new QRadioButton(PacketFormatTextGroupBox);
        allExpandedButton->setObjectName("allExpandedButton");
        sizePolicy.setHeightForWidth(allExpandedButton->sizePolicy().hasHeightForWidth());
        allExpandedButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(allExpandedButton);

        bytesCheckBox = new QCheckBox(PacketFormatTextGroupBox);
        bytesCheckBox->setObjectName("bytesCheckBox");

        verticalLayout->addWidget(bytesCheckBox);

        includeDataSourcesCheckBox = new QCheckBox(PacketFormatTextGroupBox);
        includeDataSourcesCheckBox->setObjectName("includeDataSourcesCheckBox");
        includeDataSourcesCheckBox->setChecked(true);
        includeDataSourcesCheckBox->setEnabled(false);

        verticalLayout->addWidget(includeDataSourcesCheckBox);

        timestampCheckBox = new QCheckBox(PacketFormatTextGroupBox);
        timestampCheckBox->setObjectName("timestampCheckBox");
        timestampCheckBox->setChecked(false);
        timestampCheckBox->setEnabled(false);

        verticalLayout->addWidget(timestampCheckBox);


        retranslateUi(PacketFormatTextGroupBox);

        QMetaObject::connectSlotsByName(PacketFormatTextGroupBox);
    } // setupUi

    void retranslateUi(QGroupBox *PacketFormatTextGroupBox)
    {
        PacketFormatTextGroupBox->setWindowTitle(QCoreApplication::translate("PacketFormatTextGroupBox", "GroupBox", nullptr));
        PacketFormatTextGroupBox->setTitle(QCoreApplication::translate("PacketFormatTextGroupBox", "Packet Format", nullptr));
#if QT_CONFIG(tooltip)
        summaryCheckBox->setToolTip(QCoreApplication::translate("PacketFormatTextGroupBox", "<html><head/><body><p>Packet summary lines similar to the packet list</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        summaryCheckBox->setText(QCoreApplication::translate("PacketFormatTextGroupBox", "Summary line", nullptr));
        includeColumnHeadingsCheckBox->setText(QCoreApplication::translate("PacketFormatTextGroupBox", "Include column headings", nullptr));
#if QT_CONFIG(tooltip)
        detailsCheckBox->setToolTip(QCoreApplication::translate("PacketFormatTextGroupBox", "<html><head/><body><p>Packet details similar to the protocol tree</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        detailsCheckBox->setText(QCoreApplication::translate("PacketFormatTextGroupBox", "Details:", nullptr));
#if QT_CONFIG(tooltip)
        allCollapsedButton->setToolTip(QCoreApplication::translate("PacketFormatTextGroupBox", "<html><head/><body><p>Export only top-level packet detail items</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        allCollapsedButton->setText(QCoreApplication::translate("PacketFormatTextGroupBox", "All co&llapsed", nullptr));
#if QT_CONFIG(tooltip)
        asDisplayedButton->setToolTip(QCoreApplication::translate("PacketFormatTextGroupBox", "<html><head/><body><p>Expand and collapse packet details as they are currently displayed.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        asDisplayedButton->setText(QCoreApplication::translate("PacketFormatTextGroupBox", "As displa&yed", nullptr));
#if QT_CONFIG(tooltip)
        allExpandedButton->setToolTip(QCoreApplication::translate("PacketFormatTextGroupBox", "<html><head/><body><p>Export all packet detail items</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        allExpandedButton->setText(QCoreApplication::translate("PacketFormatTextGroupBox", "All e&xpanded", nullptr));
#if QT_CONFIG(tooltip)
        bytesCheckBox->setToolTip(QCoreApplication::translate("PacketFormatTextGroupBox", "<html><head/><body><p>Export a hexdump of the packet data similar to the packet bytes view</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bytesCheckBox->setText(QCoreApplication::translate("PacketFormatTextGroupBox", "Bytes", nullptr));
        includeDataSourcesCheckBox->setText(QCoreApplication::translate("PacketFormatTextGroupBox", "Include secondary data sources", nullptr));
#if QT_CONFIG(tooltip)
        includeDataSourcesCheckBox->setToolTip(QCoreApplication::translate("PacketFormatTextGroupBox", "<html><head/><body><p>Generate hexdumps for secondary data sources like reassembled or decrypted buffers in addition to the frame</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        timestampCheckBox->setText(QCoreApplication::translate("PacketFormatTextGroupBox", "Include timestamp preamble", nullptr));
#if QT_CONFIG(tooltip)
        timestampCheckBox->setToolTip(QCoreApplication::translate("PacketFormatTextGroupBox", "<html><head/><body><p>Include each frame timestamp immediately before its hex dump, using the current time display format.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class PacketFormatTextGroupBox: public Ui_PacketFormatTextGroupBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PACKET_FORMAT_GROUP_BOX_H
