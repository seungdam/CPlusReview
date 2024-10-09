#pragma once

class Date;

class HandleDate
{
	std::unique_ptr<Date> _pbody;
public:
	// move-only class로 복사생성 복사할당이 허용되지 ㅇ낳음.

	HandleDate(int32 year, int32 month, int32 date);
	HandleDate(HandleDate&& other) noexcept;
	~HandleDate();

	HandleDate& operator=(HandleDate&& rhs) noexcept;
	void PrintDate();
};