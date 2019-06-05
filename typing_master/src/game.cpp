#include "game.h"

Game::Game()
{
    ScreenInit();
    GameInit();
}

void Game::ScreenInit()
{
    //SCREEN INITIALIZATION
    initscr();
    //text isn't displayed to the window
    noecho();
    //cursor invisible
    curs_set(0);
    //enable exit with ctrl+C
    cbreak();
    //main window must be draw in other case the children-windows wont be displayed
    refresh();
    //setting parameters of windows
    getmaxyx(stdscr, MainWindowHeight, MainWindowWidth);
    GameWindowWidth = MainWindowWidth - 20;
    ScoreWindowWidth = MainWindowWidth - 20;
    GameWindowHeight = MainWindowHeight / 7 * 6;
    ScoreWindowHeight = 3;
    GameWindowCornerX = 10;
    ScoreWindowCornerX = 10;
    GameWindowCornerY = 1;
    ScoreWindowCornerY = MainWindowHeight - ScoreWindowHeight - 1;
    //creating windows
    GameWindow = newwin(GameWindowHeight, GameWindowWidth, GameWindowCornerY, GameWindowCornerX);
    ScoreWindow = newwin(ScoreWindowHeight, ScoreWindowWidth, ScoreWindowCornerY, ScoreWindowCornerX);
    //setting boxes' lines
    box(GameWindow, 0, 0);
    box(ScoreWindow, 0, 0);
    //refreshing children-windows
    wrefresh(GameWindow);
    wrefresh(ScoreWindow);
}

void Game::GameInit()
{
    srand(time(NULL));
    //GAME INITIALIZATION
    IsGameActive = true;
    WasButtonClicked = false;
    MustBeRedrawn = false;
    MaxNumberOfLetters = 10;
    LetterFallingSpeed = 1200;
    LetterGenerationSpeed = 3200;
    Score = 0;
    mvwprintw(ScoreWindow, 1, 1, "Score %d", Score);
    wrefresh(ScoreWindow);
}

void Game::TypingMasterWelcome()
{
    wattron(GameWindow, A_BOLD);
    mvwprintw(GameWindow, GameWindowHeight / 2 - 2, GameWindowWidth / 2 - 12, "THE TYPING MASTER GAME.");
    wattron(GameWindow, A_BLINK);
    mvwprintw(GameWindow, GameWindowHeight / 2 - 1, GameWindowWidth / 2 - 10, "Tap ENTER to start.");
    wrefresh(GameWindow);
    wattroff(GameWindow, A_BOLD);
    wattroff(GameWindow, A_BLINK);
    wgetch(GameWindow);
    mvwprintw(GameWindow, GameWindowHeight / 2 - 2, GameWindowWidth / 2 - 12, "                          ");
    mvwprintw(GameWindow, GameWindowHeight / 2 - 1, GameWindowWidth / 2 - 12, "                          ");
    wrefresh(GameWindow);
}

void Game::TypingMasterGoodbye()
{
    GoodbyeWindow = newwin(ScoreWindowHeight + 3, ScoreWindowWidth - 2, MainWindowHeight / 2 - 6, ScoreWindowCornerX + 1);
    wborder(GoodbyeWindow, '#', '#', '#', '#', '#', '#', '#', '#');
    wattron(GoodbyeWindow, A_BOLD);
    mvwprintw(GoodbyeWindow, 2, (ScoreWindowWidth - 2) / 2 - 5, "GAME OVER");
    wattron(GoodbyeWindow, A_BLINK);
    mvwprintw(GoodbyeWindow, 3, (ScoreWindowWidth - 2) / 2 - 13, "Double tap ENTER to exit.");
    wrefresh(GoodbyeWindow);
    wattroff(GoodbyeWindow, A_BOLD);
    wattroff(GoodbyeWindow, A_BLINK);
    wgetch(GoodbyeWindow);
}

