#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int _quickSort( int * v, int begin, int len) {
  if( len <= 1 ) return 0;
  // using first
  // do noting

  // using final
  // swap(v[begin], v[begin+len-1]);

  // using mean of three
  // int end = begin + len - 1;   
  // int med = (begin + begin + len - 1) / 2;
  // vector<pair<int,int>> tmp { {v[begin], begin}, {v[med], med}, {v[end], end} };
  // TODO: how to use array here with list initialization
  // sort(tmp.begin(), tmp.end());
  // med = tmp[1].second;
  // swap(v[begin], v[med]); 

  int i = begin, j = begin + 1;
  for(; j < begin + len; j++) {
    if(v[j] < v[begin]) swap(v[++i], v[j]); // Attn: assume that the array is unique.
  }
  swap(v[begin], v[i]);

  int cmp_left = _quickSort(v, begin, i - begin);
  int cmp_right = _quickSort(v, i+1, begin + len - i - 1);
  return cmp_left + cmp_right + len - 1;
}

int quickSort(vector<int> &v) {
  return _quickSort(v.data(), 0, v.size());
}

void inspect(const int *v, int len) {
  for(int i = 0; i < len; i++)
    cout<<v[i]<<' ';
  cout<<endl;
}

void inspect(const vector<int> & v) {
  for(int n : v) cout<<n<<' ';
  cout<<endl;
}

int main() {
  vector<int> v;
  int n;
  while(cin>>n) v.push_back(n);
  cout<<quickSort(v);
  return 0;
}

void test() {
  vector<int> a = { 3, 8, 2, 5, 1, 4, 7, 6 };
  inspect(a);
  cout<<quickSort(a)<<endl;
  inspect(a);
}
  
