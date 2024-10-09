#pragma once

class Date;

class HandleDate
{
	std::unique_ptr<Date> _pbody;
public:
	// move-only class�� ������� �����Ҵ��� ������ ������.

	HandleDate(int32 year, int32 month, int32 date);
	HandleDate(HandleDate&& other) noexcept;
	~HandleDate();

	HandleDate& operator=(HandleDate&& rhs) noexcept;
	void PrintDate();
};