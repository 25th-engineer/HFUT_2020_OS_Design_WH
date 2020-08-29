#include "MemInitWindow.h"
#include <map>
#include <vector>
#include <stdlib.h>
#include "KWidgetUtils.h"
#include "define.h"
#include "MemoryWindow.h"
using namespace std;

extern pcb process;  //申明一个进程链表
extern int total_process;//进程总数
extern int Flash; //内存大小
extern int BLOCK;//页框大小

MemInitWindow::MemInitWindow(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
	Init();
}

MemInitWindow::~MemInitWindow()
{
}

void MemInitWindow::Init()
{
	InitUI();
	InitConnections();
}

void MemInitWindow::InitUI()
{
}

void MemInitWindow::InitConnections()
{
	connect(m_ui.btnNewPS, SIGNAL(clicked()), this, SLOT(OnCreatePS()));
	connect(m_ui.btnMemMng, SIGNAL(clicked()), this, SLOT(OnMemMng()));
	connect(m_ui.btnInputSegNum, SIGNAL(clicked()), this, SLOT(OnSegNum()));
}

void MemInitWindow::LoadData()
{
	UIQuery::SetValue(m_ui.lineEdit_memSize,"2048");
	UIQuery::SetValue(m_ui.lineEdit_pageSize,"512");

	UIQuery::SetValue(m_ui.lineEdit_ps_Name,"w");
	UIQuery::SetValue(m_ui.lineEdit_ps_SegNum,"2");
}
//OK
void MemInitWindow::OnMemMng()
{
	QString mem_size = UIQuery::GetValue(m_ui.lineEdit_memSize);
	QString block_size = UIQuery::GetValue(m_ui.lineEdit_pageSize);
	if (mem_size.trimmed() == "")
	{
        UIQuery::Alert("内存值不能为空!");
		return;
	}
	if (mem_size.toInt()<0)
	{
        UIQuery::Alert("内存大小值必须大于0，请重新输入!");
		return;
	}

	if (block_size.trimmed() == "")
	{
		UIQuery::Alert("请输入页框大小值！");
		return;
	}
	if (block_size.toInt()<0)
	{
        UIQuery::Alert("页框大小值必须大于0，请重新输入");
		return;
	}
	CreateMemory(mem_size.toInt(), block_size.toInt());
	InitProcess(&process);
	CreateProcessList();
	ApplyMemory();

	MemoryWindow* p1 = new MemoryWindow();
	p1->Enter();
    close();
}

void MemInitWindow::Enter()
{
    show();
    setFocus();
    activateWindow();
	LoadData();
}

void MemInitWindow::Exit()
{
    close();
}

void MemInitWindow::OnSegNum()
{
	int p_segNum = UIQuery::GetValue(m_ui.lineEdit_ps_SegNum).toInt();
	m_ui.tableWidget_ps_Section->clearContents();
	m_ui.tableWidget_ps_Section->setRowCount(p_segNum);
	for (int i=0;i <p_segNum;i++)
	{
		m_ui.tableWidget_ps_Section->setRowHeight(i, 32);
		m_ui.tableWidget_ps_Section->setItem(i, 0, new QTableWidgetItem("1"));
	}
}

void MemInitWindow::OnCreatePS()
{
	ProcessUnit ps;
	ps.name = UIQuery::GetValue(m_ui.lineEdit_ps_Name);
	ps.totalSeg = UIQuery::GetValue(m_ui.lineEdit_ps_SegNum).toInt();
	for (int i =0;i<ps.totalSeg;i++)
	{
		int sz = m_ui.tableWidget_ps_Section->item(i,0)->text().toInt();
		ps.segSizeList << QString::number(sz);
	}
	m_processList.push_back(ps);
	
	UpdateTable();
	//total_process = m_processList.size();
}

void MemInitWindow::CreateProcessList()//建立进程信息
{
	PCB* p, * s;
	Seg* m, * n;
	Pa* r, * t;
	p = process;
	int i, j, k;
	//printf("请输入进程总数:");
	//scanf("%d", &total_process);
	total_process = m_processList.size();
	for (i = 0; i < total_process; i++)
	{
		ProcessUnit ps = m_processList[i];
		s = (PCB*)malloc(sizeof(PCB));
		memcpy(s->name,ps.name.toStdString().c_str(),ps.name.size());
		//printf("\n请输入第%d个进程名:", i + 1);
		//scanf("%s", s->name);
		s->ID = i;
		s->total_segmet = ps.totalSeg;
		//printf("\n请输入该进程的段总数:");
		//scanf("%d", &s->total_segmet);
		InitSegment(&s->segm);
		n = s->segm;
		for (j = 0; j < s->total_segmet; j++)
		{
			m = (Seg*)malloc(sizeof(Seg));
			m->size = ps.segSizeList[j].toInt();
			//printf("\n请输入第%d个段的段大小: ", j + 1);
			//scanf("%d", &m->size);
			m->ID = j;
			m->in_out = 'N';
			InitPage(&m->page);
			t = m->page;
			for (k = 0; k < m->size / BLOCK; k++)
			{
				r = (Pa*)malloc(sizeof(Pa));
				r->block_num = -1;
				r->ID = k;
				r->in_out = 'N';
				r->time = 0;
				r->pageOffset = 0;
				r->Process_ID = i;
				r->Segment_ID = j;
				strcpy(r->name, s->name);
				t->next = r;
				t = t->next;
				t->next = NULL;
			}
			n->next = m;
			n = n->next;
			n->next = NULL;
		}
		p->next = s;
		p = p->next;
		p->next = NULL;
	}

}

void MemInitWindow::UpdateTable()
{
	int sz = m_processList.size();
	m_ui.tableWidget_ps_list->clearContents();
	m_ui.tableWidget_ps_list->setRowCount(sz);
	for (int i = 0;i < sz;++i)
	{
		m_ui.tableWidget_ps_list->setRowHeight(i, 32);
		m_ui.tableWidget_ps_list->setItem(i, 0, new QTableWidgetItem(m_processList[i].name));
		m_ui.tableWidget_ps_list->setItem(i, 1, new QTableWidgetItem(QString::number(m_processList[i].totalSeg)));
		m_ui.tableWidget_ps_list->setItem(i, 2, new QTableWidgetItem(m_processList[i].segSizeList.join("-")));
	}
}
