#include "image.h"

int main() {
    Image Happy;
    Happy.getImages("/home/panlazy/dev/pupil/data/raw/happy");
    Happy.toImage();
    Happy.listImagePaths();
    Happy.faceAndEyeDetection("/home/panlazy/dev/pupil/asset/haarcascade_frontalface_alt.xml", "/home/panlazy/dev/pupil/asset/haarcascade_eye_tree_eyeglasses.xml");
    Happy.exportImages("/home/panlazy/dev/pupil/data/result/happy/");

    return 0;
}
