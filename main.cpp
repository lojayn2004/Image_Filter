// FACI - OOP Programming - 2023 - Assignment 1
// Program Name: main.cpp
// Last Modification Date: 10/10/2023
// Laila Waleed Dawood Soliman - lailawlaeed@gmail.com -20220261
// Basmala Ahmed Ali Ibrahim - ibasmala435@gmail.com - 20220082
// Lojayn Khaled Farouk Omar - lojaynk@gmail.com - 20220258
// Purpose : Create  6 Filters used on gray Scale Image

#include <iostream>
#include "ImageFilterApp.h"
using  namespace std;

char filtersMenu(){
    
    char userChoice;

    cout << "Please select a filter to apply or 0 to exit: \n";
    cout << "   1- Black & White Filter \n";
    cout << "   2- Invert Filter \n";
    cout << "   3- Merge Filter \n";
    cout << "   4- Flip Filter \n";
    cout << "   5- Darken & Lighten Image\n";
    cout << "   6- Rotate Image\n";
    cout << "   7- Detect Image Edge\n";
    cout << "   8- Enlarge Image\n";
    cout << "   9- Shrink Image\n";
    cout << "   a- Mirror Image\n";
    cout << "   b- Shuffle Image\n";
    cout << "   c- Blur Image\n";
    cout << "   d- Crop Image\n";
    cout << "   e- Skew Image Right\n";
    cout << "   f- Skew Image Up\n";
    cout << "   l- load new Image\n";
    cout << "   s- Save the Image to a file\n";
    cout << "   0- Exit\n";
    cout << "Enter your choice: ";

    cin >> userChoice;
    return userChoice;

}

int main()
{
    // Take from user the name of photo to process
    char imageToProcess[100];
    cout << "Please enter file name of image you want to process: \n";
    cin >> imageToProcess;

    // load the image into the matrix
    loadImage(imageToProcess);

    // Let the user Choose between different choices
    char userChoice = filtersMenu();
    while(userChoice != '0')
    {
        if(userChoice == '1'){
            blackAndWhiteImage();
        }
        else if(userChoice == '2'){
            invertImage();
        }
        else if(userChoice == '3'){
            char secondImageName[100];
            cout << "Please enter name of file to merge with: \n";
            cin >> secondImageName;
            mergeTwoImages(secondImageName);
        }
        else if(userChoice == '4'){
            flipImage();
        }
        else if(userChoice == '5'){
            changeImageBrightness();
        }
        else if(userChoice == '6'){
             rotateImage();
        }
        else if(userChoice == '7'){
        }
        else if(userChoice == '8'){
            enlargeImage();
        }
        else if(userChoice  == '9')
        {
            string shrinkScale;
            cout << "shrink to (1/2), (1/3) or (1/4)? \n";
            cin >> shrinkScale;

            if(shrinkScale == "1/2") {
                shrinkImage(2);
            }
            else if(shrinkScale == "1/3") {
                shrinkImage(3);
            }
            else if(shrinkScale == "1/4"){
                shrinkImage(4);
            }
            else{
                cout << "Inavlid Choice, Try agein :) \n";
            }
        }
        else if(userChoice == 'a'){
            shuffleImage();
        }
        else if(userChoice == 'b'){
            shuffleImage();
        }
        else if(userChoice == 'c') {
            blurImage();
        }
        else if(userChoice == 'd'){
            cropImage();
        }
        else if(userChoice == 'e){
            skewHorizontally();
        }
        else if(userChoice == 'f'){
            skewVertically();
        }
        else if(userChoice == 'l'){
            char imageName[100];
            cout << "Enter new Image Name: \n";
            cin >> imageName;
            loadImage(imageName);
        }
        else if(userChoice == 's'){
            char resultFileName[100];
            cout << "Please enter name of file to save result in: \n";
            cin >> resultFileName;
            saveImage(resultFileName);
        }
        userChoice = filtersMenu();
    }
}
