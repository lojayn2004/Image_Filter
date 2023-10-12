#ifndef FILTER_COLOREDIMAGEFILTERS_H
#define FILTER_COLOREDIMAGEFILTERS_H

void blackAndWhite();

void detectEdges();

void shrinkColoredImage(int shrinkScale);

void changeColoredBrightness();

void darkenColoredImage();

void lightenColoredImage();

void mirrorImage();

void leftHalfMirror();

void rightHalfMirror();

void upperHalfMirror();

void lowerHalfMirror();

void blurColoredImage();

void cropImage();

void skewColoredHorizontally(double  angle);

void loadSecondColoredImage(char imageFileName[]);

void saveColoredImage(char imageFileName[]);
#endif //IMAGE_FILTER_COLOREDIMAGEFILTERS_H
