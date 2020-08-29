#pragma once

#include <string>
#include <QDialog>
#include "ui_MemoryWindow.h"
#include <memory>
#include "DisplayOption.h"
#include <vector>

using namespace std;

class QShowEvent;
class MemoryWindow : public QDialog
{
	Q_OBJECT
public:
	MemoryWindow(QWidget *pParent = NULL);
	virtual ~MemoryWindow();
public:
	void Enter();
	void Exit();

private:
	void Init();
	void InitUI();
	void InitConnections();
	void LoadData();
	void Apply(ProcessUnit ps);
	void Recycle(int ID);
	void PrintProcessSegment(int j);
	QString InterruptHanding(int id, int i, int j);
	
public slots:
	void OnCreatePS();
	void OnRecyle();
	void OnQueryPSInfo();
	void OnPrintMemory();
	void AddressExchange();
	void OnViewPageInfo(QTableWidgetItem *);
	void OnSegNum();
	
protected:
    void showEvent(QShowEvent *event);

private:
	Ui::MemoryWindow m_ui;
	vector<SegUnit> m_segList;
	map<int,vector<PageUnit>> m_blockMap;
};
