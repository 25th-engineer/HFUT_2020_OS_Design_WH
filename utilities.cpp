#include "define.h"

/*
	extern int Register;//段表的起始地址
	extern int Flash; //内存大小
	extern int BLOCK;//页框大小
	extern int remained;//剩余的内存
	extern pcb process;  //申明一个进程链表
	extern int total_process;//进程总数
	extern memory memory_info;//申明一个记录内存信息的链表
	extern int InterruptType;//中断类型,1表示缺段中断，0表示缺页中断
*/

 int Register;//段表的起始地址
 int Flash; //内存大小
 int BLOCK;//页框大小
 int remained;//剩余的内存
 pcb process;  //申明一个进程链表
 int total_process = 0;//进程总数
 memory memory_info;//申明一个记录内存信息的链表
 int InterruptType = -1;//中断类型,1表示缺段中断，0表示缺页中断


//初始化
void InitPage(PaNode* p)
{
	*p = (PaNode)malloc(sizeof(Pa));
	(*p)->next = NULL;
}

void InitSegment(SegNode* s)
{
	*s = (SegNode)malloc(sizeof(Seg));
	(*s)->next = NULL;
}

void InitProcess(pcb* pro)
{
	*pro = (pcb)malloc(sizeof(PCB));
	(*pro)->next = NULL;

}

void InitMemory(memory* m)
{
	*m = (memory)malloc(sizeof(Memory));
	(*m)->allocated = 'W';
	(*m)->block_size = 0;
	(*m)->ID = -1;
	(*m)->next = NULL;
}

// 建立内存信息
void CreateMemory(int nFlash, int nBlock)
{
	InitMemory(&memory_info);
	Memory* m, * s;
	s = memory_info;
	int i;
	//printf("请输入内存大小:");
	//scanf("%d", &);
	Flash = nFlash;
	remained = Flash;
	//printf("\n请输入页框大小:");
	//scanf("%d", &BLOCK);
	BLOCK = nBlock;
	for (i = 0; i < Flash / BLOCK; i++)
	{
		m = (Memory*)malloc(sizeof(Memory));
		m->ID = i;
		m->allocated = 'N';
		m->block_size = BLOCK;
		m->time_in_memory = 0;
		m->recently = 0;
		s->next = m;
		s = s->next;
		s->next = NULL;
	}
}

//随机初始化分配进程到内存
void ApplyMemory()
{
	PCB* p;
	Seg* q;
	Pa* r;
	Memory* mer;
	mer = memory_info->next;
	p = process->next;
	srand((unsigned)time(NULL));
	int tmp = 1;
	int flag;
	int m;//进程号
	int n;//段号
	int t;//页号
	int block_num;//内存块号
	for (int temp = 0; temp < Flash / BLOCK; temp++)
	{
		//随机产生一个进程号
		while (1)
		{
			flag = rand() % 100;
			if (total_process == 1)//只有一个进程
			{
				m = 0;
				break;
			}
			else if (flag >= 0 && flag <= total_process - 1)
			{
				m = flag;
				break;
			}
			else continue;
		}
		//找到那个进程
		while (p->ID != m)
			p = p->next;
		//随机产生一个段号
		while (1)
		{
			flag = rand() % 100;
			if (p->total_segmet == 1)//只有一个段
			{
				n = 0;
				break;
			}
			else if (flag >= 0 && flag <= p->total_segmet - 1)
			{
				n = flag;
				break;
			}
			else continue;
		}
		//找到那个段
		q = p->segm->next;
		while (q->ID != n)
			q = q->next;
		//随机产生一个页号
		while (1)
		{
			flag = rand();
			if (flag >= 0 && flag <= q->size / BLOCK - 1)
			{
				t = flag;
				break;
			}
			else continue;
		}
		//找到那个页
		r = q->page->next;
		while (r->ID != t)
			r = r->next;
		while (1)//一直到产生一个没有分配的块
		{
			//随机产生一个内存块号
			while (1)
			{
				flag = rand() % 1000;
				if (flag >= 0 && flag <= Flash / BLOCK - 1)
				{
					block_num = flag;
					break;
				}
				else continue;
			}
			//找到那个内存块
			while (mer->ID != block_num)
			{
				if (mer == NULL)
				{
					tmp = 0;
					break;
				}
				else
				{
					tmp = 1;
					mer = mer->next;
				}
			}
			//判断内存块是否已经被占
			if (mer->allocated == 'Y')
			{
				mer = memory_info->next;
				continue;
			}
			else
				break;
		}
		if (tmp == 0)
			break;
		mer->allocated = 'Y';
		q->in_out = 'Y';
		r->block_num = block_num;
		r->pageOffset = r->ID + block_num;
		if (r->pageOffset >= Flash)
			r->pageOffset -= Flash;
		r->in_out = 'Y';
		mer = memory_info->next;
		p = process->next;
	}
	//读取进程信息，修改内存信息，避免假分配
	p = process->next;//进程信息第一个节点
	mer = memory_info->next;//内存信息第一个节点
	q = p->segm->next;//段信息第一个节点
	while (mer != NULL)
	{
		mer->allocated = 'N';
		mer = mer->next;
	}
	mer = memory_info->next;
	for (int j = 0; j < total_process; j++)
	{
		while (p != NULL)
		{
			if (p->ID == j)
				break;
			else
				p = p->next;
		}
		q = p->segm->next;
		while (q != NULL)
		{
			r = q->page->next;
			for (int i = 0; i < q->size / BLOCK; i++)
			{
				if (r->in_out == 'Y')
				{
					while (mer->ID != r->block_num)
						mer = mer->next;
					mer->allocated = 'Y';
					mer->recently = 1;
					remained -= BLOCK;
					r->time += 1;
					mer->time_in_memory = r->time;
					mer->Process_ID = p->ID;
					mer->Segment_ID = q->ID;
					mer->Page_ID = r->ID;
					strcpy(mer->name, p->name);
					mer = memory_info->next;
					r = r->next;
				}
				else
					r = r->next;
			}
			q = q->next;
		}
	}
}

/*
对于某特定机器，其地址结构是一定的。若給定一个逻辑地址空间中的地址为A，页面的大小为L，则页号P和页内地址可按下式求得:
P = INT[A/L]
d = [A] MOD L
*/
