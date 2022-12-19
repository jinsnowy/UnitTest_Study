#pragma once

struct FileContent {
	string fileName;
	vector<string> lines;

	bool operator<(const FileContent& rhs) {
		return fileName < rhs.fileName;
	}
};

struct FileUpdate {
	string fileName;
	string newContent;
};