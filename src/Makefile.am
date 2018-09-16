lib_LTLIBRARIES = libpinyincompare.la
libpinyincompare_la_SOURCES = \
	pinyin_compare.c \
	pinyin_compare.h \
	pinyin_util.c \
	pinyin_util.h \
	u8_util.c \
	u8_util.h \
	sqlite3_pinyincompare.c
include_HEADERS = pinyin_compare.h pinyin_util.h u8_util.h
libpinyincompare_la_LIBADD = -lutf8proc -lsqlite3
#srcdir = @srcdir@
#VPATH = @srcdir@
