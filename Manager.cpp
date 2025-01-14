#include "Manager.h"
using namespace std;

bool Manager::read(const std::string& fileName)
{
    // �Զ����ƶ�ȡģʽ���ļ�
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    if (!file)
    {
        return false;
    }

    // ��ȡ����
    Person data = {};
    while (file.read((char*)&data, sizeof(Person)))
    {
        persons.push_back(data);
    }

    file.close();
    return true;
}

void Manager::write(const std::string& fileName) const
{
    // �Զ�����д��ģʽ���ļ�
    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    // д������
    for (int i = 0; i < persons.size(); i++)
    {
        file.write((const char*)&persons[i], sizeof(Person));
    }

    file.close();
}

void Manager::addPerson(const Person& student)
{
    persons.push_back(student);
}

void Manager::sortById()
{
    std::sort(persons.begin(), persons.end());
}

void Manager::sortByScore()
{
    std::sort(persons.begin(), persons.end(), std::greater<Person>());
}

const Person& Manager::getPerson(int index) const
{
    // TODO: �ڴ˴����� return ���
    return persons[index];
}

void Manager::setPerson(int index, const Person& student)
{
    persons[index] = student;
}

void Manager::deletePerson(int index)
{
    persons.erase(persons.begin() + index);
}

int Manager::size() const
{
    // TODO: �ڴ˴����� return ���
    return (int)persons.size();
}

int Manager::search(const wchar_t* searchTerms) const
{
    // TODO: �ڴ˴����� return ���
    std::vector<Person>::const_iterator iter;
    iter = std::find(persons.begin(), persons.end(), searchTerms);
    if (iter != persons.end())
    {
        // �����ɹ�����������
        return (int)(iter - persons.begin());
    }
    else
    {
        // ����ʧ�ܣ����� -1 ��ʾ����
        return -1;
    }
}

int Manager::search(int id) const
{
    std::vector<Person>::const_iterator iter;
    iter = find(persons.begin(), persons.end(), id);
    if (iter != persons.end())
    {
        // �����ɹ�����������
        return (int)(iter - persons.begin());
    }
    else
    {
        // ����ʧ�ܣ����� -1 ��ʾ����
        return -1;
    }
}

void Manager::clear()
{
    persons.clear();
}
