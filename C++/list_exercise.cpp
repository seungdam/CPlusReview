#include "pch.h"
#include <list>
#include <deque>

using namespace std;

class URL
{
	string _link;
public:
	URL() = default;
	URL(const URL&) = default;
	URL(URL&&) noexcept = default;

	friend istream& operator>>(istream& is, URL& rhs)
	{
		is >> rhs._link;
		return is;
	}
	friend ostream& operator<<(ostream& os, URL& rhs)
	{
		os << rhs._link;
		return os;
	}
	bool operator==(const URL& rhs)
	{
		return _link == rhs._link;
	}
	inline friend void swap(URL& lhs, URL& rhs) noexcept
	{
		using std::swap;
		swap(lhs._link, rhs._link);
	}
};

class History
{
	list<URL> _history;
public:
	void try_push(URL&& url)
	{
		auto res = find(_history.begin(), _history.end(), url);
		if (res == _history.end())
		{
			_history.push_front(std::move(url));
		}
		else
		{
			std::iter_swap(_history.begin(), res);
		}
	}

	void log()
	{
		cout << "===history==\n";
		for (auto& i : _history)
			cout << i << "\n";
	}
};

int main()
{
	History h;
	
	while (true)
	{
		URL url;
		if(!(cin >> url)) break;
		h.try_push(std::move(url));
		h.log();
	}

	
}