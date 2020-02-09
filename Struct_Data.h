#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H
// хранение координат в градусах 40.123456
struct degreeD
{
    double degre;
    char ch;

};

//хранение координат в градусах минутах 40° 26.767'
struct degreeDM
{
    double degree;
    double minutes;
    char ch;
};

//хранение координат в градусах минутах секундах 40° 26' 46"
struct degreeDMS
{
    double degree;
    double minutes;
    double seconds;
    char ch;
};

#endif // STRUCT_DATA_H
