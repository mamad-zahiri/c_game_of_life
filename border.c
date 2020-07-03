#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<time.h>

void draw(void *u, int w, int h)
{

    char (*world)[w] = u;

    // for clean the screen for each print
    system("clear");

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {

            if (x == 0 || x == w-1 || y == 0 ||  y == w-1) {
                printf(" *");
                // printf("\e[40m *");
            } else {
            // printf(world[y][x] ? "\e[46m  " : "\e[47m +");
            printf(world[y][x] ? " +" : "  ");
            // printf(world[y][x] ? " \u25A0" : " \u2574");

            }
        }
            printf("\n");
    }
}


void evolution(void *u, int w, int h)
{
    char (*world)[w] = u;
    char new[w][h];

    for (int x = 1; x < w - 1; x++) 
        for (int y = 1; y < h - 1; y++) {

            int lives = 0;

            for (int xd = x - 1; xd <= x + 1; xd++) 
                for (int yd =  y - 1; yd <= y + 1; yd++) 
                    if (world[(yd + h) % h][(xd + w) % w])
                        lives++;
                    
    
            if (world[y][x]) lives--;

            new[y][x] = (lives == 3 || (lives == 2 && world[y][x]));

        }
    
    for (int x = 0; x < w; x++) 
        for (int y = 0; y < h; y++) 
            world[y][x] = new[y][x];

}


int main()
{
    int w = 40;
    int h = w;

    char world[w][h];

    srand(time(0));

    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
            world[y][x] = rand() < RAND_MAX / 3 ? 1 : 0;

    while (1) {
        draw(world, w, h);
        evolution(world, w, h);
        usleep(200000);
    }
    
    return 0;
}