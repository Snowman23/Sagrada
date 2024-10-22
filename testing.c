#include <stdio.h>
#include <stdlib.h>
#include <time.h>                                 
#include <string.h>
#include <stdbool.h>

#define NUM_DICE 90
#define DICE_PER_COLOR 18
#define NUM_COLORS 5
#define NUM_ROWS 4
#define NUM_COLS 5
#define MAX_PLAYERS 4

#define RED "\x1B[31m"
#define YEL "\x1B[33m"
#define GRN "\x1B[32m"
#define BLU "\x1B[34m"
#define PRP "\x1B[35m"
#define RESET "\x1B[0m"

typedef struct{
    int value;
    char color[10];
} Cell;

typedef struct{
    int value;
    char color[10];
} Dice;

typedef struct{
    Dice rolled[NUM_DICE];
    int size;
} RolledDice;

typedef struct{
    Cell grid[NUM_ROWS][NUM_COLS];
    int dificulty; 
} WindowFace;

typedef union{
    WindowFace faces[2];
    struct
    {
        WindowFace frontFace;
        WindowFace backFace;
    };
} Windows;

typedef struct{
    WindowFace chosenWindow;
    int score;
    int helperGems;
    char PrivateGoal;
} PlayerWindow;

typedef struct {
    int id;            
    int points;         
    char description[50]; 
} PublicGoals;

const char colors[NUM_COLORS] = {'R', 'Y', 'G', 'B', 'P'};

bool isColorUsed(char color, PlayerWindow *players, int numPlayers)
{
    for (int i = 0; i < numPlayers; i++)
    {
        if (players[i].PrivateGoal == color)
        {
            return true;
        }
    }
    return false;
}

void initializePouch(Dice *pouch)
{
    int i, j;
    char colors[NUM_COLORS][10] = {"Red", "Yellow", "Green", "Blue", "Purple"};
    for (i = 0; i < NUM_COLORS; ++i)
    {
        for (j = 0; j < DICE_PER_COLOR; ++j)
        {
            pouch[i * DICE_PER_COLOR + j].value = (rand() % 6) + 1;
            strcpy(pouch[i * DICE_PER_COLOR + j].color, colors[i]);
        }
    }
}

void shuffle(Dice *pouch, int size)
{
    int i, j;
    Dice temp;
    for (i = size - 1; i > 0; --i)
    {
        j = rand() % (i + 1);
        temp = pouch[i];
        pouch[i] = pouch[j];
        pouch[j] = temp;
    }
}

void drawDice(Dice *pouch, int numDraws, int *pouchSize, RolledDice *rolledDice)
{
    int i, index;
    srand(time(NULL));

    for (i = 0; i < numDraws; ++i)
    {
        if (*pouchSize == 0)
        {
            printf("Pouch is empty!\n");
            return;
        }
        index = rand() % *pouchSize;
        rolledDice->rolled[rolledDice->size] = pouch[index];
        (rolledDice->size)++;
        printf("%d. Value %d, color %s\n", i+1,pouch[index].value, pouch[index].color);
        // Remove the selected die from the pouch
        pouch[index] = pouch[*pouchSize - 1];
        (*pouchSize)--;
    }
}

void printRemainingDice(RolledDice rolledDice,int t) {
    printf("\nRemaining dice:\n");
    for (int i = 0; i < rolledDice.size; i++) {
        if((rolledDice.size>1)&&(t==1)){
            printf("%d. Value %d, Color %s\n", i + 1, rolledDice.rolled[i].value, rolledDice.rolled[i].color);
        }
        else{
            printf("Die Value %d, Color %s was not picked\n", rolledDice.rolled[i].value, rolledDice.rolled[i].color);
        }
    }
}

void printWindowFace(WindowFace window, int o){
    if(o==1){
        printf("\nDificulty %d\n",window.dificulty);
    }
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            switch (window.grid[i][j].color[0])
            {
            case 'R':
                printf(RED "%d " RESET, window.grid[i][j].value);
                break;
            case 'Y':
                printf(YEL "%d " RESET, window.grid[i][j].value);
                break;
            case 'G':
                printf(GRN "%d " RESET, window.grid[i][j].value);
                break;
            case 'B':
                printf(BLU "%d " RESET, window.grid[i][j].value);
                break;
            case 'P':
                printf(PRP "%d " RESET, window.grid[i][j].value);
                break;
            default:
                printf("%d ", window.grid[i][j].value);
            }
        }
        printf("\n");
    }
}

