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
