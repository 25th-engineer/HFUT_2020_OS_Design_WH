/********************************************************************************
** Form generated from reading UI file 'MemoryWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMORYWINDOW_H
#define UI_MEMORYWINDOW_H

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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MemoryWindow
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit_ps_name;
    QLabel *label_4;
    QLineEdit *lineEdit_ps_SegNum;
    QTableWidget *tableWidget_ps_Section;
    QPushButton *btnNewPS;
    QPushButton *btnSegSize;
    QWidget *tab_2;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_7;
    QLabel *label;
    QLineEdit *lineEdit_pid_2;
    QPushButton *btnRecycle;
    QWidget *tab_3;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_memSize;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    QLineEdit *lineEdit_tBlocks;
    QLabel *label_6;
    QLineEdit *lineEdit_bSize;
    QLabel *label_7;
    QTableWidget *tableWidget_memList;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_MemCount;
    QPushButton *btnViewMem;
    QWidget *tab_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_ps_name;
    QLabel *label_ps_id;
    QTableWidget *tableWidget_sectionList;
    QTableWidget *tableWidget_pageList;
    QWidget *widget;
    QGridLayout *gridLayout_8;
    QLabel *label_9;
    QLineEdit *lineEdit_ps_pid;
    QPushButton *btnQueryPSInfo;
    QWidget *tab;
    QWidget *widget1;
    QGridLayout *gridLayout_6;
    QLabel *label_12;
    QTextEdit *textEdit_log;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLineEdit *lineEdit_page_id;
    QPushButton *btnPageID;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit_ps_id;
    QLineEdit *lineEdit_seg_sAddress;
    QLineEdit *lineEdit_seg_id;

    void setupUi(QWidget *MemoryWindow)
    {
        if (MemoryWindow->objectName().isEmpty())
            MemoryWindow->setObjectName(QStringLiteral("MemoryWindow"));
        MemoryWindow->resize(780, 641);
        gridLayout = new QGridLayout(MemoryWindow);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(MemoryWindow);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        layoutWidget = new QWidget(tab_1);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 191, 551));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(80, 0));
        label_3->setMaximumSize(QSize(80, 16777215));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        lineEdit_ps_name = new QLineEdit(layoutWidget);
        lineEdit_ps_name->setObjectName(QStringLiteral("lineEdit_ps_name"));
        lineEdit_ps_name->setMinimumSize(QSize(100, 0));
        lineEdit_ps_name->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(lineEdit_ps_name, 0, 1, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(80, 0));
        label_4->setMaximumSize(QSize(80, 16777215));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        lineEdit_ps_SegNum = new QLineEdit(layoutWidget);
        lineEdit_ps_SegNum->setObjectName(QStringLiteral("lineEdit_ps_SegNum"));
        lineEdit_ps_SegNum->setMinimumSize(QSize(100, 0));
        lineEdit_ps_SegNum->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(lineEdit_ps_SegNum, 1, 1, 1, 1);

        tableWidget_ps_Section = new QTableWidget(layoutWidget);
        if (tableWidget_ps_Section->columnCount() < 1)
            tableWidget_ps_Section->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_ps_Section->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget_ps_Section->setObjectName(QStringLiteral("tableWidget_ps_Section"));
        tableWidget_ps_Section->setMinimumSize(QSize(186, 0));
        tableWidget_ps_Section->setMaximumSize(QSize(180, 16777215));

        gridLayout_2->addWidget(tableWidget_ps_Section, 3, 0, 1, 2);

        btnNewPS = new QPushButton(layoutWidget);
        btnNewPS->setObjectName(QStringLiteral("btnNewPS"));

        gridLayout_2->addWidget(btnNewPS, 4, 0, 1, 2);

        btnSegSize = new QPushButton(layoutWidget);
        btnSegSize->setObjectName(QStringLiteral("btnSegSize"));

        gridLayout_2->addWidget(btnSegSize, 2, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        layoutWidget1 = new QWidget(tab_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 31, 216, 43));
        gridLayout_7 = new QGridLayout(layoutWidget1);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_7->addWidget(label, 0, 0, 1, 2);

        lineEdit_pid_2 = new QLineEdit(layoutWidget1);
        lineEdit_pid_2->setObjectName(QStringLiteral("lineEdit_pid_2"));

        gridLayout_7->addWidget(lineEdit_pid_2, 1, 0, 1, 1);

        btnRecycle = new QPushButton(layoutWidget1);
        btnRecycle->setObjectName(QStringLiteral("btnRecycle"));

        gridLayout_7->addWidget(btnRecycle, 1, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        layoutWidget2 = new QWidget(tab_3);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 20, 731, 561));
        gridLayout_4 = new QGridLayout(layoutWidget2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 0, 0, 2, 1);

        lineEdit_memSize = new QLineEdit(layoutWidget2);
        lineEdit_memSize->setObjectName(QStringLiteral("lineEdit_memSize"));

        gridLayout_3->addWidget(lineEdit_memSize, 0, 1, 2, 1);

        horizontalSpacer = new QSpacerItem(258, 38, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 2, 2, 1);

        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 0, 3, 1, 1);

        lineEdit_tBlocks = new QLineEdit(layoutWidget2);
        lineEdit_tBlocks->setObjectName(QStringLiteral("lineEdit_tBlocks"));

        gridLayout_3->addWidget(lineEdit_tBlocks, 0, 4, 1, 1);

        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 1, 3, 1, 1);

        lineEdit_bSize = new QLineEdit(layoutWidget2);
        lineEdit_bSize->setObjectName(QStringLiteral("lineEdit_bSize"));

        gridLayout_3->addWidget(lineEdit_bSize, 1, 4, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 2);

        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName(QStringLiteral("label_7"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_7, 1, 0, 1, 2);

        tableWidget_memList = new QTableWidget(layoutWidget2);
        if (tableWidget_memList->columnCount() < 5)
            tableWidget_memList->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_memList->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_memList->setHorizontalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_memList->setHorizontalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_memList->setHorizontalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_memList->setHorizontalHeaderItem(4, __qtablewidgetitem5);
        tableWidget_memList->setObjectName(QStringLiteral("tableWidget_memList"));

        gridLayout_4->addWidget(tableWidget_memList, 2, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(498, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 4, 0, 1, 1);

        label_MemCount = new QLabel(layoutWidget2);
        label_MemCount->setObjectName(QStringLiteral("label_MemCount"));
        label_MemCount->setMinimumSize(QSize(200, 0));
        label_MemCount->setStyleSheet(QStringLiteral("QLabel{color:blue;}"));
        label_MemCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_MemCount, 4, 1, 1, 1);

        btnViewMem = new QPushButton(layoutWidget2);
        btnViewMem->setObjectName(QStringLiteral("btnViewMem"));

        gridLayout_4->addWidget(btnViewMem, 5, 0, 1, 2);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        groupBox = new QGroupBox(tab_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(390, 10, 351, 71));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_ps_name = new QLabel(groupBox);
        label_ps_name->setObjectName(QStringLiteral("label_ps_name"));

        horizontalLayout_3->addWidget(label_ps_name);

        label_ps_id = new QLabel(groupBox);
        label_ps_id->setObjectName(QStringLiteral("label_ps_id"));

        horizontalLayout_3->addWidget(label_ps_id);


        gridLayout_5->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        tableWidget_sectionList = new QTableWidget(tab_4);
        if (tableWidget_sectionList->columnCount() < 3)
            tableWidget_sectionList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_sectionList->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_sectionList->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_sectionList->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        tableWidget_sectionList->setObjectName(QStringLiteral("tableWidget_sectionList"));
        tableWidget_sectionList->setGeometry(QRect(10, 90, 311, 491));
        tableWidget_pageList = new QTableWidget(tab_4);
        if (tableWidget_pageList->columnCount() < 4)
            tableWidget_pageList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_pageList->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_pageList->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_pageList->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_pageList->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        tableWidget_pageList->setObjectName(QStringLiteral("tableWidget_pageList"));
        tableWidget_pageList->setGeometry(QRect(330, 90, 411, 491));
        widget = new QWidget(tab_4);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 12, 341, 61));
        gridLayout_8 = new QGridLayout(widget);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(widget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_8->addWidget(label_9, 0, 0, 1, 2);

        lineEdit_ps_pid = new QLineEdit(widget);
        lineEdit_ps_pid->setObjectName(QStringLiteral("lineEdit_ps_pid"));

        gridLayout_8->addWidget(lineEdit_ps_pid, 1, 0, 1, 1);

        btnQueryPSInfo = new QPushButton(widget);
        btnQueryPSInfo->setObjectName(QStringLiteral("btnQueryPSInfo"));

        gridLayout_8->addWidget(btnQueryPSInfo, 1, 1, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        widget1 = new QWidget(tab);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(11, 21, 731, 571));
        gridLayout_6 = new QGridLayout(widget1);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(widget1);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_6->addWidget(label_12, 0, 0, 1, 2);

        textEdit_log = new QTextEdit(widget1);
        textEdit_log->setObjectName(QStringLiteral("textEdit_log"));
        textEdit_log->setMinimumSize(QSize(500, 0));

        gridLayout_6->addWidget(textEdit_log, 0, 2, 9, 1);

        label_13 = new QLabel(widget1);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_6->addWidget(label_13, 2, 0, 1, 2);

        label_14 = new QLabel(widget1);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_6->addWidget(label_14, 4, 0, 1, 2);

        label_15 = new QLabel(widget1);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_6->addWidget(label_15, 6, 0, 1, 2);

        lineEdit_page_id = new QLineEdit(widget1);
        lineEdit_page_id->setObjectName(QStringLiteral("lineEdit_page_id"));

        gridLayout_6->addWidget(lineEdit_page_id, 7, 0, 1, 1);

        btnPageID = new QPushButton(widget1);
        btnPageID->setObjectName(QStringLiteral("btnPageID"));
        btnPageID->setMinimumSize(QSize(0, 0));

        gridLayout_6->addWidget(btnPageID, 7, 1, 1, 1);

        verticalSpacer = new QSpacerItem(208, 278, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 8, 0, 1, 2);

        lineEdit_ps_id = new QLineEdit(widget1);
        lineEdit_ps_id->setObjectName(QStringLiteral("lineEdit_ps_id"));

        gridLayout_6->addWidget(lineEdit_ps_id, 1, 0, 1, 2);

        lineEdit_seg_sAddress = new QLineEdit(widget1);
        lineEdit_seg_sAddress->setObjectName(QStringLiteral("lineEdit_seg_sAddress"));

        gridLayout_6->addWidget(lineEdit_seg_sAddress, 3, 0, 1, 2);

        lineEdit_seg_id = new QLineEdit(widget1);
        lineEdit_seg_id->setObjectName(QStringLiteral("lineEdit_seg_id"));

        gridLayout_6->addWidget(lineEdit_seg_id, 5, 0, 1, 2);

        tabWidget->addTab(tab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(MemoryWindow);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MemoryWindow);
    } // setupUi

    void retranslateUi(QWidget *MemoryWindow)
    {
        MemoryWindow->setWindowTitle(QApplication::translate("MemoryWindow", "\345\206\205\345\255\230-\350\277\233\347\250\213\347\256\241\347\220\206", 0));
        label_3->setText(QApplication::translate("MemoryWindow", "\350\277\233\347\250\213\345\220\215", 0));
        label_4->setText(QApplication::translate("MemoryWindow", "\350\277\233\347\250\213\346\256\265\346\200\273\346\225\260", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_ps_Section->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MemoryWindow", "\346\256\265\345\244\247\345\260\217", 0));
        btnNewPS->setText(QApplication::translate("MemoryWindow", "\345\210\233\345\273\272\346\226\260\350\277\233\347\250\213", 0));
        btnSegSize->setText(QApplication::translate("MemoryWindow", "\347\241\256\350\256\244", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("MemoryWindow", "\347\224\263\350\257\267\345\206\205\345\255\230", 0));
        label->setText(QApplication::translate("MemoryWindow", "\350\257\267\350\276\223\345\205\245\350\277\233\347\250\213\345\217\267", 0));
        btnRecycle->setText(QApplication::translate("MemoryWindow", "\346\211\247\350\241\214", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MemoryWindow", "\345\233\236\346\224\266\345\206\205\345\255\230", 0));
        label_2->setText(QApplication::translate("MemoryWindow", "\345\206\205\345\255\230\345\244\247\345\260\217", 0));
        label_5->setText(QApplication::translate("MemoryWindow", "\346\200\273\345\235\227\346\225\260", 0));
        label_6->setText(QApplication::translate("MemoryWindow", "\346\257\217\345\235\227\345\244\247\345\260\217", 0));
        label_7->setText(QApplication::translate("MemoryWindow", "\345\267\262\345\210\206\351\205\215\345\206\205\345\255\230\345\235\227\350\257\246\346\203\205", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_memList->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("MemoryWindow", "\350\277\233\347\250\213\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_memList->horizontalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("MemoryWindow", "\350\277\233\347\250\213\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_memList->horizontalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("MemoryWindow", "\350\277\233\347\250\213\346\256\265\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_memList->horizontalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("MemoryWindow", "\351\241\265\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_memList->horizontalHeaderItem(4);
        ___qtablewidgetitem5->setText(QApplication::translate("MemoryWindow", "\345\235\227\345\217\267", 0));
        label_MemCount->setText(QApplication::translate("MemoryWindow", "\345\205\261\345\215\240\347\224\250", 0));
        btnViewMem->setText(QApplication::translate("MemoryWindow", "\344\277\241\346\201\257\346\237\245\350\257\242", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MemoryWindow", "\345\206\205\345\255\230\346\230\276\347\244\272", 0));
        groupBox->setTitle(QApplication::translate("MemoryWindow", "\350\277\233\347\250\213\344\277\241\346\201\257", 0));
        label_ps_name->setText(QApplication::translate("MemoryWindow", "\350\277\233\347\250\213\345\220\215", 0));
        label_ps_id->setText(QApplication::translate("MemoryWindow", "\350\277\233\347\250\213\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_sectionList->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("MemoryWindow", "\346\256\265\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_sectionList->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("MemoryWindow", "\346\256\265\345\244\247\345\260\217", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_sectionList->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("MemoryWindow", "\346\230\257\345\220\246\345\234\250\345\206\205\345\255\230", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_pageList->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("MemoryWindow", "\351\241\265\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_pageList->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QApplication::translate("MemoryWindow", "\351\241\265\345\206\205\345\201\217\347\247\273", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_pageList->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QApplication::translate("MemoryWindow", "\345\235\227\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_pageList->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QApplication::translate("MemoryWindow", "\346\230\257\345\220\246\345\255\230\345\234\250\345\206\205\345\255\230", 0));
        label_9->setText(QApplication::translate("MemoryWindow", "\350\257\267\350\276\223\345\205\245\350\246\201\346\230\276\347\244\272\345\276\227\350\277\233\347\250\213\345\217\267", 0));
        btnQueryPSInfo->setText(QApplication::translate("MemoryWindow", "\346\237\245\350\257\242", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MemoryWindow", "\350\277\233\347\250\213\351\241\265\350\241\250\346\230\276\347\244\272", 0));
        label_12->setText(QApplication::translate("MemoryWindow", "\350\257\267\350\276\223\345\205\245\350\246\201\346\230\276\347\244\272\345\276\227\350\277\233\347\250\213\345\217\267", 0));
        label_13->setText(QApplication::translate("MemoryWindow", "\350\257\267\350\276\223\345\205\245\346\256\265\350\241\250\350\265\267\345\247\213\345\234\260\345\235\200", 0));
        label_14->setText(QApplication::translate("MemoryWindow", "\350\257\267\350\276\223\345\205\245\346\256\265\345\217\267", 0));
        label_15->setText(QApplication::translate("MemoryWindow", "\350\257\267\350\276\223\345\205\245\351\241\265\345\217\267", 0));
        btnPageID->setText(QApplication::translate("MemoryWindow", "\346\237\245\350\257\242", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MemoryWindow", "\345\234\260\345\235\200\350\275\254\346\215\242", 0));
    } // retranslateUi

};

namespace Ui {
    class MemoryWindow: public Ui_MemoryWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEMORYWINDOW_H
