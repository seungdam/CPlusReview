#pragma once
class RefCounter
{
	int32 _refCnt{ 1 };
public:
	RefCounter();
	RefCounter(const RefCounter& other); 
	RefCounter(RefCounter&& other) noexcept;
	~RefCounter();
	
	void Share();
	void Release();
	int32 GetCount() const { return _refCnt; }
};

