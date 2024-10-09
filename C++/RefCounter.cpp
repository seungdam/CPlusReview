#include "pch.h"
#include "RefCounter.h"

RefCounter::RefCounter() = default;
RefCounter::RefCounter(const RefCounter& other)
{
	Share();
}
RefCounter::RefCounter(RefCounter&& other) noexcept = default;
RefCounter::~RefCounter() = default;

void RefCounter::Share()
{
	++_refCnt;
}

void RefCounter::Release()
{
	if(_refCnt > 0) --_refCnt;
}
