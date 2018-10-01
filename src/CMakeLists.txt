file(GLOB SOURCES "*.c")
add_library(pinyincompare SHARED ${SOURCES})
target_link_libraries(pinyincompare utf8proc sqlite3)
install(TARGETS pinyincompare DESTINATION /usr/local/lib)
