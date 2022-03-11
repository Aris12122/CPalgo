#include <iostream>
//#pragma GCC target("popcnt")
inline int get(long long x){
    return __builtin_popcountll(x);
}

int main(){
    long long N = 1e10;
    while(N--) get(LLONG_MAX);
    return 0;
}
/*
N   -   time
1e8     0.560 s
1e9     5.104 s
1e10    47.534 s

#pragma GCC target("popcnt")
N   -   time
1e8     0.274 s
1e9     2.075 s
1e10    19.240 s
*/
