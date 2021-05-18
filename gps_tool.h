#ifndef GPS_TOOL_H
#define GPS_TOOL_H
#include<iostream>
#include<string>
#include "Constans.h"
#include"Struct_Data.h"
#include <cmath>
#include<vector>
#include<initializer_list>

namespace Navigetion  //оборачиваю в пространство имен
{

//------------------------------------------класс долготы от -90° до 90°
class Latidude
{
public:
   Latidude(double);//конструкттор
   Latidude(const Latidude &Other);//конструктор копирования
   Latidude &operator=( const Latidude &aObj);//операторор присваивания

   Latidude (const Latidude &&Other) = delete; //не исполюзовать конструктор копирования rvalue
   Latidude &operator=( const Latidude &&) = delete; //не исполюзовать оператор присваивания rvalue

   bool operator== (const Latidude &) const; //оператор саравнения равно
   bool operator!= (const Latidude &) const; //оператор сравнения не равно

  const degreeD &Dpoint() const;   //функция возвращающая координаты долготы

private:
    degreeD mPoint;


 void Chek_Corect_Degree();   //функция проверки корректности данных координат долготы
};
    //-------------------------------------класс широты от -180° до 180°
class Longitude
{
public:
    Longitude(double);//конструкттор
    Longitude(const Longitude &Other);//конструктор копирования
    Longitude &operator=( const Longitude &aObj);//оператор присваивания

    Longitude(const Longitude &&Other) = delete ;//не исполюзовать конструктор копирования rvalue
    Longitude &operator= (Longitude &&) = delete ;//не исполюзовать оператор присваивания rvalue

    bool operator== (const Longitude &) const; //оператор саравнения равно
    bool operator!= (const Longitude &) const; //оператор сравнения не равно



    const degreeD &Dpoint() const;  //функция возвращающая координаты широты

private:
    degreeD mPoint;

    void Chek_Corect_Degree(); //функция проверки корректности данных координат широты
};

//-----------------------------класс точки координат 2D----------------
class Point_2D
{
public:
    Point_2D(double, double, std::string aDesc = ""); //конструктор точки с числовыми параметрами
    Point_2D(const Latidude &, const Longitude &, std::string aDesc = ""); // конструктор точки с готовыми координатами

    Point_2D(const Point_2D &); //Конструктор копирования точки
    Point_2D &operator=(const Point_2D &); //оператор присватвания

   // Point_2D(const Point_2D &&) = delete ;//не исполюзовать конструктор копирования rvalue
    Point_2D &operator=(const Point_2D &&) = delete ;//не исполюзовать оператор присваивания rvalue

    const Latidude &latidude() const ; //функция возврата координат долготы
    const Longitude &longitude() const; //функция возврата широты

    bool operator==(const Point_2D &) const; //оператор саравнения равно
    bool operator!=(const Point_2D &) const; //оператор сравнения не равно

    double DistanceTo(const Point_2D &) const; //функция вычисления дистанции от точки до точки
    double azimuthTo(const Point_2D &) const; //функция вычисления азимута от точки до точки

private:
    Latidude mLatidude;//координаты долготы

    Longitude mLongitude; //координаты широты

    std::string mDescription;//коментарий к точке (поворот на право...)

};
//------------------------------------вспомогательные функции------------------------------
namespace Common
{
       double degreeToRadian(const double &);//функция градусы в радианы
       double toRadian(const Latidude &); //функция долгота в радианы
       double toRadian(const Longitude &); //функция широта в радианы

       double radianToDegree(const double &);//функция радианы в градусы

       bool CorrectLongitude(double);  // общая функция проверки корректности долготы
       bool CorrectLatidude(double); // общая функция проверки корректности широты

       const degreeDM &toDM(const Latidude&) ; //функция долгота в градусы и минуты
       const degreeDM &toDM(const Longitude&); //функция широта в градусы и минуты

       const degreeDMS &toDMS(const Latidude&);//функция долгота в градусы минуты и секунды
       const degreeDMS &toDMS(const Longitude&);//функция широта в градусы минуты и секунды

       /* return minutes from degree */
       double minutes(const double&); //Функция градусы в минуты
       double minutes(const Latidude&); //функция долгота вминуты
       double minutes(const Longitude&);//функция широта в минуты

       /* return seconds from degree */
       double seconds(const double&);//функция градусы в секунды
       double seconds(const Latidude&);//функция долгота в секунды
       double seconds(const Longitude&);//функция долгота в секунды

       /*
        .p1
         \
          \
           \
          p2._______ .p3
         .p1
          \
           \
            .p2
           /
          /
         .p3
       */
    double courseAzimuth(const Point_2D&, const Point_2D&, const Point_2D&);//функция вычисления азимута

}
/*
Formula for the calculation Radius
latitude B, radius R, radius at equator r1, radius at pole r2
R = √ [ (r1² * cos(B))² + (r2² * sin(B))² ] / [ (r1 * cos(B))² + (r2 * sin(B))² ]
*/

//-------------------------------------класс маршрут из точек координат----------------------------



class TrackPoints2D
{
public:
    TrackPoints2D();//конструктор по умолчанию
    TrackPoints2D(std::initializer_list<Point_2D>);//коструктор с точками коордтнат

    TrackPoints2D(const TrackPoints2D &);//конструктор копирования
    TrackPoints2D &operator=(const TrackPoints2D &);//оператор присваивания

    TrackPoints2D &operator=(const TrackPoints2D &&) = delete;//конструктор копирования rvalue не генерить
    TrackPoints2D(const TrackPoints2D &&) = delete;//оператор присваивания rvalue  не генерить

    void add(const Point_2D&);//функция добовления новой точки к маршруту

    const std::pair<double, double> &Azimuths(size_t)const;//функция подсчета азимута

    Point_2D& operator[](size_t);//перегрузка оператора[] с возможностью менять данные
    const Point_2D& operator[](size_t) const;//перегрузка оператора[]

    size_t num_of_points()const;//функция возвращающая колличество точек координат
    const double &distance()const;
private:
    double mDistance; //переменная Дистанции

    /*
        first  - azimuth to next point(p2) (from p1 to p2 )
        second - azimuth to next point(p3) (from p2 to p3, relatively vector of movement(p1,p2))
        second needs for drawing arrow on screen, etc. (for information about direction after point)
        example 1:
                    p1
                    |
                    |
                    |
              p3----p2
              first  = 180
              second = 90
        example 2:
                    p1
                    |
                    |
                    |
                    p2-----p3
              first  = 180
              second = 270
        example 3:
                    p1     p3
                      \    /
                       \  /
                        \/
                        p2
              first  = 135
              second = ~225
    */
    std::vector<std::pair<double, double> > mAzimuths;//вектор хранения азимута
    std::vector<double>                     mDistances;//вектор хранения дистанций
    std::vector<Point_2D>                    mPoints;//вектор точек координат
};


};

#endif // GPS_TOOL_H
