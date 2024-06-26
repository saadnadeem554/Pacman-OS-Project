#include <iostream>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <unistd.h>
#include <queue>
#include <stack>
#include <vector>
#include <climits>
#include <semaphore.h>
#include <list>
using namespace std;
using namespace sf;
// Define game board size
#define ROWS 30
#define COLS 30
#define CELL_SIZE 32 // Size of each cell in pixels
sf::Music musicEat;
sf::Music musicmenu;
sf ::Music musicMunch;
sf ::Music musicReset;
// skeleton game map
int gameMapSkeleton[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, -1, -1, -1, -1, 0, 0, -1, -1, -1, -1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
// game map
int gameMap[ROWS][COLS] = {0};
// pacman x y cordinates
int pacman_x = CELL_SIZE + 25 / 8;
int pacman_y = CELL_SIZE + 25 / 4;
int powerupcount = 4;
sf::Clock powercountclock;
sf::Clock powerupClock;
int totalScorePallet;
int Score = 0;
bool powerupActive = false;
int life = 3;
bool start = false;
bool reset = false;
bool gamewon = 0;
// shared memory of user direcion
struct shared
{
    int pacman_direction = 0;
} sharedmem;
int closwindow = 0;

// Ghst structure
struct GhostData
{
    int x;
    int y;
    int ghostID;
    int direction = 2;
    int speed = 0;
    // add a clock to keep track of time of speed
    sf::Clock speedClock;
    bool hasKey = 0;
    bool hasPermit = 0;
    bool isActivated = 0;
    int pr = 0; // ghost priority
};

// Mutex to protect user input
pthread_mutex_t SharedmemMutex = PTHREAD_MUTEX_INITIALIZER;

// Mutex on gameBoard
pthread_mutex_t GameBoardMutex = PTHREAD_MUTEX_INITIALIZER;

// Mutex on pacman x y position
pthread_mutex_t PacmanPosMutex = PTHREAD_MUTEX_INITIALIZER;

// semaphores for key and permit
sem_t keySemaphore;
sem_t permitSemaphore;

// Semaphore for speed boost
sem_t speedBoostSemaphore;
// Declare list of pointers to GhostData
std::list<GhostData *> ghostlist;
std::list<GhostData *> activespeedboost;
// add a mutex to protect the ghost list
pthread_mutex_t ghostlistMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t speedboostlistMutex = PTHREAD_MUTEX_INITIALIZER;

// function that puts score pallets in gamegrid
void intitializeGrid()
{
    totalScorePallet = 0;
    Score = 0;
    // clear game map
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            gameMap[i][j] = 0;
        }
    }
    // in the gameMapSkeleton wherever there is a 0 put a score pallet there
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (gameMapSkeleton[i][j] == 0)
            {
                gameMap[i][j] = 2;
                totalScorePallet++;
            }
            else
                gameMap[i][j] = gameMapSkeleton[i][j];
        }
    }
}
// Function to draw the grid with appropriate shapes for pellets, power-ups, and walls
void drawGrid(sf::RenderWindow &window)
{
    sf::CircleShape pelletShape(5);
    sf::CircleShape powerUpShape(5);
    // sf::CircleShape p()
    sf::Texture palletTexture;
    palletTexture.loadFromFile("cherry.png");
    sf::Sprite palletSprite(palletTexture);
    palletSprite.setScale(0.6, 0.6);

    sf::RectangleShape wallShape(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1)); // wall thickness = 1
    sf::Color darkBlue(100, 20, 154);
    sf::Text scoreText;
    sf::Font font;
    sf::Text lifetext;
    font.loadFromFile("SIXTY.TTF");
    scoreText.setFont(font);
    lifetext.setFont(font);
    scoreText.setCharacterSize(24);
    lifetext.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    lifetext.setFillColor(sf::Color::White);
    scoreText.setPosition(CELL_SIZE * 10, CELL_SIZE * 30);
    lifetext.setPosition(CELL_SIZE * 20, CELL_SIZE * 30);
    scoreText.setString("Score: " + std::to_string(Score));
    lifetext.setString("Lives: " + std::to_string(life));
    window.draw(scoreText);
    window.draw(lifetext);

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            // Draw pellets, power-ups, and walls
            // lock shared gameBoard mutrx
            pthread_mutex_lock(&GameBoardMutex);
            switch (gameMap[i][j])
            {
            case 2:
                // Draw small white circle for pellet
                pelletShape.setFillColor(sf::Color::White);
                pelletShape.setPosition(j * CELL_SIZE + CELL_SIZE / 2 - 5, i * CELL_SIZE + CELL_SIZE / 2 - 5);
                window.draw(pelletShape);
                break;

            case 1:
                // Draw blue rectangle for wall
                // Set fill color of wallShape to dark blue
                wallShape.setFillColor(darkBlue);
                wallShape.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                window.draw(wallShape);
                break;
            case -1:
                // Draw magenta ghost house
                wallShape.setFillColor(sf::Color::Magenta);
                wallShape.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                window.draw(wallShape);
                break;
            case 4:
                palletSprite.setPosition(j * CELL_SIZE + CELL_SIZE / 2 - 5, i * CELL_SIZE + CELL_SIZE / 2 - 5);
                window.draw(palletSprite);
                break;
            }
            // unlock mutex
            pthread_mutex_unlock(&GameBoardMutex);
        }
    }
}

