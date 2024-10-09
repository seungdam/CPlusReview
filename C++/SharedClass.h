#pragma once
class RefCounter;

class SharedClass
{
	RefCounter* _counter{ nullptr };
	int8* _data{ nullptr };
	int32 _size;
public:
	SharedClass(const int8* str);
	SharedClass(const SharedClass& other);
	SharedClass(SharedClass&& other) noexcept;
	SharedClass& operator=(const SharedClass& rhs); // ref-count increase;
	SharedClass& operator=( SharedClass&& rhs) noexcept;

	~SharedClass() noexcept;
	void print(const char* name);
	inline void swap(SharedClass& lh,  SharedClass& rh);

};

