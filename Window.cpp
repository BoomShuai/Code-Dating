#include "Window.h"

Window::Window(int width, int height) :
	Widget(0, 0, width, height),
	isEdit(false),
	hWnd(initgraph(width, height, EX_NOCLOSE))
{
	SetWindowText(hWnd, L"ɳ����ͻ�����ϵͳ");
	setbkcolor(WHITE);
	cleardevice();
	ShowWindow(hWnd, SW_HIDE);

	// ���û�ͼ��ʽ
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = DEFAULT_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);

	// ������ť
	mainWindow_view	 = new Button((502 - 150) / 2, 160, 150, 40, L"�鿴�ͻ�");
	mainWindow_edit = new Button((502 - 150) / 2, 220, 150, 40, L"�༭�ͻ�");
	mainWindow_clear = new Button((502 - 150) / 2, 280, 150, 40, L"�������");
	mainWindow_exit = new Button((502 - 150) / 2, 340, 150, 40, L"�˳�����");

	viewPersons_pageUp = new Button(10, 380, 80, 30, L"��һҳ");
	viewPersons_pageDown = new Button(210, 380, 80, 30, L"��һҳ");
	viewPersons_back = new Button(412, 380, 80, 30, L"����");
	viewPersons_sort = new Button(300, 380, 102, 30, L"����������");

	editPersons_search = new Button(10, 380, 100, 30, L"�����ͻ�");
	editPersons_add = new Button(137, 380, 100, 30, L"��ӿͻ�");
	editPersons_delete = new Button(264, 380, 100, 30, L"ɾ���ͻ�");
	editPersons_back = new Button(392, 380, 100, 30, L"����");

	showMainWindow();	// ��ʾ������

	// �������
	table = new Table(manager, 10, 10, 502 - 20, 420 - 60);

	// ��ȡ�û�����
	if (!manager.read("Persons.dat"))
	{
		MessageBox(GetHWnd(), L" ��Persons.dat�� �ļ���ʧ�ܣ��޷�������в�����", L"����", MB_OK | MB_ICONERROR);
		exit(-1);
	}
}

Window::~Window()
{
	// ����
	delete mainWindow_view;
	delete mainWindow_edit;
	delete mainWindow_clear;
	delete mainWindow_exit;

	delete viewPersons_pageUp;
	delete viewPersons_pageDown;
	delete viewPersons_sort;
	delete viewPersons_back;

	delete editPersons_search;
	delete editPersons_add;
	delete editPersons_delete;
	delete editPersons_back;

	delete table;
}

void Window::show() const
{
	ShowWindow(hWnd, SW_SHOW);
}

