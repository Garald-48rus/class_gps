#ifndef CONSTANTS_H
#define CONSTANTS_H


//---------------------------константы----------------------------
namespace Constants {
  constexpr double PI = 3.141592653589793;   //число пи
  constexpr double PI_2 = PI / 2;    //число пи / 2
  constexpr double PI_4 = PI/4;    //число пи / 4

  constexpr double LatiduteMax = 90;   //максимальное значение долготы
  constexpr double LatidudeMin = -90;  //минимальное значение долготы

  constexpr double LongitudeMin = -180;   //минимальное значение широты
  constexpr double LohgitudeMax = 180;    //максимальное значение широты

  constexpr double DegreeToRadian = PI / 180;  //градусы в радианы
  constexpr double RadianToDegree = 180 / PI;  //радианы в градусы

  constexpr double EarthRadiusM =  6371001;   //радиус Земли в метрах
  constexpr double EarthRadiuskM = 6371.001;  //радиус земли в киллометрах

  constexpr double RadiusAtEqvatorM = 6378137;    //радиус экватора в метрах
  constexpr double RadiusAtEqvatorKM = 6378.137;  //радиус екватора в киллометрах

  constexpr double RadiusPoleM = 6356752;  //радиус полюса в метрах
  constexpr double RadiusPolekM = 6356.752; //радиус полюса в киллометрах

}


#endif // CONSTANTS_H
