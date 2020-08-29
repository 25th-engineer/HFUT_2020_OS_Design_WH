#include "MemoryWindow.h"
#include <map>
#include <vector>
#include <stdlib.h>
#ifdef __linux__
#include <sys/time.h>
#endif
#include <QShowEvent>
#include <QCursor>
#include "KWidgetUtils.h"
#include "define.h"

extern memory memory_info;
extern pcb process;
extern int BLOCK;//ҳ���С
extern int remained;//ʣ����ڴ�
extern int Register;//�α����ʼ��ַ
extern int Flash; //�ڴ��С
extern int total_process;//��������
extern  memory memory_info;//����һ����¼�ڴ���Ϣ������
extern  int InterruptType;//�ж�����,1��ʾȱ���жϣ�0��ʾȱҳ�ж�

using namespace std;

MemoryWindow::MemoryWindow(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
	Init();
}

MemoryWindow::~MemoryWindow()
{
}

void MemoryWindow::Init()
{
	InitUI();
	InitConnections();
}

void MemoryWindow::InitUI()
{
}

void MemoryWindow::InitConnections()
{
	connect(m_ui.btnPageID, SIGNAL(clicked()), this, SLOT(AddressExchange()));
	//connect(m_ui.btnQueryPID, SIGNAL(clicked()), this, SLOT(OnQueryPID()));
	connect(m_ui.btnNewPS, SIGNAL(clicked()), this, SLOT(OnCreatePS()));
	connect(m_ui.btnSegSize, SIGNAL(clicked()), this, SLOT(OnSegNum()));
	connect(m_ui.btnRecycle, SIGNAL(clicked()), this, SLOT(OnRecyle()));
	//connect(m_ui.btnQuerySegStart, SIGNAL(clicked()), this, SLOT(OnQuerySegStart()));
	connect(m_ui.btnQueryPSInfo, SIGNAL(clicked()), this, SLOT(OnQueryPSInfo()));
	//connect(m_ui.btnSegNum, SIGNAL(clicked()), this, SLOT(OnQuerySegNum()));
	connect(m_ui.btnViewMem, SIGNAL(clicked()), this, SLOT(OnPrintMemory()));
	
	connect(m_ui.tableWidget_sectionList, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(OnViewPageInfo(QTableWidgetItem *)));
	
}


void MemoryWindow::LoadData()
{
}

void MemoryWindow::OnSegNum()
{
	int p_segNum = UIQuery::GetValue(m_ui.lineEdit_ps_SegNum).toInt();
	m_ui.tableWidget_ps_Section->clearContents();
	m_ui.tableWidget_ps_Section->setRowCount(p_segNum);
	for (int i=0;i <p_segNum;i++)
	{
		m_ui.tableWidget_ps_Section->setRowHeight(i, 32);
		m_ui.tableWidget_ps_Section->setItem(i, 0, new QTableWidgetItem("809200"));
	}
}

void MemoryWindow::Enter()
{
    show();
    setFocus();
    activateWindow();
    exec();
}

void MemoryWindow::Exit()
{
    close();
}



void MemoryWindow::OnCreatePS()
{
	ProcessUnit ps;
	ps.name = UIQuery::GetValue(m_ui.lineEdit_ps_name);
	ps.totalSeg = UIQuery::GetValue(m_ui.lineEdit_ps_SegNum).toInt();
	for (int i =0;i<ps.totalSeg;i++)
	{
		int sz = m_ui.tableWidget_ps_Section->item(i,0)->text().toInt();
		ps.segSizeList << QString::number(sz);
	}
	Apply(ps);
}

