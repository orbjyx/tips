#pragma warning(disable:4996);
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib") 
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#include <graphics.h>  
#define USERNAME "ibjyx"
#define PASSWORD "182395"
SOCKADDR_IN cAddr = { 0 };
int len = sizeof cAddr;
SOCKET clientSocket;

typedef struct customer {
	char name[50];
	char sex[20];
	char phone[50];
	int number;
	int time;
	int quxiao;
}customer;//ÿλ�˿���Ϣ
typedef struct btime {
	customer message[150];
	int count;
}btime;//��Ӫҵʱ�仮������Դ洢��Ϣ
int start = 9;
int finish = 23;//���ó�ʼӪҵʱ��
int C = 0;
int g = 12;
int menu(btime group[20]);
void read(btime group[20]);
void write(btime group[20]);
int control(btime group[20], int n);
void search(btime group[20]);
int net(btime group[20]) {
	initgraph(640, 480);
	// ������䵥Ԫ
	IMAGE img;
	loadimage(&img, _T("1.jpg"), 640, 480, true);
	putimage(0, 0, &img);
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 35;						// ��������߶�Ϊ 35
	_tcscpy(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	outtextxy(80, 10, _T("��ӭ��¼bxϴԡ����ԤԼϵͳ"));
	f.lfHeight = 25;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(170, 80, _T("Ӫҵʱ�䣺"));
	char s[2];
	sprintf(s, "%d", start);
	outtextxy(290, 80, s);
	outtextxy(305, 80, _T(":00��"));
	sprintf(s, "%d", finish);
	outtextxy(380, 80, s);
	outtextxy(405, 80, _T(":00"));
	system("cls");
	//1.����汾�� 
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		return -1;
	}

	//2.����socket

	SOCKET severSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//ͨ��Э�����ͣ�ͨ���õ��������ͣ�������ʽ
	if (severSocket == -1) {
		WSACleanup();
		return -2;
	}

	//3.����Э���ַ��

	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;//Э��汾
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.5.5");//���Լ���
	addr.sin_port = htons(10086);//��10000���ң�С�Ķ˿ڱ�ϵͳ�õ�

	//4.��

	int r = bind(severSocket, (sockaddr*)&addr, sizeof addr);
	if (r == -1) {
		closesocket(severSocket);
		WSACleanup();
		return -2;
	}

	//5.����

	r = listen(severSocket, 10);
	if (r == -1) {
		closesocket(severSocket);
		WSACleanup();
		return -2;
	}

	//6.�ȴ��ͻ������� ���� β������


	clientSocket = accept(severSocket, (sockaddr*)&cAddr, &len);
	if (clientSocket == SOCKET_ERROR) {
		closesocket(severSocket);
		WSACleanup();
		return -2;
	}
	f.lfHeight = 20;
	settextstyle(&f);
	outtextxy(170, 120, _T("�пͻ������ӵ�������"));

	//7.ͨ��

	char buff[1024];
	outtextxy(170, 160, _T("������Ϣ��"));
	int i = 0;
	int x, y;
	x = 200, y = 200;
	while (1) {
		i++;
		memset(buff, 0, 1024);
		r = recv(clientSocket, buff, 1023, NULL);
		if (r > 0) {
			buff[r] = 0;//��ӡ�\0��
			if (i == 1) {
				outtextxy(x, y, _T("������"));
				outtextxy(x+60,y,buff);
			}
			if (i == 2) {
				y = y + 30;
				outtextxy(x, y, _T("�Ա�"));
				outtextxy(x+60,y,buff);
			}
			if (i == 3) {
				y = y + 30;
				outtextxy(x, y, _T("��ϵ��ʽ��"));
				outtextxy(x+100,y,buff);
			}
		}
		memset(buff, 0, 1024);
		if (i == 3) { i = 0; y = y + 40; }
	}

	//8.�ر�socket

	closesocket(severSocket);

	//9.���Э����Ϣ

	WSACleanup();
	return 0;
}
void quit(btime group[20]) {
	char ch;
	// ������䵥Ԫ
	IMAGE img;
	loadimage(&img, _T("1.jpg"), 640, 480, true);
	putimage(0, 0, &img);
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setlinecolor(YELLOW);
	rectangle(120, 250, 240, 290);
	rectangle(400, 250, 520, 290);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 35;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfHeight = 15;
	settextstyle(&f);
	outtextxy(127, 262, _T("���ص�½ҳ��"));
	outtextxy(413, 262, _T("�˳�������"));
	outtextxy(80, 10, _T("��ӭ��¼bxϴԡ����ԤԼϵͳ"));
	f.lfHeight = 25;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(170, 80, _T("Ӫҵʱ�䣺"));
	char s[2];
	sprintf(s, "%d", start);
	outtextxy(290, 80, s);
	outtextxy(315, 80, _T(":00��"));
	sprintf(s, "%d", finish);
	outtextxy(380, 80, s);
	outtextxy(405, 80, _T(":00"));
	MOUSEMSG m;// ���������Ϣ
	while (true)
	{
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if ((m.x >= 120 && m.x <= 240) && (m.y >= 250 && m.y <= 290))
			{
				menu(group);
			}
			if((m.x >= 400 && m.x <= 520) && (m.y >= 250 && m.y <= 290)){
				write(group);
				_exit(0);
			}
		}
	}
}
void book(btime group[20]) {
	int p;
	int i, j;
	int n;
	int n1;
	n1 = 0;
	initgraph(640, 480);
	IMAGE img;
	LOGFONT f;
	loadimage(&img, _T("1.jpg"), 640, 480, true);
	putimage(0, 0, &img);
	setbkcolor(WHITE);
	setlinecolor(YELLOW);
	setbkmode(TRANSPARENT);
	rectangle(245, 245, 385, 290);
	settextcolor(BLACK);
	gettextstyle(&f);
	f.lfHeight = 35;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(80, 10, _T("��ӭ��¼bxϴԡ����ԤԼϵͳ"));
	f.lfHeight = 25;
	settextstyle(&f);
	outtextxy(170, 80, _T("Ӫҵʱ�䣺"));
	char s[2];
	sprintf(s, "%d", start);
	outtextxy(290, 80, s);
	outtextxy(315, 80, _T(":00��"));
	sprintf(s, "%d", finish);
	outtextxy(380, 80, s);
	outtextxy(405, 80, _T(":00"));
	f.lfHeight = 20;
	settextstyle(&f);
	outtextxy(255, 256, _T("ѡ��ԤԼʱ��"));
	MOUSEMSG m;// ���������Ϣ
	while (true)
	{
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		char a[10];
		int r;
		if (m.uMsg == WM_LBUTTONDOWN) {
			if ((m.x >= 245 && m.x <= 385) && (m.y >= 245 && m.y <= 290)) {
				InputBox(a, 10, "������ԤԼʱ�䣨�����������ּ��ɣ�");
				sscanf(a, "%d", &r);
				n = r - start;
				group[n].count++;
				C++;
				p = control(group, n);
				if (p == 1) {
					n1 = group[n].count - 1;
					loadimage(&img, _T("1.jpg"), 640, 480, true);
					putimage(0, 0, &img);
					setbkcolor(WHITE);
					setlinecolor(YELLOW);
					setbkmode(TRANSPARENT);
					settextcolor(BLACK);
					gettextstyle(&f);
					f.lfHeight = 35;
					_tcscpy(f.lfFaceName, _T("����"));
					f.lfQuality = ANTIALIASED_QUALITY;
					settextstyle(&f);
					outtextxy(80, 10, _T("��ӭ��¼bxϴԡ����ԤԼϵͳ"));
					loadimage(&img, _T("�û�.jpg"), 100, 100, true);
					putimage(265, 100, &img);
					f.lfHeight = 20;
					settextstyle(&f);
					outtextxy(245, 256, _T("����д���¸�����Ϣ"));
					InputBox(a, 20, "����");
					sscanf(a, "%s", group[n].message[n1].name);

					InputBox(a, 20, "�Ա�");
					sscanf(a, "%s", group[n].message[n1].sex);

					InputBox(a, 20, "��ϵ��ʽ");
					sscanf(a, "%s", group[n].message[n1].phone);
					
					group[n].message[n1].time = n;
					group[n].message[n1].number =C;
					group[n].message[n1].quxiao = 0;
			}
			}
			break;
		}
	}
	quit(group);
}
void xiugai(btime group[20]) {
	initgraph(640, 480);
	// ������䵥Ԫ
	IMAGE img;
	loadimage(&img, _T("1.jpg"), 640, 480, true);
	putimage(0, 0, &img);
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 35;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(80, 10, _T("��ӭ��¼bxϴԡ����ԤԼϵͳ"));
	f.lfHeight = 25;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(170, 80, _T("Ӫҵʱ�䣺"));
	char s[2];
	sprintf(s, "%d", start);
	outtextxy(290, 80, s);
	outtextxy(315, 80, _T(":00��"));
	sprintf(s, "%d", finish);
	outtextxy(380, 80, s);
	outtextxy(405, 80, _T(":00"));
	int s1, s2;
	char a[20];
	int r,i;
	char name[20];
	InputBox(a, 10, "����������ԤԼʱ�䣨�����������ּ��ɣ�");
	sscanf(a, "%d", &r);
	s2 = r - start;
	InputBox(a, 10, "�������û�����");
	sscanf(a, "%s", name);

	for (i = 0; i < group[s2].count; i++) {
		if (strcmp(name, group[s2].message[i].name) == 0) {
			if (group[s2].message[i].quxiao == 0) {
				gettextstyle(&f);
				f.lfHeight = 25;
				_tcscpy(f.lfFaceName, _T("����"));
				f.lfQuality = ANTIALIASED_QUALITY;
				settextstyle(&f);
				outtextxy(250, 150, _T("��ѡ�������Ŀ"));
				f.lfHeight = 15;
				settextstyle(&f);
				setlinecolor(YELLOW);
				rectangle(150, 250, 230, 290);
				rectangle(350, 250, 430, 290);
				rectangle(150, 320, 230, 360);
				rectangle(350, 320, 430, 360);
				outtextxy(170, 260, _T("����"));
				outtextxy(370, 260, _T("�Ա�"));
				outtextxy(160, 330, _T("��ϵ��ʽ"));
				outtextxy(360, 330, _T("ȡ��ԤԼ"));
				MOUSEMSG m;
				while (true)
				{
					m = GetMouseMsg();
					if (m.uMsg == WM_LBUTTONDOWN) {
						if ((m.x >= 150 && m.x <= 230) && (m.y >= 250 && m.y <= 290))
						{
							InputBox(a, 20, "�����޸ĺ�����");
							sscanf(a, "%s", group[s2].message[i].name);
						}
						if ((m.x >= 350 && m.x <= 420) && (m.y >= 250 && m.y <= 290))
						{
							InputBox(a, 20, "�����޸ĺ��Ա�");
							sscanf(a, "%s", group[s2].message[i].sex);
						}
						if ((m.x >= 150 && m.x <= 230) && (m.y >= 320 && m.y <= 360))
						{
							InputBox(a, 20, "�����޸ĺ���ϵ��ʽ");
							sscanf(a, "%s", group[s2].message[i].phone);
						}
						if ((m.x >= 350 && m.x <= 420) && (m.y >= 320 && m.y <= 360))
						{
							group[s2].message[i].quxiao = 1;
							C--;
							group[s2].count--;
						}
						break;
					}
				}
			}
		}
	}
	quit(group);
}
void search(btime group[20]) {
	char a[20];
	int r;
	int s1, s2,t1,t2;
	int i;
	int flag = 0;
	char name[20];
	initgraph(640, 480);
	// ������䵥Ԫ
	IMAGE img;
	loadimage(&img, _T("1.jpg"), 640, 480, true);
	putimage(0, 0, &img);
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 35;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(80, 10, _T("��ӭ��¼bxϴԡ����ԤԼϵͳ"));
	f.lfHeight = 25;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(170, 80, _T("Ӫҵʱ�䣺"));
	char s[2];
	sprintf(s, "%d", start);
	outtextxy(290, 80, s);
	outtextxy(315, 80, _T(":00��"));
	sprintf(s, "%d", finish);
	outtextxy(380, 80, s);
	outtextxy(405, 80, _T(":00"));
	InputBox(a, 10, "����������ԤԼʱ�䣨�����������ּ��ɣ�");
	sscanf(a, "%d", &r);
	s2 = r - start;
	InputBox(a, 10, "�������û�����");
	sscanf(a, "%s", name);

	for (i = 0; i < group[s2].count; i++) {
		if (strcmp(name, group[s2].message[i].name) == 0) {
			if (group[s2].message[i].quxiao == 0) {
				f.lfHeight = 20;
				_tcscpy(f.lfFaceName, _T("����"));
				f.lfQuality = ANTIALIASED_QUALITY;
				settextstyle(&f);
				outtextxy(240, 200, _T("������"));
				outtextxy(240, 240, _T("�Ա�"));
				outtextxy(240, 280, _T("��ţ�"));
				outtextxy(240, 320, _T("ԤԼʱ�䣺"));
				outtextxy(240, 360, _T("��ϵ��ʽ��"));
				outtextxy(290, 200, group[s2].message[i].name);
				outtextxy(290, 240, group[s2].message[i].sex);
				char s[5];
				sprintf(s, "%d", group[s2].message[i].number);
				outtextxy(305, 280, s);
				t1 = s2 + start;
				t2 = t1 + 3;
				sprintf(s, "%d", t1);
				outtextxy(330, 320, s);
				outtextxy(350, 320, _T(":00��"));
				sprintf(s, "%d", t2);
				outtextxy(405, 320, s);
				outtextxy(435, 320, _T(":00"));
				outtextxy(330, 360, group[s2].message[i].phone);
				flag++;
			}
		}
	}
	if(flag==0){
		f.lfHeight = 20;
		_tcscpy(f.lfFaceName, _T("����"));
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		outtextxy(210, 250, _T("δ��ѯ�������Ϣ��")); }
	setlinecolor(YELLOW);
	rectangle(290, 400, 340, 440);
	outtextxy(295, 405, _T("����"));
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if ((m.x >= 290 && m.x <= 340) && (m.y >= 400 && m.y <= 440)) 
			{
				quit(group);
			}
			break;
		}
	}
}
void write(btime group[20]) {
	FILE* fWrite = fopen("D:\\����.txt", "w");
	if (fWrite == NULL)
	{
		return;
	}
	int j = 0, k = 0, i;
	fprintf(fWrite, "���\tԤԼʱ�����\t��  ��\t�Ա�\t��ϵ��ʽ\n");
	for (j = 0, k = 0; j < g; j++, k++) {
		if (group[j].count != 0) {
			for (k = 0; k < group[j].count; k++) {
				if (group[j].message[k].quxiao == 0) {
					i = j + 1;
					fprintf(fWrite, "%ld\t%d\t\t%s\t%s\t%s", group[j].message[k].number,
						i, group[j].message[k].name, group[j].message[k].sex, group[j].message[k].phone);
				}
				if(k<group[j].count -1)fprintf(fWrite, "\n");
			}
		}
		else continue;
	}
	fclose(fWrite);
}
void read(btime group[20]) {
	int i, k;
	long m;
	char s1[20];
	FILE* fRead = fopen("D:\\����.txt", "r");
	for (i = 0; i < 20; i++)
	{
		group[i].count = 0;
	}
	if (fRead == NULL)
	{
		write(group);	//�ļ������ھʹ����ļ�
		return;
	}
	rewind(fRead);	//���ļ��ڲ�ָ���ƻ��ļ���ͷ
	for (i = 0; i < 6; i++)fscanf(fRead, "%s", s1);
	for (k = 0; !feof(fRead); k++) {
		fscanf(fRead, "%ld%d", &m, &i);
		i--;
		fscanf(fRead, "%s%s%s", group[i].message[k].name, group[i].message[k].sex, group[i].message[k].phone);
		group[i].count++;
		group[i].message[k].quxiao = 0;
		group[i].message[k].time = i + 1;
		group[i].message[k].number = m;
		C = m;
	}
	fclose(fRead);
}
void transform(btime group[20]) {
	initgraph(640, 480);
	// ������䵥Ԫ
	IMAGE img;
	loadimage(&img, _T("1.jpg"), 640, 480, true);
	putimage(0, 0, &img);
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 35;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(80, 10, _T("��ӭ��¼bxϴԡ����ԤԼϵͳ"));
	f.lfHeight = 25;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	loadimage(&img, _T("����Ա.jpg"), 100, 100, true);
	putimage(255, 130, &img);
	outtextxy(170, 80, _T("Ӫҵʱ�䣺"));
	char s[2];
	sprintf(s, "%d", start);
	outtextxy(290, 80, s);
	outtextxy(315, 80, _T(":00��"));
	sprintf(s, "%d", finish);
	outtextxy(380, 80, s);
	outtextxy(405, 80, _T(":00"));
	InputBox(s, 20, "���Ŀ���ʱ��");
	sscanf(s, "%d", &start);
	InputBox(s, 20, "���ıչ�ʱ��");
	sscanf(s, "%d", &finish);
	quit(group);
}
void show(btime group[20]) {
	int j = 0, k = 0, i;
	initgraph(640, 480);
	// ������䵥Ԫ
	IMAGE img;
	loadimage(&img, _T("1.jpg"), 640, 480, true);
	putimage(0, 0, &img);
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 35;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(80, 10, _T("��ӭ��¼bxϴԡ����ԤԼϵͳ"));
	f.lfHeight = 25;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	loadimage(&img, _T("����Ա.jpg"), 100, 100, true);
	putimage(255, 130, &img);
	outtextxy(170, 80, _T("Ӫҵʱ�䣺"));
	char s[2];
	sprintf(s, "%d", start);
	outtextxy(290, 80, s);
	outtextxy(315, 80, _T(":00��"));
	sprintf(s, "%d", finish);
	outtextxy(380, 80, s);
	outtextxy(405, 80, _T(":00"));
	search(group);
}
void flow(btime group[20]) {
	initgraph(640, 480);
	IMAGE img;
	LOGFONT f;
	loadimage(&img, _T("1.jpg"), 640, 480, true);
	putimage(0, 0, &img);
	setbkcolor(WHITE);
	setlinecolor(YELLOW);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	gettextstyle(&f);
	f.lfHeight = 35;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(80, 10, _T("��ӭ��¼bxϴԡ����ԤԼϵͳ"));
	f.lfHeight = 25;
	settextstyle(&f);
	outtextxy(170, 80, _T("Ӫҵʱ�䣺"));
	char s[2];
	sprintf(s, "%d", start);
	outtextxy(290, 80, s);
	outtextxy(315, 80, _T(":00��"));
	sprintf(s, "%d", finish);
	outtextxy(380, 80, s);
	outtextxy(405, 80, _T(":00"));
	f.lfHeight = 20;
	settextstyle(&f);
	outtextxy(210, 180, _T("��ǰ���������࣬���Ժ�ԤԼ������"));
	setlinecolor(YELLOW);
	rectangle(290, 400, 340, 440);
	outtextxy(295, 405, _T("����"));
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if ((m.x >= 290 && m.x <= 340) && (m.y >= 400 && m.y <= 440))
			{
				quit(group);
			}
			break;
		}
	}
}
int control(btime group[20], int n) {
	if (group[n].count <= 2 && group[n].count >= 0) { return 1; }
	else { flow(group); return 0; }
}
int menu(btime group[20]) {
	initgraph(640, 480);
	// ������䵥Ԫ
	IMAGE img;
	loadimage(&img, _T("1.jpg"), 640, 480,true);
	putimage(0, 0, &img);
	setbkcolor(WHITE);
	setlinecolor(YELLOW);
	rectangle(120, 250, 210, 290);
	rectangle(400, 250, 490, 290);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
		LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 35;						// ��������߶�Ϊ 35
	_tcscpy(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	outtextxy(80, 10, _T("��ӭ��¼bxϴԡ����ԤԼϵͳ"));
	f.lfHeight = 25;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(170, 80, _T("Ӫҵʱ�䣺"));
	char s[2];
	sprintf(s, "%d", start);
	outtextxy(290, 80, s);
	outtextxy(305, 80, _T(":00��"));
	sprintf(s, "%d", finish);
	outtextxy(380, 80, s);
	outtextxy(405, 80, _T(":00"));
	f.lfHeight = 15;						
	_tcscpy(f.lfFaceName, _T("����"));		
	f.lfQuality = ANTIALIASED_QUALITY;		
	settextstyle(&f);
	outtextxy(127, 262, _T("����Ա��½"));
	outtextxy(413, 262, _T("�û���½"));
	MOUSEMSG m;// ���������Ϣ
	int k = 0;
	while (true)
	{
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if ((m.x >= 120 && m.x <= 210) && (m.y >= 250 && m.y <= 290))
			{
				loadimage(&img, _T("1.jpg"), 640, 480, true);
				putimage(0, 0, &img);
				loadimage(&img, _T("����Ա.jpg"), 100, 100, true);
				putimage(255, 100, &img);
				setbkcolor(WHITE);
				settextcolor(BLACK);
				LOGFONT f;
				gettextstyle(&f);
				f.lfHeight = 35;
				_tcscpy(f.lfFaceName, _T("����"));
				f.lfQuality = ANTIALIASED_QUALITY;
				settextstyle(&f);
				outtextxy(80, 10, _T("��ӭ��¼bxϴԡ����ԤԼϵͳ"));
				f.lfHeight = 20;
				_tcscpy(f.lfFaceName, _T("����"));
				f.lfQuality = ANTIALIASED_QUALITY;
				settextstyle(&f);
				outtextxy(255, 250, _T("����Ա��¼"));
				char manager[20], a[20];
				char password[20], b[20];
				int flag = 0;
				for (int i = 0; i < 3; i++) {
					InputBox(a, 20, "�������˺�");
					sscanf(a, "%s", manager);
					InputBox(b, 20, "����������");
					sscanf(b, "%s", password);
					if (strcmp(password, PASSWORD) == 0 && strcmp(USERNAME, manager) == 0) {
						flag = 1;
						loadimage(&img, _T("1.jpg"), 640, 480, true);
						putimage(0, 0, &img);
						setbkcolor(WHITE);
						settextcolor(BLACK);
						rectangle(250, 120, 400, 160);
						rectangle(250, 190, 400, 230);
						rectangle(250, 260, 400, 300);
						LOGFONT f;
						gettextstyle(&f);
						f.lfHeight = 35;
						_tcscpy(f.lfFaceName, _T("����"));
						f.lfQuality = ANTIALIASED_QUALITY;
						settextstyle(&f);
						outtextxy(80, 10, _T("��ӭ��¼bxϴԡ����ԤԼϵͳ"));
						f.lfHeight = 15;
						_tcscpy(f.lfFaceName, _T("����"));
						f.lfQuality = ANTIALIASED_QUALITY;
						settextstyle(&f);
						outtextxy(260, 132, _T("��ѯ�û�ԤԼ���"));
						outtextxy(275, 202, _T("����Ӫҵʱ��"));
						outtextxy(290, 272, _T("������Ϣ"));
						k = 1;
						break;
					}
				}
				if (flag == 0)return 0;
			}
				if ((m.x >= 250 && m.x <= 400) && (m.y >= 120 && m.y <= 160)&&k==1) {
					show(group); quit(group);
				}
				if ((m.x >= 250 && m.x <= 400) && (m.y >= 190 && m.y <= 230)&&k==1) {
					transform(group); quit(group);
				}
				if ((m.x >= 250 && m.x <= 400) && (m.y >= 260 && m.y <= 300)&&k==1) {
					int i;
					i = net(group); quit(group);
				}
			if ((m.x >= 400 && m.x <= 490) && (m.y >= 250 && m.y <= 290)&&k==0) 
			{
				k == 2;
				loadimage(&img, _T("1.jpg"), 640, 480, true);
				putimage(0, 0, &img);
				setbkcolor(WHITE);
				settextcolor(BLACK);
				rectangle(250, 120, 350, 160);
				rectangle(250, 190, 350, 230);
				rectangle(250, 260, 350, 300);
				LOGFONT f;
				gettextstyle(&f);
				f.lfHeight = 35;
				_tcscpy(f.lfFaceName, _T("����"));
				f.lfQuality = ANTIALIASED_QUALITY;
				settextstyle(&f);
				outtextxy(80, 10, _T("��ӭ��¼bxϴԡ����ԤԼϵͳ"));
				f.lfHeight = 15;
				_tcscpy(f.lfFaceName, _T("����"));
				f.lfQuality = ANTIALIASED_QUALITY;
				settextstyle(&f);
				outtextxy(280, 132, _T("ԤԼ"));
				outtextxy(265, 202, _T("��ѯԤԼ"));
				outtextxy(265, 272, _T("������Ϣ"));
			}
			if ((m.x >= 250 && m.x <= 350) && (m.y >= 120 && m.y <= 160)) {
				book(group); 
			}
			if ((m.x >= 250 && m.x <= 350) && (m.y >= 190 && m.y <= 230)) {
				search(group); quit(group);
			}
			if ((m.x >= 250 && m.x <= 350) && (m.y >= 260 && m.y <= 300)) {
				xiugai(group); quit(group);
			}
		}
	}

	// ��������˳�
	_getch();
	closegraph();
}
int main() {
	btime group[20];
	read(group);
	menu(group);
	return 0;
}
