#include "pch.h"

using namespace std;
// *** C++11 emplace
// �����̳ʿ� ���Ҹ� �߰��ϴ� �� �ٸ� ��� emplace
// insert, push_back�� �츮�� �����̳ʿ� ������ Ÿ���� ���� �ִ´ٴ� �����Ͽ� ����ȴ�.
// �׸��� �̹� �����ϴ� ���� ���� �����ؼ� �߰��Ѵ�. --> �� ���� ���� �����ϴ� ���� �����ϴ�.
// ��, �Ϻθ� ����Ǵ� ��Ȳ�� �߻��ϰų�, �������� Ÿ���� �߰��ϵ����ϸ� ���ܰ� �߻��Ѵٴ� ���̴�.

// �ݸ� emplace�� �����ϴ� ���̾ƴ϶� �����ϰ� �̸� ���� �ִ´�. �� ��������ڰ� ȣ����� �ʴ´�.
// �����̳ʿ� ũ�Ⱑ ū ��ü�� ������ ��� ���ǹ��� ���̸� �� �� �ִ�.

struct object
{
	int id;
	string type;
	bool available;
};
int main()
{
	vector<object> objs;

	objs.push_back({0, "none", false}); // �ӽ� ��ü ���� -> ���� ���� �� �߰� -> �ӽ� ��ü �ı�
	objs.emplace(objs.begin(), 1, "player", true); // ���� ���� X, �⺻ ���� O
	// objs.emplace_back

	// �̶� ���� Ű�� ������ ���� �����̳� �����ؼ� emplace�� �ټ� �ٸ��� �����Ѵ�.
	// �̵��� emplace�� ȣ���ϴ���, �ӽ� ��ü�� �����ϰ� �ش� ��ü�� ������� check�� �����Ѵ�.
	// �� ��� try_emplace�� ����Ѵ�.
	// try_emplace�� ��ü ���� ������ �ߺ� üũ�� �����Ѵ�.
	// �� �ߺ��� Ű�� �����Ѵٸ� �ƹ� �͵� �������� �ʴ´ٴ� ���̴�.
	map<string, object> m;
	auto [iter, success] = m.try_emplace("None", 0, "none", false);

}