//�ֶ������ڴ�
void MemoryWindow::Apply(ProcessUnit ps)
{
	PCB* p, * s;
	Seg* m = NULL, * n;
	Pa* r = NULL, * t;
	Memory* mer;
	mer = memory_info->next;
	int max;
	int j;
	int k;
	int sum = 0;//��¼���̵Ĵ�С
	//printf("�����������:");
	s = (PCB*)malloc(sizeof(PCB));
	//scanf("%s", s->name);
	memcpy(s->name,ps.name.toStdString().c_str(),ps.name.size()+1);
	p = process;
	while (p->next != NULL)
		p = p->next;
	s->ID = p->ID + 1;
	s->total_segmet = ps.totalSeg;
	//printf("\n������ý����ܶ���:");
	//scanf("%d", &s->total_segmet);
	InitSegment(&s->segm);
	n = s->segm;
	for (j = 0; j < s->total_segmet; j++)
	{
		m = (Seg*)malloc(sizeof(Seg));
		//printf("\n�������%d���εĶδ�С: ", j + 1);
		//scanf("%d", &m->size);
		m->size = ps.segSizeList[j].toInt();
		sum += m->size;
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
			t->next = r;
			t = t->next;
			t->next = NULL;
		}
		n->next = m;
		n = n->next;
		n->next = NULL;
	}
	//�ж��Ƿ�Ϸ�
	if (sum > remained)
	{
		UIQuery::Alert("����ռ����,����������!");
		sum = 0;
		//�ͷſռ�
		free(r);
		free(m);
		free(s);
	}
	else//���ڴ���ѡ����п���ý���
	{
		p->next = s;
		p = p->next;
		p->next = NULL;
		n = p->segm->next;
		max = mer->recently;
		while (mer != NULL)
		{
			if (mer->recently > max)
			{
				max = mer->recently;
				mer = mer->next;
			}
			else mer = mer->next;
		}
		mer = memory_info->next;
		for (j = 0; j < p->total_segmet; j++)
		{
			n->in_out = 'Y';
			t = n->page->next;
			for (k = 0; k < n->size / BLOCK; k++)
			{
				t->in_out = 'Y';
				t->time += 1;
				//����memory�ռ䣬�ҵ�δ����Ŀռ�
				while (mer->allocated != 'N')
					mer = mer->next;
				t->block_num = mer->ID;
				mer->allocated = 'Y';
				mer->recently = max + 1;
				mer->Process_ID = p->ID;
				mer->Segment_ID = n->ID;
				mer->Page_ID = t->ID;
				mer->time_in_memory = t->time;
				strcpy(mer->name, p->name);
				t->pageOffset = t->ID + t->block_num;
				if (t->pageOffset >= Flash)
					t->pageOffset -= Flash;
				mer = memory_info->next;
				t = t->next;
			}
			n = n->next;
		}
		remained -= sum;
		total_process++;
	}
}

//�ڴ����
void MemoryWindow::Recycle(int ID)
{
	Memory* mer;
	PCB* p;
	Seg* s;
	Pa* q;
	//int ID;//Ҫ���յĽ��̺�
	//printf("��������̺�:\n");
	//scanf("%d", &ID);
	//�޸��ڴ���Ϣ
	mer = memory_info->next;
	while (mer != NULL)
	{
		if (mer->Process_ID == ID)
		{
			mer->allocated = 'N';
			mer->Page_ID = -1;
			mer->Process_ID = -1;
			mer->Segment_ID = -1;
			mer->recently = 0;
			mer->time_in_memory = 0;
			remained += BLOCK;
			mer = mer->next;
		}
		else
			mer = mer->next;
	}
	//�޸Ľ�����Ϣ
	p = process->next;
	while (p != NULL)
	{
		if (p->ID == ID)
		{
			s = p->segm->next;
			while (s != NULL)
			{
				q = s->page->next;
				while (q != NULL)
				{
					s->in_out = 'N';
					q->in_out = 'N';
					q->pageOffset = 0;
					q->block_num = -1;
					q->time = 0;
					q->Process_ID = -1;
					q->Segment_ID = -1;
					q = q->next;
				}
				s = s->next;
			}
			break;
		}
		else
			p = p->next;
	}
}

void MemoryWindow::OnRecyle()
{
	int ID = UIQuery::GetValue(m_ui.lineEdit_pid_2).toInt();
	Recycle(ID);
}



void MemoryWindow::OnQueryPSInfo()
{
	int pid = UIQuery::GetValue(m_ui.lineEdit_ps_pid).toInt();
	PrintProcessSegment(pid);
}

