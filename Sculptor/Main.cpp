#include "./Classes/Sculptor.cpp"

int main(){
    Sculptor s(101, 101, 101);
    s.setColor(1, 1, 1, 1);
    s.putSphere(40, 40, 30, 20);
    s.putBox(40, 80, 40, 80, 10, 80);
    s.cutBox(40, 80, 40, 80, 10, 80);

    s.writeOFF("Test.off");
}