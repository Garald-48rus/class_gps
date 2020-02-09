#include <iostream>
#include <iomanip>
#include"gps_tool.h"
#include<fstream>
using namespace std;

void ffile(string &str)
{

    fstream ffile;

     ffile.open("test",fstream::in | fstream::out | fstream::app| ios_base::binary);

    if(ffile.is_open())
    {
        ffile<<str<<endl;

    }
ffile.close();
}

string ofile (string &str)
 {



    fstream ofile;

    ofile.open( "test", fstream::out| fstream::in |ios_base::binary);


     if(ofile.is_open())
     {


         while (!ofile.eof()) {

             ofile>>str;

         }






     }

     ofile.close();

     return str;

}


int main()
{
    setlocale(LC_ALL, "RU");

   Navigetion::Point_2D p1(52.64187105830553 ,39.66726445397543 );
   Navigetion::Point_2D p2(52.64208557032334,39.6668847840356);
   Navigetion::Point_2D p3(52.64062732882991 , 39.66305493125725);
   Navigetion::Point_2D p4(52.64020722096754,39.66339293249345);
   Navigetion::Point_2D p5(52.63956768911745 ,39.66116586747145);
   Navigetion::Point_2D p6(52.63716100383443, 39.66271284686925);
   Navigetion::Point_2D p7(52.63689051966875,39.66233018573829);
   Navigetion::Point_2D p8(52.6351618636515,39.66240645226425);
   Navigetion::Point_2D p9(52.63474934492878,39.66291230306805);
   Navigetion::Point_2D p10(52.63426787798252,39.66141789499217);
   Navigetion::Point_2D p11(52.63411838806992,39.66152179621229);
   Navigetion::TrackPoints2D tr{p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11};

  /*vector<Navigetion::Point_2D> point { };

for(auto i : point)
    tr.add(i);
*/
   //cout<<tr.distance()<<endl;
/*
   cout<<tr.num_of_points()<<endl;
 cout<<p1.DistanceTo(p2)+p2.DistanceTo(p3)+p3.DistanceTo(p4)+p4.DistanceTo(p5)
          +p5.DistanceTo(p6)+p6.DistanceTo(p7)+p7.DistanceTo(p8)+
          p8.DistanceTo(p9)+p9.DistanceTo(p10)+p10.DistanceTo(p11)<<" Метров"<<endl;
*/



    return 0;
}
