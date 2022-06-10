#pragma once
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

void imageResizeWithDistortions(const cv::Mat& inputImage, cv::Size targetSize, std::vector<cv::Mat>& outputImages, float const maximumAcceptableRatio = 1.5);

void splitImageByColsWithDistortions(const cv::Mat& inputImage, std::vector<cv::Mat>& outputImages);

void splitImageByRowsWithDistortions(const cv::Mat& inputImage, std::vector<cv::Mat>& outputImages);

void imageResizeWithoutDistortions(const cv::Mat& inputImage, cv::Size targetSize, std::vector<cv::Mat>& outputImages, float const maximumAcceptableRatio = 1.5);

void splitImageByColsWithoutDistortions(const cv::Mat& inputImage, std::vector<cv::Mat>& outputImages);

void splitImageByRowsWithoutDistortions(const cv::Mat& inputImage, std::vector<cv::Mat>& outputImages);