void initializeFrontFace(Windows *window,int c){
    if(c==0){//test
        window->frontFace.grid[0][0].value = 1;
        window->frontFace.grid[0][1].value = 0;
        window->frontFace.grid[0][2].value = 2;
        window->frontFace.grid[0][3].value = 0;
        window->frontFace.grid[0][4].value = 0;
        window->frontFace.grid[1][0].value = 2;
        window->frontFace.grid[1][1].value = 0;
        window->frontFace.grid[1][2].value = 0;
        window->frontFace.grid[1][3].value = 2;
        window->frontFace.grid[1][4].value = 2;
        window->frontFace.grid[2][0].value = 3;
        window->frontFace.grid[2][1].value = 2;
        window->frontFace.grid[2][2].value = 1;
        window->frontFace.grid[2][3].value = 5;
        window->frontFace.grid[2][4].value = 6;
        window->frontFace.grid[3][0].value = 4;
        window->frontFace.grid[3][1].value = 6;
        window->frontFace.grid[3][2].value = 0;
        window->frontFace.grid[3][3].value = 0;
        window->frontFace.grid[3][4].value = 4;

        strcpy( window->frontFace.grid[0][1].color, "Pueple");
        strcpy( window->frontFace.grid[0][0].color, "Red");
        strcpy( window->frontFace.grid[1][0].color, "Red");
        strcpy( window->frontFace.grid[2][1].color, "Purple");
        strcpy( window->frontFace.grid[3][0].color, "Blue");
        strcpy( window->frontFace.grid[2][4].color, "Yelllow");
        strcpy( window->frontFace.grid[2][0].color, "Green");
        strcpy( window->frontFace.grid[2][3].color, "Red");
        strcpy( window->frontFace.grid[2][2].color, "Blue");
        strcpy( window->frontFace.grid[1][2].color, "Blue");
        strcpy( window->frontFace.grid[0][4].color, "Blue");
        strcpy( window->frontFace.grid[1][4].color, "Blue");
        strcpy( window->frontFace.grid[3][4].color, "Blue");

        window->frontFace.dificulty = 4;
    }
    else if(c==1){//Kuliholen 1
        window->frontFace.grid[0][0].value = 0;
        window->frontFace.grid[0][1].value = 0;
        window->frontFace.grid[0][2].value = 4;
        window->frontFace.grid[0][3].value = 0;
        window->frontFace.grid[0][4].value = 0;
        window->frontFace.grid[1][0].value = 0;
        window->frontFace.grid[1][1].value = 5;
        window->frontFace.grid[1][2].value = 0;
        window->frontFace.grid[1][3].value = 0;
        window->frontFace.grid[1][4].value = 1;
        window->frontFace.grid[2][0].value = 0;
        window->frontFace.grid[2][1].value = 2;
        window->frontFace.grid[2][2].value = 0;
        window->frontFace.grid[2][3].value = 6;
        window->frontFace.grid[2][4].value = 0;
        window->frontFace.grid[3][0].value = 0;
        window->frontFace.grid[3][1].value = 0;
        window->frontFace.grid[3][2].value = 0;
        window->frontFace.grid[3][3].value = 3;
        window->frontFace.grid[3][4].value = 0;

        strcpy( window->frontFace.grid[0][1].color, "Y");
        strcpy( window->frontFace.grid[0][3].color, "B");
        strcpy( window->frontFace.grid[0][4].color, "Red");
        strcpy( window->frontFace.grid[1][0].color, "Red");
        strcpy( window->frontFace.grid[1][2].color, "Y");
        strcpy( window->frontFace.grid[1][3].color, "G");
        strcpy( window->frontFace.grid[2][0].color, "P");
        strcpy( window->frontFace.grid[2][4].color, "P");
        strcpy( window->frontFace.grid[3][0].color, "B");
        strcpy( window->frontFace.grid[3][1].color, "G");

        window->frontFace.dificulty = 6;
    }
    else{//Kuliholen 3
        window->frontFace.grid[0][0].value = 0;
        window->frontFace.grid[0][1].value = 0;
        window->frontFace.grid[0][2].value = 0;
        window->frontFace.grid[0][3].value = 0;
        window->frontFace.grid[0][4].value = 0;
        window->frontFace.grid[1][0].value = 0;
        window->frontFace.grid[1][1].value = 0;
        window->frontFace.grid[1][2].value = 0;
        window->frontFace.grid[1][3].value = 0;
        window->frontFace.grid[1][4].value = 0;
        window->frontFace.grid[2][0].value = 0;
        window->frontFace.grid[2][1].value = 0;
        window->frontFace.grid[2][2].value = 0;
        window->frontFace.grid[2][3].value = 0;
        window->frontFace.grid[2][4].value = 0;
        window->frontFace.grid[3][0].value = 0;
        window->frontFace.grid[3][1].value = 0;
        window->frontFace.grid[3][2].value = 0;
        window->frontFace.grid[3][3].value = 0;
        window->frontFace.grid[3][4].value = 0;

        strcpy( window->frontFace.grid[0][0].color, "G");
        strcpy( window->frontFace.grid[0][1].color, "Y");
        strcpy( window->frontFace.grid[0][2].color, "B");
        strcpy( window->frontFace.grid[0][3].color, "Red");
        strcpy( window->frontFace.grid[0][4].color, "P");
        strcpy( window->frontFace.grid[1][0].color, "Y");
        strcpy( window->frontFace.grid[1][2].color, "G");
        strcpy( window->frontFace.grid[1][4].color, "Red");
        strcpy( window->frontFace.grid[2][0].color, "P");
        strcpy( window->frontFace.grid[2][1].color, "B");
        strcpy( window->frontFace.grid[2][3].color, "G");
        strcpy( window->frontFace.grid[2][4].color, "Y");
        strcpy( window->frontFace.grid[3][0].color, "B");
        strcpy( window->frontFace.grid[3][2].color, "P");
        strcpy( window->frontFace.grid[3][4].color, "Red");
        
        
        window->frontFace.dificulty = 4;
    }

    for (int i = 0; i < NUM_ROWS; i++){
        for (int j = 0; j < NUM_COLS; j++){
            if (    window->frontFace.grid[i][j].color[0] == '\0') {
                    window->frontFace.grid[i][j].color[0] = '\0';
            }
        }
    }
}

