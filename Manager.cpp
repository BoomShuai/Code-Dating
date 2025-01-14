#include "Manager.h"
using namespace std;

bool Manager::read(const std::string& fileName)
{
    // 以二进制读取模式打开文件
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    if (!file)
    {
        return false;
    }

    // 读取数据
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
    // 以二进制写入模式打开文件
    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    // 写入数据
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
    // TODO: 在此处插入 return 语句
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
    // TODO: 在此处插入 return 语句
    return (int)persons.size();
}

int Manager::search(const wchar_t* searchTerms) const
{
    // TODO: 在此处插入 return 语句
    std::vector<Person>::const_iterator iter;
    iter = std::find(persons.begin(), persons.end(), searchTerms);
    if (iter != persons.end())
    {
        // 搜索成功，返回索引
        return (int)(iter - persons.begin());
    }
    else
    {
        // 搜索失败，返回 -1 表示错误
        return -1;
    }
}

int Manager::search(int id) const
{
    std::vector<Person>::const_iterator iter;
    iter = find(persons.begin(), persons.end(), id);
    if (iter != persons.end())
    {
        // 搜索成功，返回索引
        return (int)(iter - persons.begin());
    }
    else
    {
        // 搜索失败，返回 -1 表示错误
        return -1;
    }
}

void Manager::clear()
{
    persons.clear();
}
