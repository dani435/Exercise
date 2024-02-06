#include "raylib.h"
#include <time.h>
#include <string.h>
#include "Tetris.h"

//Game
int stage[] =                                   
{
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

//Tetrimino's 
const int lTetromino0[] =               
{
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
};

const int lTetromino90[] =
{
    0, 0, 0, 0,
    1, 1, 1, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,
};

const int lTetromino180[] =
{
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

const int lTetromino270[] =
{
    0, 0, 1, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int jTetromino0[] =
{
    0, 1, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
};

const int jTetromino90[] =
{
    1, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int jTetromino180[] =
{
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

const int jTetromino270[] =
{
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,
};


const int oTetromino[] =
{
    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int sTetromino0[] =
{
    0, 0, 0, 0,
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
};

const int sTetromino90[] =
{
    0, 0, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
};

const int sTetromino180[] =
{
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 1, 1, 0,
    1, 1, 0, 0,
};

const int sTetromino270[] =
{
    0, 0, 0, 0,
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
};


const int tTetromino0[] =
{
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

const int tTetromino90[] =
{
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

const int tTetromino180[] =
{
    0, 1, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int tTetromino270[] =
{
    1, 0, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,
};

const int iTetromino0[] =
{
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
};

const int iTetromino90[] =
{
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int iTetromino180[] =
{
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
};

const int iTetromino270[] =
{
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int zTetromino0[] =
{
    0, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
};

const int zTetromino90[] =
{
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,
};

const int zTetromino180[] =
{
    0, 0, 0, 0,
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
};

const int zTetromino270[] =
{
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

const int *tetrominoTypes[7][4] =
    {
        {zTetromino0, zTetromino90, zTetromino180, zTetromino270},
        {sTetromino0, sTetromino90, sTetromino180, sTetromino270},
        {tTetromino0, tTetromino90, tTetromino180, tTetromino270},
        {oTetromino, oTetromino, oTetromino, oTetromino},
        {iTetromino0, iTetromino90, iTetromino180, iTetromino270},
        {jTetromino0, jTetromino90, jTetromino180, jTetromino270},
        {lTetromino0, lTetromino90, lTetromino180, lTetromino270},
};

//Colors
const Color colorTypes[9] =
    {
        {255, 255, 0, 255},
        {255, 153, 255, 255},
        {255, 128, 0, 255},
        {0, 255, 0, 255},
        {0, 0, 255, 255},
        {255, 0, 255, 255},
        {0, 255, 255, 255},
        {255, 255, 255, 255},
        {0, 0, 0, 255},
};

//Score variables
int score = 0;
int scoreLines = 10;
int lvlScore = 0;

void drawTetromino(const Color currentColor, const int startOffsetX, const int startOffsetY, const int tetrominoStartX, const int tetrominoStartY, const int *tetromino)
{
    for (int y = 0; y < TETROMINO_SIZE; y++)
    {
        for (int x = 0; x < TETROMINO_SIZE; x++)
        {
            const int offset = y * TETROMINO_SIZE + x;

            if (tetromino[offset] == 1)
            {
                DrawRectangle((x + tetrominoStartX) * TILE_SIZE + startOffsetX, (y + tetrominoStartY) * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, currentColor);
            }
        }
    }
}

void ResetLines(int startLineY)
{
    //Reset the stage without completed lines
    for (int y = startLineY; y >= 0; y--)
    {
        for (int x = 1; x < STAGE_WIDTH - 1; x++)
        {
            const int offset = y * STAGE_WIDTH + x;
            const int offset_below = (y + 1) * STAGE_WIDTH + x;

            if (stage[offset_below] == 0 && stage[offset] > 0)
            {
                stage[offset_below] = stage[offset];
                stage[offset] = 0;
            }
        }
    }
}

void DeleteLines(int startOffsetX, int startOffsetY)
{
    //sound when a line is completed
    Sound lineClearMusic = LoadSound("./tetrisLineClearSound.wav");
    SetSoundVolume(lineClearMusic, 0.05f);

    //variables for multiple lines
    int count = 0;
    int startDeleteOffsetY;

    //animation
    float animationClearTimer = .15f;
    float timeToClearAnimation = animationClearTimer;
    int offsetR = 6;
    int offsetL = 5;

    for (int y = 0; y < STAGE_HEIGHT - 1; y++)
    {
        int checkLine = 1;

        for (int x = 1; x < STAGE_WIDTH - 1; x++)
        {
            const int offset = y * STAGE_WIDTH + x;

            if (stage[offset] == 0)
            {
                //checkLine 0 if there is an empty space in the line
                checkLine = 0;
                break;
            }
        }
        if (checkLine)
        {
            count++;
            if (count == 1)
            {
                startDeleteOffsetY = y;
            }
            for (int x = 1; x < STAGE_WIDTH - 1; x++)
            {
                //set the stage to start the animation
                const int offset = y * STAGE_WIDTH + x;
                stage[offset] = 8;
            }
        }
    }
    if (count > 0)
    {
        PlaySound(lineClearMusic);
        //animation loop
        while (offsetL > 0)
        {
            while (timeToClearAnimation >= 0)
            {
                BeginDrawing();
                ClearBackground(RED);
                for (int z = 0; z < STAGE_HEIGHT; z++)
                {
                    for (int x = 0; x < STAGE_WIDTH; x++)
                    {
                        const int offset = z * STAGE_WIDTH + x;
                        if (stage[offset] == 8 && (x == offsetL || x == offsetR))
                        {
                            stage[offset] = 9;
                        }
                        const int color = stage[offset];

                        if (stage[offset] != 0)
                        {
                            DrawRectangle(x * TILE_SIZE + startOffsetX, z * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, colorTypes[color - 1]);
                        }

                        DrawRectangleLines(x * TILE_SIZE + startOffsetX, z * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, BLACK);
                    }
                }
                EndDrawing();
                timeToClearAnimation -= GetFrameTime();
            }
            timeToClearAnimation = animationClearTimer;
            offsetL--;
            offsetR++;
        }

        //clear the memory
        for (int i = 0; i < count; i++)
        {
            int y = startDeleteOffsetY + i;
            const int offset = y * STAGE_WIDTH + 1;
            memset(stage + offset, 0, (STAGE_WIDTH - 2) * sizeof(int));
            ResetLines(y);
        }
        //increase the score
        score += (scoreLines * count);
    }
    UnloadSound(lineClearMusic);
}

int main(int argc, char **argv, char **environ)
{
    //Window
    const int windowWidth = 600;
    const int windowHeight = 700;

    //Spawn point of the stage
    const int startOffsetX = (windowWidth / 2) - ((STAGE_WIDTH * TILE_SIZE) / 2);
    const int startOffsetY = (windowHeight / 2) - ((STAGE_HEIGHT * TILE_SIZE) / 2);

    //Spawn point of my tetromino
    const int tetrominoStartX = STAGE_WIDTH / 2;
    const int tetrominoStartY = 0;

    //Position of the tetromino in the stage
    int currentTetrominoX = tetrominoStartX;
    int currentTetrominoY = tetrominoStartY;

    //Background music
    float timeForMusic = 0.0f;
    int isSoundPlaying = 0;
    const float musicBackgroundDuration = 83.0f;

    //GameOver
    int gameOver = 0;

    //Variables for random
    time_t unixTime;
    time(&unixTime);
    SetRandomSeed(unixTime);

    //Select a random tetromino and the next one
    int currentTetrominoType = GetRandomValue(0, 6);
    int nextTetromino = GetRandomValue(0, 6);
    int currentRotation = 0;

    //Tetromino random color
    int currentColor = GetRandomValue(1, 6);
    int nextColor = GetRandomValue(1, 6);

    //Tetromino movement time
    float moveTetrominoDownTimer = 1.f;
    float timeToMoveTetrominoDown = moveTetrominoDownTimer;

    TraceLog(LOG_INFO, "Number of arguments : %d", argc);

    for (int i = 0; i < argc; i++)
    {
        TraceLog(LOG_INFO, "Argument : %d = %s", i, argv[i]);
    }

    while (*environ != 0)
    {
        TraceLog(LOG_INFO, "Argument : %s", *environ);
        environ++;
    }

    //Init Window
    InitWindow(windowWidth, windowHeight, "Title");

    // Sound
    InitAudioDevice();
    Sound backgroundMusic = LoadSound("./Tetris.wav");
    SetSoundVolume(backgroundMusic, 0.05f);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (gameOver == 0)
        {
            //Decrease the movement time of the tetromino based on the score
            while (score > lvlScore)
            {
                moveTetrominoDownTimer -= 0.3f;
                lvlScore += 10;
            }
            
            //Print the score
            DrawText(TextFormat("SCORE: %d", score), windowWidth / 2 + 150, 30, 20, WHITE);


            //Restart the music when is finished
            if (isSoundPlaying == 0)
            {
                PlaySound(backgroundMusic);
                isSoundPlaying = 1;
            }
            else
            {
                timeForMusic += GetFrameTime();
                if (timeForMusic >= musicBackgroundDuration)
                {
                    StopSound(backgroundMusic);
                    isSoundPlaying = 0;
                    timeForMusic = 0.0f;
                }
            }

            //Decrease the time every frame
            timeToMoveTetrominoDown -= GetFrameTime();

            //Fast GameOver
            if (IsKeyPressed(KEY_L))
            {
                gameOver = 1;
            }

            //Rotate the tetromino
            if (IsKeyPressed(KEY_SPACE))
            {
                const int lastRotation = currentRotation;

                currentRotation++;

                if (currentRotation > 3)
                {
                    currentRotation = 0;
                }

                //Check if rotation is possible
                if (CheckCollision(currentTetrominoX, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation]))
                {
                    currentRotation = lastRotation;
                }
            }

            //move tetromino right
            if (IsKeyPressed(KEY_RIGHT))
            {
                // check collision with the wall
                if (!CheckCollision(currentTetrominoX + 1, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation]))
                {
                    currentTetrominoX++;
                }
            }

            //move tetromino left
            if (IsKeyPressed(KEY_LEFT))
            {
                // check collision with the wall
                if (!CheckCollision(currentTetrominoX - 1, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation]))
                {
                    currentTetrominoX--;
                }
            }

            //directly move tetromino down
            if (IsKeyPressed(KEY_UP))
            {
                while (!CheckCollision(currentTetrominoX, currentTetrominoY + 1, tetrominoTypes[currentTetrominoType][currentRotation]))
                {
                    currentTetrominoY++;
                }
                timeToMoveTetrominoDown = 0;
            }

            //directly move tetromino down by one
            if (timeToMoveTetrominoDown <= 0 || IsKeyPressed(KEY_DOWN))
            {
                // check collision 
                if (!CheckCollision(currentTetrominoX, currentTetrominoY + 1, tetrominoTypes[currentTetrominoType][currentRotation]))
                {
                    currentTetrominoY++;
                    timeToMoveTetrominoDown = moveTetrominoDownTimer;
                }

                else
                {
                    //set tetromino in the stage
                    for (int y = 0; y < TETROMINO_SIZE; y++)
                    {
                        for (int x = 0; x < TETROMINO_SIZE; x++)
                        {
                            const int offset = y * TETROMINO_SIZE + x;

                            const int *tetromino = tetrominoTypes[currentTetrominoType][currentRotation];

                            if (tetromino[offset] == 1)
                            {
                                const int offset_stage = (y + currentTetrominoY) * STAGE_WIDTH + (x + currentTetrominoX);
                                stage[offset_stage] = currentColor + 1;
                            }
                        }
                    }

                    //check if there are completed lines
                    DeleteLines(startOffsetX, startOffsetY);

                    //reset the position
                    currentTetrominoX = tetrominoStartX;
                    currentTetrominoY = tetrominoStartY;

                    //reset tetromino
                    currentTetrominoType = nextTetromino;
                    nextTetromino = GetRandomValue(0, 6);
                    currentRotation = 0;
                    currentColor = nextColor;
                    nextColor = GetRandomValue(1, 6);
                }
            }

            //Draw the stage
            BeginDrawing();
            ClearBackground(RED);

            for (int y = 0; y < STAGE_HEIGHT; y++)
            {
                for (int x = 0; x < STAGE_WIDTH; x++)
                {
                    const int offset = y * STAGE_WIDTH + x;
                    const int color = stage[offset];

                    if (stage[offset] != 0)
                    {
                        DrawRectangle(x * TILE_SIZE + startOffsetX, y * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, colorTypes[color - 1]);
                    }

                    DrawRectangleLines(x * TILE_SIZE + startOffsetX, y * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, BLACK);
                }
            }


            drawTetromino(colorTypes[currentColor], startOffsetX, startOffsetY, currentTetrominoX, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation]);
            DrawText("NEXT:", 25, 30, 20, WHITE);
            drawTetromino(colorTypes[nextColor], startOffsetX, startOffsetY, -5, 0, tetrominoTypes[nextTetromino][0]);
            EndDrawing();

            //check game over
            if (currentTetrominoX == tetrominoStartX)
            {
                if (CheckCollision(currentTetrominoX, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation]))
                {
                    gameOver = 1;
                    EndDrawing();
                    continue;
                }
            }
        }
        //if gameover, create the new scene
        else
        {
            StopSound(backgroundMusic);
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("GAME OVER", windowWidth / 2 - 150, 50, 50, RED);
            DrawText(TextFormat("SCORE: %d\n\nPRESS R TO RESTART\n\nPRESS ESC TO EXIT", score), windowWidth / 2 - 150, 150, 20, RED);

            //restart the game, reset all variables
            if (IsKeyPressed(KEY_R))
            {
                currentTetrominoX = tetrominoStartX;
                currentTetrominoY = tetrominoStartY;
                moveTetrominoDownTimer = 1.0f;
                timeToMoveTetrominoDown = moveTetrominoDownTimer;
                currentTetrominoType = GetRandomValue(0, 6);
                nextTetromino = GetRandomValue(0, 6);
                currentRotation = 0;
                currentColor = GetRandomValue(1, 6);
                nextColor = GetRandomValue(1, 6);
                for (int y = 0; y < STAGE_HEIGHT - 1; y++)
                {
                    for (int x = 1; x < STAGE_WIDTH - 1; x++)
                    {
                        const int offset = y * STAGE_WIDTH + x;
                        if (stage[offset] != 0)
                        {
                            stage[offset] = 0;
                        }
                    }
                }
                PlaySound(backgroundMusic);
                score = 0;
                gameOver = 0;
            }

            //close the game
            if (IsKeyPressed(KEY_ESCAPE))
            {
                CloseWindow();
            }
            EndDrawing();
        }
    }
    UnloadSound(backgroundMusic);
    CloseAudioDevice();
    return 0;
}
