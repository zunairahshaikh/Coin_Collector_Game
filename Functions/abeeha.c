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

