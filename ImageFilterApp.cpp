#include <iostream>
#include <cstring>
#include "bmplib.h"
#include "ImageFilterApp.h"
#define WHITE 255
#define BLACK 0

unsigned char secondImage[SIZE][SIZE];
unsigned  char image[SIZE][SIZE];
using namespace std;


// Filter allow user to darken or lighten the image
void changeImageBrightness()
{
    // ask user for which operation he would perform
    char userChoice;
    cout << "Do you want to (d)arken or (l)ighten ?";
    cin >> userChoice;

    // Execute the suitable function or report his input is wrong
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
    // loop on  image divide each  pixel by 3
    // To decrease its value , and increase its darkness
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] /= 3;
        }
    }
}

void lightenImage()
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            // Calculate the number of remaining to reach white
            int remainingToWhite = 255 - image[i][j];

            // Add Half the remaining of white pixels to the pixel
            // we add half only to make sure we don't go out of range
            image[i][j] += remainingToWhite/2;

        }
    }
}


// Filter that merges two images with each other
void mergeTwoImages(char imageFileName[])
{
    // load the second Image to be merged
    loadSecondImage(imageFileName);

    // loop on each pixel to merge it with  corresponding pixel in second Image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            // Apply merging by taking the average of two the pixels
            image[i][j] = (image[i][j] + secondImage[i][j]) / 2;
        }
    }
}


void loadSecondImage(char imageFileName[])
{
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, secondImage);
}

// Filter to shrink By given Scale
void shrinkImage(int shrinkScale)
{
    // skip some # of pixels to shrink
    int column = 0, row = 0;
    for(int i = 0;i < SIZE;i+=shrinkScale){
        for(int j = 0; j <SIZE;j+=shrinkScale) {
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

// Function to blur the Image
void blurImage()
{
    // Indecies of neighbors of a pixel 
    int dx[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    int dy[] = {0, 0, -1, 1, -1, 1, 1, -1};

    for(int i = 0;i < SIZE;i++) {
        for (int j = 0; j < SIZE; j++) {
            int sumOfneighbors = image[i][j];
            int nOfmergedPixels = 1;
            for (int neighbors = 0;neighbors < 8; neighbors++) {
                // take one level of pixels
                int x = i +  dx[neighbors];
                int y = j +  dy[neighbors];
                if (isValidPixel(x, y)) {
                    sumOfneighbors += image[x][y], nOfmergedPixels++;
                }

                // go one level further
                for(int levelTwo = 0; levelTwo < 1;levelTwo++){
                    x += dx[neighbors];
                    y += dy[neighbors];
                    if (isValidPixel(x, y)) {
                        sumOfneighbors += image[x][y], nOfmergedPixels++;
                    }
                }
            }
            // merged all taken levels
            image[i][j] = sumOfneighbors / nOfmergedPixels;
        }
    }
}


// Function checks if we went out the image bounds or no
bool isValidPixel(int i, int j)
{
    return i >= 0 && i < SIZE && j >= 0 && j < SIZE;
}


void skewVertically(double angle)
{
    // Set the background to white
    for(int i = 0;i < SIZE;i++){
        for(int j =0; j < SIZE;j++){
            secondImage[i][j] = WHITE;
        }
    }

    // define the start and end column
    int start = (int)(tan(angle *3.14 /180) *256);
    int end = 256;

    // Calculate the Compress Ratio
    int nOfCompressedBits = ceil(256./ (end - start));

    // Calculate the value by which we will decrease start and end
    double decRate = start/256.0;
    double taken = 0;

    // Calculate the unused pixels After the Compression
    int rem = abs((256/ nOfCompressedBits) - (end - start));

    // Calculate cycle To cover the unused pixels
    int turns = ceil((double)(256.0/ nOfCompressedBits)/rem);
    int tmp = turns;
    for(int i = 0;i < SIZE;i++)
    {
        int col = 0, last = 0;
        for(int j = (int) (start - taken) ;j < end - taken;j++){

            if(turns){
                int compressed = 0, cnt = 0;

                // Get the average of Compressed Bits
                for(int k = col ;k < col + nOfCompressedBits;k++){
                    compressed += image[i][k];
                    cnt++;
                }
                col += nOfCompressedBits;
                secondImage[i][j] = compressed/ max(1, cnt);

                // preserve the last Compressed bits to use it with unused Pixels
                last = secondImage[i][j];
                turns --;
            }
            else {
                secondImage[i][j] = last;
                turns = tmp;
            }

        }
        // used to decrease Start and end , so they are skewed
        taken += decRate;
    }
}
