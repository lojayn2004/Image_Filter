#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include "ColoredImageFilters.h"
#define WHITE 255
#define BlACK 0
using namespace std;

unsigned char coloredImage[SIZE][SIZE][RGB];
unsigned char secondColoredImage[SIZE][SIZE][RGB];


//============================================= Filter 1 ===============================================================
void blackAndWhite() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int avg = 0;

            // Calculate the average color intensity for the pixel (i, j,c)
            for (int c = 0; c < RGB; c++) {
                avg += image[i][j][c];
            }
            // Apply the black and white conversion
            for (int c = 0; c < RGB; c++) {
                if (avg / 3 > 127) {
                    // Set the color channel to white (255)
                    image[i][j][c] = WHITE;
                } else {
                    // Set the color channel to black (0)
                    image[i][j][c] = BLACK;
                }
            }
        }
    }
}

//============================================= Filter 2 ===============================================================

//TO INVERT COLORED IMAGE
void invertImage() {
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j) {
            for (int h = 0; h < 3; ++h) {
                //TO LOOP 3 TIMES ON THREE COLORS
                image[i][j][h] = 255 - image[i][j][h]; //CHANGES COLOR OF PIXEL TO ITS INVERSE 
            }
        }
    }
}

//============================================= Filter 3 ===============================================================
void mergeTwoColoredImages(char imageFileName[])
{
    loadSecondColoredImage(imageFileName[]);
    for(int i = 0; i<SIZE;i++ ){
        for(int j = 0; j <SIZE;j++){

            // loop on each color and merge it with the corresponding pixel
            for(int color = 0; color < 3; color++) {
                coloredImage[i][j][color] = (coloredImage[i][j][color] + secondColoredImage[i][j][color]) / 2;
            }
        }
    }

}


//=========================================== Filter 4 =================================================================
void flipImage() {
    char c;
    cout << "Enter 'v' or 'h' as you want ^_^ :";
    cin >> c;
    if (c == 'h') {
        HorizontalFlip();
    } else if (c == 'v') {
        VerticalFlip();
    } else {
        cout << "invalid choice\n";
    }
}
void horizontalFlip() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            // Swap the pixels from the left half with their corresponding pixels in the right half
            for (int c = 0; c < RGB; c++) {
                swap(image[i][j][c], image[i][SIZE - 1 - j][c]);
            }
        }
    }
}
void verticalFlip() {
    for (int i = 0; i < (SIZE / 2); ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                swap(image[i][j][k], image[SIZE - 1 - i][j][k]);
            }
        }
    }
}

//============================================= Filter 5 ===============================================================

//TO ROTATE IMAGE BY 90 OR 180 OR 270 DEGREES
void rotateImage() {
    unsigned char temp = 0;
    cout <<"Enter angle of rotation :";
    int n;
    cin >> n;
    switch (n) {
        case 90 : {
            //TO ROTATE IMAGE BY 90 DEGREE
            for(int i=0;i<SIZE/2;++i){
                for(int j=i;j<SIZE-i-1;++j) {
                    for (int h = 0; h < 3; ++h) {
                        temp = image[i][j][h];
                        image[i][j][h] = image[j][SIZE - i - 1][h];
                        image[j][SIZE - i - 1][h] = image[SIZE - i - 1][SIZE - j - 1][h];
                        image[SIZE - i - 1][SIZE - j - 1][h] = image[SIZE - 1 - j][i][h];
                        image[SIZE - 1 - j][i][h] = temp;
                    }
                }
            }
            break;
        }
        case 180 : {
            // TO ROTATE IMAGE BY 180 DEGREE
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    for (int h = 0; h < 3; ++h) {
                        temp = image[i][j][h]; // TO CHANGE PIXEL IN TO THE OOPOSITE CROSSPONDING PIXEL
                        image[i][j][h] = image[SIZE - i - 1][SIZE - j - 1][h];
                        image[SIZE - i - 1][SIZE - j - 1][h] = temp;
                    }
                }
            }
            break;
        }
        case 270 : {
            // TO ROTATE IMAGE BY 270 DEGREE
            for(int i=0;i<SIZE/2;++i){
                for(int j=i;j<SIZE -i-1;++j) {
                    for (int h = 0; h < 3; ++h) {
                        //CHANGE PIXELS WITH EACH OTHER TO ROTATE PART BY PART
                        temp = image[i][j][h];
                        image[i][j][h] = image[SIZE - 1 - j][i][h];
                        image[SIZE - 1 - j][i][h] = image[SIZE - i - 1][SIZE - j - 1][h];
                        image[SIZE - i - 1][SIZE - j - 1][h] = image[j][SIZE - 1 - i][h];
                        image[j][SIZE - 1 - i][h] = temp;
                    }
                }
            }
            break;
        }
    }
}

