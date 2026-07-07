#include <cctype>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

// Trim whitespace from both ends
string trim(const string &s) {
  int l = 0, r = (int)s.size() - 1;
  while (l <= r && isspace(s[l]))
    l++;
  while (r >= l && isspace(s[r]))
    r--;
  return s.substr(l, r - l + 1);
}

// Convert to lowercase
string toLower(string s) {
  for (char &c : s)
    c = tolower(c);
  return s;
}

// Parse a set string like "{1,2}" or "{a,b,c}" and return elements
set<string> parseSet(const string &s) {
  set<string> res;
  int i = 0;
  while (i < (int)s.size() && s[i] != '{')
    i++;
  if (i >= (int)s.size())
    return res;
  i++; // skip '{'
  string cur;
  while (i < (int)s.size() && s[i] != '}') {
    if (s[i] == ',' || s[i] == ' ') {
      cur = trim(cur);
      if (!cur.empty())
        res.insert(toLower(cur));
      cur = "";
    } else {
      cur += s[i];
    }
    i++;
  }
  cur = trim(cur);
  if (!cur.empty())
    res.insert(toLower(cur));
  return res;
}

// Parse relation string like "{<1,2>,<2,2>}" and return vector of pairs
vector<pair<string, string>> parseRelation(const string &s) {
  vector<pair<string, string>> res;
  int i = 0;
  while (i < (int)s.size() && s[i] != '{')
    i++;
  if (i >= (int)s.size())
    return res;
  i++; // skip '{'
  while (i < (int)s.size() && s[i] != '}') {
    if (s[i] == '<') {
      i++;
      string x, y;
      while (i < (int)s.size() && s[i] != ',' && s[i] != '>') {
        x += s[i];
        i++;
      }
      x = toLower(trim(x));
      if (i < (int)s.size() && s[i] == ',')
        i++; // skip comma
      while (i < (int)s.size() && s[i] != '>') {
        y += s[i];
        i++;
      }
      y = toLower(trim(y));
      if (i < (int)s.size() && s[i] == '>')
        i++; // skip '>'
      res.push_back({x, y});
    } else {
      i++;
    }
  }
  return res;
}

int main() {
  // Read all input
  string all_input;
  string line;
  while (getline(cin, line)) {
    all_input += line + "\n";
  }

  // Find three brace-enclosed parts
  vector<string> parts;
  int i = 0;
  while (i < (int)all_input.size()) {
    if (all_input[i] == '{') {
      int j = i + 1;
      int depth = 1;
      while (j < (int)all_input.size() && depth > 0) {
        if (all_input[j] == '{')
          depth++;
        else if (all_input[j] == '}')
          depth--;
        j++;
      }
      parts.push_back(all_input.substr(i, j - i));
      i = j;
    } else {
      i++;
    }
  }

  if (parts.size() < 3) {
    // Not enough parts
    return 0;
  }

  string setA_str = parts[0];
  string setB_str = parts[1];
  string rel_str = parts[2];

  set<string> A = parseSet(setA_str);
  set<string> B = parseSet(setB_str);
  vector<pair<string, string>> R = parseRelation(rel_str);

  // Check if it's a function
  map<string, string> func; // mapping from x to y
  bool isFunc = true;

  for (auto &p : R) {
    string x = p.first, y = p.second;
    // Check that x is in A (or at least not checked strictly? requirement says
    // f ⊆ A×B) We'll check x in A and y in B
    if (A.find(x) == A.end() || B.find(y) == B.end()) {
      isFunc = false;
      break;
    }
    if (func.find(x) != func.end()) {
      // x maps to a different y -> not a function
      if (func[x] != y) {
        isFunc = false;
        break;
      }
      // else duplicate pair, ignore
    } else {
      func[x] = y;
    }
  }

  // Check every element of A has a mapping
  if (isFunc) {
    for (auto &x : A) {
      if (func.find(x) == func.end()) {
        isFunc = false;
        break;
      }
    }
  }

  if (!isFunc) {
    cout << setA_str << " -> " << setB_str << ":nf" << endl;
    return 0;
  }

  // Check injective (单射): all values distinct
  set<string> values;
  bool injective = true;
  for (auto &kv : func) {
    if (values.find(kv.second) != values.end()) {
      injective = false;
      break;
    }
    values.insert(kv.second);
  }

  // Check surjective (满射): every element of B is a value
  bool surjective = true;
  for (auto &y : B) {
    if (values.find(y) == values.end()) {
      surjective = false;
      break;
    }
  }

  string type;
  if (injective && surjective)
    type = "s";
  else if (injective)
    type = "d";
  else if (surjective)
    type = "m";
  else
    type = "f";

  cout << setA_str << " -> " << setB_str << ":" << type << endl;

  return 0;
}
