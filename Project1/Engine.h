#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include "Cursor.h"
#include "AlphabetGenerator.h"
#include "NumberDecorator.h"
#include "StringGenerator.h"
#include "SpecialCharDecorator.h"
#include "Scene.h"
#include "Rain.h"
#include <random>
#include <chrono>
#include <thread>
using namespace std;

enum GameType {
	ALPHABET_ONLY = 1,
	ALPHABET_AND_NUMBER = 2,
	ALPHABET_AND_SPECIAL_CHAR = 3,
	ALL = 4
};
class Engine : protected Rain {
	clock_t time1;				//���� ����� �ð� ���
	double speed = 1000;				//���̵� ������ �ð�(��)
	string word[21];			//�н��� �ܾ ������ string �迭, ������ �迭�� " "(����� �ܾ��)

	string inputWord;			//����ڰ� �Է��� �ܾ� ����

	int score = 0;				//��������
	int life = 100;				//�����

public:
	Rain rain[23];

	Engine();					//word �迭�� ���� �ܾ� ����,  ������ �迭�� " "(����� �ܾ��)
	void drawRain(int i);		//ȭ�鿡 rain[i]�� ����Ű�� ���ڸ� �׸��� �Լ�
	void setRain(int i);		//rain[i]�� �ʱ�ȭ�ϴ� �Լ�
	void eraseRain(int i);		//ȭ���� ���ڸ� ����� �Լ�
	void upScore();				//������ �����ϴ� �Լ�
	void downLife();			//�������� �����ϴ� �Լ�
	void ending();				//������ �������� ���� ����� �����ִ� �Լ�
	void input(int ch);			//����ڰ� �Է��� Ű�� ���� �����ϴ� �Լ�
	void compare();				//����ڰ� �Է��� ���ڿ� �������� ���ڸ� ���ϴ� �Լ�
	void startGame(int gameType);
	std::string generateString(int gameType);
	std::string randomString(std::string wordTable);
	void setWord(std::string wordTable);
};


Engine::Engine() {

	// //word �迭�� ���� �ܾ� ����, ������ �迭�� " "(����� �ܾ��)
	// srand(time(NULL));
	// for (int i = 0; i < 20; i++)
	// 	//word[i] = data(rand() % size());
	// word[20] = " ";
	// 
	// //Rain ��ü�迭 �ʱ�ȭ
	// for (int i = 0; i < 23; i++)
	// 	setRain(i);
}

void Engine::drawRain(int i) {
	Cursor::gotoxy(rain[i].x, rain[i].y);
	cout << word[rain[i].index];
}

void Engine::eraseRain(int i) {
	Cursor::gotoxy(rain[i].x, rain[i].y);
	for (int j = 0; j < word[rain[i].index].length(); j++)
		cout << " ";
}

void Engine::upScore() {
	score += 10;
	Cursor::gotoxy(5, 4);
	cout << "Score : " << score;
}

void Engine::downLife() {
	life -= 10;
	Cursor::gotoxy(5, 6);
	cout << "Life :  " << life;
}

void Engine::setRain(int i) {
	// std::random_device rd;
	// std::mt19937 gen(rd());
	// std::uniform_int_distribution<int> distrib(6, 30); // 24 / 4 = 6, 124 / 4 = 31
	// 
	//int randomNumber = distrib(gen) * 5;
	int randomNumber = (rand() % (23 - 6 + 1) + 6) * 5;
	rain[i].index = rand() % 20;
	//rain[i].x = 27 + (rand() % (98 - word[rain[i].index].length()));
	rain[i].x = randomNumber;

	rain[i].y = 0;
}

void Engine::ending() {
	if (score == 100) {
		system("cls");
		Scene::endingScene1();
		Sleep(50000);
		system("pause");
		exit(0);
	}
	if (life == 0) {
		system("cls");
		Scene::endingScene2();
		Sleep(50000);
		system("pause");
		exit(0);
	}
}

void Engine::input(int ch) {
	if (ch == '\b') {
		if (inputWord.length() != 0) {
			Cursor::gotoxy(65 + inputWord.length() - 1, 28);
			cout << " ";
			inputWord.pop_back();
		}
	}
	else if (ch != '\r') {
		Cursor::gotoxy(65 + inputWord.length(), 28);
		printf("%c", ch);
		inputWord.push_back(ch);
	}
	else if (ch == '\r') {
		compare();
		Cursor::gotoxy(65, 28);
		for (int i = 0; i < inputWord.length(); i++)
			cout << " ";
		inputWord.clear();
		ending();
	}
}

void Engine::compare() {
	int x = -1;
	for (int i = 0; i < 23; i++) {
		if (inputWord.compare(word[rain[i].index]) == 0) {
			if (x == -1) x = i;
			else if (rain[i].y > rain[x].y) x = i;
		}
	}
	if (x != -1) {
		eraseRain(x);
		rain[x].index = 20;
		upScore();
	}
}
std::string Engine::randomString(std::string wordTable) {
	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(0, wordTable.size() - 1);

	std::string random_string;

	for (int i = 0; i < 5; i++)
	{
		random_string += wordTable[distribution(generator)];
	}
	return random_string;
}
std::string Engine::generateString(int gameType) {
	AlphabetGenerator generator;
	switch (gameType) {
	case ALPHABET_ONLY: {
		return generator.generateString();
		}
	case ALPHABET_AND_NUMBER: {
		NumberDecorator number(&generator);
		return number.generateString();
		}
	case ALPHABET_AND_SPECIAL_CHAR: {
		SpecialCharDecorator sc(&generator);
		return sc.generateString();
		}
	case ALL: {
		NumberDecorator nd(&generator);
		SpecialCharDecorator sc(&nd);
		return sc.generateString();
		}	
	default: {
		std::cout << "error." << std::endl;
		return " ";
		}		
	}
}
void Engine::setWord(std::string wordTable) {
	//srand(time(NULL));
	for (int i = 0; i < 20; i++)
		word[i] = randomString(wordTable);
		word[20] = " ";

	//Rain ��ü�迭 �ʱ�ȭ
	for (int i = 0; i < 23; i++)
		setRain(i);
}

void Engine::startGame(int gameType) {
	int max = 1;				//�ܾ ���������� ���� Ŀ��, rain[]�迭�� ������ ���� ����
	time1 = clock();
	int ch;
	std:string wordTable;
	wordTable = generateString(gameType);
	setWord(wordTable);
	// rand() % 5 + 1
	int dSpeed = speed;
	while (1) {
		// �⺻ 1���� ���ð����� �������� 1���� 4�� ���ð� �� �־��� 
		//std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 4000 + 1000)); // 1�ʿ��� 5�� ������ ���� �ð� ���
		if (_kbhit()) {
			ch = _getch();
			input(ch);
		}
		// dSpeed = rand() % 4000 + 1000;
		if (clock() - time1 > (speed)) {
			for (int i = 0; i < max; i++) {
				

				eraseRain(i);
				rain[i].y++;
				if (rain[i].y == 23) {
					if (rain[i].index != 20) {
						downLife();
						ending();
					}
					setRain(i);
					drawRain(i);
				}
				else drawRain(i);
			}
			if (max < 23)
				max++;
			speed = rand() % 4000 + 1000;
			time1 = clock();
	
		}
	}
}