// function to check if pacman wins
void checkwin(int gamemap[ROWS][COLS], RenderWindow &window)
{
    int count = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (gamemap[i][j] == 2)
            {
                count++;
            }
        }
    }
    if (count == 0)
    {
        // draw a sfml text on the middle of screen
        cout << "YOU WIN" << endl;
        cout << "SCORE: " << Score << endl;
        cout << "LIVES: " << life << endl;
        closwindow = 1;
        gamewon = true;
        // terminate all threads
    }
    if(life < 0 ){
        closwindow = 1 ;
        cout<<"lives ended";
    }
}
void grantspeedboost()
{
    // Try to acquire the speed boost semaphore
    if (sem_trywait(&speedBoostSemaphore) == 0)
    {
           //for(int i = 0; i < 2; i++)
           //{
                if(!ghostlist.empty())
                {
                    // Get a pointer to the first ghost in the list
                    pthread_mutex_lock(&ghostlistMutex);
                    GhostData *ghost = ghostlist.front();
                    // Set the speed of the ghost to 1
                    ghost->speed = 1;
                    ghost->speedClock.restart();
                    // Print the message
                    cout << "Speed boost granted to ghost " << ghost->ghostID << endl;
                    ghostlist.pop_front();

                    
                    // add them to the active speed boost list
                    pthread_mutex_lock(&speedboostlistMutex);
                    activespeedboost.push_back(ghost);
                    pthread_mutex_unlock(&speedboostlistMutex);

                    // Release the mutex
                    pthread_mutex_unlock(&ghostlistMutex);
                }
           //}
    }
}


// function that updates speed boost and the linked list
void updatespeedboost()
{
    // Check if active ghost list is not empty
        pthread_mutex_lock(&speedboostlistMutex);
        //for(int i = 0; i < 2; i++)
        //{
        if (!activespeedboost.empty())
        {
            // Get a pointer to the first ghost in the list
            GhostData *ghost = activespeedboost.front();
            // Check if speed boost is active and time limit exceeded
            if (ghost->speed && ghost->speedClock.getElapsedTime().asSeconds() > 5)
            {
                // Remove the speed boost
                ghost->speed = 0;
                // Print the message
                cout << "Speed boost removed from ghost " << ghost->ghostID << endl;
                // Pop the first ghost from the list
                activespeedboost.pop_front();
                // If ghost priority is not high, push it to the back
                if (ghost->pr > 1)
                {
                    pthread_mutex_lock(&ghostlistMutex);
                    ghostlist.push_back(ghost);
                    pthread_mutex_unlock(&ghostlistMutex);
                }
                pthread_mutex_lock(&ghostlistMutex);
                cout << "List of ghosts: ";
                for (auto it = ghostlist.begin(); it != ghostlist.end(); ++it)
                {
                cout << (*it)->ghostID << " ";
                }
                cout << endl;
                pthread_mutex_unlock(&ghostlistMutex);
                //  Release the semaphore
                sem_post(&speedBoostSemaphore);
            }
        }
        pthread_mutex_unlock(&speedboostlistMutex);
    //}
}


/*

// function to give speed boost to ghost
void grantspeedboost()
{
    // Try to acquire the speed boost semaphore
    if (sem_trywait(&speedBoostSemaphore) == 0)
    {
            if(!ghostlist.empty())
            {
                // Get a pointer to the first ghost in the list
                pthread_mutex_lock(&ghostlistMutex);
                GhostData *ghost = ghostlist.front();
                // Set the speed of the ghost to 1
                ghost->speed = 1;
                ghost->speedClock.restart();
                // Print the message
                cout << "Speed boost granted to ghost " << ghost->ghostID << endl;
                // get the 2nd ghost
                ghostlist.pop_front();
                if(!ghostlist.empty())
                {
                    GhostData *temp = ghostlist.front();
                    // give the speed boost to the 2nd ghost
                    temp->speed = 1;
                    temp->speedClock.restart();
                    cout << "Speed boost granted to ghost " << temp->ghostID << endl;
                }
                // push the first ghost to the back to the list
                ghostlist.push_front(ghost);

                // Release the mutex
                pthread_mutex_unlock(&ghostlistMutex);
            }

    }
}

// function that updates speed boost and the linked list
void updatespeedboost()
{
    // Check if ghost list is not empty
    if (!ghostlist.empty())
    {
        pthread_mutex_lock(&ghostlistMutex);
        // Get a pointer to the first ghost in the list
        GhostData *ghost = ghostlist.front();
        // Check if speed boost is active and time limit exceeded
        if (ghost->speed && ghost->speedClock.getElapsedTime().asSeconds() > 5)
        {
            // Remove the speed boost
            ghost->speed = 0;
            // Print the message
             cout << "Speed boost removed from ghost " << ghost->ghostID << endl;
            // Pop the first ghost from the list
            ghostlist.pop_front();
            // If ghost priority is not high, push it to the back
            if (ghost->pr > 1)
            {
                ghostlist.push_back(ghost);
            }
             cout << "List of ghosts: ";
             for (auto it = ghostlist.begin(); it != ghostlist.end(); ++it)
             {
              cout << (*it)->ghostID << " ";
              }
             cout << endl;
            //  Release the semaphore
            sem_post(&speedBoostSemaphore);
        }
        pthread_mutex_unlock(&ghostlistMutex);
    }
}
*/
// function to check a valid position
bool valid(int x, int y)
{
    if (x < 0 || x >= 30 || y < 0 || y >= 30)
        return false;
    if (gameMap[y][x] == 1 || gameMap[y][x] == -1)
        return false;
    return true;
}

