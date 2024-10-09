#pragma once


class Date
{
private:
	int32 date{ 0 };
	int32 year{ 0 };
	int32 month{ 0 };
public:
	Date(int32 y,int32 m, int32 d ) : date(d), year(y), month(m) {}
	void print();
};