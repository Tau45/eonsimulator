#include "../../include/network/Path.h"

Path::Path(vector<Link *> &path) :
		path(path) {}

Link *Path::getInputLink() {
	return path.front();
}

vector<Link *> Path::getInternalLinks() {
	return {path.begin() + 1, path.end() - 1};
}

Link *Path::getOutputLink() {
	return path.back();
}

uint64_t Path::getPathSize() {
	return path.size();
}

vector<Link *> Path::getPath() {
	return path;
}

vector<uint64_t> Path::getAvailableFirstFSUsInInputLink(uint64_t requiredNumberOfFSUs) {
	return getInputLink()->getAvailableFirstFSUs(requiredNumberOfFSUs);
}

vector<uint64_t> Path::getAvailableFirstFSUsInInternalLinks(uint64_t requiredNumberOfFSUs) {
	vector<uint64_t> availableFirstFSUs;

	for (uint64_t i = 0; i < GlobalSettings::instance().getLinkCapacity(); i++) {
		availableFirstFSUs.push_back(i);
	}

	for (auto link: getInternalLinks()) {
		vector<uint64_t> availableFirstFSUsInCurrentLink = link->getAvailableFirstFSUs(requiredNumberOfFSUs);

		vector<uint64_t> availableFirstFSUList = availableFirstFSUs;
		for (auto value: availableFirstFSUList) {
			if (!count(availableFirstFSUsInCurrentLink.begin(), availableFirstFSUsInCurrentLink.end(), value)) {
				availableFirstFSUs.erase(remove(availableFirstFSUs.begin(), availableFirstFSUs.end(), value), availableFirstFSUs.end());
			}
		}
	}
	return availableFirstFSUs;
}

vector<uint64_t> Path::getAvailableFirstFSUsInOutputLink(uint64_t requiredNumberOfFSUs) {
	return getOutputLink()->getAvailableFirstFSUs(requiredNumberOfFSUs);
}