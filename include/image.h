//
// Created by Berkcan Ucan on 24.03.2021.
//

#ifndef PUPIL_IMAGE_H
#define PUPIL_IMAGE_H

#endif //PUPIL_IMAGE_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/mat.inl.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using std::vector;
using std::string;
using cv::Mat;

class Image {
public:
    vector<string> image_path;
    vector<Mat> source_images;
    vector<Mat> pupils;

public:
    void getImages(const string& importPath);

    void listImagePaths();

    void toImage();

    void toPupil(const string& faceCascadePath, const string& eyeCascadePath);

    void exportImages(const string& exportPath);

    Mat makeCanvas(vector<Mat> &vecMat, int windowHeight, int nRows);
};


