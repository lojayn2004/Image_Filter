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
    cout << "   s- Save the Image to a file\n";
    cout << "Enter your choice: ";

    cin >> userChoice;
    return userChoice;

}




int main()
{
    char imageName[100];
    cout << "Ahlan ya user ya habibi ☺ \n";
    cout << "Please enter file name of the image to process: \n";
    cin >> imageName;

    char userChoice = filtersMenu();

    while(userChoice != '0'){
        if(userChoice == '1'){
            loadImage();
        }

        userChoice = filtersMenu();
    }
}