void Window::messageLoop()
{
	// ������Ϣѭ��
	ExMessage msg;
	while (true)
	{
		// ��ȡ���ж���Ϣ
		msg = getmessage();

		// �ж���ʾ����
		if (state == WindowState::mainWindow)		// ��������ʾ
		{
			if (mainWindow_view->state(msg))		// �鿴ѧ��
			{
				showViewPersons();
			}
			else if (mainWindow_edit->state(msg))	// �༭ѧ��
			{
				showEditPersons();
			}
			else if (mainWindow_clear->state(msg))	// �������
			{
				if (MessageBox(GetHWnd(), L"ȷ��Ҫ������пͻ����ݣ�", L"�������", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					// ȷ�����
					manager.clear();
					isEdit = true;
				}
			}
			else if (mainWindow_exit->state(msg))	// �˳�����
			{
				if (close())
				{
					return;
				}
			}
		}
		else if (state == WindowState::viewPersons)	// �鿴�û�������ʾ
		{
			if (viewPersons_pageUp->state(msg) && msg.message != WM_LBUTTONUP)			// ��һҳ
			{
				table->pageUp();
			}
			else if (viewPersons_pageDown->state(msg) && msg.message != WM_LBUTTONUP)	// ��һҳ
			{
				table->pageDown();
			}
			else if (viewPersons_back->state(msg))	// ����
			{
				// ��ʾ������
				showMainWindow();
			}
			else if (viewPersons_sort->state(msg) && msg.message != WM_LBUTTONUP)	// ����
			{
				if (viewPersons_sort->getText() == L"����������")
				{
					manager.sortByScore();
					table->show();
					viewPersons_sort->setText(L"��ID����");
					viewPersons_sort->state(msg);
				}
				else
				{
					manager.sortById();
					table->show();
					viewPersons_sort->setText(L"����������");
					viewPersons_sort->state(msg);
				}
			}
		}
		else	// �༭ѧ��������ʾ
		{
			if (editPersons_back->state(msg))	// ����
			{
				// ��ʾ������
				showMainWindow();
			}
			else if (editPersons_search->state(msg) && msg.message != WM_LBUTTONUP)	// �����û�
			{
				wchar_t str[10];
				if (InputBox(str, 5, L"������ID����������������", L"�����û�", NULL, 0, 0, false))
				{
					int number = _wtoi(str);

					if (number == 0)	//Ϊ�ַ���
					{
						table->showEditTable(str);

						if (table->getSearchIndex() == -1)	// ����ʧ��
						{
							MessageBox(GetHWnd(), L"δ�ҵ��û���", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						}
					}
					else // Ϊ����
					{
						table->showEditTable(number);
						
						if (table->getSearchIndex() == -1)
						{
							MessageBox(GetHWnd(), L"δ�ҵ��û���", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						}
					}
				}
			}
			else if (editPersons_add->state(msg) && msg.message != WM_LBUTTONUP)		// ���ѧ��
			{
				wchar_t perString[20];	// �û��ַ���

				// ���ȷ����ť�Ž������
				if (InputBox(perString, 20, L"�밴�� ��ID ���� VIP�ȼ� ���֡� �ĸ�ʽ�������ݣ�", L"����û�", NULL, 0, 0, false))
				{
					// ��ʽ�������ַ���
					std::wstringstream format(perString);
					Person per = {};
					format >> per.id >> per.name >> per.Vip >> per.score;

					// �жϸ�ʽ
					if (per.id <= 0)
					{
						MessageBox(GetHWnd(), L"ID����С�ڻ�����㣡", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					else if (std::wstring(per.name) == L"" || std::wstring(per.Vip) == L"")
					{
						MessageBox(GetHWnd(), L"������VIP�ȼ�����Ϊ�գ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					else if (per.score < 0)
					{
						MessageBox(GetHWnd(), L"���ֲ���С���㣡", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						continue;
					}

					// ��Ӻ�ˢ������
					manager.addPerson(per);
					table->showEditTable(per.name);
					manager.sortById();

					isEdit = true;
				}
			}
			else if (editPersons_delete->state(msg) && msg.message != WM_LBUTTONUP)	// ɾ��
			{
				short i = table->getSearchIndex();

				// �ж��Ƿ�������
				if (i != -1)
				{
					std::wstringstream format;
					if (MessageBox(GetHWnd(), L"ȷ��Ҫɾ������û���", L"ȷ��ɾ��", MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						manager.deletePerson(i);
						showEditPersons();
						isEdit = true;
						table->setSearchIndex(-1);
					}
				}
				else
				{
					MessageBox(GetHWnd(), L"���������û���", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				}
			}
		}
	}
}

bool Window::close()
{
	if (isEdit)
	{
		// ���б���
		int id = MessageBox(GetHWnd(), L"�Ƿ񱣴����еĲ�����", L"�˳�����", MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES)
		{
			// д���û�����
			manager.sortById();
			manager.write("Students.dat");
			closegraph();
			return true;
		}
		else if (id == IDNO)
		{
			return true;
		}
	}
	else
	{
		return true;
	}
	return false;
}

void Window::showMainWindow()
{
	state = WindowState::mainWindow;
	cleardevice();

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 502, 420);

	// ������ʾ����
	RECT rect = { 0, 0, width, 200 };
	settextstyle(50, 0, L"΢���ź�");
	drawtext(L"ɳ����ͻ�����ϵͳ", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// ��ʾ��ť
	mainWindow_view->show();
	mainWindow_edit->show();
	mainWindow_exit->show();
	mainWindow_clear->show();
}

void Window::showViewPersons()
{
	state = WindowState::viewPersons;
	cleardevice();

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 502, 420);

	// ��ʾ�ؼ�
	table->show();
	viewPersons_pageUp->show();
	viewPersons_pageDown->show();
	viewPersons_back->show();
	viewPersons_sort->show();
}

void Window::showEditPersons()
{
	state = WindowState::editPersons;
	cleardevice();

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 502, 420);

	// ��ʾ�ؼ�
	editPersons_search->show();
	editPersons_add->show();
	editPersons_delete->show();
	editPersons_back->show();
}

bool Window::isNumber(const std::wstring& string)
{
	if (_wtoi(string.c_str()) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