void initializeBackFace(Windows *window,int c){
    if(c==0){//test
        window->backFace.grid[0][0].value = 0;
        window->backFace.grid[0][1].value = 0;
        window->backFace.grid[0][2].value = 0;
        window->backFace.grid[0][3].value = 3;
        window->backFace.grid[0][4].value = 0;
        window->backFace.grid[1][0].value = 0;
        window->backFace.grid[1][1].value = 0;
        window->backFace.grid[1][2].value = 6;
        window->backFace.grid[1][3].value = 0;
        window->backFace.grid[1][4].value = 0;
        window->backFace.grid[2][0].value = 4;
        window->backFace.grid[2][1].value = 0;
        window->backFace.grid[2][2].value = 0;
        window->backFace.grid[2][3].value = 0;
        window->backFace.grid[2][4].value = 0;
        window->backFace.grid[3][0].value = 0;
        window->backFace.grid[3][1].value = 0;
        window->backFace.grid[3][2].value = 0;
        window->backFace.grid[3][3].value = 2;
        window->backFace.grid[3][4].value = 3;

        strcpy( window->backFace.grid[0][1].color, "Red");
        strcpy( window->backFace.grid[2][1].color, "Purple");

        window->backFace.dificulty = 2;
    }
    else if(c==1){//Kuliholen 6
        window->backFace.grid[0][0].value = 0;
        window->backFace.grid[0][1].value = 5;
        window->backFace.grid[0][2].value = 0;
        window->backFace.grid[0][3].value = 0;
        window->backFace.grid[0][4].value = 2;
        window->backFace.grid[1][0].value = 0;
        window->backFace.grid[1][1].value = 0;
        window->backFace.grid[1][2].value = 5;
        window->backFace.grid[1][3].value = 2;
        window->backFace.grid[1][4].value = 0;
        window->backFace.grid[2][0].value = 0;
        window->backFace.grid[2][1].value = 0;
        window->backFace.grid[2][2].value = 2;
        window->backFace.grid[2][3].value = 5;
        window->backFace.grid[2][4].value = 0;
        window->backFace.grid[3][0].value = 0;
        window->backFace.grid[3][1].value = 2;
        window->backFace.grid[3][2].value = 0;
        window->backFace.grid[3][3].value = 0;
        window->backFace.grid[3][4].value = 5;

        strcpy( window->backFace.grid[0][0].color, "Y");
        strcpy( window->backFace.grid[0][3].color, "P");
        strcpy( window->backFace.grid[1][0].color, "B");
        strcpy( window->backFace.grid[1][1].color, "G");
        strcpy( window->backFace.grid[1][4].color, "P");
        strcpy( window->backFace.grid[2][0].color, "G");
        strcpy( window->backFace.grid[2][1].color, "B");
        strcpy( window->backFace.grid[2][4].color, "Red");
        strcpy( window->backFace.grid[3][0].color, "Y");
        strcpy( window->backFace.grid[3][3].color, "Red");

        window->backFace.dificulty = 6;
    }
    else{//Vitraux
        window->backFace.grid[0][0].value = 3;
        window->backFace.grid[0][1].value = 0;
        window->backFace.grid[0][2].value = 0;
        window->backFace.grid[0][3].value = 0;
        window->backFace.grid[0][4].value = 2;
        window->backFace.grid[1][0].value = 0;
        window->backFace.grid[1][1].value = 0;
        window->backFace.grid[1][2].value = 6;
        window->backFace.grid[1][3].value = 0;
        window->backFace.grid[1][4].value = 0;
        window->backFace.grid[2][0].value = 0;
        window->backFace.grid[2][1].value = 0;
        window->backFace.grid[2][2].value = 1;
        window->backFace.grid[2][3].value = 0;
        window->backFace.grid[2][4].value = 0;
        window->backFace.grid[3][0].value = 0;
        window->backFace.grid[3][1].value = 5;
        window->backFace.grid[3][2].value = 0;
        window->backFace.grid[3][3].value = 4;
        window->backFace.grid[3][4].value = 0;

        strcpy( window->backFace.grid[0][2].color, "R");
        strcpy( window->backFace.grid[1][1].color, "G");
        strcpy( window->backFace.grid[1][3].color, "P");
        strcpy( window->backFace.grid[2][0].color, "Y");
        strcpy( window->backFace.grid[2][4].color, "B");

        window->backFace.dificulty = 5;
    }

    for (int i = 0; i < NUM_ROWS; i++){
        for (int j = 0; j < NUM_COLS; j++){
            if (    window->backFace.grid[i][j].color[0] == '\0') {
                    window->backFace.grid[i][j].color[0] = '\0';
            }
        }
    }
}

