#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include "ColoredImageFilters.h"
#define WHITE 255
using namespace std;

unsigned char coloredImage[SIZE][SIZE][RGB];
unsigned char secondColoredImage[SIZE][SIZE][RGB];


// Filter to merge two colored Images
void mergeTwoColoredImages(char imageFileName[])
{
    loadSecondColoredImage(imageFileName[]);
    for(int i = 0; i<SIZE;i++ ){
        for(int j = 0; j <SIZE;j++){
           // loop on each color and merge it with the coressponding pixel
            for(int color = 0; color < 3; color++) { 
                coloredImage[i][j][color] = (coloredImage[i][j][color] + secondColoredImage[i][j][color]) / 2;
            }
        }
    }

}

void loadSecondColoredImage(char imageFileName[])
{
    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, secondColoredImage);
}

// Filter used to lighten or darken image
void changeColoredBrightness(){
    char userChoice;
    cout << "Do you want to (d)arken or (l)ighten?";
    cin >> userChoice;

    if(userChoice == 'd')
        darkenColoredImage();
    else if(userChoice == 'l')
        lightenColoredImage();
    else
        cout << "Invalid Choice :(\n";
}
void darkenColoredImage(){
    for(int i = 0; i<SIZE;i++ ){
        for(int j = 0; j <SIZE;j++){
            for(int k = 0; k < RGB; k++) {
                coloredImage[i][j][k] /= 4;

            }
        }
    }
}

void lightenColoredImage(){
    for(int i = 0; i<SIZE;i++ ){
        for(int j = 0; j <SIZE;j++){
            for(int k = 0; k < RGB; k++) {
                // Remaining for each color to reach white
                int remainingToWhite = 255 - coloredImage[i][j][k];

                // Add Half the Value Only to oot get out of range
                coloredImage[i][j][k]  += remainingToWhite/2;

            }
        }
    }
}


// Filter to Blur an Image
void blurColoredImage()
{
    // Indecies of neighbors of a pixel 
    int dx[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    int dy[] = {0, 0, -1,1, -1, 1, 1, -1};
    for(int i = 0 ; i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            for(int k = 0; k < RGB;k++){
                int sum = coloredImage[i][j][k], pixel = 1;
                // Merge One Level of pixels
                for(int l = 0;l < 8;l++){
                    int x = i + dx[l];
                    int y = j + dy[l];
                    if (isValidPixel(x, y)) {
                        sum += coloredImage[x][y][k];
                        pixel++;
                    }

                    // Try Going Further 3 more level
                    for(int o = 0; o < 3;o++){
                        x += dx[k];
                        y += dy[k];
                        if(isValidPixel(x, y)){
                            sum += coloredImage[x][y][k];
                            pixel++;
                        }

                    }

                }
                coloredImage[i][j][k] = sum/pixel;
            }
        }
    }

}

// Filter to  Skew The Image 
void skewColoredVertically(double  angle)
{
    // Set the background to white
    for(int i = 0;i < SIZE;i++){
        for(int j =0; j < SIZE;j++){
            for(int k = 0;k < RGB;k ++) {
                secondColoredImage[i][j][k] = WHITE;
            }
        }
    }

    // define the start and end column
    int start = (int)(tan(angle *3.14 /180) *256);
    int end = 256;

    // Calculate the Compress Ratio
    int nOfCompressedBits = ceil(256./ (end - start));

    // Calculate the value by which we will decrease start and end
    double decRate = start/256.0;
    // Cumlative Sum of decrease Rate to decrease it each time
    double taken = 0;

    // Calculate the unused pixels After the Compression
    int rem = abs((256/ nOfCompressedBits) - (end - start));

    // Calculate cycle To cover the unused pixels
    int turns = ceil((double)(256.0/ nOfCompressedBits)/rem);
    int tmp = turns;
    for(int i = 0;i < SIZE;i++)
    {
        int col = 0, last[3] = {0, 0, 0};
        for(int j = (int) (start - taken) ;j < end - taken;j++){
            if(turns){
                int compressed[3] = {0, 0, 0}, cnt = 0;

                // Get the average of Compressed Bits
                for(int k = col ;k < col + nOfCompressedBits;k++){
                    for(int l = 0 ; l < 3;l++){
                        compressed[l] += coloredImage[i][k][l];
                    }
                    cnt++;
                }
                col += nOfCompressedBits;
                for(int l = 0;l <3;l++){
                    secondColoredImage[i][j][l] = compressed[l]/ max(1, cnt);
                }

                // preserve the last Compressed bits to use it with unused Pixels
                for(int l =0 ;l< 3;l++){
                    last[l]= secondColoredImage[i][j][l];
                }
                turns --;
            }
            else{
                for(int l = 0;l < 3;l++){
                    secondColoredImage[i][j][l] = last[l];
                }
                turns = tmp;
            }

        }
        // used to decrease Start and end , so they are skewed
        taken += decRate;
    }
}

// Filter to Shrink Image
void shrinkColoredImage(int shrinkScale){
    
    // Skip Some number of bits to shrink Image
    int row = 0, column = 0;
    for(int i = 0; i<SIZE; i+= shrinkScale){
        for(int j = 0; j <SIZE - 1; j+=shrinkScale){
            for(int color = 0; color < 3; color++){
                coloredImage[row][column][color] =coloredImage[i][j][color];
            }
            column++;
        }

        row++;
        column = 0;
    }

    // Set the reset of Image to white
    for(int i = 0; i<SIZE;i++){
        for(int j = 0; j <SIZE;j++){
            if(i >= SIZE/shrinkScale || j > SIZE/shrinkScale){
                for(int color = 0; color < 3; color++) {
                        coloredImage[i][j][color] = WHITE;
                }
            }
        }
    }
}


// Function To save the colored Image After sppling Filters
void saveColoredImage(char imageFileName[])
{
    // Add to i6t .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, coloredImage);

}
