#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>   // for _getch()
#include <windows.h> // for Sleep()

// Macros
#define GRID_SIZE 20
#define COINS_COUNT 10
#define OBSTACLES_COUNT 14
#define GAME_DURATION 45
#define REFRESH_RATE 100 // rate in milliseconds

// Game entities
#define EMPTY '.'
#define PLAYER 'P'
#define COIN 'C'
#define OBSTACLE 'X'

// Global Variables
char grid[GRID_SIZE][GRID_SIZE];
int playerX = 0, playerY = 0;
int score = 0;
int lives = 3;
int gameOver = 0;
int highScore = 0;
char highScoreHolder[50] = "Unknown"; // To store the name of the current high scorer
time_t startTime;

typedef struct {
    char name[50];
    int score;
} User;

const char *highScoreFile = "highscore.txt";

// Function prototypes
void clearScreen();
void initializeGrid();
int isPositionEmpty(int x, int y);
void placeRandomItems(char item, int count);
void initializeGame(User *user);
void displayGame();
void handleCollision(int newX, int newY);
void movePlayer(char direction);
void saveHighScore(User user);
char promptReplay();

// Main
int main()
{
    char replay;
    User currentUser;

    do
    {
        // Reset game variables
        playerX = 0;
        playerY = 0;
        score = 0;
        lives = 3;
        gameOver = 0;

        // Ask the user for their name
        printf("Enter your name: ");
        fgets(currentUser.name, 50, stdin);
        currentUser.name[strcspn(currentUser.name, "\n")] = '\0'; // Remove newline character

        // Initialize and start the game
        initializeGame(&currentUser);
        char userInput;

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

        // Check for a new high score
        if (score > highScore)
        {
            highScore = score;
            printf("Congratulations %s! You have achieved a new high score!\n", currentUser.name);
            saveHighScore(currentUser);
        }
        else
        {
            printf("High Score: %d by %s\n", highScore, highScoreHolder);
        }

        // Ask the user if they want to replay
        replay = promptReplay();

    } while (replay == 'Y' || replay == 'y');

    printf("Thank you for playing! Goodbye!\n");
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

void initializeGame(User *user)
{
    srand(time(NULL));
    initializeGrid();
    grid[playerY][playerX] = PLAYER;
    placeRandomItems(COIN, COINS_COUNT);
    placeRandomItems(OBSTACLE, OBSTACLES_COUNT);
    startTime = time(NULL);

    // Load the high score from the file
    FILE *fptr = fopen(highScoreFile, "r");
    if (fptr != NULL)
    {
        fscanf(fptr, "%d", &highScore);
        fgetc(fptr); // Read the newline character
        fgets(highScoreHolder, 50, fptr);
        highScoreHolder[strcspn(highScoreHolder, "\n")] = '\0'; // Remove newline character
        fclose(fptr);
    }
    else
    {
        printf("High Score File not Found!\n");
        return;
    }
}

void saveHighScore(User user)
{
    FILE *fptr = fopen(highScoreFile, "w");
    if (fptr != NULL)
    {
        fprintf(fptr, "%d\n%s", highScore, user.name);
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

char promptReplay()
{
    char choice;

    while (1)
    {
        printf("Do you want to play again? (Y/N): ");
        choice = _getch();
        printf("%c\n", choice); // Display the choice

        if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')
        {
            return choice;
        }
        else
        {
            printf("Invalid input. Please enter Y for yes or N for no.\n");
        }
    }
}
