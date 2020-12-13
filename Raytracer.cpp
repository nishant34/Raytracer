#include <bits/stdc++.h> 
using namespace std;
#include<cmath>
#include<fstream>
using namespace std;

struct Vector{
 double x,y,z;
 Vector(){
     x=y=z=0;

 }
 Vector(double a,double b, double c){
     x=a,y=b,z=c;
 }
 Vector normalize(){
     double mg = sqrt(x*x+y*y+z*z);
     return Vector(x/mg,y/mg,z/mg);
 }
 Vector operator * (double d){
     Vector result;
     result.x= x*d;
     result.y= y*d;
     result.z = z*d;
     return result ;
 }
 Vector operator / (double d){
     Vector result;
     result.x= x/d;
     result.y= y/d;
     result.z = z/d;
     return result ;
 }
 
 Vector operator + (Vector v){
     Vector result;
     result.x= x+v.x;
     result.y= y+ v.y;
     result.z = z+v.z;
     return result ;
 }
 Vector operator - (Vector v){
     Vector result;
     result.x= x-v.x;
     result.y= y- v.y;
     result.z = z-v.z;
     return result ;
 }
};

struct ray{
 Vector o; //origin
 Vector d; //direction
 ray(Vector i,Vector j){
     o = i,d=j;
 } 
 
};

double dot(Vector v,Vector b){
    return (v.x*b.x+v.y*b.y+v.z*b.z);
}

struct sphere{
    
    Vector c;
    double r;
    sphere(Vector k,double b){
        c = k;
        r = b;
    }
    Vector getNormal(Vector p){
        return (c-p)/r;
    }
    bool intersect(ray ray_1, double &t){
        Vector o = ray_1.o;
        Vector d = ray_1.d;
        Vector oc = o-c;
        double b = 2*dot(oc,d);
        double c = dot(oc,oc)-r*r;
        double disc = b*b -4*c;
        if (disc<0) 
        {return false;}
        else{
            disc = sqrt(disc);
            double t0 = -b-disc;
            double t1 = -b+disc;
            t = (t0<t1)?t0:t1;
            
        }
        return true;

    }
};
struct Color{
    double r,g,b;
    Color(){r=g=b=0;}
    Color(double i,double j,double k){r=i,g=j,b=k;}
    Color operator * (double d){return Color(r*d,g*d,b*d);}
    Color operator + (Color c){return Color((r+c.r)/2,(g+c.g)/2,(b+c.b)/2);}


};

int main(){
    
    const int W = 500;
    const int H = 500;
    
    ofstream out("out.ppm");
    out<<"P3\n"<<W<<"\n"<<H<<"\n"<<"255\n";
    
    Color white(255,255,255);
    Color red(255,0,0);
    sphere Sphere(Vector(W/2,H/2,50),50);
    sphere light(Vector(W/2,0,50),1);
    vector<vector<Color>>pixel_col(W,vector<Color>(H));
    for(int y=0;y<H;y++){
        for(int x=0;x<W;x++){
            //Send a ray through each pixel
            ray curr_ray(Vector(x,y,0),Vector(0,0,1));
             
            double t = 20000;
            if (Sphere.intersect(curr_ray,t)){
                //intersection
                Vector pi = curr_ray.o +curr_ray.d*t;
                //color the pixel
                Vector L = light.c-pi;
                Vector N = Sphere.getNormal(pi);
                double dt = dot(L.normalize(),N.normalize());
                pixel_col[y][x] = red+(white*dt);
                

            }
            out<<(int)pixel_col[y][x].r<<endl;
            out<<(int)pixel_col[y][x].g<<endl;
            out<<(int)pixel_col[y][x].b<<endl;
            
        }
       
    }
    cout<<"Completed"<<endl;
    
    
    return 0;
}