//��ӡ���̶α���Ϣ
void MemoryWindow::PrintProcessSegment(int j)
{
	int i;
	PCB* pro;
	Seg* p;
	Pa* s;
	pro = process->next;
	//printf("\n������Ҫ��ʾ�Ľ��̺���Ϣ:");
	//scanf("%d", &j);
	while (pro != NULL)
	{
		if (pro->ID == j)
			break;
		else
			pro = pro->next;
	}
	if (pro == NULL)
	{
		printf("\nERROR\n");
		UIQuery::Alert("δ�ҵ�Ŀ����̺�");
		return;
	}

	p = pro->segm->next;
	printf("\n������Ϣ:\n");
	//printf("������:%s", pro->name);
	UIQuery::SetValue(m_ui.label_ps_name,QString("ProcessName:%1").arg( pro->name));
	//printf("\n���̺�:%d\n\n", pro->ID);
	UIQuery::SetValue(m_ui.label_ps_id,QString("ProcessID:%1").arg( pro->ID));
	
	m_segList.clear();
	m_blockMap.clear();
	while (p != NULL)
	{
		s = p->page->next;
		SegUnit unit;
		unit.ID = p->ID;
		unit.size = p->size;
		unit.in_out = p->in_out;
		
		m_segList.push_back(unit);
		
		//printf("�κ�:%d\t�δ�С:%d\t�Ƿ����ڴ�:%c\n", p->ID, p->size, p->in_out);
		//printf("����ҳ��:\n");
		
		vector<PageUnit> pgList;
		pgList.clear();
		for (i = 0; i < p->size / BLOCK; i++)
		{
			PageUnit pUnit;
			printf("ҳ��:%d\tҳ��ƫ��:%d\t���:%d\t�Ƿ�����ڴ�:%c\n", s->ID, s->pageOffset, s->block_num, s->in_out);
			pUnit.ID = s->ID;
			pUnit.pageOffset = s->pageOffset;
			pUnit.block_num = s->block_num;
			pUnit.in_out = s->in_out;
			s = s->next;
			pgList.push_back(pUnit);
		}
		m_blockMap.insert(make_pair(p->ID,pgList));
		printf("\n");
		p = p->next; 
	}

	m_ui.tableWidget_sectionList->clearContents();
	int seg_sz = m_segList.size();
	m_ui.tableWidget_sectionList->setRowCount(seg_sz);
	for (int i =0;i<seg_sz;i++)
	{
		m_ui.tableWidget_sectionList->setRowHeight(i, 32);
		m_ui.tableWidget_sectionList->setItem(i, 0, new QTableWidgetItem(QString::number(m_segList[i].ID)));
		m_ui.tableWidget_sectionList->setItem(i, 1, new QTableWidgetItem(QString::number(m_segList[i].size)));
		m_ui.tableWidget_sectionList->setItem(i, 2, new QTableWidgetItem(m_segList[i].in_out));
	}
}

void MemoryWindow::OnViewPageInfo(QTableWidgetItem *)
{
	int row = m_ui.tableWidget_sectionList->currentRow();
	if (row < 0 || row >= m_segList.size())
	{
		return;
	}
	
	int seg_id = m_segList[row].ID;
	if (m_blockMap.find(seg_id) == m_blockMap.end())
	{
		return;
	}
	
	auto blockList = m_blockMap[seg_id];
	int sz = blockList.size();
	
	m_ui.tableWidget_pageList->clearContents();
	m_ui.tableWidget_pageList->setRowCount(sz);

	for (int i =0;i<sz;i++)
	{
		m_ui.tableWidget_pageList->setRowHeight(i, 32);
		m_ui.tableWidget_pageList->setItem(i, 0, new QTableWidgetItem(QString::number(blockList[i].ID)));
		m_ui.tableWidget_pageList->setItem(i, 1, new QTableWidgetItem(QString::number(blockList[i].pageOffset)));
		m_ui.tableWidget_pageList->setItem(i, 2, new QTableWidgetItem(QString::number(blockList[i].block_num)));
		m_ui.tableWidget_pageList->setItem(i, 3, new QTableWidgetItem(blockList[i].in_out));
	}
}


