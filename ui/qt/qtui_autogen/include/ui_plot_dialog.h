/********************************************************************************
** Form generated from reading UI file 'plot_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOT_DIALOG_H
#define UI_PLOT_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "widgets/customplot.h"
#include "widgets/elided_label.h"
#include "widgets/rowmove_tree_view.h"
#include "widgets/stock_icon_tool_button.h"

QT_BEGIN_NAMESPACE

class Ui_PlotDialog
{
public:
    QAction *actionReset;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionMoveUp10;
    QAction *actionMoveLeft10;
    QAction *actionMoveRight10;
    QAction *actionMoveDown10;
    QAction *actionMoveUp1;
    QAction *actionMoveLeft1;
    QAction *actionMoveRight1;
    QAction *actionMoveDown1;
    QAction *actionGoToPacket;
    QAction *actionToggleTimeOrigin;
    QAction *actionLogScale;
    QAction *actionCrosshairs;
    QAction *actionTopAxis;
    QAction *actionLegend;
    QAction *actionZoomInX;
    QAction *actionZoomOutX;
    QAction *actionZoomInY;
    QAction *actionZoomOutY;
    QAction *actionAddMarker;
    QAction *actionMoveMarker;
    QAction *actionShowPosMarker;
    QAction *actionShowMarkersDifference;
    QAction *actionDeleteMarker;
    QAction *actionDeleteAllMarkers;
    QAction *actionShowDataPointMarker;
    QAction *actionAutoScroll;
    QAction *actionEnableMultiYAxes;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    CustomPlot *plot;
    ElidedLabel *hintLabel;
    RowMoveTreeView *plotUat;
    QHBoxLayout *horizontalLayout;
    QDialogButtonBox *leftButtonBox;
    StockIconToolButton *newToolButton;
    StockIconToolButton *deleteToolButton;
    StockIconToolButton *copyToolButton;
    StockIconToolButton *moveUpwardsToolButton;
    StockIconToolButton *moveDownwardsToolButton;
    StockIconToolButton *clearToolButton;
    QCheckBox *automaticUpdateCheckBox;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *rightButtonBox;

    void setupUi(QDialog *PlotDialog)
    {
        if (PlotDialog->objectName().isEmpty())
            PlotDialog->setObjectName("PlotDialog");
        PlotDialog->resize(850, 640);
        actionReset = new QAction(PlotDialog);
        actionReset->setObjectName("actionReset");
        actionZoomIn = new QAction(PlotDialog);
        actionZoomIn->setObjectName("actionZoomIn");
        actionZoomOut = new QAction(PlotDialog);
        actionZoomOut->setObjectName("actionZoomOut");
        actionMoveUp10 = new QAction(PlotDialog);
        actionMoveUp10->setObjectName("actionMoveUp10");
        actionMoveLeft10 = new QAction(PlotDialog);
        actionMoveLeft10->setObjectName("actionMoveLeft10");
        actionMoveRight10 = new QAction(PlotDialog);
        actionMoveRight10->setObjectName("actionMoveRight10");
        actionMoveDown10 = new QAction(PlotDialog);
        actionMoveDown10->setObjectName("actionMoveDown10");
        actionMoveUp1 = new QAction(PlotDialog);
        actionMoveUp1->setObjectName("actionMoveUp1");
        actionMoveLeft1 = new QAction(PlotDialog);
        actionMoveLeft1->setObjectName("actionMoveLeft1");
        actionMoveRight1 = new QAction(PlotDialog);
        actionMoveRight1->setObjectName("actionMoveRight1");
        actionMoveDown1 = new QAction(PlotDialog);
        actionMoveDown1->setObjectName("actionMoveDown1");
        actionGoToPacket = new QAction(PlotDialog);
        actionGoToPacket->setObjectName("actionGoToPacket");
        actionToggleTimeOrigin = new QAction(PlotDialog);
        actionToggleTimeOrigin->setObjectName("actionToggleTimeOrigin");
        actionLogScale = new QAction(PlotDialog);
        actionLogScale->setObjectName("actionLogScale");
        actionLogScale->setCheckable(true);
        actionCrosshairs = new QAction(PlotDialog);
        actionCrosshairs->setObjectName("actionCrosshairs");
        actionCrosshairs->setCheckable(true);
        actionTopAxis = new QAction(PlotDialog);
        actionTopAxis->setObjectName("actionTopAxis");
        actionTopAxis->setCheckable(true);
        actionLegend = new QAction(PlotDialog);
        actionLegend->setObjectName("actionLegend");
        actionLegend->setCheckable(true);
        actionZoomInX = new QAction(PlotDialog);
        actionZoomInX->setObjectName("actionZoomInX");
        actionZoomOutX = new QAction(PlotDialog);
        actionZoomOutX->setObjectName("actionZoomOutX");
        actionZoomInY = new QAction(PlotDialog);
        actionZoomInY->setObjectName("actionZoomInY");
        actionZoomOutY = new QAction(PlotDialog);
        actionZoomOutY->setObjectName("actionZoomOutY");
        actionAddMarker = new QAction(PlotDialog);
        actionAddMarker->setObjectName("actionAddMarker");
        actionMoveMarker = new QAction(PlotDialog);
        actionMoveMarker->setObjectName("actionMoveMarker");
        actionShowPosMarker = new QAction(PlotDialog);
        actionShowPosMarker->setObjectName("actionShowPosMarker");
        actionShowPosMarker->setCheckable(true);
        actionShowPosMarker->setChecked(false);
        actionShowMarkersDifference = new QAction(PlotDialog);
        actionShowMarkersDifference->setObjectName("actionShowMarkersDifference");
        actionShowMarkersDifference->setCheckable(true);
        actionShowMarkersDifference->setChecked(true);
        actionDeleteMarker = new QAction(PlotDialog);
        actionDeleteMarker->setObjectName("actionDeleteMarker");
        actionDeleteAllMarkers = new QAction(PlotDialog);
        actionDeleteAllMarkers->setObjectName("actionDeleteAllMarkers");
        actionShowDataPointMarker = new QAction(PlotDialog);
        actionShowDataPointMarker->setObjectName("actionShowDataPointMarker");
        actionShowDataPointMarker->setCheckable(true);
        actionShowDataPointMarker->setChecked(true);
        actionAutoScroll = new QAction(PlotDialog);
        actionAutoScroll->setObjectName("actionAutoScroll");
        actionAutoScroll->setCheckable(true);
        actionAutoScroll->setChecked(false);
        actionEnableMultiYAxes = new QAction(PlotDialog);
        actionEnableMultiYAxes->setObjectName("actionEnableMultiYAxes");
        actionEnableMultiYAxes->setCheckable(true);
        actionEnableMultiYAxes->setChecked(false);
        verticalLayout_2 = new QVBoxLayout(PlotDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        splitter = new QSplitter(PlotDialog);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        plot = new CustomPlot(layoutWidget);
        plot->setObjectName("plot");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(90);
        sizePolicy.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
        plot->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(plot);

        hintLabel = new ElidedLabel(layoutWidget);
        hintLabel->setObjectName("hintLabel");

        verticalLayout->addWidget(hintLabel);

        splitter->addWidget(layoutWidget);
        plotUat = new RowMoveTreeView(splitter);
        plotUat->setObjectName("plotUat");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(plotUat->sizePolicy().hasHeightForWidth());
        plotUat->setSizePolicy(sizePolicy1);
        splitter->addWidget(plotUat);

        verticalLayout_2->addWidget(splitter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        leftButtonBox = new QDialogButtonBox(PlotDialog);
        leftButtonBox->setObjectName("leftButtonBox");
        leftButtonBox->setStandardButtons(QDialogButtonBox::StandardButton::Reset);

        horizontalLayout->addWidget(leftButtonBox);

        newToolButton = new StockIconToolButton(PlotDialog);
        newToolButton->setObjectName("newToolButton");

        horizontalLayout->addWidget(newToolButton);

        deleteToolButton = new StockIconToolButton(PlotDialog);
        deleteToolButton->setObjectName("deleteToolButton");

        horizontalLayout->addWidget(deleteToolButton);

        copyToolButton = new StockIconToolButton(PlotDialog);
        copyToolButton->setObjectName("copyToolButton");

        horizontalLayout->addWidget(copyToolButton);

        moveUpwardsToolButton = new StockIconToolButton(PlotDialog);
        moveUpwardsToolButton->setObjectName("moveUpwardsToolButton");
        moveUpwardsToolButton->setEnabled(false);

        horizontalLayout->addWidget(moveUpwardsToolButton);

        moveDownwardsToolButton = new StockIconToolButton(PlotDialog);
        moveDownwardsToolButton->setObjectName("moveDownwardsToolButton");
        moveDownwardsToolButton->setEnabled(false);

        horizontalLayout->addWidget(moveDownwardsToolButton);

        clearToolButton = new StockIconToolButton(PlotDialog);
        clearToolButton->setObjectName("clearToolButton");
        clearToolButton->setEnabled(false);

        horizontalLayout->addWidget(clearToolButton);

        automaticUpdateCheckBox = new QCheckBox(PlotDialog);
        automaticUpdateCheckBox->setObjectName("automaticUpdateCheckBox");

        horizontalLayout->addWidget(automaticUpdateCheckBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        rightButtonBox = new QDialogButtonBox(PlotDialog);
        rightButtonBox->setObjectName("rightButtonBox");
        rightButtonBox->setOrientation(Qt::Orientation::Horizontal);
        rightButtonBox->setStandardButtons(QDialogButtonBox::StandardButton::Close|QDialogButtonBox::StandardButton::Help|QDialogButtonBox::StandardButton::Save);

        horizontalLayout->addWidget(rightButtonBox);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(PlotDialog);
        QObject::connect(rightButtonBox, &QDialogButtonBox::rejected, PlotDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(PlotDialog);
    } // setupUi

    void retranslateUi(QDialog *PlotDialog)
    {
        PlotDialog->setWindowTitle(QCoreApplication::translate("PlotDialog", "Dialog", nullptr));
        actionReset->setText(QCoreApplication::translate("PlotDialog", "Reset Plot", nullptr));
#if QT_CONFIG(tooltip)
        actionReset->setToolTip(QCoreApplication::translate("PlotDialog", "Reset the plot to its initial state.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionReset->setShortcut(QCoreApplication::translate("PlotDialog", "0", nullptr));
#endif // QT_CONFIG(shortcut)
        actionZoomIn->setText(QCoreApplication::translate("PlotDialog", "Zoom In", nullptr));
#if QT_CONFIG(tooltip)
        actionZoomIn->setToolTip(QCoreApplication::translate("PlotDialog", "Zoom In", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionZoomIn->setShortcut(QCoreApplication::translate("PlotDialog", "+", nullptr));
#endif // QT_CONFIG(shortcut)
        actionZoomOut->setText(QCoreApplication::translate("PlotDialog", "Zoom Out", nullptr));
#if QT_CONFIG(tooltip)
        actionZoomOut->setToolTip(QCoreApplication::translate("PlotDialog", "Zoom Out", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionZoomOut->setShortcut(QCoreApplication::translate("PlotDialog", "-", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMoveUp10->setText(QCoreApplication::translate("PlotDialog", "Move Up 10 Pixels", nullptr));
#if QT_CONFIG(tooltip)
        actionMoveUp10->setToolTip(QCoreApplication::translate("PlotDialog", "Move Up 10 Pixels", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionMoveUp10->setShortcut(QCoreApplication::translate("PlotDialog", "Up", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMoveLeft10->setText(QCoreApplication::translate("PlotDialog", "Move Left 10 Pixels", nullptr));
#if QT_CONFIG(tooltip)
        actionMoveLeft10->setToolTip(QCoreApplication::translate("PlotDialog", "Move Left 10 Pixels", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionMoveLeft10->setShortcut(QCoreApplication::translate("PlotDialog", "Left", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMoveRight10->setText(QCoreApplication::translate("PlotDialog", "Move Right 10 Pixels", nullptr));
#if QT_CONFIG(tooltip)
        actionMoveRight10->setToolTip(QCoreApplication::translate("PlotDialog", "Move Right 10 Pixels", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionMoveRight10->setShortcut(QCoreApplication::translate("PlotDialog", "Right", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMoveDown10->setText(QCoreApplication::translate("PlotDialog", "Move Down 10 Pixels", nullptr));
#if QT_CONFIG(tooltip)
        actionMoveDown10->setToolTip(QCoreApplication::translate("PlotDialog", "Move Down 10 Pixels", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionMoveDown10->setShortcut(QCoreApplication::translate("PlotDialog", "Down", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMoveUp1->setText(QCoreApplication::translate("PlotDialog", "Move Up 1 Pixel", nullptr));
#if QT_CONFIG(tooltip)
        actionMoveUp1->setToolTip(QCoreApplication::translate("PlotDialog", "Move Up 1 Pixel", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionMoveUp1->setShortcut(QCoreApplication::translate("PlotDialog", "Shift+Up", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMoveLeft1->setText(QCoreApplication::translate("PlotDialog", "Move Left 1 Pixel", nullptr));
#if QT_CONFIG(tooltip)
        actionMoveLeft1->setToolTip(QCoreApplication::translate("PlotDialog", "Move Left 1 Pixel", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionMoveLeft1->setShortcut(QCoreApplication::translate("PlotDialog", "Shift+Left", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMoveRight1->setText(QCoreApplication::translate("PlotDialog", "Move Right 1 Pixel", nullptr));
#if QT_CONFIG(tooltip)
        actionMoveRight1->setToolTip(QCoreApplication::translate("PlotDialog", "Move Right 1 Pixel", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionMoveRight1->setShortcut(QCoreApplication::translate("PlotDialog", "Shift+Right", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMoveDown1->setText(QCoreApplication::translate("PlotDialog", "Move Down 1 Pixel", nullptr));
#if QT_CONFIG(tooltip)
        actionMoveDown1->setToolTip(QCoreApplication::translate("PlotDialog", "Move down 1 Pixel", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionMoveDown1->setShortcut(QCoreApplication::translate("PlotDialog", "Shift+Down", nullptr));
#endif // QT_CONFIG(shortcut)
        actionGoToPacket->setText(QCoreApplication::translate("PlotDialog", "Go To Packet Under Cursor", nullptr));
#if QT_CONFIG(tooltip)
        actionGoToPacket->setToolTip(QCoreApplication::translate("PlotDialog", "Go to packet currently under the cursor", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionGoToPacket->setShortcut(QCoreApplication::translate("PlotDialog", "G", nullptr));
#endif // QT_CONFIG(shortcut)
        actionToggleTimeOrigin->setText(QCoreApplication::translate("PlotDialog", "Time origin", nullptr));
#if QT_CONFIG(tooltip)
        actionToggleTimeOrigin->setToolTip(QCoreApplication::translate("PlotDialog", "Toggle between time relative to first data point and time relative to capture start", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionToggleTimeOrigin->setShortcut(QCoreApplication::translate("PlotDialog", "T", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLogScale->setText(QCoreApplication::translate("PlotDialog", "Log scale", nullptr));
#if QT_CONFIG(tooltip)
        actionLogScale->setToolTip(QCoreApplication::translate("PlotDialog", "Toggle Y-axis between logarithmic and linear scale", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCrosshairs->setText(QCoreApplication::translate("PlotDialog", "Crosshairs", nullptr));
#if QT_CONFIG(tooltip)
        actionCrosshairs->setToolTip(QCoreApplication::translate("PlotDialog", "Toggle crosshairs", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionCrosshairs->setShortcut(QCoreApplication::translate("PlotDialog", "Space", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTopAxis->setText(QCoreApplication::translate("PlotDialog", "Top axis", nullptr));
#if QT_CONFIG(tooltip)
        actionTopAxis->setToolTip(QCoreApplication::translate("PlotDialog", "Toggle top axis on and off", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionTopAxis->setShortcut(QCoreApplication::translate("PlotDialog", "A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLegend->setText(QCoreApplication::translate("PlotDialog", "Legend", nullptr));
#if QT_CONFIG(tooltip)
        actionLegend->setToolTip(QCoreApplication::translate("PlotDialog", "Toggle legend", nullptr));
#endif // QT_CONFIG(tooltip)
        actionZoomInX->setText(QCoreApplication::translate("PlotDialog", "Zoom In X Axis", nullptr));
#if QT_CONFIG(tooltip)
        actionZoomInX->setToolTip(QCoreApplication::translate("PlotDialog", "Zoom In X Axis", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionZoomInX->setShortcut(QCoreApplication::translate("PlotDialog", "X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionZoomOutX->setText(QCoreApplication::translate("PlotDialog", "Zoom Out X Axis", nullptr));
#if QT_CONFIG(tooltip)
        actionZoomOutX->setToolTip(QCoreApplication::translate("PlotDialog", "Zoom Out X Axis", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionZoomOutX->setShortcut(QCoreApplication::translate("PlotDialog", "Shift+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionZoomInY->setText(QCoreApplication::translate("PlotDialog", "Zoom In Y Axis", nullptr));
#if QT_CONFIG(tooltip)
        actionZoomInY->setToolTip(QCoreApplication::translate("PlotDialog", "Zoom In Y Axis", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionZoomInY->setShortcut(QCoreApplication::translate("PlotDialog", "Y", nullptr));
#endif // QT_CONFIG(shortcut)
        actionZoomOutY->setText(QCoreApplication::translate("PlotDialog", "Zoom Out Y Axis", nullptr));
#if QT_CONFIG(tooltip)
        actionZoomOutY->setToolTip(QCoreApplication::translate("PlotDialog", "Zoom Out Y Axis", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionZoomOutY->setShortcut(QCoreApplication::translate("PlotDialog", "Shift+Y", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAddMarker->setText(QCoreApplication::translate("PlotDialog", "Add Marker", nullptr));
        actionMoveMarker->setText(QCoreApplication::translate("PlotDialog", "Move Marker", nullptr));
        actionShowPosMarker->setText(QCoreApplication::translate("PlotDialog", "Show Pos Marker", nullptr));
        actionShowMarkersDifference->setText(QCoreApplication::translate("PlotDialog", "Show Markers Difference", nullptr));
        actionDeleteMarker->setText(QCoreApplication::translate("PlotDialog", "Delete Marker", nullptr));
        actionDeleteAllMarkers->setText(QCoreApplication::translate("PlotDialog", "Delete All", nullptr));
        actionShowDataPointMarker->setText(QCoreApplication::translate("PlotDialog", "Show Markers DataPoints", nullptr));
        actionAutoScroll->setText(QCoreApplication::translate("PlotDialog", "Auto Scroll", nullptr));
        actionEnableMultiYAxes->setText(QCoreApplication::translate("PlotDialog", "Multiple Value Axes", nullptr));
#if QT_CONFIG(tooltip)
        hintLabel->setToolTip(QCoreApplication::translate("PlotDialog", "<html><head/><body>\n"
"\n"
"<h3>Valuable and amazing time-saving keyboard shortcuts</h3>\n"
"<table><tbody>\n"
"\n"
"<tr><th>+</th><td>Zoom in</td></th>\n"
"<tr><th>-</th><td>Zoom out</td></th>\n"
"<tr><th>x</th><td>Zoom in X axis</td></th>\n"
"<tr><th>X</th><td>Zoom out X axis</td></th>\n"
"<tr><th>y</th><td>Zoom in Y axis</td></th>\n"
"<tr><th>Y</th><td>Zoom out Y axis</td></th>\n"
"<tr><th>0</th><td>Reset plot to its initial state</td></th>\n"
"\n"
"<tr><th>\342\206\222</th><td>Move right 10 pixels</td></th>\n"
"<tr><th>\342\206\220</th><td>Move left 10 pixels</td></th>\n"
"<tr><th>\342\206\221</th><td>Move up 10 pixels</td></th>\n"
"<tr><th>\342\206\223</th><td>Move down 10 pixels</td></th>\n"
"<tr><th><i>Shift+</i>\342\206\222</th><td>Move right 1 pixel</td></th>\n"
"<tr><th><i>Shift+</i>\342\206\220</th><td>Move left 1 pixel</td></th>\n"
"<tr><th><i>Shift+</i>\342\206\221</th><td>Move up 1 pixel</td></th>\n"
"<tr><th><i>Shift+</i>\342\206\223</th><td>Move down 1 pixel</td></th>\n"
"\n"
"<tr><th>g</th><t"
                        "d>Go to packet under cursor</td></th>\n"
"\n"
"<tr><th>t</th><td>Toggle time origin</td></th>\n"
"<tr><th>Space</th><td>Toggle crosshairs</td></th>\n"
"<tr><th>a</th><td>Toggle top axis</td></th>\n"
"\n"
"</tbody></table>\n"
"</body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        hintLabel->setText(QString());
#if QT_CONFIG(tooltip)
        newToolButton->setToolTip(QCoreApplication::translate("PlotDialog", "Add a new plot.", nullptr));
#endif // QT_CONFIG(tooltip)
        newToolButton->setText(QString());
#if QT_CONFIG(tooltip)
        deleteToolButton->setToolTip(QCoreApplication::translate("PlotDialog", "Remove the selected plots.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        copyToolButton->setToolTip(QCoreApplication::translate("PlotDialog", "Duplicate the selected plots.", nullptr));
#endif // QT_CONFIG(tooltip)
        copyToolButton->setText(QString());
#if QT_CONFIG(tooltip)
        moveUpwardsToolButton->setToolTip(QCoreApplication::translate("PlotDialog", "Move the selected plots upwards.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        moveDownwardsToolButton->setToolTip(QCoreApplication::translate("PlotDialog", "Move the selected plots downwards.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        clearToolButton->setToolTip(QCoreApplication::translate("PlotDialog", "Clear all plots.", nullptr));
#endif // QT_CONFIG(tooltip)
        automaticUpdateCheckBox->setText(QCoreApplication::translate("PlotDialog", "Automatic update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlotDialog: public Ui_PlotDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOT_DIALOG_H
