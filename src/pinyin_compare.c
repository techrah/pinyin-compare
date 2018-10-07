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

#include <ctype.h>
#include <string.h>
#include "macros.h"
#include "pinyin_util.h"
#include "pinyin_compare.h"

int pinyin_compare(void* data, int l1, const void* s1, int l2, const void* s2) {
  int result = 0, result_tone = 0, result_umlaut = 0;
  unsigned char ch1, ch2;
  int tone1 = 0, tone2 = 0;

  u8_state_t state1, state2;
  u8_state_init(&state1);
  u8_state_init(&state2);

  int _l1 = l1 < 0 ? strlen(s1) : l1;
  int _l2 = l1 < 0 ? strlen(s2) : l2;

  int hf1 = homonym_frequency(s1, &state1);
  int hf2 = homonym_frequency(s2, &state2);

  unsigned int count1 = u8_state_last_delta(&state1);
  unsigned int count2 = u8_state_last_delta(&state2);

  for (;;) {
    do {
      if (count1 >= _l1) {
        ch1 = (unsigned char)NULL;
        break;
      }
      ch1 = utf8proc_tolower(pinyin_normalized_char(u8_nextchar(s1, &state1), &tone1));
      count1 += u8_state_last_delta(&state1);
    } while (ch1 && ((ch1 >= '\x01' && ch1 <= '\x05') || isseparator(ch1)));

    do {
      if (count2 >= _l2) {
        ch2 = (unsigned char)NULL;
        break;
      }
      ch2 = utf8proc_tolower(pinyin_normalized_char(u8_nextchar(s2, &state2), &tone2));
      count2 += u8_state_last_delta(&state2);
    } while (ch2 && ((ch2 >= '\x01' && ch2 <= '\x05') || isseparator(ch2)));

    // Reached end of word and haven't exited loop yet?
    if (!ch1 && !ch2) {
      result = result_umlaut;
      break; // normalized strings are exactly the same.
    }
    else if (!ch1 && ch2) {
      result = result ? result : -1;
      break;
    }
    else if (!ch2) {
      result = result ? result : 1;
      break;
    }

    result = (int)pinyin_ordinal(ch1, true) - (int)pinyin_ordinal(ch2, true);
    result_umlaut = (int)pinyin_ordinal(ch1, false) - (int)pinyin_ordinal(ch2, false);

    // We're comparing pure string w/o tones. Any difference, we're done.
    if (result) goto bail;

    // Keep track of first tone difference. May use later.
    if (!result_tone) result_tone = tone1 - tone2;
  }

  // if we get here, normalized strings are exactly the same

  // Diff. in tones?
  if (!result) result = result_tone;

  // otherwise use homonym freq.
  if (!result) result = hf1 - hf2;

bail:
  return result;
}

int pinyin_exact_compare(void* data, int l1, const void* s1, int l2, const void* s2) {
  int result = 0;
  uint32_t ch1, ch2;

  u8_state_t state1, state2;
  u8_state_init(&state1);
  u8_state_init(&state2);

  int _l1 = l1 < 0 ? strlen(s1) : l1;
  int _l2 = l1 < 0 ? strlen(s2) : l2;

  /*
  utf8proc_map((utf8proc_uint8_t *)_s1, l1, &s1,
    UTF8PROC_NULLTERM | UTF8PROC_STABLE | UTF8PROC_DECOMPOSE);

  utf8proc_map((utf8proc_uint8_t *)_s2, l2, &s2,
    UTF8PROC_NULLTERM | UTF8PROC_STABLE | UTF8PROC_DECOMPOSE);
  */

  int hf1 = homonym_frequency((const char *)s1, &state1);
  int hf2 = homonym_frequency((const char *)s2, &state2);

  unsigned int count1 = u8_state_last_delta(&state1);
  unsigned int count2 = u8_state_last_delta(&state2);

  for (;;) {
    if (count1 >= _l1) {
      ch1 = (uint32_t)NULL;
    } else {
      ch1 = utf8proc_tolower(u8_nextchar((const char *)s1, &state1));
      count1 += u8_state_last_delta(&state1);
    }

    if (count2 >= _l2) {
      ch2 = (uint32_t)NULL;
    } else {
      ch2 = utf8proc_tolower(u8_nextchar((const char *)s2, &state2));
      count2 += u8_state_last_delta(&state2);
    }

    result = ch1 - ch2;

    // Reached end of a word and haven't exited loop yet?
    if (!ch1 || !ch2) break;

    // Any difference, we're done.
    if (result) break;
  }

  // Strings are equal so far, so let's check homonym frequency
  if (!result) result = hf1 - hf2;

  // Finally, return result
  return result;
}
