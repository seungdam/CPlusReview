#include "pch.h"


// network api
struct destination {};
struct connection { int32 sid{ 0 }; };

int cnt{ 0 };

connection connect(destination dest)
{
	
	connection conn{ cnt++ };
	std::cout << "\033[38;5;80mconnect session: " << conn.sid << "\033[0m\n";
	return conn;
}

void disconnect(connection* conn)
{
	if(nullptr != conn ) std::cout << "\033[38;5;140mdisconnect session: " << conn->sid << "\033[0m\n";
}


#pragma region Crash Case

void make_connection(const destination& dest)
{
	//auto conn = connect(dest);
	//auto pconn{ std::unique_ptr<connection>(&conn)};
	auto pconn{ std::make_unique<connection>(connect(dest))};
	std::cout << "get data...\n";
	// 1. conn �� �Լ� �������� ����鼭 �ڿ� ������.
	// 2. pconn�� RAII ��ü�̱� ������ �������� ����鼭 �ڿ� ������ �õ�.
	// 1~2���� ������ �ڿ��� ���� ��ø�� �������� ���� Crash �߻�
}

#pragma endregion

#pragma region Solution

// unique_ptr�� �ڿ��� ������ �� ��� ȣ���� deleter �Լ��� �����Ѵ�.
auto end_connection = [](connection* c) { disconnect(c); };

void make_connection_sol(const destination& dest)
{
	auto conn = connect(dest);
	// Ȱ����: unique_ptr<type, custon_deleter type> {}
	// �̶� deleter �Լ��� ���� Ÿ���� �츮�� ���� ǥ���� �� ���� ������(�����Ϸ��� ������ ���̱� ����) 
	// decltype Ű���带 ����Ѵ�. 
	auto pconn{ std::unique_ptr<connection,decltype(end_connection)>{&conn, end_connection}};
	std::cout << "get data...\n";
	// custom_deleter�� �ڿ� ������ ���� �����ϰ� ó���� �� �ֵ��� ����ó���� �����Ѵ�.
}
#pragma endregion
int main()
{
	destination dest;
	make_connection(dest);
	make_connection_sol(dest);
	make_connection_sol(dest);
	make_connection_sol(dest);
	make_connection_sol(dest);
	make_connection_sol(dest);
}