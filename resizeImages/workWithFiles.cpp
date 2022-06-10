#include "workWithFiles.h"

void loadWorkParams(ResizeImageParams& params, std::string fileName)
{
    json jsonConf;

    std::ifstream paramFile(fileName);
    if (!paramFile.is_open()) 
    {
        throw std::string("Can not open file with working params");
    }

    try 
    {
        jsonConf = json::parse(paramFile);
    }
    catch (...) 
    {
        paramFile.close();
        throw std::string("Error parsing params from json"); 
    }
    try 
    {
        json channelJson = jsonConf.at("RESIZE_IMAGE_PARAMS");
        params.targetSizeWidth = channelJson.at("targetSizeWidth").get<int>();
        params.targetSizeHeigth = channelJson.at("targetSizeHeigth").get<int>();
        params.acceptableRatio = channelJson.at("acceptableRatio").get<float>();
        params.resizeType = ResizeType(channelJson.at("resizeType").get<int>());
        params.directoryWithImages = channelJson.at("directoryWithImages").get<std::string>();
        params.directoryForSavingImages = channelJson.at("directoryForSavingImages").get<std::string>();
    }
    catch (...) 
    {
        paramFile.close();
        throw std::string("Error reading params from json");
    }
    paramFile.close();
}

void traversalDirectoryWithImages(const ResizeImageParams& params)
{
    if (fs::exists(params.directoryWithImages))
    {
        for (auto& imageName : fs::directory_iterator{ params.directoryWithImages })
        {
            if (!imageName.is_directory())
            {
                processedImage(params, imageName);
            }
        }
    }
    else
    {
        throw std::string("Not can found directory with images");
    }
}

void processedImage(const ResizeImageParams& params, const fs::directory_entry& pathToImage)
{
    cv::Mat originalImage{};
    std::vector<cv::Mat> resizeImages(0);
    try {
        loadImage(pathToImage.path().string(), originalImage);
        cv::Size targetSize{ params.targetSizeWidth, params.targetSizeHeigth };
        if (params.resizeType == ResizeType::WITH_DISTORTIONS)
        {
            imageResizeWithDistortions(originalImage, targetSize, resizeImages, params.acceptableRatio);
        }
        else if (params.resizeType == ResizeType::WITHOUT_DISTORTIONS)
        {
            imageResizeWithoutDistortions(originalImage, targetSize, resizeImages, params.acceptableRatio);
        }
        saveImages(params.directoryForSavingImages, pathToImage.path().filename().string(), resizeImages);
    }
    catch (std::string exeption)
    {
        std::cout << exeption << std::endl;
    }
    
}

void loadImage(const std::string& pathToImage, cv::Mat& inOutputImage)
{
    inOutputImage = cv::imread(pathToImage);
    if (inOutputImage.empty())
        throw std::string("image " + pathToImage + " not found");
}

void saveImages(const std::string& directoryForSaving, const std::string& imageName, const std::vector<cv::Mat>& savedImages)
{
    size_t pointIndex{ imageName.find_last_of(".") };
    
    for (size_t i{}; i < savedImages.size(); ++i)
    {
        std::string imageNameWithIterator{ imageName };
        imageNameWithIterator.insert(pointIndex, std::to_string(i));
        std::string pathToSave{ directoryForSaving + '/' + imageNameWithIterator };
        cv::imwrite(pathToSave, savedImages[i]);
    }
}
