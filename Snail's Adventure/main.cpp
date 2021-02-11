#include<bits/stdc++.h>

#include <iostream>
#include <stack>
#include <vector>
#include <random>

using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define m 17
#define n 38

char **maze;

int alU = 1, alD = 1, alL = 1, alR = 1, alU1 = 1, alD1 = 1, alL1 = 1, alR1 = 1;
int curr[2] = {33, 1}, curc[2] = {75, 1};
int points[2];
int M, N;
int state;                // 1 -> main menu
                          // 2 -> game
                          // 3 -> instructions
                          // 4 -> leader board


bool bPress[4];
int curp;

class Game {
    public:
                                Game();
        void                    run();

    private:
        void                    mazegnt();
        void                    processEvents();
        void                    menuEvents();
        void                    insEvents();
        void                    ldbEvents();
        void                    handleMenu();
        void                    handleGame();
        void                    handleIns();
        void                    startMusic();
        void                    handleLeaderBoard();
        vector <int>            readLeaderboard();
        void                    handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        void                    update(sf::Time elpasedTime);
        void                    valid();
        void                    render();
        void                    renderMenu();
        void                    updateStatistics(sf::Time elapsedTime);
        void                    cordgnt();
        void                    portalAct(int id);

    private:
        static float      PlayerSpeed;
        static const sf::Time   TimePerFrame;

        sf::RenderWindow        mWindow;
        sf::RenderWindow        mWindow1;
        sf::Texture             mTexture;
        sf::Texture             mTexture1;
        sf::Texture             brdTexture;
        sf::Texture             brd1Texture;
        sf::Texture             cbrdTexture;
        sf::Texture             plsTexture;
        sf::Texture             quesTexture;
        sf::Texture             arrowT;
        sf::Texture             inst;
        sf::Texture             ldbt;
        sf::Text                play;
        sf::Text                instructions;
        sf::Text                leaderboard;
        sf::Text                quit;
        sf::Texture             mbt;
        sf::Texture             wall;
        sf::Texture             road;
        sf::Texture             menut;
        sf::Texture             mnsTexture;
        sf::Texture             portalTexture;
        sf::Texture             flowerTexture;
        sf::Sprite              block;
        sf::Sprite              arrow;
        sf::Sprite              ldb;
        //sf::Sprite              mPlayer;
        //sf::Sprite              mPlayer1;
        sf::Sprite              ins;
        sf::Sprite              mBack;
        sf::Sprite              menu;
        sf::Sprite              path;
        sf::Sprite              pls;
        sf::Sprite              mns;
        sf::Sprite              ques;
        sf::Sprite              portal;
        sf::Sprite              flower;
        sf::Sprite              brd;
        sf::Sprite              brd1;
        sf::Sprite              cbrd;
        sf::Font                mFont;
        sf::Text                playerScore;
        sf::Text                playerScore1;
        sf::Text                mStatisticsText;
        sf::Text                rankk;
        sf::Text                score;
        sf::Time                mStatisticsUpdateTime;
        sf::Clock               clock;
        sf::SoundBuffer         ptlm;
        sf::SoundBuffer         chng;
        sf::SoundBuffer         ori;

        std::size_t             mStatisticsNumFrames;
        bool                    mIsMovingUp;
        bool                    mIsMovingDown;
        bool                    mIsMovingRight;
        bool                    mIsMovingLeft;
        bool                    mIsMovingUp1;
        bool                    mIsMovingDown1;
        bool                    mIsMovingRight1;
        bool                    mIsMovingLeft1;
};

float Game::PlayerSpeed = 25.f;
const sf::Time Game::TimePerFrame = sf::seconds(6.5f / 60.f);

int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};
int pt[] = {30, 40, 50, 70};
int ii[] = {1, 2, 3, 4, 5, 6};
int ctdn = 30;


sf::Sound sound, sound1;
vector < pair <int, int> > items(9);
map < pair <int, int>, bool> taken;
vector< sf::Sprite > v(9);
vector< sf::Sprite > mPlayer(2);
vector< sf::Text > ranks(10);
vector< sf::Text > pos(10);

vector< sf::SoundBuffer > musicPls(5);
vector< sf::SoundBuffer > musicMns(4);
vector< sf::SoundBuffer > remind(4);
bool eaten[2];
sf::Clock timer;
//sf::Vector2f q = sf::Vector2f(50.f, 240.f);

