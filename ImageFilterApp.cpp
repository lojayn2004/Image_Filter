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

//===================================================== Filter 1 =======================================================

// Function to convert an image to black and white
void blackAndWhiteImage() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Check pixel intensity; if greater than 127, set to white (255), otherwise set to black (0)
            if (image[i][j] > 127) {
                image[i][j] = 255; // White
            } else {
                image[i][j] = 0;   // Black
            }
        }
    }
}

//===================================================== Filter 4 =======================================================

// Function to flip the image either vertically or horizontally based on user choice
void flipImage() {
    char c;
    cout << "Enter 'v' for vertical flip or 'h' for horizontal flip ^_^ : ";
    cin >> c;

    if (c == 'h')
    {
        horizontalFlip();
    }
    else if (c == 'v')
    {
        verticalFlip();
    } else
    {
        cout << "Invalid direction. Please enter 'h' or 'v'.\n" ; // Display a message for an invalid choice
    }
}

// Function to flip the image horizontally by reversing the order of pixels
void horizontalFlip() {
    for (int i = 0; i < SIZE ; i++) {
        for (int j = 0; j < SIZE/2; j++) {
            // Swap the pixel values between the left and right sides of the image
            swap(image[i][j], image[i][SIZE-1-j]);
        }
    }
}
// Function to flip the image vertically by reversing the order of pixels
void verticalFlip() {
    for (int i = 0; i < SIZE/2; i++)
    {
        for (int j = 0; j < SIZE ; j++)
        {
            // Swap the pixels value between the top and bottom halves of the image
            swap(image[i][j], image[SIZE - 1 - i][j]);
        }
    }
}

//===================================================== Filter 7 ======================================================
void detectEdge() {
    int sum = 0;
    // Calculate the sum of all pixel values in the image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            sum += image[i][j];
        }
    }
    // Calculate the average pixel value
    int avg = (sum / (SIZE * SIZE));
    // Iterate over the image for edge detection
    for (int i = 0; i < SIZE - 1; ++i) {
        for (int j = 0; j < SIZE - 1; ++j) {
            // Compare neighboring pixel values to the average for edge detection
            if (image[i][j] > avg && image[i][j + 1] <= avg || image[i][j] <= avg && image[i][j + 1] > avg)
            {
                image[i][j] = 0; // Set pixel to 0 if it's part of an edge
            }
            else if (image[i][j] <= avg && image[i + 1][j] > avg || image[i][j] > avg && image[i + 1][j] <= avg)
            {
                image[i][j] = 0; // Set pixel to 0 if it's part of an edge
            }
            else
            {
                image[i][j] = 255; // Set pixel to 255 if it's not part of an edge
            }
        }
    }
}

//===================================================== Filter a =======================================================

void mirrorImage() {
    // Get the user's choice for the mirror side (left, right, upper, or lower)
    char choice;
    cout << "Do you want left, right, upper, or lower Mirror side?\n";
    cout << "Enter the first letter of your choice (e.g., 'l' for left) except lower enter 'd' : ";
    cin >> choice;

    // Apply the mirror filter based on the user's choice
    if (choice == 'l') {
        leftHalfMirror();
    }
    else if (choice == 'r')
    {
        rightHalfMirror();
    }
    else if (choice == 'u')
    {
        upperHalfMirror();
    } else if (choice == 'd') {
        lowerHalfMirror();
    }
    else
    {
        cout << "Invalid direction. Please enter 'l', 'r', 'u', or 'd'.\n";
    }
}

// Function to mirror the left half of the image
void leftHalfMirror() {
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE/2 ; y++) {
            // Assign the pixel value of the current position
            // to its mirror position on the opposite of the horizontal axis
            image[x][SIZE - 1 - y] = image[x][y];
        }
    }
}
// Function to mirror the right half of the image
void rightHalfMirror() {
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE/2 ; y++) {
            // Assign the pixel value of the current position
            // to its mirror position on the opposite of the horizontal axis
            image[x][y] = image[x][SIZE - 1 - y];
        }
    }
}

// Function to mirror the upper half of the image
void upperHalfMirror() {
    for (int x = 0; x < SIZE/2; x++) {
        for (int y = 0; y < SIZE; y++) {
            // Assign the pixel value of the current position
            // to its mirror position on the opposite side of the vertical axis
            image[SIZE - 1 - x][y] = image[x][y];
        }
    }
}

// Function to mirror the lower half of the image
void lowerHalfMirror() {
    for (int x = 0; x < SIZE/2; x++) {
        for (int y = 0; y < SIZE; y++) {
            // Assign the pixel value of the current position
            // to its mirror position on the opposite side of the vertical axis
            image[x][y] = image[SIZE - 1 - x][y];
        }
    }
}

