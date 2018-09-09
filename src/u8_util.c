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
#include <assert.h>
#include <utf8proc.h>
#include "u8_util.h"

#define isutf(c) (((c)&0xC0)!=0x80)

static const uint32_t offsetsFromUTF8[6] = {
  0x00000000UL, 0x00003080UL, 0x000E2080UL,
  0x03C82080UL, 0xFA082080UL, 0x82082080UL
};

void u8_state_init(u8_state_t *state) {
  state->ix = -1;
  for (int i=0; i < MAX_STATE_SLOTS; i++)
    state->pos[i] = 0;
}

int u8_state_decrement(const u8_state_t *state) {
  assert (state->ix != -1);
  int prev = state->ix - 1;
  if (prev < 0) prev = MAX_STATE_SLOTS - 1;
  return prev;
}

int u8_state_increment(const u8_state_t *state) {
  int next = state->ix + 1;
  if (next >= MAX_STATE_SLOTS) next = 0;
  return next;
}

int u8_state_last_delta(const u8_state_t *state) {
  int prev = u8_state_decrement(state);
  int delta = state->pos[state->ix] - state->pos[prev];
  return delta >= 0 ? delta : 0;
}

int u8_state_peek(u8_state_t *state) {
  if (state->ix == -1) return 0;
  return state->pos[state->ix];
}

void u8_state_push(u8_state_t *state, int ix) {
  int next = u8_state_increment(state);
  state->pos[next] = ix;
  state->ix = next;
}

int u8_state_pop(u8_state_t *state) {
  if (state->ix == -1) return 0;
  int result = state->pos[state->ix];
  int prev = u8_state_decrement(state);
  state->ix = prev;
  return result;
}

/* reads the next utf-8 sequence out of a string, updating an index */
uint32_t u8_nextchar(const char *s, struct u8_state *state)
{
  uint32_t ch = 0;
  int sz = 0;
  int ix = u8_state_peek(state);
  
  do {
    ch <<= 6;
    ch += (unsigned char)s[(ix)++];
    sz++;
  } while (s[ix] && !isutf(s[ix]));
  ch -= offsetsFromUTF8[sz-1];
  
  u8_state_push(state, ix);
  return ch;
}