//=========================================== Filter 6 =================================================================
void changeColoredBrightness(){
    char userChoice;
    cout << "Do you want to (d)arken or (l)ighten?";
    cin >> userChoice;

    if(userChoice == 'd'){
        darkenColoredImage();
    }
    else if(userChoice == 'l'){
        lightenColoredImage();
    }

    else{
        cout << "Invalid Choice :(\n";
    }
}

void darkenColoredImage(){
    for(int i = 0; i<SIZE;i++ ){
        for(int j = 0; j <SIZE;j++){
            for(int k = 0; k < RGB; k++) {
                // Loop on each colour in pixel and decrease its value
                // When decreasing the value , the darkness increases
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

//=========================================== Filter 7 =================================================================
void detectEdges()
{
    blackAndWhite();
    int sumR = 0, sumG = 0, sumB = 0;

    // Calculate the sum of all pixel values in the image for each color channel
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            sumR += image[i][j][0]; // Red channel
            sumG += image[i][j][1]; // Green channel
            sumB += image[i][j][2]; // Blue channel
        }
    }
    // Calculate the average pixel values for each channel
    int avgR = (sumR / (SIZE * SIZE));
    int avgG = (sumG / (SIZE * SIZE));
    int avgB = (sumB / (SIZE * SIZE));

    // Iterate over the image for edge detection
    for (int i = 0; i < SIZE - 1; ++i) {
        for (int j = 0; j < SIZE - 1; ++j) {
            // Compare neighboring pixel values to the average for edge detection in each channel
            if ((image[i][j][0] > avgR && image[i][j + 1][0] <= avgR) || (image[i][j][0] <= avgR && image[i][j + 1][0] > avgR) ||
                (image[i][j][1] > avgG && image[i][j + 1][1] <= avgG) || (image[i][j][1] <= avgG && image[i][j + 1][1] > avgG) ||
                (image[i][j][2] > avgB && image[i][j + 1][2] <= avgB) || (image[i][j][2] <= avgB && image[i][j + 1][2] > avgB))
            {
                image[i][j][0] = 0; // Set pixel to 0 in the Red channel if it's part of an edge
                image[i][j][1] = 0; // Set pixel to 0 in the Green channel if it's part of an edge
                image[i][j][2] = 0; // Set pixel to 0 in the Blue channel if it's part of an edge
            }
            else if ((image[i][j][0] <= avgR && image[i + 1][j][0] > avgR) || (image[i][j][0] > avgR && image[i + 1][j][0] <= avgR) ||
                     (image[i][j][1] <= avgG && image[i + 1][j][1] > avgG) || (image[i][j][1] > avgG && image[i + 1][j][1] <= avgG) ||
                     (image[i][j][2] <= avgB && image[i + 1][j][2] > avgB) || (image[i][j][2] > avgB && image[i + 1][j][2] <= avgB))
            {
                image[i][j][0] = 0; // Set pixel to 0 in the Red channel if it's part of an edge
                image[i][j][1] = 0; // Set pixel to 0 in the Green channel if it's part of an edge
                image[i][j][2] = 0; // Set pixel to 0 in the Blue channel if it's part of an edge
            }
            else
            {
                image[i][j][0] = 255; // Set pixel to 255 in the Red channel if it's not part of an edge
                image[i][j][1] = 255; // Set pixel to 255 in the Green channel if it's not part of an edge
                image[i][j][2] = 255; // Set pixel to 255 in the Blue channel if it's not part of an edge
            }
        }
    }
}

//=========================================== Filter 8 =================================================================

// TO ENLARGE IMAGE
void enlargeImage() {
    unsigned char temp[SIZE][SIZE][RGB];
    int m=0,k=0;
    int a;
    cout<<"Enter quarter to enlarge it :";
    cin>>a;
    switch(a) {
        case 1: {
            // TO COPY PART ONE
            for (int i = 0; i < SIZE/2; ++i) {
                k = 0;
                for (int j = 0; j < SIZE/2; ++j) {
                    for (int h = 0; h < RGB; ++h) {
                        // TO REPRESENT ONE PIXEL IN FOUR PIXEL
                        temp[m][k][h] = image[i][j][h];
                        temp[m][k + 1][h] = image[i][j][h];
                        temp[m + 1][k][h] = image[i][j][h];
                        temp[m + 1][k + 1][h] = image[i][j][h];
                    }
                    k+=2;
                }
                m += 2;
            }
            break;
        }
        case 2: {
            // TO ENLARGE PART TWO
            for (int i = 0; i < SIZE/2; ++i) {
                k = 0;
                for (int j = SIZE/2; j < SIZE; ++j) {
                    for (int h = 0; h < RGB; ++h) {
                        temp[m][k][h] = image[i][j][h];
                        temp[m][k + 1][h] = image[i][j][h];
                        temp[m + 1][k][h] = image[i][j][h];
                        temp[m + 1][k + 1][h] = image[i][j][h];
                    }
                    k += 2;
                }
                m += 2;
            }
            break;
        }
        case 3: {
            // TO ENLARGE PART THREE
            for (int i = SIZE/2; i < SIZE; ++i) {
                k = 0;
                for (int j = 0; j < SIZE/2; ++j) {
                    for (int h = 0; h < RGB; ++h) {
                        temp[m][k][h] = image[i][j][h];
                        temp[m][k + 1][h] = image[i][j][h];
                        temp[m + 1][k][h] = image[i][j][h];
                        temp[m + 1][k + 1][h] = image[i][j][h];
                    }
                    k += 2;
                }
                m += 2;
            }
            break;
        }
        case 4: {
            // TO ENLARGE PART FOUR
            for (int i = SIZE/2; i < SIZE; ++i) {
                k = 0;
                for (int j = SIZE/2; j < SIZE; ++j) {
                    for(int h=0;h<RGB;++h) {
                        temp[m][k][h] = image[i][j][h];
                        temp[m][k + 1][h] = image[i][j][h];
                        temp[m + 1][k][h] = image[i][j][h];
                        temp[m + 1][k + 1][h] = image[i][j][h];
                    }
                    k += 2;
                }
                m += 2;
            }
            break;
        }
    }
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j) {
            for (int h = 0; h < RGB; ++h) {
                // TO COPY NEW MATRIX IN THE LOADED IMAGE
                image[i][j][h] = temp[i][j][h];
            }
        }
    }

}

