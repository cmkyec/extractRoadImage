#ifndef _READCONFIG_H_
#define _READCONFIG_H_

#include <vector>
#include <string>

namespace gentech
{

bool readVideoPaths(std::vector<std::string>& videoPaths);

bool readImageSaveFolder(std::string& imageSaveFolder);

}

#endif /* _READCONFIG_H_ */
