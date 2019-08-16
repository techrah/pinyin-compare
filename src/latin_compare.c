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

#ifdef _WIN32
__declspec(dllexport)
#else
__attribute__ ((visibility ("default")))
#endif
int latin_compare(void* data, int l1, const void* s1, int l2, const void* s2) {
  int result = 0;
  unsigned char ch1, ch2;
  // utf8proc_ssize_t ll1, ll2;

  u8_state_t state1, state2;
  u8_state_init(&state1);
  u8_state_init(&state2);

  // Remove accents
  // utf8proc_int32_t buf1[l1 * 3], buf2[l2 * 3];
  // ll1 = utf8proc_decompose(s1, l1, buf1, l1 * 3, UTF8PROC_DECOMPOSE | UTF8PROC_STRIPMARK);
  // ll2 = utf8proc_decompose(s2, l2, buf2, l2 * 3, UTF8PROC_DECOMPOSE | UTF8PROC_STRIPMARK);

  int hf1 = homonym_frequency((const char *)s1, &state1);
  int hf2 = homonym_frequency((const char *)s2, &state2);

  unsigned int count1 = u8_state_last_delta(&state1);
  unsigned int count2 = u8_state_last_delta(&state2);

  for (;;) {
    if (count1 >= l1) {
      ch1 = (uint32_t)NULL;
    } else {
      ch1 = utf8proc_tolower(u8_nextchar((const char *)s1, &state1));

     utf8proc_int32_t ch[6];
     utf8proc_decompose_char(ch1, ch, 6, UTF8PROC_DECOMPOSE | UTF8PROC_STRIPMARK, NULL);
     utf8proc_encode_char(*ch, (utf8proc_uint8_t *)&ch1);

      count1 += u8_state_last_delta(&state1);
    }

    if (count2 >= l2) {
      ch2 = (uint32_t)NULL;
    } else {
      ch2 = utf8proc_tolower(u8_nextchar((const char *)s2, &state2));

     utf8proc_int32_t ch[6];
     utf8proc_decompose_char(ch2, ch, 6, UTF8PROC_DECOMPOSE | UTF8PROC_STRIPMARK, NULL);
     utf8proc_encode_char(*ch, (utf8proc_uint8_t *)&ch2);

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

  return result;
}
