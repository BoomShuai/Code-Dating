#pragma once

#include "Person.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

// 管理器类
class Manager
{
public:
	bool read(const std::string& fileName);				// 读取文件到数据
	void write(const std::string& fileName) const;		// 写入数据到文件
	void addPerson(const Person& student);			    // 添加用户
	void sortById();									// 按id排序
	void sortByScore();									// 按积分排序
	const Person& getPerson(int index) const;			// 获取客户数据
	void setPerson(int index, const Person& student);	// 修改
	void deletePerson(int index);						// 删除
	int size() const;									// 数量
	int search(const wchar_t* searchTerms) const;		// 按姓名搜索
	int search(int id) const;							// 按id搜索
	void clear();										// 清空所有客户

protected:
	std::vector<Person> persons;						// 客户数据
};