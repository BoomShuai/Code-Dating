#pragma once

#include "Widget.h"
#include "Button.h"
#include "Manager.h"
#include "Table.h"
#include <iostream>
#include <algorithm>

// ����ͼƬ���ĳ���
constexpr auto BACKGROUND_IMAGE = L"background.jpg";

class Window :
    public Widget
{
public:
    Window(int width = GetSystemMetrics(SM_CXSCREEN), int height = GetSystemMetrics(SM_CYSCREEN));
    ~Window();

    void show() const;                          // ��ʾ����
    void messageLoop();                         // ��Ϣѭ��
    bool close();                               // �رմ���

private:
    void showMainWindow();                      // ��ʾ������
    void showViewPersons();                    // ��ʾ�鿴����
    void showEditPersons();                    // ��ʾ�༭����
    bool isNumber(const std::wstring& string);  // �ж��ܷ�Ϊ����

public:
    // ����״̬��ʶ��ÿ��״̬������һ������
    enum class WindowState
    {
        mainWindow,     // ������
        viewPersons,   // �鿴
        editPersons    // �༭
    };

private:
    // �����ڰ�ť
    Button* mainWindow_view;
    Button* mainWindow_edit;
    Button* mainWindow_exit;
    Button* mainWindow_clear;

    // �鿴�û����ڰ�ť
    Button* viewPersons_pageUp;
    Button* viewPersons_pageDown;
    Button* viewPersons_back;
    Button* viewPersons_sort;

    // �༭�û����ڰ�ť
    Button* editPersons_add;
    Button* editPersons_delete;
    Button* editPersons_back;
    Button* editPersons_search;

    WindowState state;  // ����״̬
    Table* table;       // �û����ݱ��
    Manager manager;    // ������
    HWND hWnd;          // ���ھ��
    bool isEdit;        // �Ƿ�༭�û�
};

