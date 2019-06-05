#ifndef _GAME_H_
#define _GAME_H_
#include "letter.h"
#include <ncurses.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <cstdlib>

using namespace std;

//klasa Game realizuje cala logike gry
//odpowiada za tworzenie i zarzadzanie oknami ncurses
//odpowiada za utworzenie i uruchomienie oraz polczenie watkow gry
class Game
{
private:
//WINDOWS VARIABLES
#pragma region WINDOWS
    //windows
    WINDOW *GameWindow;
    WINDOW *ScoreWindow;
    WINDOW *GoodbyeWindow;
    //Game Window Sizes
    int GameWindowWidth;
    int GameWindowHeight;
    int GameWindowCornerX;
    int GameWindowCornerY;
    //Score Window Sizes
    int ScoreWindowWidth;
    int ScoreWindowHeight;
    int ScoreWindowCornerX;
    int ScoreWindowCornerY;
    //Main Window Size
    int MainWindowWidth;
    int MainWindowHeight;
#pragma endregion
//GAME VARIABLES
#pragma region GAME
    bool IsGameActive;
    bool WasButtonClicked;
    bool MustBeRedrawn;
    vector<Letter> Letters;
    int MaxNumberOfLetters;
    //predkosci odpowiednio spadania i generacji literek
    int LetterFallingSpeed;
    int LetterGenerationSpeed;
    int Score;
    char ClickedButton;
#pragma endregion
//THREADING VARIABLES
#pragma region THREADING
    mutex MutexForLetters;
    mutex MutexForClickedButton;
    mutex MutexForNextChar;
    condition_variable ButtonWasClicked;
    condition_variable MustRedraw;
    condition_variable NextChar;

#pragma endregion

    //WINDOWS FUNCTIONS
    void ScreenInit();
    void GameInit();
    //powitalny i pozegnalny ekran
    void TypingMasterWelcome();
    void TypingMasterGoodbye();

    //THREADING FUNCTIONS
    //funkcja generujaca kolejne obiekty --- literki
    void GenerateLetters();
    //funkcja odrysowujaca zawartosc ekranu
    void RedrawTheScreen();
    //funkcja aktualizujaca polozenie wszystkich obiektow --- literek
    void UpdatePosition();
    //funkcja pobierajaca kod klawisza
    void GetClickedButton();
    //funkcja sprawdzajaca wcisniety klawisz
    void CheckClickedButton();
    //funkcja aktualizujaca wynik gracza
    void UpdateScore();

public:
    Game();
    //funkcja PlayGame uruchamia wszytskie watki
    //jest to jednoznaczne z uruchomieniem gry
    void PlayGame();
    //helpers 4 con_vars
    bool IsRedrawNeeded();
    bool HaveButtonBeenClicked();
    char GetCharClickedButton();
    ~Game();
};

#endif