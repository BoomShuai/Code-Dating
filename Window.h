#pragma once

#include "Widget.h"
#include "Button.h"
#include "Manager.h"
#include "Table.h"
#include <iostream>
#include <algorithm>

// 背景图片名的常量
constexpr auto BACKGROUND_IMAGE = L"background.jpg";

class Window :
    public Widget
{
public:
    Window(int width = GetSystemMetrics(SM_CXSCREEN), int height = GetSystemMetrics(SM_CYSCREEN));
    ~Window();

    void show() const;                          // 显示窗口
    void messageLoop();                         // 消息循环
    bool close();                               // 关闭窗口

private:
    void showMainWindow();                      // 显示主窗口
    void showViewPersons();                    // 显示查看窗口
    void showEditPersons();                    // 显示编辑窗口
    bool isNumber(const std::wstring& string);  // 判断受否为数字

public:
    // 窗口状态标识，每个状态代表了一个界面
    enum class WindowState
    {
        mainWindow,     // 主窗口
        viewPersons,   // 查看
        editPersons    // 编辑
    };

private:
    // 主窗口按钮
    Button* mainWindow_view;
    Button* mainWindow_edit;
    Button* mainWindow_exit;
    Button* mainWindow_clear;

    // 查看用户窗口按钮
    Button* viewPersons_pageUp;
    Button* viewPersons_pageDown;
    Button* viewPersons_back;
    Button* viewPersons_sort;

    // 编辑用户窗口按钮
    Button* editPersons_add;
    Button* editPersons_delete;
    Button* editPersons_back;
    Button* editPersons_search;

    WindowState state;  // 窗口状态
    Table* table;       // 用户数据表格
    Manager manager;    // 管理器
    HWND hWnd;          // 窗口句柄
    bool isEdit;        // 是否编辑用户
};

