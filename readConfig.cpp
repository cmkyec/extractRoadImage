#include "readConfig.h"
#include "logger.h"
#include "json/json.h"
#include <fstream>

namespace gentech
{

static inline bool getJsonRoot(Json::Value& root)
{
	std::ifstream infile("./configFiles/roadImageExtractConfig");
	if (!infile.is_open()) {
		g_Logger.Error(__FILE__, __LINE__, 
			       "roadImageExtract config file does not exist.");
		return false;
	}
        Json::Reader reader;
        return reader.parse(infile, root);
}

bool readVideoPaths(std::vector<std::string>& videoPaths)
{
	Json::Value root;
	if (!getJsonRoot(root)) {
		g_Logger.Error(__FILE__, __LINE__, 
			      "config file not exist, or parse video paths failed.");
		return false;
	}
	const Json::Value videoPathsJson = root["videoPaths"];
	if (videoPathsJson.size() == 0) {
		g_Logger.Info(__FILE__, __LINE__, 
			      "video path is empty, there are no videos to be processed.");
		return false;
	}
	for (unsigned int i = 0; i < videoPathsJson.size(); ++i) {
		std::string path = videoPathsJson[i].asString();
		videoPaths.push_back(path);
	}
	return true;
}

bool readImageSaveFolder(std::string& imageSaveFolder)
{
	Json::Value root;
	if (!getJsonRoot(root)) {
		g_Logger.Error(__FILE__, __LINE__, 
			       "config file not exist, or parse save folder failed.");
		return false;
	}
	const Json::Value saveFolderJson = root["saveFolder"];
	imageSaveFolder = saveFolderJson.asString();
	return true;
}

}
