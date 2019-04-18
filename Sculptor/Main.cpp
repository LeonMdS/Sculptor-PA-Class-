#ifndef _IOSTR
#define _IOSTR
#include <iostream>
#endif

#include "./Classes/Sculptor.cpp"

using namespace std;

int main(){
    Sculptor s(5, 5, 5);
    s.setColor(1, 1, 1, 1);
    s.putVoxel(0, 0, 0);
    s.writeOFF("Test.off");
}