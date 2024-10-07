#include  "pch.h"
#include <string>


using namespace std;

// RAII 클래스의 이동 구현
// 내부적으로 동적 char 배열을 가지며, 소멸시, 동적 할당을 해제하는 RAII 객체
class String
{
	int8* _str{ nullptr };
	int32 _size{ 0 };
public:
	String() = default;
	String(const string& str)
	{
		_size = str.length();
		_str = new int8[_size + 1];
		strcpy_s(_str, _size + 1, str.c_str());
		_str[_size] = '\0';
	}
	String(const char* str)
	{
		_size = strlen(str);
		_str = new int8[_size + 1];
		strcpy_s(_str, _size + 1, str);
	}
	String(const String& rhs)
	{
		cout << "String Copy\n";
		_size = rhs._size;
		_str = new int8[_size + 1];
		strcpy_s(_str, _size + 1, rhs._str);

	}
	String(String&& rhs) noexcept : _size(rhs._size), _str(std::move(rhs._str))
	{
		rhs._str = nullptr;
		rhs._size = 0;
	}

	String& operator=(String&& rhs) noexcept
	{
		if (this != &rhs)
		{ // Copy Assign과 유사하게 동작한다.
			delete[] _str;
			_size = rhs._size;
			_str = std::move(rhs._str);
			rhs._size = 0;
			rhs._str = nullptr;
		}
		return *this;
	}

	//String& operator=(String&& rhs) noexcept
	//{
	//	if (this != &rhs)
	//	{ // Move와 Swap을 사용해 구현한다.
	//		String temp{ std::move(rhs) };
	//		swap(*this, temp);
	//	}
	//	return *this;
	//}

	String& operator=(String& rhs) 
	{
		if (this != &rhs)
		{
			if (_size > rhs._size)
			{
				_str[0] = '\0';
				strcpy_s(_str, rhs._size + 1, rhs._str);
			}
			else if (_size < rhs._size)
			{
				delete[] _str;
				_str = new int8[rhs._size + 1];
				_size = rhs._size;
				strcpy_s(_str, _size, rhs._str);
			}
			else
			{
				strcpy_s(_str, _size + 1, rhs._str);
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, const String& rhs)
	{
		os << "[size]: " << rhs._size << " [str]: " << rhs._str
			<< "\n\033[38;5;222m[ptr]: " << static_cast<void*>(rhs._str) << "\033[0m";

		return os;
	}

	friend void swap(String& l, String& r) noexcept;
	~String()
	{
		cout << "\033[38;5;222mDestructor: " << static_cast<void*>(_str) << "\n\033[0m";

		delete[] _str;
	}
};

inline void swap(String& l, String& r) noexcept
{
	using std::swap;
	swap(l._size, r._size);
	swap(l._str, r._str);
}

int main()
{
	String s{ "s: Hello" };
	cout << s << "\n\n";

	String s2{ "s2: My Friend" };
	cout << s2 << "\n\n";

	String s3{ s };
	cout << s3 << "\n\n";

	cout << "===Move===\n";
	String ms{ std::move(s) };
	cout << "s move to ms\n";
	cout << ms << "\n\n";


	String ms2{"ms2: Before Move Assign."};
	cout << ms2 << "\n\n";
	ms2 = std::move(s2);

	cout << "s2 move assign to ms2\n";
	cout << ms2 << "\n\n";
}