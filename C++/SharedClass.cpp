#include "pch.h"
#include "RefCounter.h"
#include "SharedClass.h"



SharedClass::SharedClass(const SharedClass& other) : _data(other._data), _counter(other._counter), _size(other._size)
{
	_counter->Share(); // increase counter;
}

SharedClass::SharedClass(const int8* str)
{
	_counter = new RefCounter();
	_size = strlen(str);
	_data = new int8[_size + 1];
	strcpy_s(_data, _size + 1, str);
}

SharedClass::SharedClass(SharedClass&& other) noexcept
{
	_counter = std::move(other._counter);
	_data = std::move(other._data);
	_size = other._size;

	other._data = nullptr;
	other._counter = nullptr;
}

SharedClass& SharedClass::operator=(const SharedClass& rhs)
{
	if (rhs._data == _data) // 같은 데이터라면
	{	//ref-count만 증가
		_counter->Share();
	}
	else
	{   // 기존 ref-count 감소
		_counter->Release();
		_counter = rhs._counter;
		_data = rhs._data;
		_size = rhs._size;
		_counter->Share();
	}
	return *this;
}

SharedClass& SharedClass::operator=(SharedClass&& rhs) noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
	if (rhs._data != _data)
	{
		SharedClass temp{ std::move(rhs)};
		std::swap(*this, temp);
	}
	return *this;
}

SharedClass::~SharedClass() noexcept
{
	if (nullptr != _counter)
	{
		_counter->Release();
		if (_counter->GetCount() <= 0)
		{
			delete _counter;
			delete _data;
			std::cout << "No More Shared... Destroy\n";
		}
	}
	else
	{
		delete _counter;
		delete _data;
		std::cout << "No More Shared... Destroy\n";
	}
}

void SharedClass::print(const char* name)
{
	{ std::cout << name << " Data Ptr: " << (void*)_data << " Counter: " << (void*)_counter << "\n"; }
}

inline void SharedClass::swap(SharedClass& lh, SharedClass& rh)
{
	using std::swap;
	swap(lh._data, rh._data);
	swap(lh._size, rh._size);
	swap(lh._counter, rh._counter);
}
