#include "airbnbdatabase.h"
#include <QString>
#include <iostream>
#include <QStringList>
#include <fstream>
airbnbDataBase::airbnbDataBase()
{
    fill();
}
void airbnbDataBase::fill()
{
    QFile inFile("Airbnb_Texas_Rentals.csv");
    inFile.open(QFile::ReadOnly | QFile::Text);
    inFile.readLine();
    while (!inFile.atEnd())
    {
        try
        {
            QString s = inFile.readLine();
            QList<QString> temp = s.split('"');
            airbnbProperty property;
            property.averageRatePerNight = std::stod((temp.at(3).toStdString()).erase(0,1));
            property.bedroomsCount = std::stoi((temp.at(5).toStdString()));
            property.city = temp.at(7);
            property.dateOfListing = temp.at(9);
            property.description = temp.at(11);
            property.coordinates = temp.at(12);
            property.title = temp.at(13);
            property.url = temp.at(15).toStdString();
            if (property.title.toStdString() != "")
            {
                    propertyData[property.title.toStdString()] = property;
                    setOfTowns.insert(property.city);
            }

        }
        catch (...)
        {
            continue;
        }

    }
    inFile.close();


}
void airbnbDataBase::fillingTheModel(QStandardItemModel *standartModel)
{
    int i = 0;
    QStringList list1;
    for (mapOfProperty::const_iterator it = propertyData.begin(); it != propertyData.end(); ++it)
    {
        airbnbProperty prop = (*it).second;
        QModelIndex ind = standartModel->index(i,0,QModelIndex());
        standartModel->setData(ind,prop.averageRatePerNight);
        ind = standartModel->index(i,6,QModelIndex());
        standartModel->setData(ind,prop.bedroomsCount);
        ind = standartModel->index(i,2,QModelIndex());
        standartModel->setData(ind,prop.city);
        ind = standartModel->index(i,3,QModelIndex());
        standartModel->setData(ind,prop.coordinates);
        ind = standartModel->index(i,4,QModelIndex());
        standartModel->setData(ind,prop.dateOfListing);
        ind = standartModel->index(i,7,QModelIndex());
        standartModel->setData(ind,prop.description);
        ind = standartModel->index(i,1,QModelIndex());
        standartModel->setData(ind,prop.title);
        ind = standartModel->index(i,5,QModelIndex());
        standartModel->setData(ind,QString::fromStdString(prop.url));
        ++i;
    }
    list1 << "averageRatePerNight" << "title" << "city" << "coordinates"<<  "dateOfListing" << "url" << "bedroomsCount" << "description";
    standartModel->setHorizontalHeaderLabels(list1);
}
int airbnbDataBase::countColumns()
{
    return 8;
}
int airbnbDataBase::countRows()
{
    return propertyData.size();
}
void airbnbDataBase::deleteItem(std::string s)
{
    propertyData.erase(s);
}
mapOfProperty airbnbDataBase::getValues(std::string &s)
{
    mapOfProperty map1;
    QString d = QString::fromStdString(s);
    for (mapOfProperty::iterator it = propertyData.begin();it != propertyData.end();it++)
    {
          QString s  = (*it).second.title;
          if (s.contains(d))
              map1[(*it).first] = (*it).second;
    }
    return map1;
}
airbnbDataBase::airbnbDataBase(mapOfProperty& map1):propertyData(map1){};
void airbnbDataBase::addProperty(airbnbProperty& air)
{
    propertyData[air.title.toStdString()] = air;
}
airbnbProperty airbnbDataBase::getSingleValue(std::string& s)
{
    return propertyData[s];
}
void airbnbDataBase::save()
{
    std::ofstream outFile("Airbnb_Texas_Rentals.csv", std::ios_base::trunc);
    outFile << R"("helloooo","average_rate_per_night","bedrooms_count","city","date_of_listing","description","latitude","longitude","title","url")" << '\n';
    for (mapOfProperty::const_iterator it = propertyData.begin(); it!= propertyData.end();it++)
    {
        outFile << "\" \"" << ",\"$" << (*it).second.averageRatePerNight << "\",\"" << (*it).second.bedroomsCount <<
                   "\",\"" << (*it).second.city.toStdString() << "\",\"" << (*it).second.dateOfListing.toStdString() <<
                   "\",\"" << (*it).second.description.toStdString() <<  "\"" << (*it).second.coordinates.toStdString() <<
                   "\"" << (*it).second.title.toStdString() << "\",\"" << (*it).second.url << "\"\n";
    }
    outFile.close();
}

mapOfProperty& airbnbDataBase::getPropertyData()
{
    return propertyData;
}








