#pragma once

#include <string>

// �ͻ���
class Person
{
public:
	unsigned short id;	   //���
	wchar_t name[10];    //����
	wchar_t Vip[10];	//VIP�ȼ�
	unsigned short score;	  //����

	// �����������ʹ������Խ�������
	bool operator==(const wchar_t* searchTerms) const
	{
		return std::wstring(name) == searchTerms;
	}

	bool operator==(int id) const
	{
		return id == this->id;
	}

	bool operator<(const Person& stu) const	// ��id��������
	{
		return (this->id < stu.id);
	}

	bool operator>(const Person& stu) const	// ��������������
	{
		return this->score > stu.score;
	}
};