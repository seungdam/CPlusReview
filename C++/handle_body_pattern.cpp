#include "pch.h"

// *** OPP������ Ŭ������ ���� �������̽��� Ŭ������ ���� ���� ������ �и��� �ʿ䰡 ����.

// client <== [class interface] === [class implementation]

// 1. client(�ش� Ŭ������ �ٷ�� �ڵ�)�� ���� �������̽��� ���� ��ȣ�ۿ��ϸ�, ���� ���������� �� �ʿ䰡 �������.
// 2. class ���ο� ������ ������� public m.f�� ���� �����Ǹ�,
//    �� �̿ܿ��� � ����� Ŭ���̾�Ʈ���� �����Ǹ� �ȵȴ�.
// 3. �̷ν� client�� class�� ���� �ڵ尡 �����Ǵ��� ���ٸ� ������ ���� �ʴ´�.
// 4. ���� interface�� ����Ǿ��� ���� ������ �޴´�.


// �� �ʿ��Ѱ�?
// A. �츮�� ���� cpp�� ���� .h�� ������ �س��´�. + ���� �����ڸ� ���� member�� �����Ѵ�.
//   �� ������ �̰��� ������ ���� ������� �ʴ´�. 
//   �� (prototype member or inline �Լ� or ����� Ÿ��/�̸��� ���� �� �� �ִ�.)

// A. ���� �κ��� �����̶� �ٲ�ٸ� �ٲ�ٸ�, �ݵ�� �������� ������ؾ��Ѵ�..  
//  ==> �ƹ��� ������ �ڵ尡 ���ٰ� �ѵ� �ð��� �����ɸ��� ��ȿ�����̴�.

// client <==> handle(�������̽�) <==> body(������)

// class�� body�� handle�� ���� ���´�
// handle�� body ��ü�� �����ϰ�, client�� ��û�� ���� ������ m.f�� �����Ѵ�.
// ��ġ client���� body�� �ƴ� �ٸ� ��ü�� ��ó�� ������ �Ѵ�.
// ������ �������� body����� ��� �����ȴ�.

//1. handle.h <== handle Ŭ���� ���� (public m.f only)
//2. body.h <== ���� body ��ü�� ���� �� ����

// client���� handle.h�� include 
// ��, body.h�� �����ǵ� client�� ������ ���� ����. ==> client�� �������� �ʿ䰡 X

// ������
// 
//  body.h			   handle.h
//    |                 /    \
//  body.cpp    handle.cpp client.cpp
//    |               |       |
//    [        compiler        ] compile + link 
// 
// static linking: ������ ���� binary file���� ��ó �ϳ��� binary file�� ����� ��.
           // body.exe + handle.exe = client.exe


// dynamic linking 
// body.h == body.cpp ==> body.lib
//                                \
//                                 \
// handle.h/.cpp == client.cpp ==> client.exe
// client.exe�� ��Ÿ�� �� body.lib ���̺귯�� ������ ������ Ȱ���Ѵ�.



// how to implement? 
// *** plmpl: pointer to implementation
// handle class�� body Ŭ������ �����͸� ������ ��
// �̶� Handle Class�� RAII���·� �����ؾ��Ѵ�.

// ���ó
// 1. ��Ը� ������Ʈ Ȥ�� ���̺귯������ Ȱ��
// 2. �����̳� Ŭ������ ���� Ȥ�� Ȱ���� �� �����ϰ� ����� �� �ִ�.

// ����
// 1. Body ��ü�� �������� �����ϱ� ������ �ӵ��� ������.
// 2. Body ��ü�� ���� �߰����� �Ҵ��� �����ϱ� ������ �޸𸮸� �� ��ƸԴ´�.
// 3. ���� ���̺귯�� ������ ������Ʈ ������ ���α׷� ������ �������Ѵ�.
// 4. �ڵ庣�̽��� ���⼺�� �߱��Ų��.


class Body; // body ����� �߰����� �ʰ� ���漱������ ����

class Handle
{
private:
    Body* _body; // unique_ptr�� ��ü�ؼ� ������ �� �ִ�.
public:
    void func() {};
};

#include "HandleDate.h"

int main()
{
    HandleDate h(2024,10,9);
    h.PrintDate();

}