Game::Game()
: mWindow(sf::VideoMode(1920, 1080), "Snail's Adventure", sf::Style::Close)
, mTexture()
, mTexture1()
, plsTexture()
, mnsTexture()
, quesTexture()
, portalTexture()
, flowerTexture()
, brdTexture()
, brd1Texture()
, cbrdTexture()
, play()
, instructions()
, leaderboard()
, quit()
, mbt()
, chng()
//, mPlayer()
//, mPlayer1()
, ptlm()
, mBack()
, mFont()
, mStatisticsText()
, playerScore()
, playerScore1()
, mStatisticsUpdateTime()
, path()
, wall()
, road()
, block()
, brd()
, brd1()
, cbrd()
, pls()
, mns()
, ques()
, portal()
, flower()
, clock()
, menu()
, menut()
, arrowT()
, arrow()
, ori()
, ldb()
, ldbt()
//, music()
, mStatisticsNumFrames(0)
, mIsMovingUp(false)
, mIsMovingDown(false)
, mIsMovingRight(false)
, mIsMovingLeft(false)
, mIsMovingDown1(false)
, mIsMovingLeft1(false)
, mIsMovingRight1(false)
, mIsMovingUp1(false)
{

    if(!road.loadFromFile("media/textures/go.png"))
    {
        printf("Error loading soil");
        exit(0);
    }

    block.setTexture(road);

    if(!arrowT.loadFromFile("media/textures/arrow2.png"))
    {
        printf("Error loading arrow");
        exit(0);
    }

    arrow.setTexture(arrowT);

    if(!ldbt.loadFromFile("media/textures/ldb.jpg"))
    {
        printf("Error loading arrow");
        exit(0);
    }

    ldb.setTexture(ldbt);

    if(!inst.loadFromFile("media/textures/instructions.jpg"))
    {
        printf("Error loading instructions");
        exit(0);
    }

    ins.setTexture(inst);

    if (!ptlm.loadFromFile("media/sounds/portal.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }

    if (!chng.loadFromFile("media/sounds/chng.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }

    if (!ori.loadFromFile("media/sounds/ori.ogg"))
    {
        puts("Error loading music !");
        exit(0);
    }

    if (!musicPls[0].loadFromFile("media/sounds/30 points.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }
    if (!musicPls[1].loadFromFile("media/sounds/40 points.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }
    if (!musicPls[2].loadFromFile("media/sounds/50 points.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }
    if (!musicPls[3].loadFromFile("media/sounds/70 points.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }

     if (!musicPls[4].loadFromFile("media/sounds/100 points.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }

    if (!musicMns[0].loadFromFile("media/sounds/30 points lost.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }
    if (!musicMns[1].loadFromFile("media/sounds/40 points lost.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }
    if (!musicMns[2].loadFromFile("media/sounds/50 points lost.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }
    if (!musicMns[3].loadFromFile("media/sounds/70 points lost.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }

    if (!remind[0].loadFromFile("media/sounds/30 seconds.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }

    if (!remind[1].loadFromFile("media/sounds/10 seconds.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }

    if (!remind[2].loadFromFile("media/sounds/vic2.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }

    if (!remind[3].loadFromFile("media/sounds/vic1.wav"))
    {
        puts("Error loading music !");
        exit(0);
    }
    //musicMns[0].play();
    //music.setLoop(true);
    if(!wall.loadFromFile("media/textures/soil.png"))
    {
        printf("Error loading walls!");
        exit(0);
    }

    path.setTexture(wall);

    if(!mbt.loadFromFile("media/textures/snail.png"))
    {
        printf("Error loading background!");
        exit(0);
    }

    mbt.setRepeated(true);
    mBack.setTexture(mbt);
    mBack.setTextureRect({ 0, 120, 1920, 1080 });

    if(!menut.loadFromFile("media/textures/menu.png"))
    {
        printf("Error loading background!");
        exit(0);
    }
    menu.setTexture(menut);

    if(!mTexture.loadFromFile("media/textures/Eagle.png"))
    {
        printf("Error loading player0 !");
        exit(0);
    }

    if(!mTexture1.loadFromFile("media/textures/Eagle1.png"))
    {
        printf("Error loading player1 !");
        exit(0);
    }

    if(!plsTexture.loadFromFile("media/textures/plus.png"))
    {
        printf("Error loading plus !");
        exit(0);
    }
    pls.setTexture(plsTexture);

    if(!mnsTexture.loadFromFile("media/textures/minus.png"))
    {
        printf("Error loading minus !");
        exit(0);
    }
    mns.setTexture(mnsTexture);

    if(!quesTexture.loadFromFile("media/textures/ques.png"))
    {
        printf("Error loading ques !");
        exit(0);
    }
    ques.setTexture(quesTexture);

    if(!portalTexture.loadFromFile("media/textures/portal.png"))
    {
        printf("Error loading portal !");
        exit(0);
    }
    portal.setTexture(portalTexture);

    if(!flowerTexture.loadFromFile("media/textures/flower.png"))
    {
        printf("Error loading flower !");
        exit(0);
    }
    flower.setTexture(flowerTexture);

    if(!brdTexture.loadFromFile("media/textures/board6.png"))
    {
        printf("Error loading board0 !");
        exit(0);
    }
    brd.setTexture(brdTexture);

    if(!brd1Texture.loadFromFile("media/textures/board3.png"))
    {
        printf("Error loading board1 !");
        exit(0);
    }
    brd1.setTexture(brd1Texture);

    if(!cbrdTexture.loadFromFile("media/textures/cbrd.png"))
    {
        printf("Error loading clock-board !");
        exit(0);
    }
    cbrd.setTexture(cbrdTexture);

    mPlayer[0].setTexture(mTexture1);
    mPlayer[1].setTexture(mTexture);

    if (!mFont.loadFromFile("media/fonts/lsb.ttf"))
    {
        printf("Error loading fonts!");
        exit(0);
    }
    mStatisticsText.setFont(mFont);
    playerScore.setFont(mFont);
    playerScore1.setFont(mFont);
    playerScore.setFillColor(sf::Color::Black);
    playerScore1.setFillColor(sf::Color::Black);
    //playerScore.setStyle(sf::Text::Bold);
    //playerScore1.setStyle(sf::Text::Bold);
    playerScore.setCharacterSize(30);
    playerScore1.setCharacterSize(30);
    //mStatisticsText.setFillColor(0, 0, 0);
    mStatisticsText.setFillColor(sf::Color::Black);
    //mStatisticsText.setStyle(sf::Text::Bold);
    mStatisticsText.setCharacterSize(25);

}

void Game::startMusic() {
    sound1.setBuffer(ori);
    sound1.setVolume(30.f);
    sound1.setLoop(true);
    sound1.play();
}

void Game::handleMenu() {
    for(int i = 0; i < 3; ++i) bPress[i] = 0;
    bPress[0] = 1;
    curp = 0;
    renderMenu();
}

void Game::handleGame() {
    sound1.stop();
    mazegnt();
    alU = 1, alD = 1, alL = 1, alR = 1, alU1 = 1, alD1 = 1, alL1 = 1, alR1 = 1;
    curr[0] = 33, curr[1] = 1, curc[0] = 75, curc[1] = 1;
    eaten[0] = eaten[1] = 0;
    taken.clear();
    //curr[2] = {33, 1}, curc[2] = {75, 1};
    Game::PlayerSpeed = 25.f;
    points[0] = points[1] = 0;
    brd.setPosition(130.f, 10.f);
    brd1.setPosition(1600.f, 15.f);
    cbrd.setPosition(870.f, 5.f);
    mPlayer[1].setPosition(25.f, 190.f);
    mPlayer[0].setPosition(1875.f, 990.f);
    playerScore.setPosition(175.f, 60.f);
    playerScore1.setPosition(1635.f, 85.f);
    mStatisticsText.setPosition(930.f, 60.f);
    cordgnt();
    timer.restart();
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    int timer = clock.getElapsedTime().asSeconds();
    while (mWindow.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);
        }
        updateStatistics(elapsedTime);
        render();
    }
}

void Game::handleIns() {
    while (mWindow.isOpen()) {
        insEvents();
        mWindow.clear();
        ins.setPosition(0.f, 0.f);
        mWindow.draw(ins);
        mWindow.display();
    }
}

void Game::handleLeaderBoard() {
    while(mWindow.isOpen()) {
        ldbEvents();
        mWindow.clear();
        ldb.setPosition(0.f, 0.f);
        mWindow.draw(ldb);
        rankk.setString("POSITION");
        rankk.setPosition(250.f, 50.f);
        rankk.setFont(mFont);
        rankk.setCharacterSize(50);
        rankk.setColor(sf::Color::Blue);
        rankk.setStyle(sf::Text::Bold);
        mWindow.draw(rankk);
        score.setString("SCORE");
        score.setPosition(1400.f, 50.f);
        score.setFont(mFont);
        score.setCharacterSize(50);
        score.setColor(sf::Color::Blue);
        score.setStyle(sf::Text::Bold);
        mWindow.draw(score);
        vector <int> sc = readLeaderboard();
        float x0 = 300.f, y0 = 150.f;
        sf::Vector2f dp = sf::Vector2f(x0, y0);
        for (int i = 0; i < 10; ++i) {
            pos[i].setPosition(x0, y0);
            pos[i].setString(to_string(i + 1));
            pos[i].setFont(mFont);
            pos[i].setCharacterSize(40);
            pos[i].setColor(sf::Color::Black);
            pos[i].setStyle(sf::Text::Bold);
            ranks[i].setPosition(x0 + 1150.f, y0);
            ranks[i].setString(to_string(sc[i]));
            ranks[i].setFont(mFont);
            ranks[i].setCharacterSize(40);
            ranks[i].setColor(sf::Color::Black);
            ranks[i].setStyle(sf::Text::Bold);
            y0 += 75.f;
            dp = sf::Vector2f(x0, y0);
            mWindow.draw(pos[i]);
            mWindow.draw(ranks[i]);
        }
        mWindow.display();
    }
}

void Game::ldbEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
       if (event.type == sf::Event::Closed) {
            mWindow.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) handleMenu();
        }
    }
}

void Game::insEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
       if (event.type == sf::Event::Closed) {
            mWindow.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) handleMenu();
        }
    }
}

void Game::run() {
    //re:
    startMusic();
    if (state == 1) {
        handleMenu();
    } if (state == 2) {
        handleGame();
    } if (state == 3) {
        handleIns();
    } if (state == 4) {
        handleLeaderBoard();
    }
}

void Game::menuEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
       if (event.type == sf::Event::Closed) {
            mWindow.close();
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Up:
                {
                    sound.setBuffer(chng);
                    sound.setVolume(10.f);
                    sound.play();
                    if (curp == 0) {
                        bPress[0] = 1;
                    } else {
                        bPress[curp] = 0;
                        curp--;
                        bPress[curp] = 1;
                    }
                    break;
                }
            case sf::Keyboard::Down:
                {
                    sound.setBuffer(chng);
                    sound.setVolume(10.f);
                    sound.play();
                    if (curp == 3) {
                        bPress[3] = 1;
                    } else {
                        bPress[curp] = 0;
                        curp++;
                        bPress[curp] = 1;
                    }
                    break;
                }
            case sf::Keyboard::Enter:
                {
                    if (curp == 0) handleGame();
                    else if (curp == 1) handleIns();
                    else if (curp == 2) handleLeaderBoard();
                    else if (curp == 3) mWindow.close();
                    //goto re;
                }
            }
        }
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Up /*&& maze[curx][cury + 1] != '#'*/) {
        //cury++;
        mIsMovingUp = isPressed;
    } else if (key == sf::Keyboard::Down /*&& maze[curx][cury - 1] != '#'*/) {
        //cury--;
        mIsMovingDown = isPressed;
    } else if (key == sf::Keyboard::Left /*&& maze[curx - 1][cury] != '#'*/) {
        //curx--;
        mIsMovingLeft = isPressed;
    } else if (key == sf::Keyboard::Right /*&& maze[curx + 1][cury] != '#'*/) {
        //curx++;
        mIsMovingRight = isPressed;
    }

    if (key == sf::Keyboard::W /*&& maze[curr1 - 1][curc1] != '#'*/) {
        //curr1--;
        mIsMovingUp1 = isPressed;
    } else if (key == sf::Keyboard::S /*&& maze[curr1 + 1][curc1] != '#'*/) {
        //curr1++;
        mIsMovingDown1 = isPressed;
    } else if (key == sf::Keyboard::A /*&& maze[curr1][curc1 - 1] != '#'*/) {
        //curc1--;
        mIsMovingLeft1 = isPressed;
    } else if (key == sf::Keyboard::D /*&& maze[curr1][curc1 + 1] != '#'*/) {
        //curc1++;
        mIsMovingRight1 = isPressed;
    }
}

void Game::update(sf::Time deltaTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp) {
        //printf("Trying to go from (%d, %d) : %c to (%d, %d) : %c \n", curr1,curc1,maze[curr1][curc1],curr1 - 1,curc1,maze[curr1 - 1][curc1]);
        if(maze[curr[0] - 1][curc[0]] != '#') {
            curr[0]--;
            alU = 1;
        } else alU = 0;
        movement.y -= PlayerSpeed * alU;
    } if (mIsMovingDown) {
        //printf("Trying to go from (%d, %d) : %c to (%d, %d) : %c \n", curr1,curc1,maze[curr1][curc1],curr1 + 1,curc1,maze[curr1 + 1][curc1]);
        if(maze[curr[0] + 1][curc[0]] != '#') {
            curr[0]++;
            alD = 1;
        } else alD = 0;
        movement.y += PlayerSpeed * alD;
    } if (mIsMovingLeft) {
        //printf("Trying to go from (%d, %d) : %c to (%d, %d) : %c \n", curr1,curc1,maze[curr1][curc1],curr1,curc1 - 1,maze[curr1][curc1 - 1]);
        if(maze[curr[0]][curc[0] - 1] != '#') {
            curc[0]--;
            alL = 1;
        } else alL = 0;
        movement.x -= PlayerSpeed * alL;
    } if(mIsMovingRight) {
        //printf("Trying to go from (%d, %d) : %c to (%d, %d) : %c \n", curr1,curc1,maze[curr1][curc1],curr1,curc1 + 1,maze[curr1][curc1 + 1]);
        if(maze[curr[0]][curc[0] + 1] != '#') {
            curc[0]++;
            alR = 1;
            //mPlayer1.scale(-1.f,1.f);
        } else alR = 0;
        movement.x += PlayerSpeed * alR;
    }
    mPlayer[0].move(movement /** deltaTime.asSeconds()*/);


    sf::Vector2f movement1(0.f, 0.f);
    if (mIsMovingUp1) {
        //printf("Trying to go from (%d, %d) : %c to (%d, %d) : %c \n", curr1,curc1,maze[curr1][curc1],curr1 - 1,curc1,maze[curr1 - 1][curc1]);
        if(maze[curr[1] - 1][curc[1]] != '#') {
            curr[1]--;
            alU1 = 1;
        } else alU1 = 0;
        movement1.y -= PlayerSpeed * alU1;
    } if (mIsMovingDown1) {
        //printf("Trying to go from (%d, %d) : %c to (%d, %d) : %c \n", curr1,curc1,maze[curr1][curc1],curr1 + 1,curc1,maze[curr1 + 1][curc1]);
        if(maze[curr[1] + 1][curc[1]] != '#') {
            curr[1]++;
            alD1 = 1;
        } else alD1 = 0;
        movement1.y += PlayerSpeed * alD1;
    } if (mIsMovingLeft1) {
        //printf("Trying to go from (%d, %d) : %c to (%d, %d) : %c \n", curr1,curc1,maze[curr1][curc1],curr1,curc1 - 1,maze[curr1][curc1 - 1]);
        if(maze[curr[1]][curc[1] - 1] != '#') {
            curc[1]--;
            alL1 = 1;
        } else alL1 = 0;
        movement1.x -= PlayerSpeed * alL1;
    } if(mIsMovingRight1) {
        //printf("Trying to go from (%d, %d) : %c to (%d, %d) : %c \n", curr1,curc1,maze[curr1][curc1],curr1,curc1 + 1,maze[curr1][curc1 + 1]);
        if(maze[curr[1]][curc[1] + 1] != '#') {
            curc[1]++;
            alR1 = 1;
            //mPlayer1.scale(-1.f,1.f);
        } else alR1 = 0;
        movement1.x += PlayerSpeed * alR1;
    }
    mPlayer[1].move(movement1 /** deltaTime.asSeconds()*/);
}

void updateLeaderBoard(int a, int b) {
    FILE *fp;
    if ((fp = fopen("Leaderboard.txt", "a")) == NULL) {
        cout << "Could not open leaderboard !";
        exit(0);
    }
    fprintf(fp, "%d\n", a);
    fprintf(fp, "%d\n", b);
    fclose(fp);
}

vector <int> Game::readLeaderboard() {
    vector <int> sc;
    FILE *fp;
    if ((fp = fopen("Leaderboard.txt", "r")) == NULL) {
        cout << "Error reading the leaderboard";
        exit(0);
    }
    int a;
    while (fscanf(fp, "%d", &a) > 0) {
        sc.emplace_back(a);
    }
    fclose(fp);
    sort(sc.rbegin(), sc.rend());
    return sc;
}

sf::Vector2f getFloats(int r, int c) {
    float x = 25 * c + 0.f;
    float y = 25 * r + 165.f;
    return sf::Vector2f(x, y);
}

pair <int, int> newCords(int r, int c) {
    int rr, rc;
    //srand(time(0));
    rr = rand() % 34, rc = rand() % 75;
    for (int i = 0; i < 8; ++i) {
        rr += dx[i], rc += dy[i];
        if ((curr[0] == rr && curc[0] == rc) || (curr[1] == rr && curc[1] == rc) || rr < 0 || rc < 0 || rr >= M || rc >= N || maze[rr][rc] == '#' || taken[{rr, rc}]) continue;
        else {
            taken[{r, c}] = 0;
            taken[{rr, rc}] = 1;
            return make_pair(rr, rc);
        }
    }
}

void inc(int sn, int id) {
    int p = rand() % 4;
    points[id] += pt[p] * sn;
    if (sn == 1) sound.setBuffer(musicPls[p]);
    else sound.setBuffer(musicMns[p]);
    sound.play();
}

void Game::portalAct(int id) {

    sound.setBuffer(ptlm);
    sound.play();
    int rr, rc;
    //srand(time(0));
    rr = rand() % 34, rc = rand() % 75;
    for (int i = 0; i < 8; ++i) {
        rr += dx[i], rc += dy[i];
        if ((curr[id ^ 1] == rr && curc[id ^ 1] == rc) || rr < 0 || rc < 0 || rr >= M || rc >= N || maze[rr][rc] == '#' || taken[{rr, rc}]) continue;
        else {
            taken[{curr[id], curc[id]}] = 0;
            taken[{rr, rc}] = 1;
            curr[id] = rr, curc[id] = rc;
            break;
        }
    }
    mPlayer[id].setPosition(getFloats(curr[id], curc[id]));
}

void Game::renderMenu() {
    while (mWindow.isOpen()) {
        menuEvents();
        mWindow.clear();
        menu.setPosition(0.f, 0.f);
        mWindow.draw(menu);
        play.setString("PLAY");
        play.setPosition(775.f, 400.f);
        play.setFont(mFont);
        play.setCharacterSize(50);
        play.setStyle(sf::Text::Bold);
        instructions.setString("INSTRUCTIONS");
        instructions.setPosition(775.f, 475.f);
        instructions.setFont(mFont);
        instructions.setCharacterSize(50);
        instructions.setStyle(sf::Text::Bold);
        leaderboard.setString("LEADERBOARD");
        leaderboard.setPosition(775.f, 550.f);
        leaderboard.setFont(mFont);
        leaderboard.setCharacterSize(50);
        leaderboard.setStyle(sf::Text::Bold);
        quit.setString("EXIT");
        quit.setPosition(775.f, 625.f);
        quit.setFont(mFont);
        quit.setCharacterSize(50);
        quit.setStyle(sf::Text::Bold);
        if(bPress[0]) arrow.setPosition(680.f, 400.f);
        else if(bPress[1]) arrow.setPosition(680.f, 475.f);
        else if(bPress[2]) arrow.setPosition(680.f, 550.f);
        else if(bPress[3]) arrow.setPosition(680.f, 625.f);
        mWindow.draw(play);
        mWindow.draw(instructions);
        mWindow.draw(leaderboard);
        mWindow.draw(quit);
        mWindow.draw(arrow);
        mWindow.display();
    }
}

void Game::render() {
    sound1.stop();
    mWindow.clear();
    mBack.setPosition(0.f, 0.f);
    mWindow.draw(mBack);
    float x0 = 0.0f, y0 = 165.0f;
    int ct = 25;
    sf::Vector2f dp = sf::Vector2f(x0, y0);
    for (int i = 0; i < 2 * m + 1 ; ++i) {
        for (int j = 0; j < 2 * n + 1; ++j) {
            sf::Vector2f p = dp;
            path.setPosition(p);
            block.setPosition(p);
            if(maze[i][j] == '#') mWindow.draw(block);
            else mWindow.draw(path);
            dp.x += ct;
        }
        dp.x = x0;
        dp.y += ct;
    }
    mWindow.draw(brd);
    mWindow.draw(brd1);
    mWindow.draw(cbrd);

    for (int i = 0; i < 9; ++i) {
        int r = items[i].first, c = items[i].second;
        //v[i].setPosition(getFloats(r, c));
        int ni = i;
        if ((curr[0] == r && curc[0] == c)) {
            items[i] = newCords(r, c);
            ni = (ni == 7 || ni == 8) ? ii[rand() % 6] : ni;
            if (ni == 0 && !eaten[1]) {
                    eaten[0] = 1;
                    points[0] += 100;
                    sound.setBuffer(musicPls[4]);
                    sound.play();
            }
            if (ni == 1 || ni == 2) inc(1, 0);
            if (ni == 3 || ni == 4) inc(-1, 0);
            if (ni == 5 || ni == 6) portalAct(0);
            //cout << r << " " << c << "  Vs  " << items[i].first << " " << items[i].second << "\n";
        } else if ((curr[1] == r && curc[1] == c)) {
            items[i] = newCords(r, c);
            ni = (ni == 7 || ni == 8) ? ii[rand() % 6] : ni;
            if (ni == 0 && !eaten[0]) {
                    eaten[1] = 1;
                    points[1] += 100;
                    sound.setBuffer(musicPls[4]);
                    sound.play();
            }
            if (ni == 1 || ni == 2) inc(1, 1);
            if (ni == 3 || ni == 4) inc(-1, 1);
            if (ni == 5 || ni == 6) portalAct(1);
        }
        if(i == 0 && (eaten[0] || eaten[1])) continue;
        v[i].setPosition(getFloats(items[i].first, items[i].second));
        mWindow.draw(v[i]);
    }
    if (!eaten[0]) mWindow.draw(mPlayer[0]);
    if (!eaten[1]) mWindow.draw(mPlayer[1]);
    mWindow.draw(mStatisticsText);
    mWindow.draw(playerScore);
    mWindow.draw(playerScore1);
    mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime) {
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;

    if(mStatisticsUpdateTime >= sf::seconds(1.0f)) {
        playerScore.setString(
                                  "Player 1\n    " + to_string(points[1])
                                  //"Player 2 = " + std::to_string(points[1])
                                  );
        playerScore1.setString(
                                  "Player 2\n    " + to_string(points[0])
                                  //"Player 2 = " + std::to_string(points[1])
                                  );
        int t = timer.getElapsedTime().asSeconds();
        if (t == 30) {
            sound.setBuffer(remind[0]);
            sound.play();
        } else if (t == 50) {
            sound.setBuffer(remind[1]);
            sound.play();
        } else if (t == 60) {
            if(points[0] > points[1]) sound.setBuffer(remind[2]);
            else sound.setBuffer(remind[3]);
            sound.play();
            Game::PlayerSpeed = 0.f;
            updateLeaderBoard(points[0], points[1]);
        } else if (t == 63) {
            startMusic();
            handleMenu();
        }
        int sh = 60 - t;
        sh = max(sh, 0);
        mStatisticsText.setString(
                                  "Time\n  " + to_string(sh)
                                  //"Player 2 = " + std::to_string(points[1])
                                  );

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
    //sf::Clock clock;
    /*int timer = clock.getElapsedTime().asSeconds();

    if (timer > 0) {
        cout << timer << "\n";
        ctdn--;
        mStatisticsText.setString( "TIME : " + std::to_string(ctdn) );
        clock.restart();
    }*/
}

int getIdx(int x, int y, vector < pair<int, pair<int, int> > > cell_list) {
    for (int i = 0; i < cell_list.size(); i++)
    {
        if (cell_list[i].second.first == x && cell_list[i].second.second == y)
            return cell_list[i].first;
    }
    cout << "getIdx() couldn't find the index!" << endl;
    return -1;
}

void createMaze(int M, int N) {

    vector < pair<int, pair<int, int> > > cell_list;
    vector <bool> visited(m*n, false);
    stack<pair<int, pair<int, int> > > m_stack;
    random_device rdev;
    mt19937 rng(rdev());
    uniform_int_distribution<mt19937::result_type> dist100(1, 100);

    int nVisited = 0;
    int k = 0;

    for (int i = 1; i < M; i+=2) {
        for (int j = 1; j < N; j+=2) {
            cell_list.push_back(make_pair(k, make_pair(i, j)));
            k++;
        }
    }

    //int randIdx = dist100(rng) % m*n;
    int randIdx = rand() % m*n;
    m_stack.push(cell_list[randIdx]);
    visited[randIdx] = true;
    nVisited++;

    // Algo
    while(nVisited < m*n) {

        vector <int> neighbours;
        // North
        if (m_stack.top().second.first > 1) {
            if (maze[m_stack.top().second.first - 2][m_stack.top().second.second + 0] &&
                !visited[getIdx(m_stack.top().second.first - 2, m_stack.top().second.second + 0, cell_list)]) {
                neighbours.push_back(0);
            }
        }
        // East
        if (m_stack.top().second.second < N - 2) {
            if (maze[m_stack.top().second.first + 0][m_stack.top().second.second + 2] &&
                !visited[getIdx(m_stack.top().second.first + 0, m_stack.top().second.second + 2, cell_list)]) {
                neighbours.push_back(1);
            }
        }
        // South
        if (m_stack.top().second.first < M - 2) {
            if (maze[m_stack.top().second.first + 2][m_stack.top().second.second + 0] &&
                !visited[getIdx(m_stack.top().second.first + 2, m_stack.top().second.second + 0, cell_list)]) {
                neighbours.push_back(2);
            }
        }
        // West
        if (m_stack.top().second.second > 1) {
            if (maze[m_stack.top().second.first + 0][m_stack.top().second.second - 2] &&
                !visited[getIdx(m_stack.top().second.first + 0, m_stack.top().second.second - 2, cell_list)]) {
                neighbours.push_back(3);
            }
        }
        // Neighbours available?
        if (!neighbours.empty()) {
            // Choose a random direction
            int next_cell_dir = neighbours[dist100(rng) % neighbours.size()];
            // Create a path between this cell and neighbour
            switch (next_cell_dir) {
                case 0: // North
                    maze[m_stack.top().second.first - 1][m_stack.top().second.second + 0] = '*';
                    m_stack.push(cell_list[getIdx(m_stack.top().second.first - 2, m_stack.top().second.second + 0, cell_list)]);
                    break;
                case 1: // East
                    maze[m_stack.top().second.first + 0][m_stack.top().second.second + 1] = '*';
                    m_stack.push(cell_list[getIdx(m_stack.top().second.first + 0, m_stack.top().second.second + 2, cell_list)]);
                    break;
                case 2: // South
                    maze[m_stack.top().second.first + 1][m_stack.top().second.second + 0] = '*';
                    m_stack.push(cell_list[getIdx(m_stack.top().second.first + 2, m_stack.top().second.second + 0, cell_list)]);
                    break;
                case 3: // West
                    maze[m_stack.top().second.first + 0][m_stack.top().second.second - 1] = '*';
                    m_stack.push(cell_list[getIdx(m_stack.top().second.first + 0, m_stack.top().second.second - 2, cell_list)]);
                    break;
            }

            visited[m_stack.top().first] = true;
            nVisited++;
        }
        else {
            m_stack.pop();
        }
    }
}

void Game::mazegnt()
{
    M = 2*m+1;
    N = 2*n+1;

    maze = new char* [M];

    for (int i = 0; i < M; i++) {
        maze[i] = new char [N];
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (!(i&1)||!(j&1))
                maze[i][j] = '#';
            else
                maze[i][j] = '*';

        }
    }

    for (int i = 1; i < M; i+=2) {
        for (int j = 1; j < N; j+=2) {
            maze[i][j] = '*';
        }

    }
    createMaze(M, N);
    maze[0][1] = '#';
    maze[2*m][2*n-1] = '#';
}

void brute (int r, int c, int idx) {
    for (int i = 0; i < 8; ++i) {
        r += dx[i], c += dy[i];
        if (maze[r][c] != '#' && !taken[{r, c}]) {
            taken[{r, c}] = 1;
            break;
        }
    }
    items[idx] = make_pair(r, c);
}

void Game::cordgnt() {
    brute(16, 37, 0);
    brute(25, 7, 1);
    brute(8, 67, 2);
    brute(20, 21, 3);
    brute(13, 53, 4);
    brute(4, 23, 5);
    brute(29, 51, 6);
    brute(2, 18, 7);
    brute(31, 56, 8);
    v[0] = flower;
    v[1] = v[2] = pls;
    v[3] = v[4] = mns;
    v[5] = v[6] = portal;
    v[7] = v[8] = ques;
}

int main(){
    srand(time(0));
    //mazegnt();
    state = 1;
    Game game;
    //game.startMusic();
    game.run();
}
