#include <iostream>
#include <cstring>
#include "bmplib.h"
#include "ImageFilterApp.h"
#define WHITE 255
#define BLACK 0

unsigned char secondImage[SIZE][SIZE];
unsigned  char image[SIZE][SIZE];
using namespace std;


// =========================== Question 5 =======================================
void changeImageBrightness()
{
    char userChoice;
    cout << "Do you want to (d)arken or (l)ighten?";
    cin >> userChoice;

    if(userChoice == 'd'){
        darkenImage();
    }
    else if(userChoice == 'l'){
        lightenImage();
    }
    else{
        cout << "Invalid Choice :(\n";
    }

}

void darkenImage()
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] /= 3;
        }
    }
}

void lightenImage()
{
// char lightShade[] = "gray";
   // mergeTwoImages(lightShade);
    for(int i  =0 ;i<SIZE;i++){
        for(int j = 0; j< SIZE;j++){
            image[i][j] = (image[i][j] + 140)/2;
        }
    }
}


// ======================== question 3 ==============================

void loadSecondImage(char imageFileName[])
{
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, secondImage);
}

void mergeTwoImages(char imageFileName[])
{
    loadSecondImage(imageFileName);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j] = (image[i][j] + secondImage[i][j])/2;
        }
    }
}

//=============================================================

void shrinkImage(int shrinkScale)
{
    // skip some # of pixels to shrink
    int column = 0, row = 0;
    for(int i = 0;i < SIZE;i += shrinkScale){
        for(int j = 0; j < SIZE;j += shrinkScale) {
            image[row][column++] = image[i][j];
        }
        row++;
        column = 0;
    }

    // set the rest of pixels to white
    for(int i = 0 ;i < SIZE;i++){
        for(int j = 0; j <SIZE;j++){
            if(i >= SIZE/shrinkScale || j > SIZE/shrinkScale)
                image[i][j] = WHITE;
        }
    }
}


// ===========================================
bool isValidPixel(int x, int y){
    return x >=0 && x <SIZE && y >=0 && y <SIZE;
}
void blurImage()
{
    int dx[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    int dy[] = {0, 0, -1,1, -1, 1, 1, -1};



    for(int i = 0;i < SIZE;i++) {
        for (int j = 0; j < SIZE; j++) {
            int sumOfneighbors = 0;
            int nOfmergedPixels = 1;
            // iterate over all neighbors of the pixel and sum their values
            for (int k = 0; k < 8; k++) {
                int x = i +  dx[k];
                int y = j +  dy[k];
                // go one level further
                for(int l = 0; l < 1;l++){
                    x += dx[k];
                    y += dy[k];
                    if (isValidPixel(x, y)) {
                        sumOfneighbors+= image[x][y], nOfmergedPixels++;
                    }
                }
                if (isValidPixel(x, y)) {
                    sumOfneighbors += image[x][y], nOfmergedPixels++;
                }
            }
            // take the average of the neighbors colors with thw color of the pixel
            image[i][j] = (image[i][j] + sumOfneighbors) / nOfmergedPixels;
        }
    }
}

// =====================================

void skewVertically(int degreeOfSkeweness){

    int start = 50 + degreeOfSkeweness;
    int end = 256;
    // skip some # if bits to fit in new size
    int skip =2*(256/(end - start));


    int changeCycle = 3;

    for(int i = 0; i < SIZE;i++){
        int k  =start;
        for(int j = 0;j < SIZE && k < end;j+= skip){
            secondImage[i][k++] = image[i][j];
        }
        changeCycle--;
        if(!changeCycle){
            start--;
            end--;
            changeCycle = 3;
        }
    }
}