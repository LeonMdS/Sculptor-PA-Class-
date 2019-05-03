#include "./Classes/Sculptor.cpp"

int main(){
    Sculptor s(100, 100, 100);
    s.setColor(0, 0, 0, 0.5);
    
    s.putBox(0,99,0,99,0,99);
    s.cutBox(0,99,1,98,1,98);
    
    s.setColor(1,0,0,1);
    s.putSphere(20,20,20,15);
    
    s.setColor(1,0,0,1);
    s.putBox(70,90,70,90,70,90);
    s.cutSphere(80,80,80,15);

    s.setColor(0,1,1,1);
    s.putEllipsoid(60,20,50,25,10,15);

    s.setColor(0,0,1,1);
    s.putBox(40,60,20,40,70,90);
    s.cutEllipsoid(50,30,60,25,10,15);
    
    s.setColor(1,1,1,1);
    s.putVoxel(40,40,40);
    s.putVoxel(40,42,40);
    s.putVoxel(40,40,42);
    s.putVoxel(42,40,40);
    s.putVoxel(44,40,40);
    s.putVoxel(40,44,40);
    s.putVoxel(40,40,44);
    s.putVoxel(42,40,42);
    s.putVoxel(44,40,44);
    
    s.cutVoxel(45,99,45);
    s.cutVoxel(47,99,45);
    s.cutVoxel(49,99,45);
    s.cutVoxel(47,99,45);
    s.cutVoxel(47,99,47);
    s.cutVoxel(47,99,49);
    s.cutVoxel(49,99,45);
    s.cutVoxel(49,99,47);
    s.cutVoxel(49,99,49);
    
    s.writeOFF("teste.off");
    s.writeVECT("teste.vect");
    
    return 0;
}
