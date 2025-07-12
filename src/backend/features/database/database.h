#pragma once
#include <sqlite3pp/sqlite3pp.h>

extern sqlite3pp::database db;

bool init_db(const char *db_name);