#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>   //for _getch()
#include <windows.h> //for Sleep()

// Macros
#define GRID_SIZE 10
#define COINS_COUNT 3
#define OBSTACLES_COUNT 4
#define GAME_DURATION 30
#define REFRESH_RATE 100 // rate in milliseconds

// Game entities
#define EMPTY '.'
#define PLAYER 'P'
#define COIN 'C'
#define OBSTACLE 'X'

// Global Variables
// Game state
char grid[GRID_SIZE][GRID_SIZE];
int playerX = 0, playerY = 0;
int score = 0;
int lives = 3;
int gameOver = 0;
int highScore = 0;
time_t startTime;

const char *highScoreFile = "highscore.txt";

// Functions
void clearScreen();
void initializeGrid();
int isPositionEmpty(int x, int y);
void placeRandomItems(char item, int count);
void initializeGame();
void displayGame();
void handleCollision(int newX, int newY);
void movePlayer(char direction);
void saveHighScore();

// Main
int main()
{
    char userInput;

    initializeGame();

    while (!gameOver)
    {
        displayGame();

        userInput = _getch();

        if (userInput == 'q')
            break;

        movePlayer(userInput);

        if (time(NULL) - startTime >= GAME_DURATION)
        {
            gameOver = 1;
        }

        Sleep(REFRESH_RATE);
    }

    clearScreen();
    printf("\nGame Over!\nYour Score: %d\n", score);
    if (score > highScore)
    {
        highScore = score;
        saveHighScore();
        printf("Congratulations! You reached a new high score! :)\n");
    }

    return 0;
}

// Function Definitions
void clearScreen()
{
    system("cls"); // For Windows
}

void initializeGrid()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            grid[i][j] = EMPTY;
        }
    }
}

int isPositionEmpty(int x, int y)
{
    return grid[y][x] == EMPTY;
}

void placeRandomItems(char item, int count)
{
    for (int i = 0; i < count; i++)
    {
        int x, y;
        do
        {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        } while (!isPositionEmpty(x, y));
        grid[y][x] = item;
    }
}

void initializeGame()
{
    srand(time(NULL));
    initializeGrid();
    grid[playerY][playerX] = PLAYER;
    placeRandomItems(COIN, COINS_COUNT);
    placeRandomItems(OBSTACLE, OBSTACLES_COUNT);
    startTime = time(NULL);

    FILE *fptr = fopen(highScoreFile, "r");
    if (fptr != NULL)
    {
        fscanf(fptr, "%d", &highScore);
        fclose(fptr);
    }
    else
    {
        printf("High Score File not Found!");
        return;
    }
}

void saveHighScore()
{
    FILE *fptr = fopen(highScoreFile, "w");
    if (fptr != NULL)
    {
        fprintf(fptr, "%d", highScore);
        fclose(fptr);
    }
}

void displayGame()
{
    clearScreen();
    printf("Score: %d  Lives: %d  Time left: %d\n\n",
           score, lives, GAME_DURATION - (int)(time(NULL) - startTime));

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            switch (grid[i][j])
            {
            case PLAYER:
                printf("🦊 ");
                break;
            case COIN:
                printf("🟡 ");
                break;
            case OBSTACLE:
                printf("🔺 ");
                break;
            case EMPTY:
                printf(" . ");
                break;
            default:
                printf("%c ", grid[i][j]); // fallback for unexpected characters
            }
        }
        printf("\n");
    }
    printf("\nUse WASD to move, Q to quit\n");
}

void handleCollision(int newX, int newY)
{
    if (grid[newY][newX] == COIN)
    {
        score += 10;
        placeRandomItems(COIN, 1);
    }
    else if (grid[newY][newX] == OBSTACLE)
    {
        lives--;
        if (lives <= 0)
        {
            gameOver = 1;
        }
        else
        {
            // Reset player position
            grid[playerY][playerX] = EMPTY;
            playerX = 0;
            playerY = 0;
            grid[playerY][playerX] = PLAYER;
            return;
        }
    }
}

void movePlayer(char direction)
{
    int newX = playerX;
    int newY = playerY;

    switch (direction)
    {
    case 'w':
    case 'W':
        newY = (playerY > 0) ? playerY - 1 : playerY;
        break;
    case 's':
    case 'S':
        newY = (playerY < GRID_SIZE - 1) ? playerY + 1 : playerY;
        break;
    case 'a':
    case 'A':
        newX = (playerX > 0) ? playerX - 1 : playerX;
        break;
    case 'd':
    case 'D':
        newX = (playerX < GRID_SIZE - 1) ? playerX + 1 : playerX;
        break;
    }

    if (newX != playerX || newY != playerY)
    {
        handleCollision(newX, newY);
        if (!gameOver)
        {
            grid[playerY][playerX] = EMPTY;
            playerX = newX;
            playerY = newY;
            grid[playerY][playerX] = PLAYER;
        }
    }
}