//��ӡ�ڴ������Ϣ
void MemoryWindow::OnPrintMemory()
{
	int flag = 1;
	PCB* p;
	Seg* s;
	Memory* m;
	Pa* pag;
	p = process->next;
	m = memory_info->next;
	s = p->segm->next;
	pag = s->page->next;
	//printf("\n�ڴ��СΪ:%d", Flash);
	UIQuery::SetValue(m_ui.lineEdit_memSize,QString::number(Flash));
	//printf("\t�ܹ��ֳ���%d��,ÿ��Ϊ:%d", , BLOCK);
	UIQuery::SetValue(m_ui.lineEdit_tBlocks,QString::number(Flash / BLOCK));
	UIQuery::SetValue(m_ui.lineEdit_bSize,QString::number(BLOCK));
	printf("\n�ѷ�����ڴ�����Ϊ:");
	vector<MemUnit> memList;
	memList.clear();
	while (m != NULL)
	{
		if (m->allocated == 'Y')
		{
			//printf("\n������\t���̺�\t���̶κ�\tҳ��\t���\n");
			printf("%s\t%d\t%d\t\t%d\t%d\n", m->name, m->Process_ID, m->Segment_ID, m->Page_ID, m->ID);
			MemUnit unit;
			unit.name = m->name;
			unit.pid =m->Process_ID;
			unit.seg_id = m->Segment_ID;
			unit.page_id =m->Page_ID;
			unit.block_id =m->ID;
			memList.push_back(unit);
			m = m->next;
		}
		else
			m = m->next;
	}
	
	m_ui.tableWidget_memList->clearContents();
	int sz = memList.size();
	m_ui.tableWidget_memList->setRowCount(sz);
	for (int i =0;i<sz;i++)
	{
		m_ui.tableWidget_memList->setRowHeight(i, 32);
		//
		m_ui.tableWidget_memList->setItem(i, 0, new QTableWidgetItem(memList[i].name));
		m_ui.tableWidget_memList->setItem(i, 1, new QTableWidgetItem(QString::number(memList[i].pid)));
		m_ui.tableWidget_memList->setItem(i, 2, new QTableWidgetItem(QString::number(memList[i].seg_id)));
		m_ui.tableWidget_memList->setItem(i, 3, new QTableWidgetItem(QString::number(memList[i].page_id)));
		m_ui.tableWidget_memList->setItem(i, 4, new QTableWidgetItem(QString::number(memList[i].block_id)));
	}
	//printf("\n��ռ��%d���ڴ��,ʣ��%d��.\n", (Flash - remained) / BLOCK, remained / BLOCK);
	UIQuery::SetValue(m_ui.label_MemCount,QString("��ռ��%1���ڴ��,ʣ��%2��").arg((Flash - remained) / BLOCK).arg(remained / BLOCK));
}


