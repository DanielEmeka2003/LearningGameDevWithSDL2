#include "error_file.h"

Error_file::Error_file(fs::path path, CreateDirectory flag, const char* filename) :
	m_file{}, m_path { path }
{
	if (flag)
	{
		fs::create_directory(m_path);
		m_path /= filename;
	}
}
Error_file::Error_file(const Error_file& source) : m_path{ source.m_path }
{}

Error_file::~Error_file()
{}

Error_file& Error_file::operator=(const Error_file& source)
{
	if (this->m_path == source.m_path)
		return *this;

	m_path = source.m_path;
	return *this;
}

std::ofstream& Error_file::InsertErrorMessageToFile()
{
	return m_file;
}
const fs::path& Error_file::getPath()
{
	return m_path;
}

void Error_file::openFile()
{
	m_file.open(m_path, std::ios::out);
	if (!m_file.is_open())
	{
		std::cerr << "Could not open Error file: " << m_path.filename() << '\n';
		std::cerr << "Check directory: " << m_path.parent_path() << " for any problems\n";
		std::exit(1);
	}
}

void Error_file::closeFile()
{
	m_file.close();
}

void Error_file::getErrorNotification()
{
	std::cerr << "An Error occured, check file: " << m_path.filename() << " in directory: " << m_path.parent_path() << '\n';
}
