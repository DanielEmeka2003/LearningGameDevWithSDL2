#ifndef ERROR_FILE_H
#define ERROR_FILE_H

#pragma once

#include "C:\Users\MIKE EMEKA\Documents\C++\includes.h"

namespace fs = std::filesystem;

class Error_file
{
	using CreateDirectory = bool;

	std::ofstream m_file{};
	fs::path m_path{};
public:

	Error_file(fs::path path, CreateDirectory flag = false, const char* filename = nullptr);

	Error_file() = default;
	Error_file(const Error_file& source);
	Error_file(Error_file&&) = default;

	Error_file& operator=(const Error_file& source);
	Error_file& operator=(Error_file&&) = default;

	virtual ~Error_file();

	std::ofstream& InsertErrorMessageToFile();
	const fs::path& getPath();

	void openFile();
	void closeFile();

	void getErrorNotification();
};


#endif // !ERROR_FILE_H

