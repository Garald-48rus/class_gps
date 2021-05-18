#include "gps_tool.h"



namespace Navigetion
{
//--------------------------------------вспомогательные функции-----------------------------
namespace Common {
//----------------------------------------------функция градусы в радианы---------------
double degreeToRadian(const double &aDegree)
   {
       return aDegree * Constants::DegreeToRadian;
   }
//-------------------------------------------функция долгота в радианы----------------------------

double toRadian(const Latidude &aLat)
    {
        return aLat.Dpoint().degre * Constants::DegreeToRadian;
    }
//----------------------------------------------------функция широта в радианы---------------------------
double toRadian(const Longitude &aLong)
    {
        return aLong.Dpoint().degre * Constants::DegreeToRadian;
    }
//----------------------------------------------функция радианы в градусы-----------------------
double radianToDegree(const double &aRadian)
    {
        return aRadian * Constants::RadianToDegree;
    }
//------------------------------------------- // общая функция проверки корректности долготы--------------------

bool CorrectLongitude(double aDegree)
{
    return (aDegree >= Constants::LongitudeMin)
            &&(aDegree <= Constants::LohgitudeMax);

}
//------------------------------------------общая функция проверки корректности широты--------------

bool CorrectLatidude(double aDegree)
{
    return (aDegree <= Constants::LatiduteMax)
            &&(aDegree >= Constants::LatidudeMin);
}


//-------------------------------------Функция градусы в минуты--------------------------

double minutes(const double &aDegree)
   {
       return 60. * (aDegree - (int)aDegree);
   }

//----------------------------------------функция долгота вминуты------------------


double minutes(const Latidude &aLat)
    {
        return 60. * (aLat.Dpoint().degre - (int)(aLat.Dpoint().degre));
    }
//--------------------------------------------функция широта в минуты-----------------------

double minutes(const Longitude &aLon)
    {
        return 60. * (aLon.Dpoint().degre - (int)(aLon.Dpoint().degre));
    }

//------------------------------------------функция градусы в секунды-----------------

double seconds(const double &aDegree)
    {
        double minutes = 60. * (aDegree - (int)aDegree);
        return 60. * (minutes - (int)minutes);
    }

//--------------------------------------функция долгота в секунды-----------------------

double seconds(const Latidude &aLat)
   {
       double minutes = 60. * (aLat.Dpoint().degre - (int)aLat.Dpoint().degre);
       return 60. * (minutes - (int)minutes);
   }

//-----------------------------------------функция долгота в секунды--------------------
double seconds(const Longitude &aLon)
    {
        double minutes = 60. * (aLon.Dpoint().degre - (int)aLon.Dpoint().degre);
        return 60. * (minutes - (int)minutes);
    }


//------------------------------------функция долгота в градусы и минуты------------------------

const degreeDM &toDM(const Latidude&aLat)
{
    static degreeDM res{0.0, 0.0, 'N'};
           res.degree  = std::fabs((int)aLat.Dpoint().degre);
           res.minutes = std::fabs(minutes(aLat.Dpoint().degre));
           res.ch      = aLat.Dpoint().ch;
           return res;
}

//-----------------------------------------функция широта в градусы и минуты---------------------------

const degreeDM &toDM(const Longitude &aLong)
   {
       static degreeDM res{0.0, 0.0, 'E'};
       res.degree  = std::fabs((int)aLong.Dpoint().degre);
       res.minutes = std::fabs(minutes(aLong.Dpoint().degre));
       res.ch      = aLong.Dpoint().ch;
       return res;
   }

//-------------------------------функция долгота в градусы минуты и секунды-----------------


const degreeDMS &toDMS(const Latidude &aLat)
   {
       static degreeDMS res{0.0, 0.0, 0.0, 'N'};
       res.degree  = std::fabs((int)aLat.Dpoint().degre);
       res.minutes = std::fabs((int)minutes(aLat.Dpoint().degre));
       res.seconds = std::fabs(seconds(aLat.Dpoint().degre));
       res.ch      = aLat.Dpoint().ch;
       return res;
   }
//-------------------------------функция широта в градусы минуты и секунды-----------------

const degreeDMS &toDMS(const Longitude &aLong)
    {
        static degreeDMS res{0.0, 0.0, 0.0, 'E'};
        res.degree  = std::fabs((int)aLong.Dpoint().degre);
        res.minutes = std::fabs((int)minutes(aLong.Dpoint().degre));
        res.seconds = std::fabs(seconds(aLong.Dpoint().degre));
        res.ch      = aLong.Dpoint().ch;
        return res;
    }

//---------------------------функция вычисления азимута----------------------------

double courseAzimuth(const Point_2D &aP1, const Point_2D &aP2, const Point_2D &aP3)
    {
        double az1 = aP1.azimuthTo(aP2);
        double az2 = aP2.azimuthTo(aP3);
        double res = 0.;

        if(az1 >= 0.0 && az1 < 90.0)
            res = (az2 - 90.0) + (90.0 - az1);
        if(az1 >= 90.0 && az1 < 180.0)
            res = (az2 - 180.0) + (180.0 - az1);
        if(az1 >= 180.0 && az1 < 270.0)
            res = (az2 - 270.0) + (270.0 - az1);
        if(az1 >= 270.0 && az1 <= 360.0)
            res = (az2 - 360.0) + (360.0 - az1);

        if(res < 0.0)
            res = 360.0 + res;
        return res;
    }


}

//-------------------------долгота----------------------------------------------------
Latidude::Latidude(double Adegree) :mPoint{Adegree, 'S'}
{
    Chek_Corect_Degree();
}
//-------------------конструктор копирования--------------------------------------------

Latidude::Latidude(const Latidude &Other) :mPoint{Other.mPoint.degre , Other.mPoint.ch}
{
     //std::cout << "Констуктор копирования" << std::endl;
}
//-----------------------------//операторор присваивания----------------------------------------------------

Latidude &Latidude::operator=( const Latidude &aObj)
{
    if(this == &aObj) return *this;

    mPoint.degre = aObj.mPoint.degre;
    mPoint.ch = aObj.mPoint.ch;
    std::cout<<"Оператор присваивания"<<std::endl;
     return *this;


}

//-------------------------------------функция проверки корректности данных координат долготы---------------------------------------


void Latidude::Chek_Corect_Degree()
{
  if(!Common::CorrectLatidude(mPoint.degre))
{
    if(mPoint.degre >= 0.0) mPoint.degre = Constants::LatiduteMax;
     else mPoint.degre = Constants::LatidudeMin;
}

  mPoint.ch = (mPoint.degre >= 0.0) ? 'N' : 'S';
}

//--------------------------//функция возвращающая координаты долготы-----------------------------------------------------
const degreeD &Latidude::Dpoint() const
{
    return mPoint;
}

//-----------------------------//оператор саравнения равно----------------------------------
bool Latidude::operator== (const Latidude &Other) const
{
    return  mPoint.degre == Other.mPoint.degre;
}

//-----------------------------//оператор сравнения не равно-------------------------------------------
bool Latidude::operator!= (const Latidude &Other) const
{
    return !(*this == Other);
}


//---------------------------------широта---------------------------------------------
Longitude::Longitude(double Adegree)  :mPoint{Adegree, 'W'}
{
    Chek_Corect_Degree();
}
//----------------------------конструктор копирования------------------------------------------------

Longitude::Longitude(const Longitude &Other) :mPoint{Other.mPoint.degre , Other.mPoint.ch}
{
 //std::cout << "Констуктор копирования" << std::endl;
}

//----------------------------//операторор присваивания---------------------------------------------------

Longitude &Longitude::operator=(const Longitude &aObj)
{
    if(this == &aObj) return *this;

    mPoint.degre = aObj.mPoint.degre;
    mPoint.ch = aObj.mPoint.ch;
    std::cout<<"Оператор присваивания"<<std::endl;
     return *this;

}
//------------------------------------функция проверки корректности данных координат долготы----------------------------------------------------
void Longitude::Chek_Corect_Degree()
{
    if(!Common::CorrectLongitude(mPoint.degre))
  {

   if(mPoint.degre >= 0.0) mPoint.degre = Constants::LohgitudeMax;

   else mPoint.degre = Constants::LongitudeMin;

   }
  mPoint.ch = (mPoint.degre >= 0.0) ? 'E' : 'W';

}
//---------------------------//функция возвращающая координаты долготы----------------------------------------------

const degreeD &Longitude::Dpoint() const
{
    return  mPoint;

}

//----------------------------//оператор саравнения равно-----------------------------------------

bool Longitude::operator== (const Longitude &Other) const
{
    return  mPoint.degre == Other.mPoint.degre;
}

//--------------------------------//оператор сравнения не равно-------------------------------------
bool Longitude::operator!= (const Longitude &Other) const
{
    return !(*this == Other);
}


//-----------------------------класс точки координат 2D----------------

//-------------------------------------------///конструктор точки с  числовыми параметрами-------------------------------------------
Point_2D::Point_2D(double lat , double lon, std::string aDescription)
    :mLatidude{lat}
    ,mLongitude{lon}
    ,mDescription{aDescription}
   {
   }
 //-----------------------------------конструктор точки с готовыми координатами----------------------------------------------------