// function to leave the ghost house based on key and permit
void leaveGhostHouse(GhostData *ghost)
{
    // Attempt to acquire a key
    if (sem_trywait(&keySemaphore) == 0)
    {
        ghost->hasKey = true;
        //cout << "Ghost " << ghost->ghostID << " got a key." << endl;
        usleep(1000000);
        // if key acquired, attempt to get permit
        if (sem_trywait(&permitSemaphore) == 0)
        {
            ghost->hasPermit = true;
            //cout << "Ghost " << ghost->ghostID << " got an exit permit amd key." << endl;
            //cout << "Ghost " << ghost->ghostID << " left the ghost house." << endl;
            ghost->isActivated = true;
            usleep(1000000);
            // release the semaphores
            sem_post(&permitSemaphore);
            sem_post(&keySemaphore);
            return;
        }
        else
        {
            // if dont get permit leave key and exit
            //cout << "Ghost " << ghost->ghostID << " got a key. BUT NO EXIT" << endl;
            // release the key semaphore
            sem_post(&keySemaphore);
            return;
        }
    }

    // if didnt get key, Attempt to acquire an exit permit
    if (sem_trywait(&permitSemaphore) == 0)
    {
        ghost->hasPermit = true;
        //cout << "Ghost " << ghost->ghostID << " got an exit permit." << endl;
        usleep(1000000);

        // if got exit permit attempt to get key
        if (sem_trywait(&keySemaphore) == 0)
        {
            ghost->hasKey = true;
            //cout << "Ghost " << ghost->ghostID << " got a key amd exit." << endl;
            //cout << "Ghost " << ghost->ghostID << " left the ghost house." << endl;
            ghost->isActivated = true;
            usleep(1000000);
            // release the semaphores
            sem_post(&permitSemaphore);
            sem_post(&keySemaphore);
            return;
        }
        else
        {
            // if not, leave
            //cout << "Ghost " << ghost->ghostID << " got an exit permit. BUT NO KEY" << endl;
            // release the permit semaphore
            sem_post(&permitSemaphore);
            return;
        }
    }
}

// leave this function commented out might need it in demo

/*
void leaveGhostHousee(GhostData* ghost) {
    // Attempt to acquire a key
    sem_wait(&keySemaphore);
    ghost->hasKey = true;
    //cout << "Ghost " << ghost->ghostID << " got a key." << endl;
    sem_post(&keySemaphore);

    // Attempt to acquire an exit permit
    sem_wait(&permitSemaphore);
    ghost->hasPermit = true;
    //cout << "Ghost " << ghost->ghostID << " got an exit permit and key." << endl;
    sem_post(&permitSemaphore);

    // Ghost leaves the ghost house
    usleep(100000); // Simulate leaving the house
    //cout << "Ghost " << ghost->ghostID << " left the ghost house." << endl;
    ghost->isActivated = true;
    // Release resources
    ghost->hasKey = false;
    ghost->hasPermit = false;
}
*/

// function to find path for ghost
int findPath(pair<int, int> source, pair<int, int> dest)
{
    // perform bfs to find distance and return
    int distance[ROWS][COLS];
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            distance[i][j] = INT_MAX;
        }
    }
    distance[source.first][source.second] = 0;
    queue<pair<int, int>> q;
    q.push(source);
    while (!q.empty())
    {
        pair<int, int> current = q.front();
        q.pop();
        int x = current.first;
        int y = current.second;
        if (x == dest.first && y == dest.second)
        {
            return distance[x][y];
        }
        if (valid(x + 1, y) && distance[x + 1][y] == INT_MAX)
        {
            distance[x + 1][y] = distance[x][y] + 1;
            q.push(make_pair(x + 1, y));
        }
        if (valid(x - 1, y) && distance[x - 1][y] == INT_MAX)
        {
            distance[x - 1][y] = distance[x][y] + 1;
            q.push(make_pair(x - 1, y));
        }
        if (valid(x, y + 1) && distance[x][y + 1] == INT_MAX)
        {
            distance[x][y + 1] = distance[x][y] + 1;
            q.push(make_pair(x, y + 1));
        }
        if (valid(x, y - 1) && distance[x][y - 1] == INT_MAX)
        {
            distance[x][y - 1] = distance[x][y] + 1;
            q.push(make_pair(x, y - 1));
        }
    }
    return distance[dest.first][dest.second];
}
// function to find the next move for ghost
int findNextMove(pair<int, int> source, pair<int, int> dest)
{
    // call find path from all neighbors of source to dest
    // return the direction of the neighbor with minimum distance
    int minDistance = INT_MAX;
    int direction = -1;
    // Array to store the 4 possible directions
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        int x = source.first + dx[i];
        int y = source.second + dy[i];
        // Check if the neighbor is valid
        if (valid(x, y))
        {
            // Find the distance of the neighbor from the destination
            int d = findPath(make_pair(x, y), dest);
            // Update the minimum distance and direction
            if (d != -1 && d < minDistance)
            {
                minDistance = d;
                direction = i + 1;
            }
        }
    }
    return direction;
}
// Function to reset all positions when pacman collide with ghost
void resetGame(GhostData &ghost1, GhostData &ghost2, GhostData &ghost3, GhostData &ghost4)
{
    // Reset the game
    ghost1.x = 355;
    ghost1.y = 454;
    ghost1.speed = 0;
    ghost2.x = 387;
    ghost2.y = 454;
    ghost3.x = 451;
    ghost3.y = 454;
    ghost3.speed = 0;
    ghost4.x = 483;
    ghost4.y = 454;
    ghost4.speed = 0;
    ghost1.isActivated = 0;
    ghost2.isActivated = 0;
    ghost3.isActivated = 0;
    ghost4.isActivated = 0;
    ghost2.speed = 0;
    ghost1.speedClock.restart();
    ghost2.speedClock.restart();
    ghost3.speedClock.restart();
    ghost4.speedClock.restart();
    // Reset the pacman
    pthread_mutex_lock(&PacmanPosMutex);
    pacman_x = CELL_SIZE + 25 / 8;
    pacman_y = CELL_SIZE + 25 / 4;
    pthread_mutex_unlock(&PacmanPosMutex);
    pthread_mutex_lock(&SharedmemMutex);
    sharedmem.pacman_direction = 0;
    pthread_mutex_unlock(&SharedmemMutex);
    // Reset the powerup
    powerupActive = false;
    // Reset the speed boost
    sem_init(&speedBoostSemaphore, 0, 2);
    sem_init(&keySemaphore, 0, 2);
    sem_init(&permitSemaphore, 0, 2);
    // Reset the ghost list
    ghostlist.clear();
    ghostlist.push_back(&ghost2);
    ghostlist.push_back(&ghost3);
    // Reset the reset flag
    reset = false;
    cout << "GAME RESET";
    start = 1;
}

