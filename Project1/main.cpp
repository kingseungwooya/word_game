#include <iostream>
#include <windows.h>
#include <conio.h>
#include <random>
#include <string>
#include <conio.h>
#include <stdio.h>

// 메뉴 선택을 위한 constant 
#define UP 0
#define DOWN 1
#define SUBMIT 2

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void init() {
    system("mode con cols=60 lines=20 || title wordgame");
}


class Component {
public:
    virtual std::string generateString(int length) = 0;
    virtual ~Component() {}
};

// ConcreteComponent 클래스
class ConcreteComponent : public Component {
public:
    std::string generateString(int legnth) override {
        return "Default String";
    }
};

class GeneratorDecorator : public Component {
protected:
    Component* generator;
public:
    GeneratorDecorator(Component* generator) : generator(generator) {}

    std::string generateString(int length)  override {
        return generator->generateString(length);
    }
};

class GenerateAlphabet : public GeneratorDecorator {
public:
    GenerateAlphabet(Component* generator) : GeneratorDecorator(generator) {}

    std::string generateString(int length) override {
        const std::string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

        std::string random_string;

        for (std::size_t i = 0; i < length; ++i)
        {
            random_string += CHARACTERS[distribution(generator)];
        }
        return Component::generateString(length) + random_string;

    }
};

class GenerateNumber : public GeneratorDecorator {
public:
    GenerateNumber(Component* generator) : GeneratorDecorator(generator) {}

    std::string generateString(int length) override {
        const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

        std::string random_string;

        for (std::size_t i = 0; i < length; ++i)
        {
            random_string += CHARACTERS[distribution(generator)];
        }
        return Component::generateString(length) + random_string;

    }
};

class GenerateSC : public GeneratorDecorator {
public:
    GenerateSC(Component* generator) : GeneratorDecorator(generator) {}

    std::string generateString(int length) override {
        const std::string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()-_=+[]{};:,.<>?";

        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

        std::string random_string;

        for (std::size_t i = 0; i < length; ++i)
        {
            random_string += CHARACTERS[distribution(generator)];
        }
        return Component::generateString(length) + random_string;

    }
};
void titleDraw() {
    printf("\n\n\n\n");
   // std::cout << "                      #####     #    #     # ######" << std::endl;
   // std::cout << "                     #         ###   ##   ## #" << std::endl;
   // std::cout << "                    #  ####  #   #  # # # # # " << std::endl;
   // std::cout << "                   #    ## ####### #  #  # ######" << std::endl;
   // std::cout << "                  #     # #     # #     # #" << std::endl;
   // std::cout << "                 #####  #     # #     # ######" << std::endl;
}
int keyControl() {
    char temp = _getch();
    // 방향키
    if (temp == 'w' || temp == 'W') {

        return UP;
    }
    if (temp == 's' || temp == 'S') {
        return DOWN;
    }
    // 공백 입력시 종료
    if (temp == ' ' ) {
        return SUBMIT;
    }
}
int menuDraw() {
    int x = 24;
    int y = 12;
    gotoxy(x - 2, y);
    printf("> only alphabet");
    gotoxy(x, y + 1);
    printf("alphabet and number");
    gotoxy(x, y + 2);
    printf("alphabet and special symbol");
    while (1) {
        int n = keyControl();
        switch (n)
        {
        case UP: {
            if (y > 12) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, --y);
                printf(">");
            }
            break;
        }
        case DOWN: {
            if (y < 14) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, ++y);
                printf(">");
            }
            break;
        }
        case SUBMIT: {
            return y - 12;
        }

        }

    }
};
void gameStart(Component* component) {
    system("cls");
    printf(" 게임 시작띠");
    std::string generatedString = component->generateString(4);

};
int main() {
    init();
    while (1) {
        titleDraw();
        int menuCode = menuDraw();
        Component* component = new ConcreteComponent();
        if (menuCode == 0) {
            gameStart(new GenerateAlphabet(component));
        }
        if (menuCode == 1) {
            gameStart(new GenerateNumber(component));
        }
        if (menuCode == 2) {
            gameStart(new GenerateSC(component));
        }
        system("cls");
    }

    // int maxY = 30; // 콘솔 창의 최대 Y 좌표
    // int y = 0;
    // HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // 
    // SMALL_RECT windowSize = { 0, 0, 20, 31 }; // 
    // COORD bufferSize = { 20, 31 }; // 
    // SetConsoleWindowInfo(hOut, TRUE, &windowSize);
    // SetConsoleScreenBufferSize(hOut, bufferSize);    
    // 
    // 
    // while (true) {
    //     system("cls"); // 화면을 클리어하여 이전 문자열을 지웁니다.
    //     gotoxy(0, y); // 새로운 위치로 이동하여 문자열을 출력합니다.
    //     std::cout << "hi";
    // 
    //     // 문자열을 아래로 이동합니다.
    //     y++;
    // 
    //     // 일시 정지
    //     Sleep(200); // 100ms 지연
    // 
    //     // 콘솔 창의 최대 높이를 넘어가지 않도록 설정합니다.
    //     if (y > maxY) {
    //         y = 0; // 문자열을 맨 위로 이동시킵니다.
    //     }
    //     
    // }
    // std::string userInput;
    // 
    // // 사용자 입력 받기 위해 커서 이동
    // gotoxy(0, 31);
    // std::cout << "Enter input: ";
    // 
    // // 커서 이동하여 입력 받을 위치로
    // gotoxy(13, 31);
    // std::getline(std::cin, userInput);
    return 0;
};


