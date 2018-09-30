/*
Copyright 2009 Ryan Homer

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <stdlib.h>
#include <ctype.h>
#include "macros.h"
#include "u8_util.h"
#include "pinyin_util.h"

// Converts subscript number from 0 to 9 to standard int format
// Returns -1 if invalid input.
int pinyin_subscript(uint32_t digit) {
  int result;
  if (digit == 0x2070) result = 0;
  else if (digit == 0x00B9) result = 1;
  else if (digit == 0x00B2) result = 2;
  else if (digit == 0x00B3) result = 3;
  else if (digit >= 0x2074 && digit <= 0x2079) result = digit - 0x2070;
  else result = -1;
  return result;
}

int homonym_frequency(const char *word, u8_state_t *state) {
  uint32_t aChar;
  int units = 0, tens = 0;
  
  // First digit
  aChar = u8_nextchar(word, state);
  tens = pinyin_subscript(aChar);
  if (tens == -1) {
    u8_state_pop(state);
    // everything else equal, no homonym freq. < zero HF.
    return -1;
  }
  
  // second digit
  aChar = u8_nextchar(word, state);
  units = pinyin_subscript(aChar);
  if (units == -1) {
    units = tens;
    tens = 0;
  }
  if (!tens) u8_state_pop(state);
  return (10 * tens) + units;
}

unsigned char pinyin_normalized_char(uint32_t ch, int *tone) {
  static const unsigned short width = 6;
  static const uint32_t chs[] = {
    // letters with tones
    0x0041, 0x0100, 0x00C1, 0x01CD, 0x00C0, 0x1EA0, // A
    0x0061, 0x0101, 0x00E1, 0x01CE, 0x00E0, 0x1EA1, // a
    0x0045, 0x0112, 0x00C9, 0x011A, 0x00C8, 0x1EB8, // E
    0x0065, 0x0113, 0x00E9, 0x011B, 0x00E8, 0x1EB9, // e
    0x0049, 0x012A, 0x00CD, 0x01CF, 0x00CC, 0x1ECA, // I
    0x0069, 0x012B, 0x00ED, 0x01D0, 0x00EC, 0x1ECB, // i
    0x004F, 0x014C, 0x00D3, 0x01D1, 0x00D2, 0x1ECC, // O
    0x006F, 0x014D, 0x00F3, 0x01D2, 0x00F2, 0x1ECD, // o
    0x0055, 0x016A, 0x00DA, 0x01D3, 0x00D9, 0x1EE4, // U
    0x0075, 0x016B, 0x00FA, 0x01D4, 0x00F9, 0x1EE5, // u
    0x00DC, 0x01D5, 0x01D7, 0x01D9, 0x01DB, 0x01DB, // Ü
    0x00FC, 0x01D6, 0x01D8, 0x01DA, 0x01DC, 0x01DC, // ü
    // tones by themselves, e.g.: ụ̌ is represented as ụ (0x1EE5) +  ̌ (0x30C)
    0x0001, 0x0304, 0x0304, 0x0304, 0x0304, 0x0304, // 1st tone
    0x0002, 0x0301, 0x0301, 0x0301, 0x0301, 0x0301, // 2nd tone
    0x0003, 0x030C, 0x030C, 0x030C, 0x030C, 0x030C, // 3rd tone
    0x0004, 0x0300, 0x0300, 0x0300, 0x0300, 0x0300  // 4rd tone
  };
  for (int i = 0; i < sizeof(chs)/sizeof(uint32_t); i++) {
    if (chs[i] == ch) {
      int ix = i / width * width;
      if (tone) *tone = i % width;
      if (*tone == 5) *tone = 0; // col 5 is for vowels with . underneath, not a tone.
      return chs[ix];
    }
  }
  if (tone) *tone = 0;
  return ch;
}

int pinyin_ordinal(uint32_t ch, utf8proc_bool ignore_umlaut) {
  static const uint32_t chs[] = {
    0x01, 0x002, 0x003, 0x004, 0x005,
    0x61, 0x101, 0x0E1, 0x1CE, 0x0E0, // a
    'b', 'c', 'd',
    0x65, 0x113, 0x0E9, 0x118, 0x0E8, // e
    'f', 'g', 'h',
    0x69, 0x12B, 0x0ED, 0x1D0, 0x0EC, // i
    'j', 'k', 'l', 'm', 'n',
    0x6F, 0x14D, 0x0F3, 0x1D2, 0x0F2, // o
    'p', 'q', 'r', 's', 't',
    0x75, 0x16B, 0x0FA, 0x1D4, 0x0F9, // u
    0xFC, 0x1D6, 0x1D8, 0x1DA, 0x1DC, // ü
    'v', 'w', 'x', 'y', 'z'
  };
  
  for (int i = 0; i < sizeof(chs)/sizeof(uint32_t); i++) {
    if (chs[i] == ch) {
      if (ignore_umlaut && i==46) i=41;
      return i;
    }
  }
  
  return -1;
}

void pinyin_next_word(const char *s, char *word, int *tone, u8_state_t *state) {
  *word = '\0';
  *tone = 0;
  int next_tone = 0;
  enum e_pos {initial, vowels, final_n, final_g, g_pending} pos = initial;
  
  for (;;) {
    unsigned char ch = utf8proc_tolower(pinyin_normalized_char(u8_nextchar(s, state), &next_tone));
    if (!ch || ch=='\'' || ch==' ') break;
    switch (pos) {
      case initial:
        if (isconsonant(ch)) {
          *word++ = ch;
          pos = vowels;
          break;
        } else if (ch=='a' || ch=='e' || ch=='o') {
          pos = vowels;
          // fall through to vowels
        } else {
          *word = '\0';
          return;
        }
      case vowels:
        // final, one or more consecutive vowels, only one tone marked
        
        // tone separated from vowel
        if (ch >= 01 && ch <= 0x4) {
          next_tone = ch;
          ch = '\0';
        }
        
        if (isconsonant(ch)) pos = final_n; // fall through
        else if (isvowel(ch) || !ch /* special case from above */) {
          if (!*tone || (*tone && !next_tone)) {
            if (next_tone) *tone = next_tone;
            if (ch) *word++ = ch;
            break;
          } else {
            // another tone marked vowel? assume the start of a new word
            u8_state_pop(state);
            goto finish;
          }
        } else break; // some other character from vowel decomposition so we can ignore
      case final_n:
        // final, n or ng
        if (ch=='n') {
          *word++ = ch;
          pos = final_g;
        } else {
          // assume start of a new word
          u8_state_pop(state);
          goto finish;
        }
        break;
      case final_g:
        if (ch=='g') {
          pos = g_pending;
          // fall through to g_pending
        } else {
          // assume start of a new word
          u8_state_pop(state);
          goto finish;
        }
      case g_pending:
        if (isconsonant(ch)) {
          // 'g' followed by consonant, so keep 'g'
          *word++ = 'g';
          u8_state_pop(state); // restore 'g'
          goto finish;
        } else {
          // 'g' followed by vowel so don't keep 'g', it belongs to next word.
          u8_state_pop(state); // restore vowel
          u8_state_pop(state); // restore 'g'
        }
        break;
    }
  }
finish:
  *word = '\0';
}
