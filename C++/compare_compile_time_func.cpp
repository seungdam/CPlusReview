#include "pch.h"
// *** MACRO
#define macro(a) (a >= 0) ? a : -(a)

//  *** GENRAL
int general(const int& i)
{
	return (i >= 0 ? i : -i);
}


// *** INLINE
inline int safe(const int& i)
{
	return (i >= 0) ? i : -(i);
}

// *** CONSTEXPR
constexpr int expr(const int& i)
{
	return (i >= 0) ? i : -i;
}



int main()
{

	int ans, x = 0;

	ans = general(x++);
	std::cout << "일반 함수:" << ans  << " " << x << "\n";
	x = 0;


	// 여기서 매크로 함수만 잘못된 결과를 도출하는데 \
	   그 이유는 매크로 함수는 x++를 그대로 대입하기 때문이다.

	// x++ >= 0 ? (x++) : -(x++) ==> 총 2값이 증가
	ans = macro(x++);
	std::cout << "매크로 함수:" << ans << " " << x << "\n";
	x = 0;

	ans = safe(x++);
	std::cout << "인라인 함수:" << ans << " " << x << "\n";
	x = 0;

	ans = expr(x++);
	std::cout << "constexpr 함수:" << ans << " " << x << "\n";
}