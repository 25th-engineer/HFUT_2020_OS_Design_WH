#include "define.h"

void CreateProcess()//建立进程信息
{
	PCB* p, * s;
	Seg* m, * n;
	Pa* r, * t;
	p = process;
	int i, j, k;
	printf("请输入进程总数:");
	scanf("%d", &total_process);
	for (i = 0; i < total_process; i++)
	{
		s = (PCB*)malloc(sizeof(PCB));
		printf("\n请输入第%d个进程名:", i + 1);
		scanf("%s", s->name);
		s->ID = i;
		printf("\n请输入该进程的段总数:");
		scanf("%d", &s->total_segmet);
		InitSegment(&s->segm);
		n = s->segm;
		for (j = 0; j < s->total_segmet; j++)
		{
			m = (Seg*)malloc(sizeof(Seg));
			printf("\n请输入第%d个段的段大小: ", j + 1);
			scanf("%d", &m->size);
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
void CreateMemory()
{
	InitMemory(&memory_info);
	Memory* m, * s;
	s = memory_info;
	int i;
	printf("请输入内存大小:");
	scanf("%d", &Flash);
	remained = Flash;
	printf("\n请输入页框大小:");
	scanf("%d", &BLOCK);
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

//手动申请内存
void Apply()
{
	PCB* p, * s;
	Seg* m = NULL, * n;
	Pa* r = NULL, * t;
	Memory* mer;
	mer = memory_info->next;
	int max;
	int j;
	int k;
	int sum = 0;//记录进程的大小
	printf("请输入进程名:");
	s = (PCB*)malloc(sizeof(PCB));
	scanf("%s", s->name);
	p = process;
	while (p->next != NULL)
		p = p->next;
	s->ID = p->ID + 1;
	printf("\n请输入该进程总段数:");
	scanf("%d", &s->total_segmet);
	InitSegment(&s->segm);
	n = s->segm;
	for (j = 0; j < s->total_segmet; j++)
	{
		m = (Seg*)malloc(sizeof(Seg));
		printf("\n请输入第%d个段的段大小: ", j + 1);
		scanf("%d", &m->size);
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
	//判断是否合法
	if (sum > remained)
	{
		printf("申请空间过大,请重新申请!\n");
		sum = 0;
		//释放空间
		free(r);
		free(m);
		free(s);
	}
	else//从内存中选择空闲块给该进程
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
				//查找memory空间，找到未分配的空间
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

/*
对于某特定机器，其地址结构是一定的。若給定一个逻辑地址空间中的地址为A，页面的大小为L，则页号P和页内地址可按下式求得:
P = INT[A/L]
d = [A] MOD L
*/
//地址转换
void AddressExchange()
{
	int ID;//进程ID
	int i;//段号
	int j;//页号
	int address;//物理地址
	int flag = 1;//用来标记输入是否合法
	PCB* p;
	Seg* s;
	Pa* q;
	Memory* mer;
	p = process->next;
	mer = memory_info->next;
	while (flag)//判断进程ID是否合法
	{
		printf("请输入进程ID:");
		scanf("%d", &ID);
		if (ID >= total_process)
		{
			printf("\n输入不合法!请重新输入!\n");
			flag = 1;
		}
		else flag = 0;
	}
	printf("\n请输入段表起始地址:");
	scanf("%d", &Register);
	flag = 1;
	while (flag)//判断段号是否合法
	{
		printf("\n请输入段号:");
		scanf("%d", &i);
		//找到进程号为ID的进程
		p = process->next;
		while (p->ID != ID)
			p = p->next;
		if (p->total_segmet <= i)
		{
			printf("\n输入不合法!请重新输入!\n");
			flag = 1;
		}
		else flag = 0;
	}
	flag = 1;
	while (flag)//判断页号是否合法
	{
		printf("\n请输入页号:");
		scanf("%d", &j);
		//找到段
		s = p->segm->next;
		while (s->ID != i)
			s = s->next;
		if (j >= s->size / BLOCK)
		{
			printf("\n输入不合法!请重新输入!\n");
			flag = 1;
		}
		else flag = 0;
	}
	//判断是否缺段
	//查找进程的段表
	while (p->ID != ID)
		p = p->next;
	s = p->segm->next;
	//找到段号为i的段
	while (s->ID != i)
		s = s->next;
	if (s->in_out == 'N')
	{
		InterruptType = 1;
		printf("\n缺段中断!");
		Sleep(2000);
		InterruptHanding(ID, i, j);
	}
	//判断是否缺页中断
	else
	{
		//找到页号为j的页
		q = s->page->next;
		while (q->ID != j)
			q = q->next;
		if (q->in_out == 'N')
		{
			InterruptType = 0;
			printf("\n缺页中断!");
			Sleep(2000);
			InterruptHanding(ID, i, j);
		}
		else
		{
			q->time += 1;
			//改变访问内存块的最近时间
			mer = memory_info->next;
			while (mer->Page_ID != j)
			{
				mer = mer->next;
			}
			mer->recently += 1;
			address = Register + q->block_num * BLOCK + q->pageOffset - 1;
			printf("\n物理地址为:%d", address);
			printf("\n");
		}
	}

}

//中断处理
void InterruptHanding(int id, int i, int j)
{
	char name[10];//置换出来的进程名
	int ID;//置换出来的进程ID
	int segment_ID;//置换出来的段号ID
	int page_ID;//置换出来的页号
	int enough = 0;//标记内存空间是否足够
	int min;
	int address;
	PCB* p;
	Seg* s;
	Pa* q;
	Memory* mer, * temp;
	if (InterruptType == 1)//缺段中断
	{
		//找到该段和该段的页，若没有足够的空间，用LRU法置换
		p = process->next;
		//找到该进程
		while (p->ID != id)
			p = p->next;
		s = p->segm->next;
		//找到该段
		while (s->ID != i)
			s = s->next;
		//将该段放入内存
		s->in_out = 'Y';
		//找到该页
		q = s->page->next;
		while (q->ID != j)
			q = q->next;
		//将该页放入内存，首先判断内存空间是否足够
		mer = memory_info->next;
		if (remained >= BLOCK)//空间够
		{
			//找到内存中空闲块分配给该页
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
			//修改recently
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
			//内存中的所有页时间加1
			mer = memory_info->next;
			while (mer != NULL)
			{
				if (mer->Process_ID == id && mer->Segment_ID == i && mer->Page_ID == j)
					mer = mer->next;
				else if (mer->allocated == 'Y')
				{
					//修改进程链表
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
		else// 空间不够,内存已占满
		{
			//利用LRU淘汰内存中的页
			//遍历表，查找占用内存时间最长的块,即recently最小
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
			//将temp指向的进程的信息置换出内存
			//找到该进程号
			p = process->next;
			while (p->ID != temp->Process_ID)
				p = p->next;
			//找到该进程的段号
			s = p->segm->next;
			while (s->ID != temp->Segment_ID)
				s = s->next;
			//找到该进程的页号
			q = s->page->next;
			while (q->ID != temp->Page_ID)
				q = q->next;
			//将该页换出
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
			//找到该进程
			while (p->ID != id)
				p = p->next;
			s = p->segm->next;
			//找到该段
			while (s->ID != i)
				s = s->next;
			//将该段放入内存
			s->in_out = 'Y';
			//找到该页
			q = s->page->next;
			while (q->ID != j)
				q = q->next;
			//将该页放入内存
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
			//修改recently
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
			//内存中的所有页时间加1
			mer = memory_info->next;
			while (mer != NULL)
			{
				if (mer->Process_ID == id && mer->Segment_ID == i && mer->Page_ID == j)
					mer = mer->next;
				else if (mer->allocated == 'Y')
				{
					//修改进程链表
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
		printf("\n该段已经调入内存!");
		printf("\n该页已经调入内存!");
	}
	else//缺页中断
	{
		p = process->next;
		//找到该进程
		while (p->ID != id)
			p = p->next;
		s = p->segm->next;
		//找到该段
		while (s->ID != i)
			s = s->next;
		//将该段放入内存
		s->in_out = 'Y';
		//找到该页
		q = s->page->next;
		while (q->ID != j)
			q = q->next;
		//查看内存情况
		mer = memory_info->next;
		if (remained >= BLOCK)//空间足够
		{
			enough = 1;
			//找到内存中空闲块分配给该页
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
			//修改recently
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
			//内存中的所有页时间加1
			mer = memory_info->next;
			while (mer != NULL)
			{
				if (mer->Process_ID == id && mer->Segment_ID == i && mer->Page_ID == j)
					mer = mer->next;
				else if (mer->allocated == 'Y')
				{
					//修改进程链表
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
		else//空间不够,采用LRU置换
		{
			enough = 0;
			//利用LRU淘汰内存中的页
			//遍历表，查找最近很少使用的块,即renctly最小的
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
			//将temp指向的进程的信息置换出内存
			//找到该进程号
			p = process->next;
			while (p->ID != temp->Process_ID)
				p = p->next;
			//找到该进程的段号
			s = p->segm->next;
			while (s->ID != temp->Segment_ID)
				s = s->next;
			//找到该进程的页号
			q = s->page->next;
			while (q->ID != temp->Page_ID)
				q = q->next;
			//将该页换出
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
			//找到该进程
			while (p->ID != id)
				p = p->next;
			s = p->segm->next;
			//找到该段
			while (s->ID != i)
				s = s->next;
			//将该段放入内存
			s->in_out = 'Y';
			//找到该页
			q = s->page->next;
			while (q->ID != j)
				q = q->next;
			//将该页放入内存
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
			//修改recently
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
			//内存中的所有页时间加1
			mer = memory_info->next;
			while (mer != NULL)
			{
				if (mer->Process_ID == id && mer->Segment_ID == i && mer->Page_ID == j)
					mer = mer->next;
				else if (mer->allocated == 'Y')
				{
					//修改进程链表
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
		printf("\n该页已经调入内存!");
	}
	//计算地址
	Sleep(2000);
	printf("\n地址为:%d", address);
	printf("\n");
	if (!enough)
	{
		printf("\n换出内存的信息:\n");
		printf("进程名\t进程号\t段号\t页号\n");
		printf("%s\t%d\t%d\t%d\n", name, ID, segment_ID, page_ID);
	}
}
//内存回收
void Recycle()
{
	Memory* mer;
	PCB* p;
	Seg* s;
	Pa* q;
	int ID;//要回收的进程号
	printf("请输入进程号:\n");
	scanf("%d", &ID);
	//修改内存信息
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
	//修改进程信息
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
/*
int main()
{
	return 0;
}
*/