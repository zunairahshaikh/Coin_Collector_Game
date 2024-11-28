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
