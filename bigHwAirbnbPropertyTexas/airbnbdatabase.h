#ifndef AIRBNBDATABASE_H
#define AIRBNBDATABASE_H

#include <map>
#include "airbnbProperty.h"
#include <QFile>
#include <QStringList>
#include <QtGui>
#include <set>

typedef std::map<std::string,airbnbProperty> mapOfProperty;
class airbnbDataBase
{
public:
    airbnbDataBase();
     void fill();
     QStringList getKeysAndPrice();
     void fillingTheModel(QStandardItemModel *standartModel);
     int countRows();
     int countColumns();
     void deleteItem(std::string s);
     airbnbDataBase(mapOfProperty& map1);
     mapOfProperty getValues(std::string& s);
     airbnbProperty getSingleValue(std::string& s);
     void addProperty(airbnbProperty& air);
     void save();
     std::set<QString> setOfTowns;
     mapOfProperty& getPropertyData();
private:
     mapOfProperty propertyData;
};

#endif // AIRBNBDATABASE_H
