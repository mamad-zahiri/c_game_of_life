#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<time.h>

void draw(void *u, int w, int h)
{

    char (*world)[w] = u;

    // for clean the screen for each print
    system("clear");
    printf("\n------------------------------\n");
    
    for (int y = 0; y < h; y ++) {
        for (int x = 0; x < w; x ++)
            // printf(world[y][x] ? "#" : " ");
            // printf((world[y][x]) ? "1" : "0");
            printf(world[y][x] ? "@" : " ");
            // printf(world[y][x] ? "\e[47m " : "\e[40m ");
            // printf(world[y][x] ? "\u25A0" : "\u25A1");
        printf("\n");
    }
    printf("------------------------------\n");


}


void evolution(void *u, int w, int h)
{
    char (*world)[w] = u;
    char new[w][h];

    for (int x = 0; x < w; x++) 
        for (int y = 0; y < h; y++) {
            int lives = 0;
            for (int xd = x - 1; xd <= x + 1; xd++) 
                for (int yd =  y - 1; yd <= y + 1; yd++) 
                    if (world[(yd + h) % h][(xd + w) % w])
                        lives++;
                    
    
            if (world[y][x]) lives--;

            new[y][x] = (lives==3 || (lives==2 && world[y][x]));

        }
    
    for (int x = 0; x < w; x++) 
        for (int y = 0; y < h; y++) 
            world[y][x] = new[y][x];

}


int main()
{
    int w = 52;
    int h = 52;

    char world[w][h];

    srand(time(0));

    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
            world[y][x] = rand() < RAND_MAX / 3 ? 1 : 0;

    while (1) {
        draw(world, w, h);
        evolution(world, w, h);
        usleep(100000);
    }

    return 0;
}