void Game::GenerateLetters()
{
    while (IsGameActive)
    {
        if (Letters.size() < MaxNumberOfLetters)
        {
            char letter = (char)(rand() % 26 + 97);
            int posX = rand() % (GameWindowWidth - 2) + 1;
            unique_lock<mutex> Locked(MutexForLetters);
            Letters.push_back(Letter(letter, posX, 0));
            MustBeRedrawn = true;
            Locked.unlock();
            MustRedraw.notify_one();
        }
        this_thread::sleep_for(chrono::milliseconds(LetterGenerationSpeed));
    }
}

void Game::RedrawTheScreen()
{
    while (IsGameActive)
    {
        unique_lock<mutex> Locked(MutexForLetters);
        MustRedraw.wait(Locked, [this]() { return this->IsRedrawNeeded(); });
        for (auto &L : Letters)
        {
            mvwprintw(GameWindow, L.PosY - 1, L.PosX, " ");
            box(GameWindow, 0, 0);
            mvwaddch(GameWindow, L.PosY, L.PosX, L.letter);
            wrefresh(GameWindow);
        }
        MustBeRedrawn = false;
    }
}

void Game::UpdatePosition()
{
    while (IsGameActive)
    {
        unique_lock<mutex> Locked(MutexForLetters);
        for (auto &L : Letters)
        {
            if (++L.PosY >= GameWindowHeight - 1)
            {
                IsGameActive = false;
            };
        }
        MustBeRedrawn = true;
        Locked.unlock();
        MustRedraw.notify_one();
        this_thread::sleep_for(chrono::milliseconds(LetterFallingSpeed));
    }
}

void Game::GetClickedButton()
{
    while (IsGameActive)
    {
        unique_lock<mutex> LockedButton(MutexForClickedButton);
        ClickedButton = (char)getch();
        WasButtonClicked = true;
        LockedButton.unlock();
        ButtonWasClicked.notify_one();
        //prevents calling the function before CheckClickedButton() will execute
        unique_lock<mutex> LockedNextChar(MutexForNextChar);
        NextChar.wait(LockedNextChar, [this]() { return !this->HaveButtonBeenClicked(); });
    }
}

void Game::CheckClickedButton()
{
    while (IsGameActive)
    {

        unique_lock<mutex> LockedButton(MutexForClickedButton);
        ButtonWasClicked.wait(LockedButton, [this]() { return this->HaveButtonBeenClicked(); });
        unique_lock<mutex> LockedLetters(MutexForLetters);
        auto FoundL = find_if(Letters.begin(), Letters.end(), [this](Letter L) { return this->GetCharClickedButton() == L.letter; });
        if (FoundL != Letters.end())
        {
            mvwprintw(GameWindow, FoundL.base()->PosY, FoundL.base()->PosX, " ");
            wrefresh(GameWindow);
            Letters.erase(FoundL);
            Score++;
        }
        LockedLetters.unlock();
        WasButtonClicked = false;
        LockedButton.unlock();
        NextChar.notify_one();
        mvwprintw(ScoreWindow, 1, 1, "Score %d", Score);
        wrefresh(ScoreWindow);
        if (Score % 4 == 0 && LetterFallingSpeed > 200)
        {
            LetterFallingSpeed -= 100;
            LetterGenerationSpeed -= 270;
        }
    }
}

void Game::PlayGame()
{
    TypingMasterWelcome();
    //here each thread is being created and started with reference to private class method with this as parameters
    thread t1(&Game::RedrawTheScreen, this);
    thread t2(&Game::UpdatePosition, this);
    thread t3(&Game::GenerateLetters, this);
    thread t4(&Game::GetClickedButton, this);
    thread t5(&Game::CheckClickedButton, this);
    t4.detach();
    t5.detach();
    t2.join();
    t3.join();
    t1.join();
    //t4.join();
    //t5.join();
}

bool Game::IsRedrawNeeded()
{
    return MustBeRedrawn;
}

bool Game::HaveButtonBeenClicked()
{
    return WasButtonClicked;
}

char Game::GetCharClickedButton()
{
    return ClickedButton;
}

Game::~Game()
{
    //here all threads are joined
    TypingMasterGoodbye();
    endwin();
}