void *ghostController(void *arg)
{
    GhostData *ghost = (GhostData *)arg;
    while (true)
    {
        // Wait for all ghosts threads to be initialized
        while (!start)
            ;

        // attempt to leave the house
        while (ghost->isActivated == 0)
        {
            // usleep(3000000);
            leaveGhostHouse(ghost);
            if (ghost->isActivated == 0)
            {
                // Ghost is still in the ghost house sleep for 3 seconds
                cout << ghost->ghostID << "  is still in house" << endl
                     << endl;
                usleep(3000000);
            }
        }

        // higher priority ghost wants the boost, push to the front of the list
        if (ghost->pr == 1 && ghost->speed == 0 && ghost->speedClock.getElapsedTime().asSeconds() > 10)
        {
            ghost->speedClock.restart();
            // Push the ghost to front of ghostlist
            pthread_mutex_lock(&ghostlistMutex);
            ghostlist.push_front(ghost);
            cout << "Ghost " << ghost->ghostID << " pushed to front of list because high priority" << endl;
            pthread_mutex_unlock(&ghostlistMutex);
            updatespeedboost();
            // Grant the speed boost
            grantspeedboost();
        }
        else if (ghost->pr != 1 && ghost->speed == 0) // lower priority want the boost always
        {
            // Grant the speed boost
            grantspeedboost();
        }

        // Update the speed boost
        updatespeedboost();

        // collisions of pacman with ghost
        pthread_mutex_lock(&PacmanPosMutex);
        // powerup active
        if (powerupActive && (pacman_x / CELL_SIZE == ghost->x / CELL_SIZE && pacman_y / CELL_SIZE == ghost->y / CELL_SIZE))
        {
            // cout<<"Ghost caught pacman"<<endl;
            //  reset ghost position
            ghost->x = 451;
            ghost->y = 454;
            ghost->isActivated = 0;
        }
        else if (!powerupActive && (pacman_x / CELL_SIZE == ghost->x / CELL_SIZE && pacman_y / CELL_SIZE == ghost->y / CELL_SIZE))
        {
            // signal main to reset game.
            reset = 1;
            pthread_mutex_unlock(&PacmanPosMutex);
            continue;
        }
        pthread_mutex_unlock(&PacmanPosMutex);

        if ((ghost->ghostID == 2 || ghost->ghostID == 3) && !powerupActive)
        {
            // execute smart ghost movement

            // Find the next move for the ghost
            pthread_mutex_lock(&GameBoardMutex);
            pthread_mutex_lock(&PacmanPosMutex);
            int direction = findNextMove(make_pair(ghost->x / CELL_SIZE, ghost->y / CELL_SIZE), make_pair(pacman_x / CELL_SIZE, pacman_y / CELL_SIZE));
            pthread_mutex_unlock(&PacmanPosMutex);
            pthread_mutex_unlock(&GameBoardMutex);
            // Update the direction of the ghost
            ghost->direction = direction;
            // Move the ghost in the direction
            pthread_mutex_lock(&GameBoardMutex);
            if (direction == 4 && valid((ghost->x + CELL_SIZE) / CELL_SIZE, ghost->y / CELL_SIZE))
            {
                ghost->x += CELL_SIZE;
            }
            else if (direction == 3 && valid((ghost->x - CELL_SIZE) / CELL_SIZE, ghost->y / CELL_SIZE))
            {
                ghost->x -= CELL_SIZE;
            }
            else if (direction == 2 && valid(ghost->x / CELL_SIZE, (ghost->y + CELL_SIZE) / CELL_SIZE))
            {
                ghost->y += CELL_SIZE;
            }
            else if (direction == 1 && valid(ghost->x / CELL_SIZE, (ghost->y - CELL_SIZE) / CELL_SIZE))
            {
                ghost->y -= CELL_SIZE;
            }
            pthread_mutex_unlock(&GameBoardMutex);
            // Sleep for 0.5 seconds
            usleep(300000);
        }
        else
        {
            // execute dumb ghost movement

            int directionX = 0;
            int directionY = 0;

            bool chosen = false;
            pthread_mutex_lock(&GameBoardMutex);
            if (ghost->direction == 1 || ghost->direction == 2)
            { // Up or down
              // Randomly choose left or right
                if (valid((ghost->x + CELL_SIZE) / CELL_SIZE, ghost->y / CELL_SIZE) && rand() % 2 == 0)
                {
                    directionX = 1;
                    chosen = true;
                    ghost->direction = 4;
                }
                else if (valid((ghost->x - CELL_SIZE) / CELL_SIZE, ghost->y / CELL_SIZE) && rand() % 2 == 0)
                {

                    directionX = -1;
                    chosen = true;
                    ghost->direction = 3;
                }
            }
            else if (ghost->direction == 3 || ghost->direction == 4)
            {   // Left or right
                // Randomly choose up or down
                if (valid(ghost->x / CELL_SIZE, (ghost->y + CELL_SIZE) / CELL_SIZE) && rand() % 2 == 0)
                {
                    directionY = 1;
                    chosen = true;
                    ghost->direction = 2;
                }

                else if (valid(ghost->x / CELL_SIZE, (ghost->y - CELL_SIZE) / CELL_SIZE) && rand() % 2 == 0)
                {

                    directionY = -1;
                    chosen = true;
                    ghost->direction = 1;
                }
            }
            pthread_mutex_unlock(&GameBoardMutex);
            if (!chosen)
            {
                // Continue in current direction
                if (ghost->direction == 1)
                {
                    directionY = -1;
                }
                else if (ghost->direction == 2)
                {
                    directionY = 1;
                }
                else if (ghost->direction == 3)
                {
                    directionX = -1;
                }
                else
                {
                    directionX = 1;
                }
            }

            int nextX = ghost->x + directionX * CELL_SIZE;
            int nextY = ghost->y + directionY * CELL_SIZE;

            // Check for collisions with walls
            pthread_mutex_lock(&GameBoardMutex);
            if (valid(nextX / CELL_SIZE, nextY / CELL_SIZE))
            {
                ghost->x += directionX * CELL_SIZE;
                ghost->y += directionY * CELL_SIZE;
                // cout<<ghost->x/CELL_SIZE<<" "<< ghost->y/CELL_SIZE<<endl;
            }
            else
            {
                // move ghost in opposite direction
                // cout<<"walled";
                if (ghost->direction == 1 && valid(ghost->x / CELL_SIZE, (ghost->y + CELL_SIZE) / CELL_SIZE))
                {
                    ghost->direction = 2;
                    directionY = 1;
                    ghost->x += directionX * CELL_SIZE;
                    ghost->y += directionY * CELL_SIZE;
                }
                else if (ghost->direction == 2 && valid(ghost->x / CELL_SIZE, (ghost->y - CELL_SIZE) / CELL_SIZE))
                {
                    ghost->direction = 1;
                    directionY = -1;
                    ghost->x += directionX * CELL_SIZE;
                    ghost->y += directionY * CELL_SIZE;
                }
                else if (ghost->direction == 3 && valid((ghost->x + CELL_SIZE) / CELL_SIZE, ghost->y / CELL_SIZE))
                {
                    ghost->direction = 4;
                    directionX = 1;
                    ghost->x += directionX * CELL_SIZE;
                    ghost->y += directionY * CELL_SIZE;
                }
                else if (ghost->direction == 4 && valid((ghost->x - CELL_SIZE) / CELL_SIZE, ghost->y / CELL_SIZE))
                {
                    ghost->direction = 3;
                    directionX = -1;
                    ghost->x += directionX * CELL_SIZE;
                    ghost->y += directionY * CELL_SIZE;
                }
                // sleep(1);
                // cout<<ghost->x/CELL_SIZE<<" "<< ghost->y/CELL_SIZE<<endl;
            }
            pthread_mutex_unlock(&GameBoardMutex);
        }

        pthread_mutex_lock(&PacmanPosMutex);
        if (powerupActive && (pacman_x / CELL_SIZE == ghost->x / CELL_SIZE && pacman_y / CELL_SIZE == ghost->y / CELL_SIZE))
        {
            // cout<<"Ghost caught pacman"<<endl;
            //  reset ghost position
            ghost->x = 451;
            ghost->y = 454;
            ghost->isActivated = 0;
        }
        else if (!powerupActive && (pacman_x / CELL_SIZE == ghost->x / CELL_SIZE && pacman_y / CELL_SIZE == ghost->y / CELL_SIZE))
        {

            reset = true;
            pthread_mutex_unlock(&PacmanPosMutex);
            continue;
        }
        pthread_mutex_unlock(&PacmanPosMutex);

        // if close
        if (closwindow == 1)
        {
            pthread_exit(NULL);
        }
        // Sleep to control the speed of the ghost
        if (ghost->speed == 0)
            usleep(200000); // unbosted ghost speed
        else if (ghost->speed == 1 && ghost->ghostID == 2 || ghost->ghostID == 3)
        {
            usleep(150000); // smart ghost speed(not super fast otherwise it will be impossible to win)
        }
        else
            usleep(100000); // dumb ghost speed
    }
    pthread_exit(NULL);
}

