#include "resizeImage.h"

void imageResizeWithDistortions(const cv::Mat& inputImage, cv::Size targetSize, std::vector<cv::Mat>& outputImages, float const maximumAcceptableRatio)
{
    try {
        float minimumcceptableRatio{ 1 / maximumAcceptableRatio };
        float ratioRowsToCols{ inputImage.rows / static_cast<float>(inputImage.cols) };
        if (ratioRowsToCols > maximumAcceptableRatio)
        {
            splitImageByRowsWithDistortions(inputImage, outputImages);
        }
        else if (ratioRowsToCols < minimumcceptableRatio)
        {
            splitImageByColsWithDistortions(inputImage, outputImages);
        }
        else
        {
            outputImages.push_back(inputImage);
        }

        for (size_t i{}; i < outputImages.size(); ++i)
        {
            cv::resize(outputImages[i], outputImages[i], targetSize);
        }
    }
    catch (...)
    {
        throw std::string("Exeption in function imageResizeWithDistortions");
    }
}

void splitImageByColsWithDistortions(const cv::Mat& inputImage, std::vector<cv::Mat>& outputImages)
{
    float ratioColsToRows{ static_cast<float>(inputImage.cols) / inputImage.rows };
    int quantityOutputImages{ static_cast<int>(round(ratioColsToRows)) };
    outputImages.resize(quantityOutputImages);

    int splitStep{ inputImage.cols / quantityOutputImages };

    for (int i{}; i < quantityOutputImages; ++i)
    {
        cv::Rect cutoutPart{ i * splitStep, 0, splitStep - 1, inputImage.rows - 1};
        outputImages[i] = inputImage(cutoutPart);
    }
}

void splitImageByRowsWithDistortions(const cv::Mat& inputImage, std::vector<cv::Mat>& outputImages)
{
    float ratioRowsToCols{ static_cast<float>(inputImage.rows) / inputImage.cols };
    int quantityOutputImages{ static_cast<int>(round(ratioRowsToCols)) };
    outputImages.resize(quantityOutputImages);

    int splitStep{ inputImage.rows / quantityOutputImages };

    for (int i{}; i < quantityOutputImages; ++i)
    {
        cv::Rect cutoutPart{ 0 , i * splitStep, inputImage.cols - 1, splitStep - 1};
        outputImages[i] = inputImage(cutoutPart);
    }
}

void imageResizeWithoutDistortions(const cv::Mat& inputImage, cv::Size targetSize, std::vector<cv::Mat>& outputImages, float const maximumAcceptableRatio)
{
    try {
        float minimumcceptableRatio{ 1 / maximumAcceptableRatio };
        float ratioRowsToCols{ inputImage.rows / static_cast<float>(inputImage.cols) };
        if (ratioRowsToCols > maximumAcceptableRatio)
        {
            splitImageByRowsWithoutDistortions(inputImage, outputImages);
        }
        else if (ratioRowsToCols < minimumcceptableRatio)
        {
            splitImageByColsWithoutDistortions(inputImage, outputImages);
        }
        else if (ratioRowsToCols >= 1.0)
        {
            int x_y_Coordinate{ 0 };
            int widthAndHeigth{ inputImage.cols - 1 };
            cv::Rect cutoutPart(x_y_Coordinate, x_y_Coordinate, widthAndHeigth, widthAndHeigth);
            outputImages.push_back(inputImage(cutoutPart));
        }
        else
        {
            int x_y_Coordinate{ 0 };
            int widthAndHeigth{ inputImage.rows - 1 };
            cv::Rect cutoutPart(x_y_Coordinate, x_y_Coordinate, widthAndHeigth, widthAndHeigth);
            outputImages.push_back(inputImage(cutoutPart));
        }

        for (size_t i{}; i < outputImages.size(); ++i)
        {
            cv::resize(outputImages[i], outputImages[i], targetSize);
        }
    }
    catch (...)
    {
        throw std::string("Exeption in function imageResizeWithoutDistortions");
    }
}

void splitImageByColsWithoutDistortions(const cv::Mat& inputImage, std::vector<cv::Mat>& outputImages)
{
    float ratioColsToRows{ static_cast<float>(inputImage.cols) / inputImage.rows };
    int quantityOutputImages{ static_cast<int>(round(ratioColsToRows)) };
    outputImages.resize(quantityOutputImages);

    int widthAndHeigth{ inputImage.rows };

    for (int i{}; i < quantityOutputImages - 1; ++i)
    {
        cv::Rect cutoutPart{ i * widthAndHeigth, 0, widthAndHeigth - 1, widthAndHeigth - 1 };
        outputImages[i] = inputImage(cutoutPart);
    }
    int xCoordinate{ inputImage.cols - inputImage.rows };
    int yCoordinate{ 0 };
    cv::Rect cutoutPart{ xCoordinate, yCoordinate, widthAndHeigth - 1, widthAndHeigth - 1 };
    outputImages[quantityOutputImages - 1] = inputImage(cutoutPart);
}

void splitImageByRowsWithoutDistortions(const cv::Mat& inputImage, std::vector<cv::Mat>& outputImages)
{
    float ratioRowsToCols{ static_cast<float>(inputImage.rows) / inputImage.cols };
    int quantityOutputImages{ static_cast<int>(round(ratioRowsToCols)) };
    outputImages.resize(quantityOutputImages);

    int widthAndHeigth{ inputImage.cols };

    for (int i{}; i < quantityOutputImages - 1; ++i)
    {
        cv::Rect cutoutPart{ i * widthAndHeigth, 0, widthAndHeigth - 1, widthAndHeigth - 1 };
        outputImages[i] = inputImage(cutoutPart);
    }
    int xCoordinate{ 0 };
    int yCoordinate{ inputImage.rows - inputImage.cols };
    cv::Rect cutoutPart{ xCoordinate, yCoordinate, widthAndHeigth - 1, widthAndHeigth - 1 };
    outputImages[quantityOutputImages - 1] = inputImage(cutoutPart);
}