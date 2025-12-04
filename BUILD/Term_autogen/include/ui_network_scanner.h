/********************************************************************************
** Form generated from reading UI file 'network_scanner.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORK_SCANNER_H
#define UI_NETWORK_SCANNER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_network_scanner
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLabel *label_5;
    QLineEdit *lineEdit_5;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_3;
    QTableWidget *tableWidget;

    void setupUi(QWidget *network_scanner)
    {
        if (network_scanner->objectName().isEmpty())
            network_scanner->setObjectName(QString::fromUtf8("network_scanner"));
        network_scanner->resize(660, 456);
        gridLayout = new QGridLayout(network_scanner);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(50, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(network_scanner);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(network_scanner);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(lineEdit);

        label_2 = new QLabel(network_scanner);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMaximumSize(QSize(10, 16777215));

        horizontalLayout->addWidget(label_2);

        lineEdit_2 = new QLineEdit(network_scanner);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);
        lineEdit_2->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(lineEdit_2);

        label_3 = new QLabel(network_scanner);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setMaximumSize(QSize(10, 16777215));

        horizontalLayout->addWidget(label_3);

        lineEdit_3 = new QLineEdit(network_scanner);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        sizePolicy.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy);
        lineEdit_3->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(lineEdit_3);

        label_4 = new QLabel(network_scanner);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setMaximumSize(QSize(10, 16777215));

        horizontalLayout->addWidget(label_4);

        lineEdit_4 = new QLineEdit(network_scanner);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        sizePolicy.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy);
        lineEdit_4->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(lineEdit_4);

        label_5 = new QLabel(network_scanner);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setMaximumSize(QSize(15, 16777215));

        horizontalLayout->addWidget(label_5);

        lineEdit_5 = new QLineEdit(network_scanner);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        sizePolicy.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy);
        lineEdit_5->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(lineEdit_5);

        checkBox = new QCheckBox(network_scanner);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);

        horizontalSpacer = new QSpacerItem(30, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(network_scanner);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_3 = new QSpacerItem(50, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        tableWidget = new QTableWidget(network_scanner);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(true);
        tableWidget->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(tableWidget, 1, 0, 1, 1);


        retranslateUi(network_scanner);

        QMetaObject::connectSlotsByName(network_scanner);
    } // setupUi

    void retranslateUi(QWidget *network_scanner)
    {
        network_scanner->setWindowTitle(QApplication::translate("network_scanner", "Nerwork Scan", nullptr));
        label->setText(QApplication::translate("network_scanner", "IP address range:", nullptr));
        lineEdit->setText(QApplication::translate("network_scanner", "192", nullptr));
        label_2->setText(QApplication::translate("network_scanner", ".", nullptr));
        lineEdit_2->setText(QApplication::translate("network_scanner", "168", nullptr));
        label_3->setText(QApplication::translate("network_scanner", ".", nullptr));
        lineEdit_3->setText(QApplication::translate("network_scanner", "61", nullptr));
        label_4->setText(QApplication::translate("network_scanner", ".", nullptr));
        lineEdit_4->setText(QApplication::translate("network_scanner", "1", nullptr));
        label_5->setText(QApplication::translate("network_scanner", "->", nullptr));
        lineEdit_5->setText(QApplication::translate("network_scanner", "20", nullptr));
        checkBox->setText(QApplication::translate("network_scanner", "monitor", nullptr));
        pushButton->setText(QApplication::translate("network_scanner", "Start Scan", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("network_scanner", "IP Address", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("network_scanner", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("network_scanner", "FTP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class network_scanner: public Ui_network_scanner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORK_SCANNER_H