//��ַת��
void MemoryWindow::AddressExchange()
{
	int ID = UIQuery::GetValue(m_ui.lineEdit_ps_id).toInt();//����ID
	int i = UIQuery::GetValue(m_ui.lineEdit_seg_id).toInt(); //�κ�
	int j = UIQuery::GetValue(m_ui.lineEdit_page_id).toInt();//ҳ��
	Register = UIQuery::GetValue(m_ui.lineEdit_seg_sAddress).toInt();
	
	int address;//�����ַ
	int flag = 1;//������������Ƿ�Ϸ�
	PCB* p;
	Seg* s;
	Pa* q;
	Memory* mer;
	p = process->next;
	mer = memory_info->next;
	if (ID >= total_process)
	{
		printf("\n���벻�Ϸ�!����������!\n");
		UIQuery::Alert("���벻�Ϸ�!����������!");
		return;
	}

	//printf("\n������α���ʼ��ַ:");
	//scanf("%d", &Register);
	//flag = 1;
	//	printf("\n������κ�:");
	//	scanf("%d", &i);
	//�ҵ����̺�ΪID�Ľ���
	p = process->next;
	while (p->ID != ID)
		p = p->next;
	if (p->total_segmet <= i)
	{
		printf("\n���벻�Ϸ�!����������!\n");
		UIQuery::Alert("���벻�Ϸ�!����������!");
		return;
	}

	//�ҵ���
	s = p->segm->next;
	while (s->ID != i)
		s = s->next;
	if (j >= s->size / BLOCK)
	{
		printf("\n���벻�Ϸ�!����������!\n");
		UIQuery::Alert("���벻�Ϸ�!����������!");
		return;
	}
	QStringList log;
	//�ж��Ƿ�ȱ��
	//���ҽ��̵Ķα�
	while (p->ID != ID)
		p = p->next;
	s = p->segm->next;
	//�ҵ��κ�Ϊi�Ķ�
	while (s->ID != i)
		s = s->next;
	if (s->in_out == 'N')
	{
		InterruptType = 1;
		printf("\nȱ���ж�!");
		log << "ȱ���ж�!";
		Sleep(2000);
		log << InterruptHanding(ID, i, j);
	}
	//�ж��Ƿ�ȱҳ�ж�
	else
	{
		//�ҵ�ҳ��Ϊj��ҳ
		q = s->page->next;
		while (q->ID != j)
			q = q->next;
		if (q->in_out == 'N')
		{
			InterruptType = 0;
			printf("\nȱҳ�ж�!");
			log << "ȱ���ж�!";
			Sleep(2000);
			log << InterruptHanding(ID, i, j);
		}
		else
		{
			q->time += 1;
			//�ı�����ڴ������ʱ��
			mer = memory_info->next;
			while (mer->Page_ID != j)
			{
				mer = mer->next;
			}
			mer->recently += 1;
			address = Register + q->block_num * BLOCK + q->pageOffset - 1;
			//printf("\n�����ַΪ:%d", address);
			log << QString("�����ַΪ:%1").arg(address);
			printf("\n");
		}
	}
	
	UIQuery::SetValue(m_ui.textEdit_log,log.join("\n"));
}

