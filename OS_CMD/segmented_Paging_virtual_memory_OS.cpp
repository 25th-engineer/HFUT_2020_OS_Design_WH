#include "define.h"
//#include <dlfcn.h>
//#include "utilities.cpp"

//函数声明 
void PrintMemory();
void PrintProcessSegment();

//打印进程段表信息
void PrintProcessSegment()
{
	int i, j;
	PCB* pro;
	Seg* p;
	Pa* s;
	pro = process->next;
	printf("\n请输入要显示的进程号信息:");
	scanf("%d", &j);
	while (pro != NULL)
	{
		if (pro->ID == j)
			break;
		else
			pro = pro->next;
	}
	if (pro == NULL)
		printf("\nERROR\n");
	else
	{
		p = pro->segm->next;
		printf("\n进程信息:\n");
		printf("进程名:%s", pro->name);
		printf("\n进程号:%d\n\n", pro->ID);
		while (p != NULL)
		{
			s = p->page->next;
			printf("段号:%d\t段大小:%d\t是否在内存:%c\n", p->ID, p->size, p->in_out);
			printf("段内页表:\n");
			for (i = 0; i < p->size / BLOCK; i++)
			{
				printf("页号:%d\t页内偏移:%d\t块号:%d\t是否存在内存:%c\n", s->ID, s->pageOffset, s->block_num, s->in_out);
				s = s->next;
			}
			printf("\n");
			p = p->next; 
		}
	}
}

//打印内存分配信息
void PrintMemory()
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
	printf("\n内存大小为:%d", Flash);
	printf("\t总共分成了%d块,每块为:%d", Flash / BLOCK, BLOCK);
	printf("\n已分配的内存块情况为:");
	while (m != NULL)
	{
		if (m->allocated == 'Y')
		{
			printf("\n进程名\t进程号\t进程段号\t页号\t块号\n");
			printf("%s\t%d\t%d\t\t%d\t%d\n", m->name, m->Process_ID, m->Segment_ID, m->Page_ID, m->ID);
			m = m->next;
		}
		else
			m = m->next;
	}
	printf("\n共占用%d块内存块,剩余%d块.\n", (Flash - remained) / BLOCK, remained / BLOCK);
}

void test()
{
	int flag = 1;
	int slect;
	CreateMemory();
	InitProcess(&process);
	CreateProcess();
	ApplyMemory();
	system("cls");
	while (flag)
	{
		printf("1.申请内存\n");
		printf("2.回收内存\n");
		printf("3.显示内存信息\n");
		printf("4.显示进程页表信息\n");
		printf("5.地址转换\n");
		printf("6.退出\n");
		printf("请选择:");
		scanf("%d", &slect);
		switch (slect)
		{
		case 1:
			system("cls");
			Apply();
			break;
		case 2:
			system("cls");
			Recycle();
			break;
		case 3:
			system("cls");
			PrintMemory();
			break;
		case 4:
			system("cls");
			PrintProcessSegment();
			break;
		case 5:
			system("cls");
			AddressExchange();
			break;
		case 6:
			flag = 0;
			free(memory_info);
			free(process);
			break;
		default:
			printf("输入错误,请重新选择!\n");
			break;
		}
	}

}

int main()
{
	test();
	return 0;
}
