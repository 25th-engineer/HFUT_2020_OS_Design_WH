#pragma once

#include <QString>
#include <string>
#include <vector>
#include <QMessageBox>

using namespace std;

class QComboBox;
class QLineEdit;
class QPushButton;
class QLabel;
class QTextEdit;
class QCheckBox;
class QRadioButton;
class QSpinBox;
class QTableWidget;

namespace UIQuery
{
	void SetComboboxValue(QComboBox * pWidget,QString value,QStringList & range,int defaultValue);		
	QString GetValue(QComboBox * pWidget);
	QString GetValue(QLineEdit * pWidget);
	QString GetValue(QPushButton * pWidget);
	QString GetValue(QLabel * pWidget);
	QString GetValue(QTextEdit * pWidget);
	int GetValue(QSpinBox * pWidget);
	bool GetValue(QCheckBox * pWidget);
	bool GetValue(QRadioButton * pWidget);

	void SetValue(QCheckBox * pWidget,bool state);
	void SetValue(QLineEdit * pWidget,QString value);
	void SetValue(QRadioButton * pWidget,bool state);
	void SetValue(QComboBox * pWidget,std::vector<std::string> & valList);
	void SetValue(QComboBox * pWidget,QStringList & valList);
	void SetValue(QTextEdit * pWidget,QString value);
	void SetValue(QLabel * pWidget,QString value);
	void SetValue(QSpinBox * pWidget,int value);

	void InitTableOption(QTableWidget* pTable);

	void Alert(QString msg);
	bool VerifyEmpty(QString input,QString tip);

	void AppendText(QTextEdit* pTextEdit,const QString& qsrText, QColor c);
}