//�жϴ���
QString MemoryWindow::InterruptHanding(int id, int i, int j)
{
	QStringList rList;
	char name[10];//�û������Ľ�����
	int ID;//�û������Ľ���ID
	int segment_ID;//�û������Ķκ�ID
	int page_ID;//�û�������ҳ��
	int enough = 0;//����ڴ�ռ��Ƿ��㹻
	int min;
	int address;
	PCB* p;
	Seg* s;
	Pa* q;
	Memory* mer, * temp;
	if (InterruptType == 1)//ȱ���ж�
	{
		//�ҵ��öκ͸öε�ҳ����û���㹻�Ŀռ䣬��LRU���û�
		p = process->next;
		//�ҵ��ý���
		while (p->ID != id)
			p = p->next;
		s = p->segm->next;
		//�ҵ��ö�
		while (s->ID != i)
			s = s->next;
		//���öη����ڴ�
		s->in_out = 'Y';
		//�ҵ���ҳ
		q = s->page->next;
		while (q->ID != j)
			q = q->next;
		//����ҳ�����ڴ棬�����ж��ڴ�ռ��Ƿ��㹻
		mer = memory_info->next;
		if (remained >= BLOCK)//�ռ乻
		{
			//�ҵ��ڴ��п��п�������ҳ
			enough = 1;
			while (mer->allocated != 'N')
				mer = mer->next;
			mer->allocated = 'Y';
			mer->Page_ID = j;
			mer->Process_ID = id;
			strcpy(mer->name, p->name);
			mer->Segment_ID = i;
			q->block_num = mer->ID;
			q->Process_ID = id;
			q->Segment_ID = i;
			q->time++;
			mer->time_in_memory = q->time;
			strcpy(q->name, p->name);
			q->in_out = 'Y';
			q->pageOffset = q->ID + mer->ID;
			if (q->pageOffset >= Flash)
				q->pageOffset -= Flash;
			address = Register + q->block_num * BLOCK + q->pageOffset - 1;
			remained -= BLOCK;
			temp = mer;
			//�޸�recently
			mer = memory_info->next;
			int max = mer->recently;
			while (mer != NULL)
			{
				if (mer->recently > max)
				{
					max = mer->recently;
					mer = mer->next;
				}
				else mer = mer->next;
			}
			temp->recently = max + 1;
			//�ڴ��е�����ҳʱ���1
			mer = memory_info->next;
			while (mer != NULL)
			{
				if (mer->Process_ID == id && mer->Segment_ID == i && mer->Page_ID == j)
					mer = mer->next;
				else if (mer->allocated == 'Y')
				{
					//�޸Ľ�������
					p = process->next;
					while (p->ID != mer->Process_ID)
						p = p->next;
					s = p->segm->next;
					while (s->ID != mer->Segment_ID)
						s = s->next;
					q = s->page->next;
					while (q->ID != mer->Page_ID)
						q = q->next;
					q->time++;
					mer->time_in_memory = q->time;
					mer = mer->next;
				}
				else mer = mer->next;
			}
		}
		else// �ռ䲻��,�ڴ���ռ��
		{
			//����LRU��̭�ڴ��е�ҳ
			//����������ռ���ڴ�ʱ����Ŀ�,��recently��С
			enough = 0;
			mer = memory_info->next;
			temp = memory_info->next;
			min = mer->recently;
			while (mer != NULL)
			{
				if (mer->allocated == 'Y')
				{
					if (mer->recently < min)
					{
						temp = mer;
						min = mer->time_in_memory;
						mer = mer->next;
					}
					else
						mer = mer->next;
				}
				else
					mer = mer->next;
			}
			strcpy(name, temp->name);
			ID = temp->Process_ID;
			segment_ID = temp->Segment_ID;
			page_ID = temp->Page_ID;
			//��tempָ��Ľ��̵���Ϣ�û����ڴ�
			//�ҵ��ý��̺�
			p = process->next;
			while (p->ID != temp->Process_ID)
				p = p->next;
			//�ҵ��ý��̵Ķκ�
			s = p->segm->next;
			while (s->ID != temp->Segment_ID)
				s = s->next;
			//�ҵ��ý��̵�ҳ��
			q = s->page->next;
			while (q->ID != temp->Page_ID)
				q = q->next;
			//����ҳ����
			q->block_num = -1;
			q->in_out = 'N';
			q->Process_ID = -1;
			q->Segment_ID = -1;
			q->pageOffset = 0;
			q->time = 0;
			temp->allocated = 'N';
			temp->time_in_memory = 0;
			temp->recently = 0;
			temp->Page_ID = -1;
			temp->Process_ID = -1;
			temp->Segment_ID = -1;
			p = process->next;
			//�ҵ��ý���
			while (p->ID != id)
				p = p->next;
			s = p->segm->next;
			//�ҵ��ö�
			while (s->ID != i)
				s = s->next;
			//���öη����ڴ�
			s->in_out = 'Y';
			//�ҵ���ҳ
			q = s->page->next;
			while (q->ID != j)
				q = q->next;
			//����ҳ�����ڴ�
			mer = memory_info->next;
			while (mer->allocated != 'N')
				mer = mer->next;
			mer->allocated = 'Y';
			mer->Page_ID = j;
			//mer->recently = 1;
			mer->Process_ID = id;
			strcpy(mer->name, p->name);
			mer->Segment_ID = i;
			mer->time_in_memory++;
			q->block_num = mer->ID;
			q->in_out = 'Y';
			q->time++;
			strcpy(q->name, p->name);
			q->Process_ID = p->ID;
			q->Segment_ID = s->ID;
			q->pageOffset = q->ID + mer->ID;
			if (q->pageOffset >= Flash)
				q->pageOffset -= Flash;
			address = Register + q->block_num * BLOCK + q->pageOffset - 1;
			temp = mer;
			//�޸�recently
			mer = memory_info->next;
			int max = mer->recently;
			while (mer != NULL)
			{
				if (mer->recently > max)
				{
					max = mer->recently;
					mer = mer->next;
				}
				else mer = mer->next;
			}
			temp->recently = max + 1;
			//�ڴ��е�����ҳʱ���1
			mer = memory_info->next;
			while (mer != NULL)
			{
				if (mer->Process_ID == id && mer->Segment_ID == i && mer->Page_ID == j)
					mer = mer->next;
				else if (mer->allocated == 'Y')
				{
					//�޸Ľ�������
					p = process->next;
					while (p->ID != mer->Process_ID)
						p = p->next;
					s = p->segm->next;
					while (s->ID != mer->Segment_ID)
						s = s->next;
					q = s->page->next;
					while (q->ID != mer->Page_ID)
						q = q->next;
					q->time++;
					mer->time_in_memory = q->time;
					mer = mer->next;
				}
				else mer = mer->next;
			}
		}
		printf("\n�ö��Ѿ������ڴ�!");
		printf("\n��ҳ�Ѿ������ڴ�!");
		rList << "��ҳ�Ѿ������ڴ�!";
	}
	else//ȱҳ�ж�
	{
		p = process->next;
		//�ҵ��ý���
		while (p->ID != id)
			p = p->next;
		s = p->segm->next;
		//�ҵ��ö�
		while (s->ID != i)
			s = s->next;
		//���öη����ڴ�
		s->in_out = 'Y';
		//�ҵ���ҳ
		q = s->page->next;
		while (q->ID != j)
			q = q->next;
		//�鿴�ڴ����
		mer = memory_info->next;
		if (remained >= BLOCK)//�ռ��㹻
		{
			enough = 1;
			//�ҵ��ڴ��п��п�������ҳ
			while (mer->allocated != 'N')
				mer = mer->next;
			mer->allocated = 'Y';
			mer->Page_ID = j;
			mer->Process_ID = id;
			strcpy(mer->name, p->name);
			mer->Segment_ID = i;
			mer->time_in_memory++;
			q->block_num = mer->ID;
			q->Process_ID = id;
			q->Segment_ID = i;
			q->time++;
			strcpy(q->name, p->name);
			q->in_out = 'Y';
			q->pageOffset = q->ID + mer->ID;
			if (q->pageOffset >= Flash)
				q->pageOffset -= Flash;
			address = Register + q->block_num * BLOCK + q->pageOffset - 1;
			remained -= BLOCK;
			temp = mer;
			//�޸�recently
			mer = memory_info->next;
			int max = mer->recently;
			while (mer != NULL)
			{
				if (mer->recently > max)
				{
					max = mer->recently;
					mer = mer->next;
				}
				else mer = mer->next;
			}
			temp->recently = max + 1;
			//�ڴ��е�����ҳʱ���1
			mer = memory_info->next;
			while (mer != NULL)
			{
				if (mer->Process_ID == id && mer->Segment_ID == i && mer->Page_ID == j)
					mer = mer->next;
				else if (mer->allocated == 'Y')
				{
					//�޸Ľ�������
					p = process->next;
					while (p->ID != mer->Process_ID)
						p = p->next;
					s = p->segm->next;
					while (s->ID != mer->Segment_ID)
						s = s->next;
					q = s->page->next;
					while (q->ID != mer->Page_ID)
						q = q->next;
					q->time++;
					mer->time_in_memory = q->time;
					mer = mer->next;
				}
				else mer = mer->next;
			}
		}
		else//�ռ䲻��,����LRU�û�
		{
			enough = 0;
			//����LRU��̭�ڴ��е�ҳ
			//�����������������ʹ�õĿ�,��renctly��С��
			mer = memory_info->next;
			temp = memory_info->next;
			min = mer->recently;
			while (mer != NULL)
			{
				if (mer->allocated == 'Y')
				{
					if (mer->recently < min)
					{
						temp = mer;
						min = mer->time_in_memory;
						mer = mer->next;
					}
					else
						mer = mer->next;
				}
				else
					mer = mer->next;
			}
			strcpy(name, temp->name);
			ID = temp->Process_ID;
			segment_ID = temp->Segment_ID;
			page_ID = temp->Page_ID;
			//��tempָ��Ľ��̵���Ϣ�û����ڴ�
			//�ҵ��ý��̺�
			p = process->next;
			while (p->ID != temp->Process_ID)
				p = p->next;
			//�ҵ��ý��̵Ķκ�
			s = p->segm->next;
			while (s->ID != temp->Segment_ID)
				s = s->next;
			//�ҵ��ý��̵�ҳ��
			q = s->page->next;
			while (q->ID != temp->Page_ID)
				q = q->next;
			//����ҳ����
			q->block_num = -1;
			q->in_out = 'N';
			q->Process_ID = -1;
			q->Segment_ID = -1;
			q->pageOffset = 0;
			q->time = 0;
			temp->allocated = 'N';
			temp->recently = 0;
			temp->time_in_memory = 0;
			temp->Page_ID = -1;
			temp->Process_ID = -1;
			temp->Segment_ID = -1;
			p = process->next;
			//�ҵ��ý���
			while (p->ID != id)
				p = p->next;
			s = p->segm->next;
			//�ҵ��ö�
			while (s->ID != i)
				s = s->next;
			//���öη����ڴ�
			s->in_out = 'Y';
			//�ҵ���ҳ
			q = s->page->next;
			while (q->ID != j)
				q = q->next;
			//����ҳ�����ڴ�
			mer = memory_info->next;
			while (mer->allocated != 'N')
				mer = mer->next;
			mer->allocated = 'Y';
			mer->Page_ID = j;
			mer->Process_ID = id;
			strcpy(mer->name, p->name);
			mer->Segment_ID = i;
			mer->time_in_memory++;
			q->block_num = mer->ID;
			q->in_out = 'Y';
			q->time++;
			strcpy(q->name, p->name);
			q->Process_ID = p->ID;
			q->Segment_ID = s->ID;
			q->pageOffset = q->ID + mer->ID;
			if (q->pageOffset >= Flash)
				q->pageOffset -= Flash;
			address = Register + q->block_num * BLOCK + q->pageOffset - 1;
			temp = mer;
			//�޸�recently
			mer = memory_info->next;
			int max = mer->recently;
			while (mer != NULL)
			{
				if (mer->recently > max)
				{
					max = mer->recently;
					mer = mer->next;
				}
				else mer = mer->next;
			}
			temp->recently = max + 1;
			//�ڴ��е�����ҳʱ���1
			mer = memory_info->next;
			while (mer != NULL)
			{
				if (mer->Process_ID == id && mer->Segment_ID == i && mer->Page_ID == j)
					mer = mer->next;
				else if (mer->allocated == 'Y')
				{
					//�޸Ľ�������
					p = process->next;
					while (p->ID != mer->Process_ID)
						p = p->next;
					s = p->segm->next;
					while (s->ID != mer->Segment_ID)
						s = s->next;
					q = s->page->next;
					while (q->ID != mer->Page_ID)
						q = q->next;
					q->time++;
					mer->time_in_memory = q->time;
					mer = mer->next;
				}
				else mer = mer->next;
			}
		}
		printf("\n��ҳ�Ѿ������ڴ�!");
		rList << "��ҳ�Ѿ������ڴ�!";
	}
	//�����ַ
	Sleep(2000);
	rList << QString("��ַΪ:%1").arg(address);
	//printf("\n��ַΪ:%d", address);
	//printf("\n");
	if (!enough)
	{
		rList << "�����ڴ����Ϣ:";
		//printf("\n�����ڴ����Ϣ:\n");
		printf("������\t���̺�\t�κ�\tҳ��\n");
		rList << "������\t���̺�\t�κ�\tҳ��";
		rList << QString("%1\t%2\t%3\t%4").arg(name).arg(ID).arg(segment_ID).arg(page_ID);
		//printf("%s\t%d\t%d\t%d\n", , , , );
	}
	return rList.join("\n");
}


void MemoryWindow::showEvent(QShowEvent *event)
{
	QDialog::showEvent(event);
}
