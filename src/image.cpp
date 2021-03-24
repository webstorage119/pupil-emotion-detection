//
// Created by Berkcan Ucan on 24.03.2021.
//

#include "image.h"
#include <filesystem>
#include <random>
#include <string>

namespace fs = std::filesystem;

/**
 * @brief Reads full image path and pushes to vector as string.
 * @param p (FUll path)
 */
void Image::getImages(const string &p) {
    for (const auto &entry : fs::directory_iterator(p)) {
        image_path.push_back(entry.path());
    }
}

/**
 * @brief Stdout full path of all images.
 */
void Image::listImagePaths() {
    for (const auto &i: image_path)
        std::cout << "Read success: " + i << std::endl;
}

/**
 * @brief Reads path from vector and turns into cv::Mat while loading the image then pushes to source images vector.
 */
void Image::toImage() {
    for (const auto &i: image_path)
        try {
            cv::Mat image = cv::imread(i);
            source_images.push_back(image);
        } catch (char const *s) {
            std::cout << s << std::endl;
        }
}

/**
 * @brief Makes composite image from the given images.
 *        source https://stackoverflow.com/a/22858549
 *
 * @param vecMat Vector of Images.
 * @param windowHeight The height of the new composite image to be formed.
 * @param nRows Number of rows of images. (Number of columns will be calculated depending on the value of total number of images).
 * @return new composite image.
 */
Mat Image::makeCanvas(vector<Mat> &vecMat, int windowHeight, int nRows) {
    int N = vecMat.size();
    nRows = nRows > N ? N : nRows;
    int edgeThickness = 10;
    int imagesPerRow = ceil(double(N) / nRows);
    int resizeHeight = floor(2.0 * ((floor(double(windowHeight - edgeThickness) / nRows)) / 2.0)) - edgeThickness;
    int maxRowLength = 0;

    std::vector<int> resizeWidth;
    for (int i = 0; i < N;) {
        int thisRowLen = 0;
        for (int j = 0; j < imagesPerRow; j++) {
            double aspectRatio = double(vecMat[i].cols) / vecMat[i].rows;
            int temp = int(ceil(resizeHeight * aspectRatio));
            resizeWidth.push_back(temp);
            thisRowLen += temp;
            if (++i == N) break;
        }

        if ((thisRowLen + edgeThickness * (imagesPerRow + 1)) > maxRowLength) {
            maxRowLength = thisRowLen + edgeThickness * (imagesPerRow + 1);
        }
    }

    int windowWidth = maxRowLength;
    cv::Mat canvasImage(windowHeight, windowWidth, CV_8UC3, cv::Scalar(0, 0, 0));

    for (int k = 0, i = 0; i < nRows; i++) {
        int y = i * resizeHeight + (i + 1) * edgeThickness;
        int x_end = edgeThickness;
        for (int j = 0; j < imagesPerRow && k < N; k++, j++) {
            int x = x_end;
            cv::Rect roi(x, y, resizeWidth[k], resizeHeight);
            cv::Size s = canvasImage(roi).size();
            cv::Mat target_ROI(s, CV_8UC3);
            if (vecMat[k].channels() != canvasImage.channels()) {
                if (vecMat[k].channels() == 1) {
                    cv::cvtColor(vecMat[k], target_ROI, cv::COLOR_BGR2GRAY);
                }
            } else {
                vecMat[k].copyTo(target_ROI);
            }
            cv::resize(target_ROI, target_ROI, s);
            if (target_ROI.type() != canvasImage.type()) {
                target_ROI.convertTo(target_ROI, canvasImage.type());
            }
            target_ROI.copyTo(canvasImage(roi));
            x_end += resizeWidth[k] + edgeThickness;
        }
    }

    return canvasImage;
}

/**
 * @todo Detect Pupil.
 * @brief Load images from source_images vector. Find face then eyes then push to pupils vector.
 * @warning Replace paths to cascades for your configuration.
 */
void Image::toPupil() {
    cv::String eyes_cascade_path = "/home/panlazy/dev/pupil/asset/haarcascade_eye_tree_eyeglasses.xml";
    cv::String face_cascade_path = "/home/panlazy/dev/pupil/asset/haarcascade_frontalface_alt.xml";
    cv::CascadeClassifier eyes_cascade;
    cv::CascadeClassifier faces_cascade;

    if (!eyes_cascade.load(eyes_cascade_path)) {
        std::cout << "Error loading eyes cascade." << std::endl;
    }

    if (!faces_cascade.load(face_cascade_path)) {
        std::cout << "Error loading face cascade." << std::endl;
    }

    for (const auto &source: source_images) {
       std::vector<cv::Rect> face;
       cv::Mat gray;

       // Convert to grayscale.
       cv::cvtColor(source, gray, cv::COLOR_BGR2GRAY);
       cv::equalizeHist(gray, gray);

       // Detect face
       faces_cascade.detectMultiScale(gray, face, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

        for (size_t i = 0; i < face.size(); i++) {
            cv::Point center(face[i].x + face[i].width * 0.5, face[i].y + face[i].height * 0.5);
            cv::ellipse(source, center, cv::Size(face[i].width * 0.5, face[i].height * 0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);

            cv::Mat faceROI = gray(face[i]);
            std::vector<cv::Rect> eye;

            // Each face, detect eyes.
            eyes_cascade.detectMultiScale(faceROI, eye, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

            for (size_t j = 0; j < eye.size(); j++) {
                cv::Point eyeCenter(face[i].x + eye[j].x + eye[j].width * 0.5, face[i].y + eye[j].y + eye[j].height * 0.5);
                int radius = cvRound((eye[j].width + eye[j].height) * 0.25);
                cv::circle(source, eyeCenter, radius, cv::Scalar(255, 0, 0), 4, 8, 0);
            }
        }

        pupils.push_back(source);
    }
}
// pupil cap
// gozun etrafindaki deri ile pupil arasindaki mesafe

void Image::exportImages(const string& exportPath) {
    for (const auto& entry: fs::directory_iterator(exportPath)) {
        fs::remove_all(entry.path());
    }

    std::cout << "Deleted old files." << std::endl;

    for(const auto &i: pupils) {
        std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
        std::random_device rd;
        std::mt19937 generator(rd());
        std::shuffle(str.begin(), str.end(), generator);
        string fileName = str.substr(0,16);
        cv::imwrite(exportPath + fileName + ".jpg", i);
        std::cout << "Exported to " + fileName + ".jpg" << std::endl;
    }
}
