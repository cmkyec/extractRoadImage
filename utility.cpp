#include "utility.h"
#include "logger.h"

namespace gentech
{

bool extractName(std::string& videoPath, std::string& videoName)
{
	std::size_t dotPos = videoPath.rfind(".");
	if (dotPos == std::string::npos) {
		g_Logger.Error(__FILE__, __LINE__, 
			       "there is not a dot in the video path: %s", 
			       videoPath.c_str());
		return false;
	}

	std::size_t backslashPos = videoPath.rfind("/");
	if (backslashPos == std::string::npos) {
		videoName = videoPath.substr(0, dotPos);
	} else {
		videoName = videoPath.substr(backslashPos+ 1, 
					     dotPos - backslashPos - 1);
	}
	return true;
}

cv::Mat meanMat(std::vector<cv::Mat>& mats)
{
	CV_Assert(mats.size() > 0);

	cv::Mat& mat_0 = mats[0];
	cv::Mat mean;

	if (mat_0.channels() == 3) {
		mean = cv::Mat::zeros(mat_0.size(), CV_64FC3);
	}
	else {
		mean = cv::Mat::zeros(mat_0.size(), CV_64FC1);
	}
	for (std::size_t i = 0; i < mats.size(); ++i) {
		CV_Assert(mean.size() == mats[i].size());
		cv::add(mean, mats[i], mean, cv::Mat(), mean.depth());
	}
	mean /= (double)mats.size();
	mean.convertTo(mean, mat_0.depth());
	return mean;
}

}