void addfirstDieToWindow(PlayerWindow *player, Dice chosenDie){
    int row, col;
    printWindowFace(player->chosenWindow,0);
    printf("Choose a corner to place the die (11 15 41 45)");
    scanf("%d%d", &row, &col);

    int corner= row*10 +col;
    if(corner==11 || corner==15 || corner==41 || corner==45){
        // Check if the chosen cell is valid
        if (row < 1 || row > NUM_ROWS || col < 1 || col > NUM_COLS)
        {
            printf("Invalid cell. Please choose a valid row and column.\n");
            addfirstDieToWindow(player, chosenDie);
            return;
        }

        // Check if the chosen cell is empty
        if (player->chosenWindow.grid[row - 1][col - 1].value != 0 && (player->chosenWindow.grid[row - 1][col - 1].color[0] == 'R' || player->chosenWindow.grid[row - 1][col - 1].color[0] == 'Y' || player->chosenWindow.grid[row - 1][col - 1].color[0] == 'G' || player->chosenWindow.grid[row - 1][col - 1].color[0] == 'B' || player->chosenWindow.grid[row - 1][col - 1].color[0] == 'P'))
        {
            printf("The chosen cell is already occupied. Please choose an empty cell.\n");
            addfirstDieToWindow(player, chosenDie);
            return;
        } 

        // Check for value restriction
        if (player->chosenWindow.grid[row - 1][col - 1].value != 0 && chosenDie.value != player->chosenWindow.grid[row - 1][col - 1].value)
        {
            printf("The chosen cell has a restriction on value. Please choose a die with value %d.\n", player->chosenWindow.grid[row - 1][col - 1].value);
            addfirstDieToWindow(player, chosenDie);
            return;
        }

        // Check for color restriction
        if(player->chosenWindow.grid[row - 1][col - 1].color[0]=='R' || player->chosenWindow.grid[row - 1][col - 1].color[0]=='Y' || player->chosenWindow.grid[row - 1][col - 1].color[0]=='G' || player->chosenWindow.grid[row - 1][col - 1].color[0]=='B' || player->chosenWindow.grid[row - 1][col - 1].color[0]=='P'){
            if (player->chosenWindow.grid[row - 1][col - 1].value == 0 && player->chosenWindow.grid[row - 1][col - 1].color[0] != chosenDie.color[0])
            {
                printf("The chosen cell has a restriction on color. Please choose a die with color %s.\n", player->chosenWindow.grid[row - 1][col - 1].color);
                addfirstDieToWindow(player, chosenDie);
                return;
            }
        }
    }
    else{
        printf("CHOOSE A CORNER\n");
        addfirstDieToWindow(player, chosenDie);
    }

    // Place the die in the chosen cell
    player->chosenWindow.grid[row - 1][col - 1].value = chosenDie.value;
    strcpy(player->chosenWindow.grid[row - 1][col - 1].color, chosenDie.color);

    printf("Updated Window:\n");
    printWindowFace(player->chosenWindow,0);
}

