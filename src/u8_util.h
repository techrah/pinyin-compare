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

#ifndef u8_util_h
#define u8_util_h

#include <stdlib.h>

#define MAX_STATE_SLOTS 4

struct u8_state {
  int pos[MAX_STATE_SLOTS];  // character index positions
  int ix;                    // last valid ix in pos array
};
typedef struct u8_state u8_state_t;

void u8_state_init(u8_state_t *state);
int u8_state_decrement(const u8_state_t *state);
int u8_state_increment(const u8_state_t *state);
int u8_state_last_delta(const u8_state_t *state);
int u8_state_peek(u8_state_t *state);
void u8_state_push(u8_state_t *state, int ix);
int u8_state_pop(u8_state_t *state);
uint32_t u8_nextchar(const char *s, struct u8_state *state);

#endif /* u8_util_h */
