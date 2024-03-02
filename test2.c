#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#define WIDTH 80
#define HEIGHT 25

void initializeField(char (*field)[WIDTH]);
void displayGame(char (*field)[WIDTH]);
int countNeighbors(char (*field)[WIDTH], int x, int y);
void updateGame(char (*field)[WIDTH], char (*newField)[WIDTH]);

int main() {
    char field[HEIGHT][WIDTH];
    char newField[HEIGHT][WIDTH];

    /*     char **field = malloc(HEIGHT * sizeof(char *));
    for (int i = 0; i < HEIGHT; i++) {
        field[i] = malloc(WIDTH * sizeof(char));}
    
    char **newField = malloc(HEIGHT * sizeof(char *));
    for (int i = 0; i < HEIGHT; i++) {
        newField[i] = malloc(WIDTH * sizeof(char));} */ 
    //хотел выделить память динамически, по времени не успел адаптировать код
    
    initializeField(field);
    
    while (1) {
        displayGame(field);
        updateGame(field, newField);
        int key = getch();
        int speed = 1000000;
        usleep(speed); 
        if (key >= '1' && key <= '4') {
             int key = getch();
        if (key >= '1' && key <= '4') {
            switch (key) {
                case 1:
                    speed = 1000000;
                    break;
                case 2:
                    speed = 2000000;
                    break;
                case 3:
                    speed = 3000000;
                    break;
                case 4:
                    speed = 9000000;
                    break;
                case 'p':
                    speed = 0;
                default:
                    break;
            }
        
    }
        }
    return 0;
    }
}

void initializeField(char (*field)[WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = ' ';
        }
    }
    //заполняем пробелами

    printf("Введите клетки в чашку петри: ");
    int numLiveCells;
    scanf("%d", &numLiveCells);
    char input;
    srand(time(NULL));
    for (int k = 0; k < numLiveCells; k++) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        field[y][x] = '#';
    }
}
// с помощью рандома заполняем шарпами матрицу

void displayGame(char (*field)[WIDTH]) {
    system("clear");
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", field[i][j]);
        }
        printf("\n");
    }
}
// выводим игру притф

int countNeighbors(char (*field)[WIDTH], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (!(i == 0 && j == 0) && field[(x + i + HEIGHT) % HEIGHT][(y + j + WIDTH) % WIDTH] == '#') {
                count++;
            }
        }
    }
    return count;
}
//итерируется по соседним клеткам вокруг точки (x, y) (включая саму точку), и если клетка содержит живую ячейку ('#'), увеличивает счетчик count.


void updateGame(char (*field)[WIDTH], char (*newField)[WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int neighbors = countNeighbors(field, i, j);
            
            if (field[i][j] == '#' && (neighbors < 2 || neighbors > 3)) {
                newField[i][j] = ' ';
            } else if (field[i][j] == ' ' && neighbors == 3) {
                newField[i][j] = '#';
            } else {
                newField[i][j] = field[i][j];
            }
        }
    }
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = newField[i][j];
        }
    }
}

// вычисляя количество соседей каждой клетки с помощью функции countNeighbors, и обновляет состояние клетки в массиве newField. 
//После этого она копирует данные из массива newField обратно в массив field, чтобы обновить текущее поле.