void addDieToWindow(PlayerWindow *player, Dice chosenDie){ 
    int row, col,adjacent=1;
    printWindowFace(player->chosenWindow,0);
    printf("Choose a row (1-%d) and column (1-%d) to place the die: ", NUM_ROWS, NUM_COLS);
    scanf("%d %d", &row, &col);
    row-=1;
    col-=1;
    int value=player->chosenWindow.grid[row][col].value;
    char color=player->chosenWindow.grid[row][col].color[0];

    // Check if the chosen cell is valid
    if (row < 0 || row > NUM_ROWS || col < 0 || col > NUM_COLS)
    {
        printf("Invalid cell. Please choose a valid row and column.\n");
        addDieToWindow(player, chosenDie);
        return;
    }

    if(adjacent==1){
        // Check if the chosen cell is empty
        if (value != 0 && (color == 'R' || color == 'Y' || color == 'G' || color == 'B' || color == 'P'))
        {
            printf("The chosen cell is already occupied. Please choose an empty cell.\n");
            addDieToWindow(player, chosenDie);
            return;
        } 
        // Check for value restriction
        if (value != 0 && chosenDie.value != value)
        {
            printf("The chosen cell has a restriction on value. Please choose a die with value %d.\n",value);
            addDieToWindow(player, chosenDie);
            return;
        }

        if(color =='R' ||color =='Y' || color =='G' || color =='B' || color =='P'){
            if (value == 0 && color != chosenDie.color[0])
            {
                printf("The chosen cell has a restriction on color. Please choose a die with color %s.\n", player->chosenWindow.grid[row][col].color);
                addDieToWindow(player, chosenDie);
                return;
            }
        }
    }
    else{
        addDieToWindow(player, chosenDie);
    }

    // Place the die in the chosen cell
    player->chosenWindow.grid[row][col].value = chosenDie.value;
    strcpy(player->chosenWindow.grid[row][col].color, chosenDie.color);

    printf("Updated Window:\n");
    printWindowFace(player->chosenWindow,0);
}

int* randomNumber(int pro, int size) {
    int* selected = (int*)malloc(size * sizeof(int));
    if (selected == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    int count = 0;

    while (count < size) {
        int num = rand() % pro;
        int isUnique = 1;

        // Check if the number is already selected
        for (int i = 0; i < count; i++) {
            if (selected[i] == num) {
                isUnique = 0;
                break;
            }
        }

        // If the number is unique, add it to the selected array
        if (isUnique) {
            selected[count] = num;
            count++;
        }
    }
    return selected;
}

void InitializePublicObjectives(PublicGoals *publicGoals) {
    srand(time(NULL));
    int size=3;
    int *selected=randomNumber(10,size);

    for (int i = 0; i < size; i++) {
        switch (selected[i]) {
            case 0:
                publicGoals[i].id = 0;
                publicGoals[i].points = 6;
                strcpy(publicGoals[i].description, "Rows with no repeated colors");
                break;
            case 1:
                publicGoals[i].id = 1;
                publicGoals[i].points = 4;
                strcpy(publicGoals[i].description, "Columns with no repeated values");
                break;
            case 2:
                publicGoals[i].id = 2;
                publicGoals[i].points = 5;
                strcpy(publicGoals[i].description, "Rows with no repeated values");
                break;
            case 3:
                publicGoals[i].id = 3;
                publicGoals[i].points = 5;
                strcpy(publicGoals[i].description, "Columns with no repeated colors");
                break;
            case 4:
                publicGoals[i].id = 4;
                publicGoals[i].points = 7;
                strcpy(publicGoals[i].description, "Diagonals with no repeated colors");
                break;
            case 5:
                publicGoals[i].id = 5;
                publicGoals[i].points = 2;
                strcpy(publicGoals[i].description, "Sets of 1 & 2 values anywhere");
                break;
            case 6:
                publicGoals[i].id = 6;
                publicGoals[i].points = 2;
                strcpy(publicGoals[i].description, "Sets of 3 & 4 values anywhere");
                break;
            case 7:
                publicGoals[i].id = 7;
                publicGoals[i].points = 2;
                strcpy(publicGoals[i].description, "Sets of 5 & 6 values anywhere");
                break;
            case 8:
                publicGoals[i].id = 8;
                publicGoals[i].points = 5;
                strcpy(publicGoals[i].description, "Sets of one of each value anywhere");
                break;
            case 9:
                publicGoals[i].id = 9;
                publicGoals[i].points = 4;
                strcpy(publicGoals[i].description, "Sets of one of each color anywhere");
                break;
            default:
                break;
        }
    }

    printf("\nPublic Objectives:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s (%d points)\n", i + 1, publicGoals[i].description, publicGoals[i].points);
    }
}

