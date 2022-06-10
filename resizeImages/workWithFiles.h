#pragma once
#include <string>
#include <fstream>
#include <filesystem>

#include "json.hpp"
#include "ResizeImageParams.h"
#include "resizeImage.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

void loadWorkParams(ResizeImageParams& params, std::string fileName = "params.json");

void traversalDirectoryWithImages(const ResizeImageParams& params);

void processedImage(const ResizeImageParams& params, const fs::directory_entry& pathToImage);

void loadImage(const std::string& pathToImage, cv::Mat& inOutputImage);

void saveImages(const std::string& directoryForSaving, const std::string& imageName, const std::vector<cv::Mat>& savedImages);