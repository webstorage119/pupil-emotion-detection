
#include "image.h"

using std::cout;
using std::endl;

int main() {
    Image Happy;
    Happy.getImages("/home/panlazy/dev/pupil/data/raw/happy");
    Happy.toImage();
    Happy.listImagePaths();
    Happy.toPupil("/home/panlazy/dev/pupil/asset/haarcascade_eye_tree_eyeglasses.xml", "/home/panlazy/dev/pupil/asset/haarcascade_frontalface_alt.xml");
    Happy.exportImages("/home/panlazy/dev/pupil/data/result/");

    return 0;
}