void PrintPublicObjectives(PublicGoals *publicGoals) {
    printf("\nPublic Objectives:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s (%d points)\n", i + 1, publicGoals[i].description, publicGoals[i].points);
    }
}

void Scoring(PlayerWindow *player,int x,PublicGoals *publicGoals){
    int a=publicGoals[0].id,b=publicGoals[1].id,c=publicGoals[2].id;
    int t0,t2;                          //condition for pb 0 and 2
    int d1=0,d2=0,d3=0,d4=0,d5=0,d6=0;  //number of dies of each number
    player[x].score=0;

    for(int i=0;i<NUM_ROWS;i++){
        t0=0;
        t2=0;
        for(int j=0;j<NUM_COLS;j++){
            int value = player->chosenWindow.grid[i][j].value;
            char color=player->chosenWindow.grid[i][j].color[0];
            if (value != 0 && (color == 'R' || color == 'Y' || color == 'G' || color == 'B' || color == 'P'))
            {
                player[x].score+=0;
                if(player[x].PrivateGoal==player->chosenWindow.grid[i][j].color[0]){
                    player[x].score+=0;
                }
                //Rows with no repeated colors
                if(a==0||b==0||c==0){
                    if( color !='\0'){
                        t0++;
                        if(t0==5){
                            if (player->chosenWindow.grid[i][0].color[0] != player->chosenWindow.grid[i][1].color[0] &&
                                player->chosenWindow.grid[i][0].color[0] != player->chosenWindow.grid[i][2].color[0] &&
                                player->chosenWindow.grid[i][0].color[0] != player->chosenWindow.grid[i][3].color[0] &&
                                player->chosenWindow.grid[i][0].color[0] != player->chosenWindow.grid[i][4].color[0] &&
                                player->chosenWindow.grid[i][1].color[0] != player->chosenWindow.grid[i][2].color[0] &&
                                player->chosenWindow.grid[i][1].color[0] != player->chosenWindow.grid[i][3].color[0] &&
                                player->chosenWindow.grid[i][1].color[0] != player->chosenWindow.grid[i][4].color[0] &&
                                player->chosenWindow.grid[i][2].color[0] != player->chosenWindow.grid[i][3].color[0] &&
                                player->chosenWindow.grid[i][2].color[0] != player->chosenWindow.grid[i][4].color[0] &&
                                player->chosenWindow.grid[i][3].color[0] != player->chosenWindow.grid[i][4].color[0]) 
                                    {
                                        player[x].score+=6;
                                    }
                        }
                    }
                }
                //columns with no repeted value
                if((a==1||b==1||c==1)&&(i==0)){
                    if(player->chosenWindow.grid[0][j].value!=0 && player->chosenWindow.grid[1][j].value!=0 && player->chosenWindow.grid[2][j].value!=0 && player->chosenWindow.grid[3][j].value!=0){
                        if (player->chosenWindow.grid[0][j].value != player->chosenWindow.grid[1][j].value &&
                            player->chosenWindow.grid[0][j].value != player->chosenWindow.grid[2][j].value &&
                            player->chosenWindow.grid[0][j].value != player->chosenWindow.grid[3][j].value &&
                            player->chosenWindow.grid[1][j].value != player->chosenWindow.grid[2][j].value &&
                            player->chosenWindow.grid[1][j].value != player->chosenWindow.grid[3][j].value &&
                            player->chosenWindow.grid[2][j].value != player->chosenWindow.grid[3][j].value)
                                    {
                                        player[x].score+=4;
                                    }
                    }
                }
                //rows with no repeated values
                if(a==2||b==2||c==2){
                    if(value !=0){
                        t2++;
                        if(t2==5){
                            if (player->chosenWindow.grid[i][0].value != player->chosenWindow.grid[i][1].value &&
                                player->chosenWindow.grid[i][0].value != player->chosenWindow.grid[i][2].value &&
                                player->chosenWindow.grid[i][0].value != player->chosenWindow.grid[i][3].value &&
                                player->chosenWindow.grid[i][0].value != player->chosenWindow.grid[i][4].value &&
                                player->chosenWindow.grid[i][1].value != player->chosenWindow.grid[i][2].value &&
                                player->chosenWindow.grid[i][1].value != player->chosenWindow.grid[i][3].value &&
                                player->chosenWindow.grid[i][1].value != player->chosenWindow.grid[i][4].value &&
                                player->chosenWindow.grid[i][2].value != player->chosenWindow.grid[i][3].value &&
                                player->chosenWindow.grid[i][2].value != player->chosenWindow.grid[i][4].value &&
                                player->chosenWindow.grid[i][3].value != player->chosenWindow.grid[i][4].value) 
                                    {
                                        player[x].score+=5;
                                    }
                        }
                    }
                }
                //columns with no repeated color
                if((a==3||b==3||c==3)&&(i==0)){
                    if( player->chosenWindow.grid[0][j].color[0]!='\0' && player->chosenWindow.grid[1][j].color[0]!='\0' && player->chosenWindow.grid[2][j].color[0]!='\0' && player->chosenWindow.grid[3][j].color[0]!='\0'){
                        if (player->chosenWindow.grid[0][j].color[0] != player->chosenWindow.grid[1][j].color[0] &&
                            player->chosenWindow.grid[0][j].color[0] != player->chosenWindow.grid[2][j].color[0] &&
                            player->chosenWindow.grid[0][j].color[0] != player->chosenWindow.grid[3][j].color[0] &&
                            player->chosenWindow.grid[1][j].color[0] != player->chosenWindow.grid[2][j].color[0] &&
                            player->chosenWindow.grid[1][j].color[0] != player->chosenWindow.grid[3][j].color[0] &&
                            player->chosenWindow.grid[2][j].color[0] != player->chosenWindow.grid[3][j].color[0])
                                    {
                                        player[x].score+=5;
                                    }
                    }
                }
                switch (value){
                    case 1:
                        d1++;
                        break;
                    case 2:
                        d2++;
                        break;
                    case 3:
                        d3++;
                        break;
                    case 4:
                        d4++;
                        break;
                    case 5:
                        d5++;
                        break;
                    case 6:
                        d6++;
                        break;
                    default:
                        printf("I am uselees here :)\n");
                        break;
                }
            //end of checking a die
            }
        }
    }
    //pairs of number 
    if(a==5||b==5||c==5){
        if(d1>d2){
            player[x].score+=2*d2;
        }
        else{
            player[x].score+=2*d1;
        }
    }
    if(a==6||b==6||c==6){
        if(d3>d4){
            player[x].score+=2*d4;
        }
        else{
            player[x].score+=2*d3;
        }
    }
    if(a==7||b==7||c==7){
        if(d5>d6){
            player[x].score+=2*d6;
        }
        else{
            player[x].score+=2*d5;
        }
    }
    
    //to be determened
    if(a==8||b==8||c==8){
        
    }
    if(a==9||b==9||c==9){
    }

    printf("Player %d has %d points\n",x+1,player[x].score); 
}

