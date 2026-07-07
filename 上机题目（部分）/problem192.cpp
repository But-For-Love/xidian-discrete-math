#include <cstdio>
char s[999];
int p, v[128];
int E(int x) {
  int l;
  s[p] == '~'   ? (p++, l = 1 - E(4))
  : s[p] == '(' ? (p++, l = E(0), p++)
                : (l = v[s[p]], p++);
  for (;;) {
    if (x < 3 && s[p] == '/' && s[p + 1] == '\\') {
      p += 2;
      l &= E(3);
    } else if (x < 3 && s[p] == '\\' && s[p + 1] == '/') {
      p += 2;
      l |= E(3);
    } else if (x < 2 && s[p] == '-' && s[p + 1] == '>') {
      p += 2;
      l = !l | E(1);
    } else if (x < 1 && s[p] == '<' && s[p + 1] == '-' && s[p + 2] == '>') {
      p += 3;
      l = l == E(1);
    } else
      break;
  }
  return l;
}
int main() {
  scanf("%s", s);
  int vis[26] = {}, n = 0, vars[5];
  for (int i = 0; s[i]; i++) {
    if (s[i] >= 'a' && s[i] <= 'z')
      s[i] -= 32;
    if (s[i] >= 'A' && s[i] <= 'Z')
      vis[s[i] - 'A'] = 1;
  }
  for (int i = 0; i < 26; i++)
    if (vis[i])
      vars[n++] = i + 'A';
  for (int i = 0; i < n; i++)
    printf("%s%c", i ? "\t" : "", vars[i]);
  printf("\t%s\n", s);
  for (int m = 0; m < (1 << n); m++) {
    for (int i = 0; i < n; i++) {
      int val = (m >> (n - 1 - i)) & 1;
      v[vars[i]] = val;
      printf("%s%d", i ? "\t" : "", val);
    }
    p = 0;
    printf("\t%d\n", E(0));
  }
}