//=========================================== Filter 9 =================================================================
void shrinkColoredImage(int shrinkScale){

    // Skip Some number of bits to shrink Image
    int row = 0, column = 0;
    for(int i = 0; i<SIZE; i+= shrinkScale){
        for(int j = 0; j <SIZE - 1; j+=shrinkScale){
            for(int k = 0; k < 3; k++){
                coloredImage[row][column][k] =coloredImage[i][j][k];
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
                for(int k = 0; k < 3; k++) {
                    coloredImage[i][j][k] = WHITE;
                }
            }
        }
    }
}

//=========================================== Filter a =================================================================
void mirrorImage() {
    // get the user's choice
    char choice;
    cout << "Do you want left, right, upper, or lower Mirror side?\n";
    cout << "Enter the first letter of your choice (e.g., 'l' for left) except lower enter 'd' : ";
    cin >> choice;
    // Apply the mirror filter based on user's choice
    if (choice == 'l') {
        // Mirror the left half of the image to the right
        leftHalfMirror();
    } 
    else if (choice == 'r') {
        // Mirror the right half of the image to the left
        rightHalfMirror();
    }
    else if (choice == 'u') {
        // Mirror the upper half of the image to the lower half
        upperHalfMirror();
    }
    else if (choice == 'd') {
        // Mirror the lower half of the image to the upper half
        lowerHalfMirror();
    } 
    else {
        cout << "Invalid direction. Please enter 'l', 'r', 'u', or 'd'.\n";
    }
}

void leftHalfMirror() {
    // Iterate through the rows of the image
    for (int x = 0; x < SIZE; x++) {
        // Iterate through the columns in the left half of the image
        for (int y = 0; y < SIZE / 2; y++) {
            // Iterate through the color channels ( Red, Green, Blue)
            for (int k = 0; k < RGB; ++k) {
                // Set the pixel at (x, y, k) to be the same as the pixel on the opposite side of the mirror
                image[x][y][k] = image[x][SIZE - 1 - y][k];
            }
        }
    }
}

void rightHalfMirror() {
    // Iterate through the rows of the image
    for (int x = 0; x < SIZE; x++) {
        // Iterate through the columns in the right half of the image
        for (int y = SIZE / 2; y < SIZE; y++) {
            // Iterate through the color channels (Red, Green, Blue)
            for (int k = 0; k < RGB; ++k) {
                // Set the pixel at (x, y, k) to be the same as the pixel on the opposite side of the mirror
                image[x][y][k] = image[x][SIZE - 1 - y][k];
            }
        }
    }
}