int main(){
    Windows window;
    int players;
    printf("Nr of players: ");
    scanf("%d", &players);
    if (players > 4)
    {
        printf("too many players");
        return -1;
    }

    PlayerWindow player[players];
    int choice;
    int c;
    srand(time(NULL));

    // Choosing windows
    for (int i = 0; i < players; i++){
        int *w=randomNumber(3,players);
        initializeFrontFace(&window,w[i]);
        initializeBackFace(&window,w[i]);

        printWindowFace(window.frontFace,1);
        printWindowFace(window.backFace,1);
        printf("Player %d, choose a window (1 for front, 2 for back): ", i + 1);
        scanf("%d", &choice);

        if (choice == 1){
            player[i].chosenWindow = window.frontFace;
            player[i].helperGems = window.frontFace.dificulty;
        }
        else if (choice == 2){
            player[i].chosenWindow = window.backFace;
            player[i].helperGems = window.backFace.dificulty;
        }
        else{
            printf("Invalid choice.\n");
            return -1;
        }
        char color;
        do
        {
            color = colors[rand() % NUM_COLORS];
        } while (isColorUsed(color, player, i));
        player[i].PrivateGoal = color;
        player[i].score = 0;
        printf("Player's %d Private goal is: %c\n", i + 1, player[i].PrivateGoal);
        printf("Player %d has %d gems\n", i + 1, player[i].helperGems);
    }

    RolledDice rolledDice;
    rolledDice.size = 0;
    Dice pouch[NUM_DICE];
    int pouchSize = NUM_DICE;
    initializePouch(pouch);
    shuffle(pouch, NUM_DICE);
    int rolls = 2 * players + 1;
    int turns = 0;
    PublicGoals publicGoals[3];
    InitializePublicObjectives(publicGoals);

    for (int round = 1; round <= 5; round++){
        printf("\nTurn number %d\n",round);
        printf("Rolled dies:\n");
        rolledDice.size = 0;
        drawDice(pouch, rolls, &pouchSize, &rolledDice);
        // Clockwise turns
        for (int i = 1; i <= players; i++){
            if (i == 1){
                turns++;
            }
            printf("\nIt's player %d's turn\n", i);
            printf("0-pass \n1-choose die \n2-check public goals\n");
            scanf("%d", &choice);
            if (choice >2){
                printf("Invalid choice.\n");
                return 0;
            }
            else if(choice==1){
                printf("Choose a die (1-%d): ", rolledDice.size);
                int die;
                scanf("%d", &die);
                if (die > rolledDice.size){
                    printf("Invalid choice.\n");
                    return 1;
                }
                else{
                    printf("Player %d has chosen a die with value %d, color %s\n", i, rolledDice.rolled[die - 1].value, rolledDice.rolled[die - 1].color);
                    if(round==1){
                        addfirstDieToWindow(&player[i-1], rolledDice.rolled[die - 1]);
                        //addDieToWindow(&player[i-1], rolledDice.rolled[die - 1]);
                    }
                    else{
                        addDieToWindow(&player[i-1], rolledDice.rolled[die - 1]);
                    }
                    // Remove the selected die from the rolled dice
                    for (int j = die - 1; j < rolledDice.size - 1; j++){
                       rolledDice.rolled[j] = rolledDice.rolled[j + 1];
                    }
                    (rolledDice.size)--;
                }
                printRemainingDice(rolledDice,1);
            }
            else if(choice==2){
                PrintPublicObjectives(publicGoals);
            }
            else{
                printf("player %d passed\n",i);
            }
        }

        // Counterclockwise turns
        for (int i = players; i > 0; i--){
            if (i == 1){
                turns++;
            }
            printf("\nIt's player %d's turn\n", i);
            printf("0-pass \n1-choose die \n2-check public goals\n");
            scanf("%d", &choice);
            if (choice >2){
                printf("Invalid choice.\n");
                return 0;
            }
            else if(choice==1){
                printf("Choose a die (1-%d): ", rolledDice.size);
                int die;
                scanf("%d", &die);
                if (die > rolledDice.size)
                {
                    printf("Invalid choice.\n");
                    return 1;
                }
                else{
                    printf("Player %d has chosen a die with value %d, color %s\n", i, rolledDice.rolled[die - 1].value, rolledDice.rolled[die - 1].color);
                    addDieToWindow(&player[i - 1], rolledDice.rolled[die - 1]);

                    // Remove the selected die from the rolled dice
                    for (int j = choice - 1; j < rolledDice.size - 1; j++){
                       rolledDice.rolled[j] = rolledDice.rolled[j + 1];
                    }
                    (rolledDice.size)--;
                }
                printRemainingDice(rolledDice,1);
            }
            else if(choice==2){
                PrintPublicObjectives(publicGoals);
            }
            else{
                printf("player %d passed\n",i);
            }

        }
        printRemainingDice(rolledDice,0);
        while(rolledDice.size>0){
            (rolledDice.size)--;
        }
    }
    
    for(int i=0;i<players;i++){
        Scoring(&player[i],i,publicGoals);
    }
    return 0;
}



