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
	std::cout << "�Ϲ� �Լ�:" << ans  << " " << x << "\n";
	x = 0;


	// ���⼭ ��ũ�� �Լ��� �߸��� ����� �����ϴµ� \
	   �� ������ ��ũ�� �Լ��� x++�� �״�� �����ϱ� �����̴�.

	// x++ >= 0 ? (x++) : -(x++) ==> �� 2���� ����
	ans = macro(x++);
	std::cout << "��ũ�� �Լ�:" << ans << " " << x << "\n";
	x = 0;

	ans = safe(x++);
	std::cout << "�ζ��� �Լ�:" << ans << " " << x << "\n";
	x = 0;

	ans = expr(x++);
	std::cout << "constexpr �Լ�:" << ans << " " << x << "\n";
}