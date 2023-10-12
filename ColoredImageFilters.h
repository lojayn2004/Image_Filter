#ifndef FILTER_COLOREDIMAGEFILTERS_H
#define FILTER_COLOREDIMAGEFILTERS_H

void shrinkColoredImage(int shrinkScale);

void changeColoredBrightness();

void darkenColoredImage();

void lightenColoredImage();

void blurColoredImage();

void skewColoredHorizontally(double  angle);

void loadSecondColoredImage(char imageFileName[]);

void saveColoredImage(char imageFileName[]);
#endif //IMAGE_FILTER_COLOREDIMAGEFILTERS_H