// Function to handle user input (UI TREAD)
void *userInput(void *arg)
{
    sf::RenderWindow *window = (sf::RenderWindow *)arg;
    while (window->isOpen())
    {
        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
            {

                // signal main to close window
                closwindow = 1;
                pthread_exit(NULL);
            }
            else if (event.type == Event::KeyPressed)
            {
                // Lock mutex before accessing shared variable
                pthread_mutex_lock(&SharedmemMutex);
                pthread_mutex_lock(&PacmanPosMutex);
                if (event.key.code == Keyboard::Up && valid(pacman_x / CELL_SIZE, (pacman_y - CELL_SIZE) / CELL_SIZE))
                {
                    sharedmem.pacman_direction = 1;
                }
                else if (event.key.code == Keyboard::Down && valid(pacman_x / CELL_SIZE, (pacman_y + CELL_SIZE) / CELL_SIZE))
                {
                    sharedmem.pacman_direction = 2;
                }
                else if (event.key.code == Keyboard::Left && valid((pacman_x - CELL_SIZE) / CELL_SIZE, pacman_y / CELL_SIZE))
                {
                    sharedmem.pacman_direction = 3;
                }
                else if (event.key.code == Keyboard::Right && valid((pacman_x + CELL_SIZE) / CELL_SIZE, pacman_y / CELL_SIZE))
                {
                    sharedmem.pacman_direction = 4;
                }
                // Unlock mutex after updating shared variable
                pthread_mutex_unlock(&PacmanPosMutex);
                pthread_mutex_unlock(&SharedmemMutex);
            }
        }
    }
    pthread_exit(NULL);
}
// array of ghosts
GhostData ghosts[4];
void movePacman(sf::Texture &pacman_texture)
{
    int pacman_direction_x = 0;
    int pacman_direction_y = 0;
    int pacdirection;
    pthread_mutex_lock(&SharedmemMutex);
    pacdirection = sharedmem.pacman_direction;
    pthread_mutex_unlock(&SharedmemMutex);
    // check direction of pacman and move it accordingly
    switch (pacdirection)
    {
    case 1: // Up
        pacman_direction_x = 0;
        pacman_direction_y = -1;
        pacman_texture.loadFromFile("pacmanUp.png");
        break;
    case 2: // Down
        pacman_direction_x = 0;
        pacman_direction_y = 1;
        pacman_texture.loadFromFile("pacmanDown.png");
        break;
    case 3: // Left
        pacman_direction_x = -1;
        pacman_direction_y = 0;
        pacman_texture.loadFromFile("pacmanLeft.png");
        break;
    case 4: // Right
        pacman_direction_x = 1;
        pacman_direction_y = 0;
        // Load pacman image
        pacman_texture.loadFromFile("pacmanRight.png");
        break;
    default:
        break;
    }
    pthread_mutex_lock(&PacmanPosMutex);
    // boundary detection
    int nextX = pacman_x + pacman_direction_x * CELL_SIZE;
    int nextY = pacman_y + pacman_direction_y * CELL_SIZE;
    pthread_mutex_lock(&GameBoardMutex);
    if (valid(nextX / CELL_SIZE, nextY / CELL_SIZE))
    {
        // Update pacman's position
        pacman_x += pacman_direction_x * CELL_SIZE;
        pacman_y += pacman_direction_y * CELL_SIZE;
    }

    // ScorePallet Detection
    if (abs(gameMap[nextY / CELL_SIZE][nextX / CELL_SIZE]) == 2)
    {
        // ScorePallet found, update gameMap and increment score
        musicMunch.stop();
        gameMap[nextY / CELL_SIZE][nextX / CELL_SIZE] = 0;
        totalScorePallet--;
        Score++;
        musicMunch.play();
        // cout<<Score<<endl;
    }
    if (abs(gameMap[nextY / CELL_SIZE][nextX / CELL_SIZE] == 4) && powerupActive == false)
    {
        gameMap[nextY / CELL_SIZE][nextX / CELL_SIZE] = 0;
        powerupActive = true;
        if (powerupActive)
        {
            musicEat.play();
            // cout << "Eaten power up ";
            powerupClock.restart();
            powercountclock.restart();
            powerupcount++;
            // make a new thread and let it sleep for 5 sec , then change the flag
        }
        // maybe start a new thread for 5 seconds and then change the flag back to false ;
    }
    // ghost collision detection with all ghosts 1 2 3 4

    //pthread_mutex_unlock(&PacmanPosMutex);
    //pthread_mutex_lock(&PacmanPosMutex);
    if (powerupActive)
    {
        for (int i = 0; i < 4; i++)
        {
            if (ghosts[i].x / CELL_SIZE == pacman_x / CELL_SIZE && ghosts[i].y / CELL_SIZE == pacman_y / CELL_SIZE)
            {
                // cout << "Ghost caught pacman" << endl;
                //  reset ghost position
                ghosts[i].x = 451;
                ghosts[i].y = 454;
                ghosts[i].isActivated = 0;
            }
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            if (ghosts[i].x / CELL_SIZE == pacman_x / CELL_SIZE && ghosts[i].y / CELL_SIZE == pacman_y / CELL_SIZE)
            {
                // signal main to reset game.
                reset = 1;
                musicReset.stop();
                musicReset.play();
                pthread_mutex_unlock(&GameBoardMutex);
                pthread_mutex_unlock(&PacmanPosMutex);
                return;
            }
        }
    }
    pthread_mutex_unlock(&GameBoardMutex);
    pthread_mutex_unlock(&PacmanPosMutex);
}

