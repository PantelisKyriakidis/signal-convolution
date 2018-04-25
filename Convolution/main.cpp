#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void convolve(double x[],double y[],double h[],int xlen,int ylen,int hlen){
    for(int i=0;i<(ylen-hlen+1);i++){      //the algorithm for the convolve.
        for(int j=0;j<hlen;j++){            //every time the second for ends we have a y value (result).
            y[i]+=x[i+j]*h[j];
        }
    }
}

void hreverse(double h[],int hlen){
    double temp[hlen]={0};          //i make a temporary array in which i pass all the h values for the end.
    int j=0;                        //then i copy temp to h so h is now reversed.
    for (int i=hlen-1;i>=0;i--){
        temp[j]=h[i];
        j++;
    }
    for (int i=0;i<hlen;i++){
        h[i]=temp[i];
    }
}

int main()
{
    ifstream xFile("x.txt");

    int xlen=0;
    double temp;
    if (xFile.is_open())        //checking if x is open.
        while(xFile>>temp){     //i have a counter(xlen) to see how many numbers the input has.
            xlen+=1;
        }
    else{
        cout<< "error opening x.txt..."<<endl;  //error message
        exit(0);
    }

    double x[xlen]={0};
    xFile.close();

    xFile.open("x.txt");

    if (xFile.is_open()){
        for(int i=0; i<xlen;i++){           //giving x array values from x.txt
            xFile >> x[i];
        }
    }
    else{
        cout<< "error opening x.txt..."<<endl;
        exit(0);
    }
    xFile.close();

    ifstream hFile("h.txt");

    int hlen=0;
    if (hFile.is_open())
        while(hFile>>temp){
            hlen+=1;
        }
    else{
        cout<< "error opening h.txt..."<<endl;
        exit(0);
    }
    if(hlen>xlen){
        cout<<"length of x < length of h"<<endl;
        exit(0);
    }
    double h[hlen]={0};
    hFile.close();

    hFile.open("h.txt");

    if (hFile.is_open()){
        for(int i=0; i<hlen;i++){
            hFile >> h[i];
        }
    }
    else{
        cout<< "error opening h.txt..."<<endl;
        exit(0);
    }
    hFile.close();

    hreverse(h,hlen);       //reversing h array

    int ylen=xlen;
    double y[ylen]={0};
    convolve(x,y,h,xlen,ylen,hlen);     //calling convolve method

    ofstream yFile("y.txt");

    if(yFile.is_open())             //writing the results to y.txt output
        for (int i=0;i<ylen;i++)
            yFile<<y[i]<<endl;
    else{
        cout<< "error opening y.txt..."<<endl;
        terminate();
    }

    return 0;
}
