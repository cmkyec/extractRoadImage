#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

namespace gentech
{

bool extractName(std::string& videoPath, std::string& videoName);

cv::Mat meanMat(std::vector<cv::Mat>& mats);

}

#endif /* _UTILITY_H_ */
