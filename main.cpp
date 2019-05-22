#include "sculptor.cpp"
#include <iostream>

using namespace std;

//Test example
/**
 * @brief main
 * @return
 */
int main(){
    Sculptor s(100, 100, 100);
    s.setColor(1, 1, 1, 1);
    s.putSphere(50,50, 50, 49);
    s.writeOFF("teste.off");
    return 0;
}