int main()
{
    Music bgMusic;
    if (!bgMusic.openFromFile("sounds/pacman_intermission.wav"))
        cout << "issue";
    bgMusic.setLoop(1);
    bgMusic.setVolume(20);
    bgMusic.play();
    if (!musicmenu.openFromFile("sounds/pacman_beginning.wav"))
        cout << "sound not loaded";
    if (!musicEat.openFromFile("sounds/pacman_eatfruit.wav"))
        cout << "sound  1 not loaded";
    if (!musicMunch.openFromFile("sounds/pacman_chomp.wav"))
        cout << "sound  1 not loaded";
    musicMunch.setVolume(50);
    if (!musicReset.openFromFile("sounds/pacman_death.wav"))
        cout << "sound  1 not loaded";
    //  Initialize random seed
    srand(time(nullptr));
    // Initialize game board
    intitializeGrid();
    int count = 0; // Counter for the number of positions initialized with 4
    // 4 random posiiton for red circle (power up value  = 4 )
    while (powerupcount > 0)
    {
        int randRow = rand() % ROWS;
        int randCol = rand() % COLS;
        if (valid(randCol, randRow) && gameMap[randRow][randCol] != 4)
        {
            gameMap[randRow][randCol] = 4;
            powerupcount--;
        }
    }

    sf::RenderWindow windoww(sf::VideoMode(477, 661), "PHAK MAYN");
    //  Create SFML window
    sf::Texture menu_texture;
    menu_texture.loadFromFile("Menu.png");
    sf::Sprite menu(menu_texture);
    // set position of menu in the middle of the screen
    // dispplay menu
    windoww.draw(menu);
    windoww.display();
    musicmenu.setLoop(true);
    musicmenu.setVolume(50);
    musicmenu.play();
    while (windoww.isOpen())
    {
        Event event;
        while (windoww.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {

                // signal main to close window
                windoww.close();
                exit(0);
            }
            else if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Enter)
                {
                    windoww.close();
                    musicmenu.stop();
                }
            }
        }
    }
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "PHAK MAYN");
    // background image
    sf::Texture background_texture;
    background_texture.loadFromFile("Background.png");
    sf::Sprite background(background_texture);
    // Create the yellow circle (player)
    sf::CircleShape pacman_shape(25 / 2);
    // load pacman image
    sf::Texture pacman_texture;
    pacman_texture.loadFromFile("pacmanRight.png");
    pacman_shape.setTexture(&pacman_texture);
    sf::CircleShape ghost_shape1(25 / 2);
    sf::CircleShape ghost_shape2(25 / 2);
    sf::CircleShape ghost_shape3(25 / 2);
    sf::CircleShape ghost_shape4(25 / 2);
    sf::Texture palletFeatureTexture;
    palletFeatureTexture.loadFromFile("cherry.png");
    sf::Sprite palletFeatSprite(palletFeatureTexture);

    sf::Texture livetexture;
    livetexture.loadFromFile("live.png");
    sf::Sprite livesprite(livetexture);
    livesprite.setPosition(700, 960);
    livesprite.setScale(0.08, 0.08);
    sf::Texture ghost_texture1, ghost_texture2, ghost_texture3, ghost_texture4;
    ghost_texture1.loadFromFile("GhostRed.png");
    ghost_shape1.setTexture(&ghost_texture1);
    ghost_texture2.loadFromFile("GhostBlue.png");
    ghost_shape2.setTexture(&ghost_texture2);
    ghost_texture3.loadFromFile("GhostGreen.png");
    ghost_shape3.setTexture(&ghost_texture3);
    ghost_texture4.loadFromFile("GhostYellow.png");
    ghost_shape4.setTexture(&ghost_texture4);
    pacman_shape.setPosition(25 / 8, 25 / 4); // Set initial position to (100, 50)

    // Initialize semaphore for speed boost
    sem_init(&speedBoostSemaphore, 0, 2); // Initialize with 2 speed boosts available

    // Initialize semaphores foe key and permit
    sem_init(&keySemaphore, 0, 2);
    sem_init(&permitSemaphore, 0, 2);

    // Create thread for user input
    pthread_t userInputThread;
    pthread_create(&userInputThread, nullptr, userInput, &window);

    // Initialize ghosts' data
    ghosts[0].x = 355;
    ghosts[0].y = 454;
    ghosts[1].x = 387;
    ghosts[1].y = 454;
    ghosts[2].x = 451;
    ghosts[2].y = 454;
    ghosts[3].x = 483;
    ghosts[3].y = 454;
    ghosts[0].ghostID = 1;
    ghosts[1].ghostID = 2;
    ghosts[2].ghostID = 3;
    ghosts[3].ghostID = 4;
    ghosts[0].pr = 1;
    ghosts[1].pr = 2;
    ghosts[2].pr = 3;
    ghosts[3].pr = 1;

    // push the low priority ghosts in the ghostlist
    ghostlist.push_back(&ghosts[1]);
    ghostlist.push_back(&ghosts[2]);

    // Create threads for ghost controllers
    pthread_t ghost1Thread;
    pthread_t ghost2Thread;
    pthread_t ghost3Thread;
    pthread_t ghost4Thread;

    pthread_create(&ghost1Thread, nullptr, ghostController, &ghosts[0]);
    pthread_create(&ghost2Thread, nullptr, ghostController, &ghosts[1]);
    pthread_create(&ghost3Thread, nullptr, ghostController, &ghosts[2]);
    pthread_create(&ghost4Thread, nullptr, ghostController, &ghosts[3]);
    start = true;
    // Main loop
    while (window.isOpen())
    {
        // Clear, draw, and display
        while (powerupcount > 0 && powercountclock.getElapsedTime().asSeconds() >= 20)
        {
            int randRow = rand() % ROWS;
            int randCol = rand() % COLS;
            if (valid(randCol, randRow) && gameMap[randRow][randCol] != 4)
            {
                gameMap[randRow][randCol] = 4;
                powerupcount--;
                powercountclock.restart();
            }
        }

        if (powerupActive)
        {
            ghost_texture1.loadFromFile("ghostscared.png");
            ghost_texture2.loadFromFile("ghostscared.png");
            ghost_texture3.loadFromFile("ghostscared.png");
            ghost_texture4.loadFromFile("ghostscared.png");
        }
        if (powerupClock.getElapsedTime().asSeconds() >= 10)
        {
            powerupActive = false;
            musicEat.stop();
            ghost_texture1.loadFromFile("GhostRed.png");
            ghost_texture2.loadFromFile("GhostBlue.png");
            ghost_texture3.loadFromFile("GhostGreen.png");
            ghost_texture4.loadFromFile("GhostYellow.png");
        }

        // move the pcman
        movePacman(pacman_texture);
        // check if game needs to be reset on collision with ghost
        if (reset == true)
        {
            start = 0;
            life--;
            resetGame(ghosts[0], ghosts[1], ghosts[2], ghosts[3]);
        }

        // draw the game
        window.clear();
        window.draw(background);
        drawGrid(window);
        pacman_shape.setPosition(pacman_x, pacman_y);       // Update pacman position
        ghost_shape1.setPosition(ghosts[0].x, ghosts[0].y); // Update ghost position
        ghost_shape2.setPosition(ghosts[1].x, ghosts[1].y); // Update ghost position
        ghost_shape3.setPosition(ghosts[2].x, ghosts[2].y); // Update ghost position
        ghost_shape4.setPosition(ghosts[3].x, ghosts[3].y); // Update ghost position
        window.draw(pacman_shape);
        window.draw(ghost_shape1);
        window.draw(ghost_shape2);
        window.draw(ghost_shape3);
        window.draw(ghost_shape4);
        for (int kk = 0; kk < life; kk++)
        {
            livesprite.setPosition(700 + kk * 30, 960);
            window.draw(livesprite);
        }
        for (int i = powerupcount; i < 4; i++)
        {
            palletFeatSprite.setPosition(150 + i * 30, 960);
            window.draw(palletFeatSprite);
        }

        window.display();
        checkwin(gameMap, window);
        usleep(150000); // Sleep for 0.3 seconds
       
        if (closwindow == 1)
        {
            pthread_cancel(userInputThread);
            pthread_cancel(ghost1Thread);
            pthread_cancel(ghost2Thread);
            pthread_cancel(ghost3Thread);
            pthread_cancel(ghost4Thread);
            window.close();
        }
    }

    // Join threads
    pthread_join(userInputThread, nullptr);
    pthread_join(ghost1Thread, nullptr);
    pthread_join(ghost2Thread, nullptr);
    pthread_join(ghost3Thread, nullptr);
    pthread_join(ghost4Thread, nullptr);
    // Destroy mutexes
    pthread_mutex_destroy(&SharedmemMutex);
    pthread_mutex_destroy(&GameBoardMutex);
    // Destroy semaphore
    sem_destroy(&speedBoostSemaphore);
    sem_destroy(&keySemaphore);
    sem_destroy(&permitSemaphore);


    if(gamewon){

     sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Text");

    // Create a font
    sf::Font font;
    if (!font.loadFromFile("SIXTY.TTF")) {
        // Error handling if the font fails to load
        std::cerr << "Failed to load font file" << std::endl;
        return EXIT_FAILURE;
    }

    // Create a text object
    sf::Text text;
    text.setFont(font);
    text.setString("Congrats You WON the Game!\n Press Enter to end!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(400, 500);

    // Main loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
                // Check if the Enter key is pressed
                window.close(); // Close the window if Enter is pressed
            }
        }

        // Clear the window
        window.clear();

        // Draw the text
        window.draw(text);

        // Display the window
        window.display();
    }

    }
   else if(!gamewon){

     sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Text");

    // Create a font
    sf::Font font;
    if (!font.loadFromFile("SIXTY.TTF")) {
        // Error handling if the font fails to load
        std::cerr << "Failed to load font file" << std::endl;
        return EXIT_FAILURE;
    }

    // Create a text object
    sf::Text text;
    text.setFont(font);
    text.setString("Hard Luck Next Time:( \nPress Enter to end!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(400, 500);

    // Main loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
                // Check if the Enter key is pressed
                window.close(); // Close the window if Enter is pressed
            }
        }

        // Clear the window
        window.clear();

        // Draw the text
        window.draw(text);

        // Display the window
        window.display();
    }

    }


    return 0;
}