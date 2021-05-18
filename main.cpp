#include <iostream>
#include <iomanip>
#include"gps_tool.h"
#include<fstream>
using namespace std;

int main()
{
  //координаты точек взяты с помощью https://earth.google.com/web/
   Navigetion::Point_2D p1{52.64187105830553 ,39.66726445397543};
   Navigetion::Point_2D p2{52.64208557032334,39.6668847840356};
   Navigetion::Point_2D p3{52.64062732882991 , 39.66305493125725};
   Navigetion::Point_2D p4{52.64020722096754,39.66339293249345};
   Navigetion::Point_2D p5{52.63956768911745 ,39.66116586747145};
   Navigetion::Point_2D p6{52.63716100383443, 39.66271284686925};
   Navigetion::Point_2D p7{52.63689051966875,39.66233018573829};
   Navigetion::Point_2D p8{52.6351618636515,39.66240645226425};
   Navigetion::Point_2D p9{52.63474934492878,39.66291230306805};
   Navigetion::Point_2D p10{52.63426787798252,39.66141789499217};
   Navigetion::Point_2D p11{52.63411838806992,39.66152179621229};
   Navigetion::TrackPoints2D tr{p1,p2,p3,p4,p5,p6,p7,p8,p9,p10};

   auto d = tr.distance();

   cout << "Колличество точек в маршруте: "<<tr.num_of_points()<<endl;

   if(static_cast<int>(d) >= 1000){

       d /= 1000;
       cout << "Расстояние маршрута равно: " << std::fixed<<std::setprecision(3) << d <<" киллометров" << endl;
     }

   else {

        cout << "Расстояние маршрута равно: " << static_cast<int>(d) <<" метров" << endl;
   }

    return 0;
}
