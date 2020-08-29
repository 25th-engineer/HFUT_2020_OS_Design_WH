/********************************************************************************
** Form generated from reading UI file 'MemInitWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMINITWINDOW_H
#define UI_MEMINITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MemInitWindow
{
public:
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLineEdit *lineEdit_memSize;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QLineEdit *lineEdit_pageSize;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnMemMng;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPushButton *btnNewPS;
    QLineEdit *lineEdit_ps_SegNum;
    QLabel *label_4;
    QTableWidget *tableWidget_ps_Section;
    QLineEdit *lineEdit_ps_Name;
    QLabel *label_3;
    QPushButton *btnInputSegNum;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget_ps_list;

    void setupUi(QWidget *MemInitWindow)
    {
        if (MemInitWindow->objectName().isEmpty())
            MemInitWindow->setObjectName(QStringLiteral("MemInitWindow"));
        MemInitWindow->resize(708, 639);
        gridLayout_5 = new QGridLayout(MemInitWindow);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(MemInitWindow);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        lineEdit_memSize = new QLineEdit(groupBox);
        lineEdit_memSize->setObjectName(QStringLiteral("lineEdit_memSize"));
        lineEdit_memSize->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(lineEdit_memSize, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(258, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_pageSize = new QLineEdit(groupBox);
        lineEdit_pageSize->setObjectName(QStringLiteral("lineEdit_pageSize"));
        lineEdit_pageSize->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(lineEdit_pageSize, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(268, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 1, 2, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);

        btnMemMng = new QPushButton(groupBox);
        btnMemMng->setObjectName(QStringLiteral("btnMemMng"));
        btnMemMng->setMinimumSize(QSize(120, 40));

        gridLayout_4->addWidget(btnMemMng, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(MemInitWindow);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnNewPS = new QPushButton(groupBox_2);
        btnNewPS->setObjectName(QStringLiteral("btnNewPS"));

        gridLayout->addWidget(btnNewPS, 4, 0, 1, 2);

        lineEdit_ps_SegNum = new QLineEdit(groupBox_2);
        lineEdit_ps_SegNum->setObjectName(QStringLiteral("lineEdit_ps_SegNum"));
        lineEdit_ps_SegNum->setMinimumSize(QSize(100, 0));
        lineEdit_ps_SegNum->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(lineEdit_ps_SegNum, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(80, 0));
        label_4->setMaximumSize(QSize(80, 16777215));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        tableWidget_ps_Section = new QTableWidget(groupBox_2);
        if (tableWidget_ps_Section->columnCount() < 1)
            tableWidget_ps_Section->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_ps_Section->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget_ps_Section->setObjectName(QStringLiteral("tableWidget_ps_Section"));
        tableWidget_ps_Section->setMinimumSize(QSize(186, 0));
        tableWidget_ps_Section->setMaximumSize(QSize(180, 16777215));

        gridLayout->addWidget(tableWidget_ps_Section, 3, 0, 1, 2);

        lineEdit_ps_Name = new QLineEdit(groupBox_2);
        lineEdit_ps_Name->setObjectName(QStringLiteral("lineEdit_ps_Name"));
        lineEdit_ps_Name->setMinimumSize(QSize(100, 0));
        lineEdit_ps_Name->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(lineEdit_ps_Name, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(80, 0));
        label_3->setMaximumSize(QSize(80, 16777215));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        btnInputSegNum = new QPushButton(groupBox_2);
        btnInputSegNum->setObjectName(QStringLiteral("btnInputSegNum"));

        gridLayout->addWidget(btnInputSegNum, 2, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        tableWidget_ps_list = new QTableWidget(groupBox_2);
        if (tableWidget_ps_list->columnCount() < 3)
            tableWidget_ps_list->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_ps_list->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_ps_list->setHorizontalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_ps_list->setHorizontalHeaderItem(2, __qtablewidgetitem3);
        tableWidget_ps_list->setObjectName(QStringLiteral("tableWidget_ps_list"));
        tableWidget_ps_list->setMinimumSize(QSize(450, 0));

        horizontalLayout->addWidget(tableWidget_ps_list);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);


        gridLayout_5->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(MemInitWindow);

        QMetaObject::connectSlotsByName(MemInitWindow);
    } // setupUi

    void retranslateUi(QWidget *MemInitWindow)
    {
        MemInitWindow->setWindowTitle(QApplication::translate("MemInitWindow", "\350\277\233\347\250\213/\345\206\205\345\255\230\345\210\233\345\273\272", 0));
        groupBox->setTitle(QApplication::translate("MemInitWindow", "\345\206\205\345\255\230\351\242\204\350\256\276", 0));
        label->setText(QApplication::translate("MemInitWindow", "\350\257\267\350\276\223\345\205\245\345\206\205\345\255\230\345\244\247\345\260\217", 0));
        label_2->setText(QApplication::translate("MemInitWindow", "\350\257\267\350\276\223\345\205\245\351\241\265\346\241\206\345\244\247\345\260\217", 0));
        btnMemMng->setText(QApplication::translate("MemInitWindow", "\350\277\233\345\205\245\345\206\205\345\255\230\350\277\233\347\250\213\347\256\241\347\220\206", 0));
        groupBox_2->setTitle(QApplication::translate("MemInitWindow", "\350\277\233\347\250\213\351\242\204\350\256\276", 0));
        btnNewPS->setText(QApplication::translate("MemInitWindow", "\345\210\233\345\273\272\346\226\260\350\277\233\347\250\213", 0));
        label_4->setText(QApplication::translate("MemInitWindow", "\350\277\233\347\250\213\346\256\265\346\200\273\346\225\260", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_ps_Section->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MemInitWindow", "\346\256\265\345\244\247\345\260\217", 0));
        label_3->setText(QApplication::translate("MemInitWindow", "\350\277\233\347\250\213\345\220\215", 0));
        btnInputSegNum->setText(QApplication::translate("MemInitWindow", "\347\241\256\350\256\244", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_ps_list->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("MemInitWindow", "\350\277\233\347\250\213\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_ps_list->horizontalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("MemInitWindow", "\350\277\233\347\250\213\346\256\265\346\200\273\346\225\260", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_ps_list->horizontalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("MemInitWindow", "\350\277\233\347\250\213\346\256\265\345\220\204\345\244\247\345\260\217", 0));
    } // retranslateUi

};

namespace Ui {
    class MemInitWindow: public Ui_MemInitWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEMINITWINDOW_H
