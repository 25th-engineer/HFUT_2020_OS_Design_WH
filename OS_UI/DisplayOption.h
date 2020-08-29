#pragma once
#include <vector>
#include <string>
#include <QString>

using namespace std;

class ProcessUnit
{
public:
	QString name;
	int totalSeg;
	QStringList segSizeList;
};

class MemUnit
{
public:
	QString name;
	int pid;
	int seg_id;
	int page_id;
	int block_id;
};

class SegUnit
{
public:
	int ID;
	int size;
	QString in_out;
};

class PageUnit
{
public:
	int ID;
	int pageOffset;
	int block_num;
	QString in_out;
};