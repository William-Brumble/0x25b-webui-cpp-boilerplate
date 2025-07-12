#include "features/database/database.h"
#include <iostream>
#include <sqlite3pp/sqlite3pp.h>

sqlite3pp::database db(":memory:");

bool init_db(const char *db_path) {
  if (!db_path) {
    std::cerr << "You must pass in a string" << std::endl;
    return false;
  }

  try {
    db = sqlite3pp::database(db_path);
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Failed to open database: " << e.what() << std::endl;
    return false;
  }
}