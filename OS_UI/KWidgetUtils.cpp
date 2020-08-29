#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QRadioButton>
#include <QCheckBox>
#include <QMessageBox>
#include <QSpinBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QScrollBar>
#include <QApplication>

namespace UIQuery
{
	void SetComboboxValue(QComboBox * pWidget,QString value,QStringList & range,int defaultValue)
	{
		if ( range.contains(value) == true )
		{
			pWidget->setCurrentText(value);
		}
		else
		{
			pWidget->setCurrentText(QString::number(defaultValue));
		}
	}

	QString GetValue(QComboBox * pWidget)
	{
		if (pWidget != NULL)
		{
			return pWidget->currentText();
		}
		return "";
	}

	int GetValue(QSpinBox * pWidget)
	{
		if (pWidget != NULL)
		{
			return pWidget->value();	
		}
		return 0;
	}

	QString GetValue(QLineEdit * pWidget)
	{
		if (pWidget != NULL)
		{
			return pWidget->text();
		}
		return "";
	}

	QString GetValue(QPushButton * pWidget)
	{
		if (pWidget != NULL)
		{
			return pWidget->text();	
		}
		return "";
	}

	QString GetValue(QLabel * pWidget)
	{
		if (pWidget != NULL)
		{
			return pWidget->text();
		}
		return "";
	}

	QString GetValue(QTextEdit * pWidget)
	{
		if (pWidget != NULL)
		{
			return pWidget->toPlainText();
		}
		return "";
	}

	bool GetValue(QCheckBox * pWidget)
	{
		if (pWidget != NULL)
		{
			return pWidget->isChecked();
		}
		return false;
	}

	bool GetValue(QRadioButton * pWidget)
	{
		if (pWidget != NULL)
		{
			return pWidget->isChecked();
		}
		return false;
	}

	void SetValue(QCheckBox * pWidget,bool state)
	{
		if (pWidget == NULL)
		{
			return;
		}
		pWidget->setCheckState( (state==true) ? (Qt::Checked) : (Qt::Unchecked) );
	}

	void SetValue(QLineEdit * pWidget,QString value)
	{
		if (pWidget == NULL)
		{
			return;
		}
		pWidget->setText(value);
	}

	void SetValue(QLabel * pWidget,QString value)
	{
		if (pWidget == NULL)
		{
			return;
		}
		pWidget->setText(value);
	}

	void SetValue(QSpinBox * pWidget,int value)
	{
		if (pWidget == NULL)
		{
			return;
		}
		pWidget->setValue(value);
	}

	void SetValue(QRadioButton * pWidget,bool state)
	{
		if (pWidget == NULL)
		{
			return;
		}
		pWidget->setChecked(state);
	}

	void SetValue(QComboBox * pWidget,std::vector<std::string> & valList)
	{
		if (pWidget == NULL)
		{
			return;
		}
		pWidget->clear();
		for(auto val : valList)
		{
			pWidget->addItem(QString::fromStdString(val));
		}
	}

	void SetValue(QComboBox * pWidget,QStringList & valList)
	{
		if (pWidget == NULL)
		{
			return;
		}
		pWidget->clear();
		pWidget->addItems(valList);
	}

	void SetValue(QTextEdit * pWidget,QString value)
	{
		if (pWidget == NULL)
		{
			return;
		}
		pWidget->setPlainText(value);
	}

	void Alert(QString msg)
	{
		QMessageBox msgBox;
		msgBox.setText(msg);
		msgBox.exec();
	}

	bool VerifyEmpty(QString input,QString tip)
	{
		if (input.trimmed().isEmpty())
		{
			Alert(tip);
			return true;
		}
		return false;
	}

	void InitTableOption(QTableWidget* pTable)
	{
		pTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    		pTable->horizontalHeader()->setSectionsMovable(false);
		pTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
		pTable->horizontalHeader()->setSectionsClickable(false);
		pTable->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
		pTable->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
		pTable->setSelectionBehavior(QAbstractItemView::SelectRows);
		pTable->setSelectionMode(QAbstractItemView::SingleSelection);
		pTable->setDragDropMode(QAbstractItemView::NoDragDrop);
	}

	void AppendText(QTextEdit* pTextEdit,const QString& qsrText, QColor c)
	{
		if (pTextEdit == NULL)
		{
			return;
		}

		pTextEdit->setTextColor(c);
		pTextEdit->insertPlainText(qsrText.trimmed() + "\n");
		pTextEdit->moveCursor(QTextCursor::End);
	    QScrollBar* p_scrollbar = pTextEdit->verticalScrollBar();
	    p_scrollbar->setSliderPosition(p_scrollbar->maximum());
	    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
	}
}

