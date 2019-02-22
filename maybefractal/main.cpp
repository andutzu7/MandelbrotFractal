#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
double mapToReal(int x,int imgWidth,double minR,double maxR)
{
    double range=maxR-minR;
    return x*(range/imgWidth)+minR;
}
double mapToImaginary(int y,int imgHeight,double minI,double maxI)
{
    double range=maxI-minI;
    return y*(range/imgHeight)+minI;
}
int findN(double cr,double ci,int maxIterations)
{
    int i=0;
    double zr=0.0,zi=0.0;
    while(i<maxIterations&& zr*zr+zi*zi<4.0)
    {
        double xtemp=zr*zr-zi*zi+cr;
        zi=2.0*zr*zi+ci;
        zr=xtemp;
        i++;
    }
    return i;

}
int main()
{
    ifstream fin("input.txt");
    int imgWidth,imgHeight,maxN;
    double minR,maxR,minI,maxI;
    if(!fin)
    {
        cout<<"Eroare...Nu s-a putut accesa fisierul \n";
        return -1;
    }
    fin>>imgWidth>>imgHeight>>maxN;
    fin>>minR>>maxR>>minI>>maxI;
    fin.close();//I need to start doing that...
    //output file
    ofstream fout("image.ppm");
    //urmatorii pasi sunt obligatorii pt lucrul cu ppm
    fout<<"P3"<<endl;//Magic number, necesar pt formatul asta de ppm
    fout<<imgWidth<<" "<<imgHeight<<endl;//dimensiuni
    fout<<"255"<<endl;//maximul de culoare pe care un pixel poate sa l ia(max r max g max b)

    //parcurgem pixel cu pixel
    for(int i=0; i<imgHeight; i++)
    {
        for(int j=0; j<imgWidth; j++)
        {
            double cr=mapToReal(j,imgWidth,minR,maxR);
            double ci=mapToImaginary(i,imgHeight,minI,maxI);
            int n=findN(cr,ci,maxN);
            //color time
            int r=((n)%255);
            int g=((int)(n*sin(n))%255);
            int b=((n*n)%255);
            fout<<r<<" "<<g<<" "<<b<<" ";
        }
        fout<<endl;
    }
    fout.close();
    return 0;
}
