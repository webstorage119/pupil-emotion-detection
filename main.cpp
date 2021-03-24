
#include "image.h"

using std::cout;
using std::endl;

int main() {
    Image Happy;
    Happy.path = "/home/panlazy/dev/pupil/data/raw/happy";
    Happy.getImages(Happy.path);
    Happy.toImage();
    Happy.listImagePaths();
    Happy.toPupil();
    Happy.exportImages("/home/panlazy/dev/pupil/data/result/");

    return 0;
}