//===================================================== Filter d ======================================================
void cropImage() {
    int x, y, l, w;
    bool valid = true;
    // Get user input for the cropping parameters
    cout << "Please enter the values of: x, y, l, and w: ";
    cin >> x >> y >> l >> w;

    // Check if the cropping parameters are within bounds
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || l <= 0 || w <= 0 || x + l > SIZE || y + w > SIZE)
    {
        cout << "Invalid crop dimensions. Make sure they fit within the image.\n";
        valid = false;
    }
    if(valid){
        //Iterate over the image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // Check if the current pixel is outside the defined crop region
                if (i < x || i > x + l || j < y || j > y + w) {
                    // Set pixels outside the crop region to white (pixel value 255)
                    image[i][j] = 255;
                }
            }
        }
    }
}
//===================================================== Filter 2 =======================================================
//function to invert color of image to the other color
void invertImage() {
    for(int i = 0 ; i < SIZE ; ++i ){
        for(int  j = 0  ; j < SIZE ; ++j ){
            image[i][j ]= 255 - image[i][j] ; //invert image pixel from black to white and vice versa

        }
    }
}

//===================================================== Filter 5 =======================================================
// function for image rotation
void   rotateImage() {
    unsigned char temp = 0;
    cout <<"Enter angle of rotation :";         
    int n;                                        
    cin >> n;       // input rotation angle degree                              
    switch (n) {                                  
        case 90 : {                               
            //for rotation image by 90 degree
            for(int i = 0 ; i < SIZE/2 ; ++i ){         
                for(int j = i ; j < SIZE - i - 1 ; ++j ){
                    temp = image[i][j];//set value in image to another value 
                    image[i][j] = image[j][SIZE-i-1];    //changing images pixel
                    image[j][SIZE-i-1] = image[SIZE-i-1][SIZE-j-1];
                    image[SIZE-i-1][SIZE-j-1] = image[SIZE-1-j][i];
                    image[SIZE-1-j][i] = temp;
                
                }                                             
            }                                             
            break;                                           
        }
        case 180 : {
            //for rotation image 180 degree
            for (int i = 0; i < SIZE / 2; ++i) { // will loop on half rows
                for (int j = 0; j < SIZE; ++j) { // will loop on all coloum to copy upper image to lower in opposite side and vice
                    temp = image[i][j];
                    image[i][j] = image[SIZE - i - 1][SIZE - j - 1];
                    image[SIZE - i - 1][SIZE - j - 1] = temp;
                }
            }
            break;                                         
        }                                                    
        case 270 : {        
            //this loop for rotating image by 270 degree
            for(int i = 0 ; i < SIZE/2 ; ++i ){                
                for(int j = i ; j<SIZE - i - 1 ;++j){
                    temp = image[i][j];
                    image[i][j] = image[SIZE-1-j][i];//chaning pixel value in it to other pixel value
                    image[SIZE-1-j][i] = image[SIZE-i-1][SIZE-j-1];
                    image[SIZE-i-1][SIZE-j-1] = image[j][SIZE-1-i]
                    image[j][SIZE-1-i] = temp;
    
                }   
            }                                        
break;                                  
        }                                           
    }
}

//===================================================== Filter b =======================================================

void shuffleImage () {
    cout<<"Enter the order of the image : ";
    int n = 4, a = 0, cnt = 1,m=0,k=0,l=0,o=0;
    unsigned char temp[SIZE][SIZE];
    for (int p = 0; p < n; ++p) {
        cin >> a;// for entering order of image
        if (cnt == 1)m = 0,k = 0,l=m,o=k; //to fill new matrix with pixels
        else if (cnt == 2)m=0,k=SIZE/2,l=m,o=k;
        else if(cnt ==3)m=SIZE/2,k=0,l=m,o=k;
        else m=SIZE/2,k=SIZE/2,l=m,o=k;
        ++cnt;
        if(a==1) {
            //first quarter
            for (int i = 0, l = m; i < SIZE/2; ++i, ++l) {
                for (int j = 0, o = k; j < SIZE/2; ++j, ++o) {
                    temp[l][o] = image[i][j];
                }
            }
        }
         else if(a==2){
             //second quarter
                for(int i=0,l=m;i<SIZE/2;++i,++l){
                    for(int j=SIZE/2,o=k;j<SIZE;++j,++o){
                        temp[l][o] = image[i][j];
                    }
                }

            }
         else if(a==3){
             //third quarter
                for(int i=SIZE/2,l=m;i<SIZE;++i,++l){
                    for(int j=0,o=k;j< SIZE/2;++j,++o){
                        temp[l][o] = image[i][j];
                    }
                }

            }
         else{
             //fourth quater
                for(int i=SIZE/2,l=m;i<SIZE;++i,++l){
                    for(int j=SIZE/2,o=k;j<SIZE;++j,++o){
                        temp[l][o] = image[i][j];
                    }
                }

            }
    }
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j){
            //to copy new matrix in loaded image
            image[i][j] = temp[i][j];
        }
    }
}
