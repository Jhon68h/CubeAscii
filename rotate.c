#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 160
#define HEIGHT 44
#define BUFFER_SIZE (WIDTH * HEIGHT)

float cubeWidth = 20.0;
float A = 0.0, B = 0.0, C = 0.0;
float k1 = 40.0;
float speed = 0.5;
float distance = 100.0;
float x, y, z;
int xp, yp;
char zbuffer[BUFFER_SIZE];
char buffer[BUFFER_SIZE];


float rotateX(int i, int j, int k) {
  return j * sin(A) * sin(B) * cos(C)
       - k * cos(A) * sin(B) * cos(C) 
       + j * cos(A) * sin(C) 
       + k * sin(A) * sin(C) 
       + i * cos(B) * cos(C);
}

float rotateY(int i, int j, int k) {
  return   j * cos(A) * cos(C) 
         + k * sin(A) * cos(C) 
         - j * sin(A) * sin(B) * sin(C) 
         + k * cos(A) * sin(B) * sin(C) 
         - i * cos(B) * sin(C);
}

float rotateZ(int i, int j, int k) {
  return k * cos(A) * cos(B) 
         - j * sin(A) * cos(B) 
         + i * sin(B);
}

void surface(float cubeX, float cubeY, float cubeZ, int ch) {

    x = rotateX(cubeX, cubeY, cubeZ);
    y = rotateY(cubeX, cubeY, cubeZ);
    z = rotateZ(cubeX, cubeY, cubeZ) + distance;
    float invz = 1 / z;
    xp = (int)(WIDTH / 2 + k1 * invz * x * 2);
    yp = (int)(HEIGHT / 2 + k1 * invz * y);

    int idx = xp + yp * WIDTH;
    if (idx >= 0 && idx < BUFFER_SIZE) {
        if (invz > zbuffer[idx]) {
            zbuffer[idx] = invz;
            buffer[idx] = ch;
        }
    }
}

int main(){
    printf("\x1b[2J"); // Clear screen

    while (1) {
        memset(buffer, ' ', BUFFER_SIZE);
        memset(zbuffer, 0, BUFFER_SIZE);
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += speed) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += speed) {
                surface(cubeX, cubeY, -cubeWidth, '@');
                surface(cubeWidth, cubeY, cubeX, '$');
                surface(-cubeWidth, cubeY, -cubeX, '~');
                surface(-cubeX, cubeY, cubeWidth, '#');
                surface(cubeX, -cubeWidth, -cubeY, ';');
                surface(cubeX, cubeWidth, cubeY, '+');
            }
        }


        for (int k = 0; k < WIDTH * HEIGHT; k++) {
        putchar(k % WIDTH ? buffer[k] : 10);
        }
        A += 0.002;
        B += 0.002;
        C += 0.001;
        usleep(1000);
    }

    return 0;
}
