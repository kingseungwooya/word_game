#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Cursor.h"
#include "Scene.h"
#include "Rain.h"
#include "Engine.h"
#include <string>
using namespace std;


int main() {
    system("mode con: cols=150 lines=50");
    Cursor::hideCursor();
    
    Engine engine;
    
    
    while (1) {
        Scene::scene1();
        system("cls");
    
        // Scene::sceneBox();			//두번째 화면
        Scene::scene2();
        int selectedMenu = Scene::selectMenu();
        system("cls");
        // 여기서 gametype을 받아야함
        Scene::sceneBox2();			//게임 화면
        engine.startGame(selectedMenu);
        
    }
   

    return 0;
};