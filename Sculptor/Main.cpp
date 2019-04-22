#include "./Classes/Sculptor.cpp"

//Test example
int main(){
    Sculptor s(101, 101, 101);
    s.setColor(1, 1, 1, 1);
    s.putSphere(40, 40, 30, 20);
    s.putSphere(80, 80, 30, 20);
    s.putSphere(60, 60, 80, 20);
    s.putBox(40, 80, 40, 80, 10, 80);
    s.writeOFF("Test.off");
}