void lowerHalfMirror() {
    // Iterate through the rows in the lower half of the image
    for (int x = 0; x < SIZE / 2; x++) {
        // Iterate through all the columns
        for (int y = 0; y < SIZE; y++) {
            // Iterate through the color channels (Red, Green, Blue)
            for (int k = 0; k < RGB; k++) {
                // Set the pixel at (x, y, k) to be the same as the pixel on the opposite side of the mirror
                image[x][y][k] = image[SIZE - 1 - x][y][k];
            }
        }
    }
}

void upperHalfMirror() {
    for (int x = SIZE / 2; x < SIZE; x++) {
        // Iterate through all the rows in the top half of the image
        for (int y = 0; y < SIZE; y++) {
            // Iterate through the color channels (Red, Green, Blue)
            for (int k = 0; k < RGB; ++k) {
                // Set the pixel at (x, y, k) to be the same as the pixel on the opposite side of the mirror
                image[x][y][k] = image[SIZE - 1 - x][y][k];
            }
        }
    }
}

// ========================================== Filter b =================================================================

// REORDER ORDER OF IMAGE
void shuffleImage() {
    cout<<"Enter the order of the image : ";
    int n = 4, a = 0, cnt = 1,m=0,k=0,l=0,o=0;
    unsigned char temp[SIZE][SIZE][RGB];
    for (int p = 0; p < n; ++p) {
        cin >> a; // INPUT USER ORDER 
        if (cnt == 1)m = 0,k = 0,l=m,o=k;// TO KNOW WHICH PART OF NEW MATRIX TO FILL IN
        else if (cnt == 2)m=0,k=SIZE/2,l=m,o=k;
        else if(cnt ==3)m=SIZE/2,k=0,l=m,o=k;
        else m=SIZE/2,k=SIZE/2,l=m,o=k;
        ++cnt;
        // ORDER OF IMAGE 
        if(a==1) {
            for (int i = 0, l = m; i < SIZE/2; ++i, ++l) {
                for (int j = 0, o = k; j < SIZE/2; ++j, ++o) {
                    for (int h = 0; h < RGB; ++h) {
                        //LOOP ON 3 COLORS
                        temp[l][o][h] = image[i][j][h];
                    }
                }
            }
        }
        else if(a==2){
            for(int i=0,l=m;i<SIZE/2;++i,++l) {
                for (int j = SIZE/2, o = k; j < SIZE; ++j, ++o) {
                    for (int h = 0; h < RGB; ++h) {
                        temp[l][o][h] = image[i][j][h];
                    }
                }
            }

        }
        else if(a==3){
            for(int i=SIZE/2,l=m;i<SIZE;++i,++l) {
                for (int j = 0, o = k; j < SIZE/2; ++j, ++o) {
                    for (int h = 0; h < RGB; ++h) {
                        temp[l][o][h] = image[i][j][h];
                    }
                }
            }

        }
        else{
            for(int i=SIZE/2,l=m;i<SIZE;++i,++l) {
                for (int j = SIZE/2, o = k; j < SIZE; ++j, ++o) {
                    for (int h = 0; h < RGB; ++h) {
                        temp[l][o][h] = image[i][j][h];
                    }
                }
            }

        }
    }
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j) {
            for (int h = 0; h < RGB; ++h) {
                image[i][j][h] = temp[i][j][h];
            }
        }
    }
}

// ========================================== Filter c =================================================================
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
                    for(int l = 0; l < 3;l++){
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

//=========================================== Filter d =================================================================
void cropImage() {
    int x, y, l, w;
    // Get user input for the cropping parameters
    cout << "Please enter the values of x, y, l, and w: ";
    cin >> x >> y >> l >> w;

    // Check if the cropping parameters are within bounds
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || l <= 0 || w <= 0 || x + l > SIZE || y + w > SIZE) {
        cout << "Invalid cropping parameters. No crop applied.";
    }

    // Iterate through the entire image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) 
            {
                if (i >= x && i < x + l && j >= y && j < y + w) {
                    // Copy pixels inside the crop region as is
                    image[i][j][k] = image[i][j][k];
                } else {
                    // Set pixels outside the crop region to black (color value 255)
                    image[i][j][k] = 255;
                }
            }
        }
    }
}

// ============================================ Filter e ===============================================================
void skewColoredHorizontally(double  angle)
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



// Loading other Image for functions that uses two images
void loadSecondColoredImage(char imageFileName[])
{
    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, secondColoredImage);
}


// Function To save the colored Image After appling Filters
void saveColoredImage(char imageFileName[])
{
    // Add to i6t .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, coloredImage);

}
