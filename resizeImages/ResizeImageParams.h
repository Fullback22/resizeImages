#pragma once
#include <string>

enum class ResizeType
{
	WITH_DISTORTIONS,
	WITHOUT_DISTORTIONS
};

struct ResizeImageParams
{
	int targetSizeWidth{};
	int targetSizeHeigth{};
	float acceptableRatio{};
	ResizeType resizeType{};
	std::string directoryWithImages{};
	std::string directoryForSavingImages{};
};