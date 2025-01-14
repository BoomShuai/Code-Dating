#pragma once

#include <string>

// 客户类
class Person
{
public:
	unsigned short id;	   //编号
	wchar_t name[10];    //名字
	wchar_t Vip[10];	//VIP等级
	unsigned short score;	  //积分

	// 重载运算符，使对象可以进行排序
	bool operator==(const wchar_t* searchTerms) const
	{
		return std::wstring(name) == searchTerms;
	}

	bool operator==(int id) const
	{
		return id == this->id;
	}

	bool operator<(const Person& stu) const	// 按id升序排序
	{
		return (this->id < stu.id);
	}

	bool operator>(const Person& stu) const	// 按积分升序排序
	{
		return this->score > stu.score;
	}
};