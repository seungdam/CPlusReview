#include "pch.h"
#include "HandleDate.h"
#include "Date.h"
HandleDate::HandleDate(int32 year, int32 month, int32 date)
{
	_pbody = std::make_unique<Date>(Date{ year, month, date });
}

HandleDate::HandleDate(HandleDate&& other) noexcept = default;
HandleDate::~HandleDate() = default;
HandleDate& HandleDate::operator=(HandleDate&& rhs) noexcept = default;


void HandleDate::PrintDate()
{
	_pbody->print();
}
