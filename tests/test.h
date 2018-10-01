#ifndef __test_h__
#define __test_h__

#include "../src/pinyin_compare.h"

static const char * CAP_A_MACRON = "\u0100";
static const char * CAP_A_ACUTE  = "\u00C1";
static const char * CAP_A_CARON  = "\u01CD";
static const char * CAP_A_GRAVE  = "\u00C0";

static const char * CAP_E_MACRON = "\u0112";
static const char * CAP_E_ACUTE  = "\u00C9";
static const char * CAP_E_CARON  = "\u011A";
static const char * CAP_E_GRAVE  = "\u00C8";

static const char * CAP_I_MACRON = "\u012A";
static const char * CAP_I_ACUTE  = "\u00CD";
static const char * CAP_I_CARON  = "\u01CF";
static const char * CAP_I_GRAVE  = "\u00CC";

static const char * CAP_O_MACRON = "\u014C";
static const char * CAP_O_ACUTE  = "\u00D3";
static const char * CAP_O_CARON  = "\u01D1";
static const char * CAP_O_GRAVE  = "\u00D2";

static const char * CAP_U_MACRON = "\u016A";
static const char * CAP_U_ACUTE  = "\u00DA";
static const char * CAP_U_CARON  = "\u01D3";
static const char * CAP_U_GRAVE  = "\u00D9";

static const char * CAP_U_DIAERESIS_MACRON = "\u01D5";
static const char * CAP_U_DIAERESIS_ACUTE  = "\u01D7";
static const char * CAP_U_DIAERESIS_CARON  = "\u01D9";
static const char * CAP_U_DIAERESIS_GRAVE  = "\u01DB";

static const char * SM_A_MACRON = "\u0101";
static const char * SM_A_ACUTE  = "\u00E1";
static const char * SM_A_CARON  = "\u01CE";
static const char * SM_A_GRAVE  = "\u00E0";

static const char * SM_E_MACRON = "\u0113";
static const char * SM_E_ACUTE  = "\u00E9";
static const char * SM_E_CARON  = "\u011B";
static const char * SM_E_GRAVE  = "\u00E8";

static const char * SM_I_MACRON = "\u012B";
static const char * SM_I_ACUTE  = "\u00ED";
static const char * SM_I_CARON  = "\u01D0";
static const char * SM_I_GRAVE  = "\u00EC";

static const char * SM_O_MACRON = "\u014D";
static const char * SM_O_ACUTE  = "\u00F3";
static const char * SM_O_CARON  = "\u01D2";
static const char * SM_O_GRAVE  = "\u00F2";

static const char * SM_U_MACRON = "\u016B";
static const char * SM_U_ACUTE  = "\u00FA";
static const char * SM_U_CARON  = "\u01D4";
static const char * SM_U_GRAVE  = "\u00F9";

static const char * SM_U_DIAERESIS_MACRON = "\u01D6";
static const char * SM_U_DIAERESIS_ACUTE  = "\u01D8";
static const char * SM_U_DIAERESIS_CARON  = "\u01DA";
static const char * SM_U_DIAERESIS_GRAVE  = "\u01DC";

__inline int _pinyin_compare(const char *s1, const char* s2) {
  return pinyin_compare(0, strlen(s1), s1, strlen(s2), s2);
}

#endif
