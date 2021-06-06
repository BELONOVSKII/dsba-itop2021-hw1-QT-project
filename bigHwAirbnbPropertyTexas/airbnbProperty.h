#ifndef AIRBNBPROPERTY_H
#define AIRBNBPROPERTY_H

#include <QString>
#include <string>
struct airbnbProperty
{
    double averageRatePerNight;
    int bedroomsCount;
    QString city;
    QString dateOfListing;
    QString description;
    QString coordinates;
    QString title;
    std::string url;
};

#endif // AIRBNBPROPERTY_H
