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



