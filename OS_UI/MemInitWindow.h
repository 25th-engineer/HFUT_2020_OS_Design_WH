#pragma once

#include <string>
#include <QDialog>
#include "ui_MemInitWindow.h"
#include <memory>
#include "DisplayOption.h"

class QShowEvent;
class MemInitWindow : public QDialog
{
	Q_OBJECT
public:
	MemInitWindow(QWidget *pParent = NULL);
	virtual ~MemInitWindow();
public:
	void Enter();
	void Exit();

private:
	void Init();
	void InitUI();
	void InitConnections();
	void LoadData();
	void CreateProcessList();
	void UpdateTable();

public slots:
	void OnCreatePS();
    void OnMemMng();
	void OnSegNum();

private:
	Ui::MemInitWindow m_ui;
	vector<ProcessUnit> m_processList;
};
