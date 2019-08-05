#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

#include "pinyin_compare.h"

#ifdef _WIN32
__declspec(dllexport)
#else
__attribute__ ((visibility ("default")))
#endif
int sqlite3_pinyincompare_init(
  sqlite3 *db,
  char **pzErrMsg,
  const sqlite3_api_routines *pApi
){
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
  sqlite3_create_collation(db, "pinyin", SQLITE_UTF8, NULL, pinyin_compare);
  sqlite3_create_collation(db, "latin", SQLITE_UTF8, NULL, latin_compare);
  return rc;
}
