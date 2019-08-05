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

unsigned char process_next_char(const void* s, const int l, unsigned int *count, struct u8_state *state, int *tone) {
  unsigned char ch;
  do {
    if (*count >= l) {
      ch = (unsigned char)NULL;
      break;
    }
    ch = utf8proc_tolower(pinyin_normalized_char(u8_nextchar(s, state), tone));
    *count += u8_state_last_delta(state);
  } while (ch && ((ch >= '\x01' && ch <= '\x05') || isseparator(ch)));

  return ch;
}

#ifdef _WIN32
__declspec(dllexport)
#else
__attribute__ ((visibility ("default")))
#endif
int pinyin_compare(void* data, int l1, const void* s1, int l2, const void* s2) {
  int result = 0, result_tone = 0, result_umlaut = 0;
  unsigned char ch1, ch2;
  int tone1 = 0, tone2 = 0;

  u8_state_t state1, state2;
  u8_state_init(&state1);
  u8_state_init(&state2);

  int _l1 = l1 < 0 ? strlen(s1) : l1;
  int _l2 = l2 < 0 ? strlen(s2) : l2;

  int hf1 = homonym_frequency(s1, &state1);
  int hf2 = homonym_frequency(s2, &state2);

  unsigned int count1 = u8_state_last_delta(&state1);
  unsigned int count2 = u8_state_last_delta(&state2);

  for (;;) {
    ch1 = process_next_char(s1, _l1, &count1, &state1, &tone1);
    ch2 = process_next_char(s2, _l2, &count2, &state2, &tone2);

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

    // Keep track of tone difference. May use later.
    // For every pair of tones, calculate difference, until first diff.
    if (!result_tone && tone1 && tone2) {
      result_tone = tone1 - tone2;
      tone1 = 0;
      tone2 = 0;
    };
  }

  // if we get here, normalized strings are exactly the same

  // If at least one tone stayed at zero, force tone difference calc. now
  if (!result_tone) result_tone = tone1 - tone2;

  // Tone difference to be tie breaker?
  if (!result) result = result_tone;

  // otherwise use homonym freq.
  if (!result) result = hf1 - hf2;

bail:
  return result;
}
