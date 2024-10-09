#include "pch.h"
#include "RefCounter.h"
#include "SharedClass.h"
#include <format>


SharedClass::SharedClass(const SharedClass& other) : _name(other._name), _data(other._data), _counter(other._counter), _size(other._size)
{
	std::cout << "Copy cons: ";
	_counter->Share(); // increase counter;
	print();
}

SharedClass::SharedClass(const int8* name, const int8* str)
{
	std::cout << "Default cons: ";
	_name = name;
	_counter = new RefCounter();
	_size = strlen(str);
	_data = new int8[_size + 1];
	strcpy_s(_data, _size + 1, str);
	print();
}

SharedClass::SharedClass(SharedClass&& other) noexcept
{
	std::cout << "Move cons: ";
	_counter = std::move(other._counter);
	_data = std::move(other._data);
	_name = std::move(other._name);
	_size = other._size;
	print();

	other._data = nullptr;
	other._counter = nullptr;
	other.print();
}

SharedClass& SharedClass::operator=(const SharedClass& rhs)
{
	std::cout << "Copy assign: ";
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
		_name = rhs._name;
		_counter->Share();
	}
	print();
	return *this;
}

SharedClass& SharedClass::operator=(SharedClass&& rhs) noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
	if (rhs._data != _data)
	{
		SharedClass temp{ std::move(rhs)};
		std::swap(*this, temp);
		std::cout << "Move assign: ";
		print();
	}
	return *this;
}

SharedClass::~SharedClass() noexcept
{
	if (nullptr != _counter)
	{
		_counter->Release();
		std::cout << "~SharedClass(): Release Object Current Ref Count: " << _counter->GetCount() << "\n";

		if (_counter->GetCount() < 0)
		{
			delete _counter;
			delete _data;
			std::cout << "No More Shared... Destroy\n";
		}
	}
}

void SharedClass::print()
{
	std::cout << std::format("obj name: [{:^6}] data ptr: {} counter ptr: {}", _name, (void*)_data, (void*)_counter);
	if (_counter) std::cout << " ref-count: " << _counter->GetCount() << "\n";
	else std::cout << "\n";
}

inline void SharedClass::swap(SharedClass& lh, SharedClass& rh)
{
	using std::swap;
	swap(lh._data, rh._data);
	swap(lh._size, rh._size);
	swap(lh._counter, rh._counter);
	swap(lh._name, rh._name);
}
