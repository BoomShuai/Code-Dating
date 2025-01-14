#pragma once

#include "Person.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

// ��������
class Manager
{
public:
	bool read(const std::string& fileName);				// ��ȡ�ļ�������
	void write(const std::string& fileName) const;		// д�����ݵ��ļ�
	void addPerson(const Person& student);			    // ����û�
	void sortById();									// ��id����
	void sortByScore();									// ����������
	const Person& getPerson(int index) const;			// ��ȡ�ͻ�����
	void setPerson(int index, const Person& student);	// �޸�
	void deletePerson(int index);						// ɾ��
	int size() const;									// ����
	int search(const wchar_t* searchTerms) const;		// ����������
	int search(int id) const;							// ��id����
	void clear();										// ������пͻ�

protected:
	std::vector<Person> persons;						// �ͻ�����
};