 Point_2D::Point_2D(const Latidude & lat, const Longitude &lon, std::string aDesc)
     :mLatidude{lat},
       mLongitude{lon},
       mDescription{aDesc}
 {
 }

 //----------------------------------------Конструктор копирования точки---------------------------------------------------------
Point_2D::Point_2D(const Point_2D &oPoint)
    :mLatidude{oPoint.mLatidude},
      mLongitude{oPoint.mLongitude},
      mDescription{oPoint.mDescription}
{
}

//--------------------------------------оператор присваивания-----------------------------------

Point_2D &Point_2D::operator= (const Point_2D &oPoint)
{
    if(this == &oPoint) return *this;

   mLongitude = oPoint.mLongitude;
   mLatidude = oPoint.mLatidude;
   mDescription = oPoint.mDescription;
   return  *this;
}
 //----------------------------------функция возврата координат долготы---------------------------------------------

 const Latidude &Point_2D::latidude() const
 {
     return  mLatidude;
 }
 //----------------------------------функция возврата широты----------------------------------------

const Longitude &Point_2D::longitude() const
{
    return mLongitude;

}
 //------------------------------------оператор саравнения равно---------------------------------------------------

bool Point_2D::operator==(const Point_2D &oPoint) const
{
    return (mLatidude == oPoint.mLatidude)
            && (mLongitude == oPoint.mLongitude);
}
 //------------------------------------оператор сравнения не равно---------------------------------------------

bool Point_2D::operator!=(const Point_2D &oPoint) const
{
    return !(operator==(oPoint));
}
//-----------------------------------------------------функция измерения дистанции от точки до точки------------

double Point_2D::DistanceTo(const Point_2D &aTarget) const
{
    double a1 = Common::toRadian(mLatidude);
        double a2 = Common::toRadian(mLongitude);
        double b1 = Common::toRadian(aTarget.mLatidude);
        double b2 = Common::toRadian(aTarget.mLongitude);

        double t1 = std::cos(a1) * std::cos(a2) * std::cos(b1) * std::cos(b2);
        double t2 = std::cos(a1) * std::sin(a2) * std::cos(b1) * std::sin(b2);
        double t3 = std::sin(a1) * std::sin(b1);
        double tt = std::acos(t1 + t2 + t3);

        return Constants::EarthRadiusM * tt;
}
//-----------------------------------------функция вычисления азимута от точки до точки----------------------

double Point_2D::azimuthTo(const Point_2D &aTarget) const
{
    double lat1  = Common::toRadian(mLatidude);
    double lat2  = Common::toRadian(aTarget.mLatidude);
    double long1 = Common::toRadian(mLongitude);
    double long2 = Common::toRadian(aTarget.mLongitude);

    double cl1      = std::cos(lat1);
    double cl2      = std::cos(lat2);
    double sl1      = std::sin(lat1);
    double sl2      = std::sin(lat2);
    double delta    = long2 - long1;
    double cdelta   = std::cos(delta);
    double sdelta   = std::sin(delta);

    double y    = std::sqrt(std::pow(cl2 * sdelta, 2) +
                            std::pow(cl1 * sl2 - sl1 * cl2 * cdelta, 2));

    double x    = sl1 * sl2 + cl1 * cl2 * cdelta;

    x = (cl1 * sl2) - (sl1 * cl2 * cdelta);
    y = sdelta * cl2;
    double z = ((std::atan(-y/x))*180.0)/Constants::PI;

    if (x < 0)
        z = z+180.0;

    double z2 = std::fmod((z+180.0),360.0) - 180.0;

    z2 = -1.0 * ((Constants::PI*z2)/180.0);
    double anglerad2 = z2 - ((2*Constants::PI)*std::floor((z2/(2*Constants::PI))));

    return (anglerad2 * 180.0) / Constants::PI;
}

//----------------------------------------класс маршрут из точек координат//------------------------

//---------------------------конструктор по умолчанию----------------------------------

TrackPoints2D::TrackPoints2D()
    :mDistance(0.0)
{
}

//-------------------------------------коструктор с точками коордтна------------------
TrackPoints2D::TrackPoints2D(std::initializer_list<Point_2D> aInitList)
{
    for( auto i : aInitList)
      add(i);

}

//-------------------------------------конструктор копирования----------------------------
TrackPoints2D::TrackPoints2D(const TrackPoints2D &aObj)
    :mDistance(aObj.mDistance)
    ,mAzimuths(aObj.mAzimuths)
    ,mDistances(aObj.mDistances)
    ,mPoints(aObj.mPoints)
{
}
//---------------------------------------------оператор присваивания----------------------------
TrackPoints2D &TrackPoints2D::operator=(const TrackPoints2D &aObj)
{
    if(this == &aObj)
        return *this;

    mDistance = aObj.mDistance;

    mAzimuths.resize(aObj.mAzimuths.size());
    std::copy(aObj.mAzimuths.begin(),
              aObj.mAzimuths.end(),
              mAzimuths.begin());

    mDistances.resize(aObj.mDistances.size());
    std::copy(aObj.mDistances.begin(),
              aObj.mDistances.end(),
              mDistances.begin());

    mPoints.clear();
    mPoints.reserve(aObj.mPoints.size());
    for(auto i : aObj.mPoints)
        mPoints.push_back(i);

    return *this;
}
//--------------------------------------------------функция добовления новой точки к маршруту----------------------


void TrackPoints2D::add(const Point_2D &aPoint)
{
    double distance = 0;

    if(mPoints.size() >= 1)
    {
        Point_2D &pp = mPoints[mPoints.size() - 1];
        auto    &pa = mAzimuths[mAzimuths.size() - 1];
        auto    &pd = mDistances[mDistances.size() - 1];

        pd = pp.DistanceTo(aPoint);
        pa.first = pp.azimuthTo(aPoint);

        mDistance += pd;

        if(mPoints.size() >= 2)
        {
            Point_2D &ppp = mPoints[mPoints.size() - 2];
            auto    &ppa = mAzimuths[mAzimuths.size()- 2];
            ppa.second   = Common::courseAzimuth(ppp, pp, aPoint);
        }
    }

    mAzimuths.push_back(std::pair<double, double>{0.,0.});
    mDistances.push_back(distance);
    mPoints.push_back(aPoint);
}
 //----------------------------------------функция подсчета азимута-------------------


const std::pair<double, double> &TrackPoints2D::Azimuths(size_t aIndex)const
{
    return mAzimuths[aIndex];
}

//-------------------------------------перегрузка оператора[] с возможностью менять данные------------------

Point_2D &TrackPoints2D::operator[](size_t aIndex)
{
    return mPoints[aIndex];
}
//---------------------------------------------------//перегрузка оператора[]-------------

const Point_2D &TrackPoints2D::operator[](size_t aIndex) const
{
    return mPoints[aIndex];
}

//-------------------------------------------------функция возвращающая колличество точек координат----------------------------------


size_t TrackPoints2D::num_of_points()const
{
    return mPoints.size();
}

//--------------------------------------------------------


const double &TrackPoints2D::distance()const
{
    return mDistance;
}
}
/*
The formula for heading between two lat/long coords is:
=atan2(cos(lat1)*sin(lat2)-sin(lat1)*cos(lat2)*cos(lon2-lon1), sin(lon2-lon1)*cos(lat2))
where lat2/lon2 is your end point, lat1/lon1 is your start point.
Your answer will be between -pi and pi radians.
To get the heading in degrees, convert your radians to degrees then do:
(degrees+360)%360 = heading. The heading will then be 0 for north, 90 for east etc.
The compass heading means nothing, unless you need to adjust your heading
from true north to magnetic north.
*/
//------------------------------------------------------------------------------
/*
double azimuth(const Point2D &p1, const Point2D &p2)
{
    double res = 0.0;
    double lat1 = common::toRadian(p1.latitude());
    double lat2 = common::toRadian(p2.latitude());
    double lon1 = common::toRadian(p1.longitude());
    double lon2 = common::toRadian(p2.longitude());
    res = atan2(cos(lat1)*sin(lat2)-sin(lat1)*cos(lat2)*cos(lon2-lon1), sin(lon2-lon1)*cos(lat2));
    res = radianToDegree(res);
    res = (res + 360.) / 360.;
    return res;
}
*/


