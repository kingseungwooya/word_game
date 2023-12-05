#pragma once
#include <iostream>
#include <string>
#include "Cursor.h"

using namespace std;

class Scene {
public:
	static int difficulty;			//���̵� ����
	static void sceneBox();			//ȭ�� Ʋ ��� 
	static void sceneTitle();		//���� ���
	static void scene1();			//ȭ�� 1 ���� ���
	static void scene2();			//ȭ�� 2 ���� ��� �� ���̵� ����
	static void sceneBox2();		//���� ȭ�� Ʋ ���
	static void endingScene1();
	static void endingScene2();
	static int selectMenu();
};

int Scene::difficulty = 1;

void Scene::sceneBox() {
	Cursor::gotoxy(25, 5);
	for (int i = 0; i < 51; i++) {
		cout << "-";
	}
	for (int i = 6; i < 30; i++) {
		Cursor::gotoxy(25, i);
		cout << "-";
	}
	for (int i = 6; i < 30; i++) {
		Cursor::gotoxy(125, i);
		cout << "-";
	}
	Cursor::gotoxy(25, 30);
	for (int i = 0; i < 51; i++) {
		cout << "-";
	}
}

int::Scene::selectMenu() {
	Cursor::gotoxy(24, 18);
	std::cout << "input : " << std::endl;
	int ch;
	do {
		ch = _getch();
	} while (ch < '1' || ch > '4');
	return ch - '0';
}

void Scene::sceneTitle() {
	std::cout << "                          #####     #    #     # ######" << std::endl;
	std::cout << "                         #         ###   ##   ## #" << std::endl;
	std::cout << "                        #  ####  #   #  # # # # # " << std::endl;
	std::cout << "                       #    ## ####### #  #  # ######" << std::endl;
	std::cout << "                      #     # #     # #     # #" << std::endl;
	std::cout << "                     #####  #     # #     # ######" << std::endl;
}

void Scene::scene1() {
	Cursor::gotoxy(41, 23);
	cout << "201801783 seungwookim term project <WORD_GAME>";
	Cursor::gotoxy(41, 25);
	cout << "press any key";
	system("pause>null");
}

void Scene::scene2() {
	Cursor::gotoxy(24, 12);
	std::cout << "choose your game type:" << std::endl;
	Cursor::gotoxy(24, 13);
	std::cout << "1. only alphabet" << std::endl;
	Cursor::gotoxy(24, 14);
	std::cout << "2. alphabet and num" << std::endl;
	Cursor::gotoxy(24, 15);
	std::cout << "3. alphabet and special char" << std::endl;
	Cursor::gotoxy(24, 16);
	std::cout << "4. alphabet and special char and num" << std::endl;
}

void Scene::sceneBox2() {
	for (int i = 0; i < 30; i++) {
		Cursor::gotoxy(25, i);
		cout << "o";
	}
	for (int i = 0; i < 30; i++) {
		Cursor::gotoxy(125, i);
		cout << "o";
	}
	// x
	Cursor::gotoxy(25, 30);
	for (int i = 0; i < 51; i++) {
		cout << "o";
	}
	// x
	Cursor::gotoxy(27, 23);
	for (int i = 0; i < 98; i++) {
		cout << "o";
	}
	// x
	Cursor::gotoxy(65, 29);
	for (int i = 0; i < 21; i++) {
		cout << "o";
	}
	Cursor::gotoxy(5, 4);
	cout << "Score : " << '0';
	Cursor::gotoxy(5, 6);
	cout << "Life : " << "100";
}

void Scene::endingScene1() {
	sceneBox();
	Cursor::gotoxy(60, 15);
	cout << "c++�� ���� ���ϴ±���? ���ϵ帳�ϴ�!";
}

void Scene::endingScene2() {
	sceneBox();
	Cursor::gotoxy(65, 15);
	cout << "�� �� ������ �ʿ��ؿ�!";
}