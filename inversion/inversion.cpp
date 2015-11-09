#include <iostream>
#include <algorithm>
#include <cstring>
#include <utility>
#include <vector>
using namespace std;

void inspect(const int *, int);

long inversion( int *ary, int start, int len ) { 
  if( len <= 1 ) return 0;
  else if( len == 2 ) {
    if( ary[start] > ary[start+1] ) {
      swap(ary[start], ary[start+1]);
      return 1;
    } else {
      return 0;
    }
  } else {
    long inv_left = inversion( ary, start, len/2 );
    long inv_right = inversion( ary, start + len/2, len - len/2);

    int *copy = new int [len], *org = ary + start;
    memcpy(copy, org, sizeof(int) * len); 
    // Attn: 3rd arg of memcpy is the length of bytes, so sizeof() is necessary !!
    //       the 1st and 2nd arg, take care of the beginning

    int *left = copy, *right = copy + len/2;
    long inv = 0;

    int i = 0, j = 0, k = 0;
    while(  i < len/2 && j < len - len/2 ) {
      if( left[i] > right[j] ){
        inv += len/2 - i;
        org[k] = right[j];
        ++j;
      } else {
        org[k] = left[i];
        ++i;
      }
      ++k;
    }

    memcpy( org + k, i == len/2 ? right + j : left + i, sizeof(int) * (len - k));

    delete [] copy;

    return inv + inv_left + inv_right;
  }
}

void inspect(const int *ary, int len) {
  for(int i = 0; i < len; i++)
    cout<<ary[i]<<' ';
  cout<<endl;
}

int main() {
  vector<int> ary;
  int n;
  while( cin>>n ) ary.push_back(n);
  
  cout << inversion(&ary.front(), 0, ary.size())<<endl;

  return 0;
}
