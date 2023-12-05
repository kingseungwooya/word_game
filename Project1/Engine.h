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
	clock_t time1;				//게임 진행용 시각 상수
	double speed = 1000;				//난이도 조절용 시간(초)
	string word[21];			//학습할 단어를 저장할 string 배열, 마지막 배열은 " "(사라진 단어용)

	string inputWord;			//사용자가 입력한 단어 저장

	int score = 0;				//게임점수
	int life = 100;				//생명력

public:
	Rain rain[23];

	Engine();					//word 배열에 랜던 단어 저장,  마지막 배열은 " "(사라진 단어용)
	void drawRain(int i);		//화면에 rain[i]이 가리키는 글자를 그리는 함수
	void setRain(int i);		//rain[i]를 초기화하는 함수
	void eraseRain(int i);		//화면의 글자를 지우는 함수
	void upScore();				//점수를 조절하는 함수
	void downLife();			//라이프를 조절하는 함수
	void ending();				//점수와 라이프에 따라 결과를 보여주는 함수
	void input(int ch);			//사용자가 입력한 키에 따라 반응하는 함수
	void compare();				//사용자가 입력한 글자와 떨어지는 글자를 비교하는 함수
	void startGame(int gameType);
	std::string generateString(int gameType);
	std::string randomString(std::string wordTable);
	void setWord(std::string wordTable);
};


Engine::Engine() {

	// //word 배열에 랜덤 단어 저장, 마지막 배열은 " "(사라진 단어용)
	// srand(time(NULL));
	// for (int i = 0; i < 20; i++)
	// 	//word[i] = data(rand() % size());
	// word[20] = " ";
	// 
	// //Rain 객체배열 초기화
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

	//Rain 객체배열 초기화
	for (int i = 0; i < 23; i++)
		setRain(i);
}

void Engine::startGame(int gameType) {
	int max = 1;				//단어가 떨어질수록 값이 커짐, rain[]배열의 갯수를 넘지 않음
	time1 = clock();
	int ch;
	std:string wordTable;
	wordTable = generateString(gameType);
	setWord(wordTable);
	// rand() % 5 + 1
	int dSpeed = speed;
	while (1) {
		// 기본 1초의 대기시간에서 랜덤으로 1에서 4초 대기시간 더 주어짐 
		//std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 4000 + 1000)); // 1초에서 5초 사이의 랜덤 시간 대기
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

