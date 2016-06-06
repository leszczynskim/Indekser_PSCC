#include "stdafx.h"
#include "DBOperations.h"
using namespace std;

const char* DBOperations::DATABASE_NAME = "IndexerDB.db";
void DBOperations::Create(const std::string scriptToRun, std::unordered_map<std::string, bool> *filesInDb)
{
	ifstream fin;
	fin.exceptions(ios::badbit | ios::failbit | ios::eofbit);
	fin.open("script.txt");
	string contents((istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
	auto x = contents.c_str();
	fin.close();
	ExecuteCommand(contents.c_str(), NULL);
	char*query = "select filepath from filetable";
	std::vector<std::vector<std::string>> res;
	ExecuteCommand(query, &res);
	for (auto &x : res)
		filesInDb->insert(FilePair(x[0], false));
}

int command_callback(void * p_data, int num_fields, char ** p_fields, char ** p_col_names)
{
	std::vector<std::vector<string>>* records = static_cast<std::vector<std::vector<string>>*>(p_data);
	try {
		records->emplace_back(p_fields, p_fields + num_fields);
	}
	catch (...) {
		return 1;
	}
	return 0;
}

bool DBOperations::ExecuteCommand(const char * command, std::vector<std::vector<std::string>>* result, bool getRowId, int * rowId)
{
	int  rc;
	char *zErrMsg = 0;
	sqlite3 *db = GetConnection();
	if (!result) rc = sqlite3_exec(db, command, NULL, 0, &zErrMsg);
	else rc = sqlite3_exec(db, command, command_callback, result, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		result = NULL;
		sqlite3_free(zErrMsg);
		return false;
	}
	if (getRowId)
	{
		*rowId = (int)sqlite3_last_insert_rowid(db);
	}
	sqlite3_close(db);
	return true;
}

std::string DBOperations::GetDateOfModification(boost::filesystem::path p, bool *isModified, bool *doesExsist, std::string *id)
{
	std::time_t t = boost::filesystem::last_write_time(p);
	char buff[20];
	strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&t));
	std::vector<std::vector<string>> result;
	string command("Select dateofmod, id from filetable where filepath='");
	command += p.string() + string("'");
	ExecuteCommand(command.c_str(), &result);
	string date(buff);
	*doesExsist = result.size() != 0;
	*isModified = result.size() != 0 && date != result[0][0];
	*id = result.size() != 0 ? result[0][1] : "-1";
	return date;
}

void DBOperations::RemoveFileFromDB(std::string filename)
{
	string com = "select id from filetable where filepath='" + filename + "'";
	std::vector<std::vector<string>> res, res1;
	DBOperations::ExecuteCommand(com.c_str(), &res);
	com = "select ft.id, fo.item_id, fo.typ_id from filetable ft join file_object fo on fo.file_id = ft.id where ft.id = " + res[0][0];
	DBOperations::ExecuteCommand(com.c_str(), &res1);
	int typ = boost::lexical_cast<int>(res1[0][2]);
	string tableName = "";
	switch (typ)
	{
	case FIXTURE:
		tableName = "fixture";
		break;
	case TOOLBLOCK:
		tableName = "toolblock";
		break;
	case ITD:
		tableName = "itd";
		break;
	}
	if (res1.size() == 0) return;
	com = "delete from " + tableName + " where id = " + res1[0][1];
	for (int i = 1; i < res1.size(); i++) com += " or id = " + res1[i][1];
	com += "; delete from file_object where file_id = " + res[0][0] + ";";
	com += " delete from filetable where id = " + res[0][0];
	DBOperations::ExecuteCommand(com.c_str(), NULL);
}

sqlite3 * DBOperations::GetConnection()
{
	int  rc;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE_NAME, &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return NULL;
	}
	return db;
}
