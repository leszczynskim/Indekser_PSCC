#pragma once

#include "sqlite3.h"
#include <boost/filesystem.hpp>
#include <vector>
#include <string.h>
#include <unordered_map>
class DBOperations
{
public:
	static void Create(const std::string scriptToRun,std::unordered_map<std::string, bool> *filesInDb);
	static bool ExecuteCommand(const char *command, std::vector<std::vector<std::string>>* result, bool getRowId = false, int *rowId = NULL);
	static std::string GetDateOfModification(boost::filesystem::path p, bool *isModified, bool *doesExsist, std::string *id);
	static sqlite3* GetConnection();
	const static char* DATABASE_NAME;
};