#include "logger.h"
#include "readConfig.h"
#include "utility.h"
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

void extractRoadImage(std::string videoPath, std::string saveFolder)
{
	std::string videoName;
	if (!gentech::extractName(videoPath, videoName)) return;

	cv::VideoCapture capture;
	if (!capture.open(videoPath)) {
		g_Logger.Error(__FILE__, __LINE__, 
			       "video does not exist: %s.", videoPath.c_str());
		return;
	}

	cv::Mat frame;
	std::vector<cv::Mat> frames;
	for (int i = 0; i < 5; i++) capture >> frame;
	cv::namedWindow(videoName.c_str(), 0);
	for (int i = 0; i < 200; i++) {
		capture >> frame;
		if (!frame.data) break;
		cv::Mat tmpFrame;
		frame.copyTo(tmpFrame);
		frames.push_back(tmpFrame);
		cv::imshow(videoName.c_str(), frame);
		if (cv::waitKey(10) == 27) break;
	}
	cv::destroyWindow(videoName.c_str());

	cv::Mat roadImg = gentech::meanMat(frames);
	std::string savePath = saveFolder + "/" + videoName + ".png";
	cv::imwrite(savePath.c_str(), roadImg);
}

int main()
{
	g_Logger.startSystem("./configFiles/log4cplusConfig");

	std::vector<std::string> videoPaths;
	gentech::readVideoPaths(videoPaths);
	std::string saveFolder;
	gentech::readImageSaveFolder(saveFolder);

	if (access(saveFolder.c_str(), F_OK) != 0) {
		mkdir(saveFolder.c_str(), 0777);
	}

	for (std::size_t i = 0; i < videoPaths.size(); ++i) {
		std::string videoPath = videoPaths[i];
		extractRoadImage(videoPath, saveFolder);	
	}

	return 0;
}
