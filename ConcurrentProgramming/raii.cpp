#include "pch.h"

// *** Dead Lock : ���� ����
// �Ͼ�� ���� �Ͽ� ���� ������ ����ϴ� ���¸� ���´´�.
//  - �߻� ����
// lock�� unlock�� pair�� ������ ���� ���
//  �� lock �� unlock ������ �ڵ忡�� ���ܰ� �߻��� ���
//  �� lock�� ����� �� unlock�� �������� ���� ���


// RAII (Resource Acquisition Is Initialization)
// ���� ���� ��Ȳ�� �����ϱ� ����, �츮�� lock_guard, unique_lock, shared_lock
// �� ���� ���ؽ��� RAII�� �ǰ��� ó���ϴ� �Լ��� �ݵ�� ����ϴ� ���� ����.
// �ܼ��ϰ� ����ϴ� ��� lock_guard��..
// ��޽����� ����� ����ϴ� ��� unique_lock, shared_lock�� ����Ѵ�.

int main()
{

}