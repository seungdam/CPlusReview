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
	// 1. conn 도 함수 스코프를 벗어나면서 자원 해제됨.
	// 2. pconn도 RAII 객체이기 때문에 스코프를 벗어나면서 자원 해제를 시도.
	// 1~2에서 해제된 자원에 관한 중첩된 접근으로 인해 Crash 발생
}

#pragma endregion

#pragma region Solution

// unique_ptr이 자원을 해제할 때 대신 호출할 deleter 함수를 구현한다.
auto end_connection = [](connection* c) { disconnect(c); };

void make_connection_sol(const destination& dest)
{
	auto conn = connect(dest);
	// 활용방법: unique_ptr<type, custon_deleter type> {}
	// 이때 deleter 함수에 관한 타입을 우리가 직접 표현할 수 없기 때문에(컴파일러가 생성한 것이기 때문) 
	// decltype 키워드를 사용한다. 
	auto pconn{ std::unique_ptr<connection,decltype(end_connection)>{&conn, end_connection}};
	std::cout << "get data...\n";
	// custom_deleter에 자원 해제에 관해 안전하게 처리할 수 있도록 예외처리를 구현한다.
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