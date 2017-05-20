#include "jsonparser.h"
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QPixmap>

jsonparser::jsonparser(){



}

void jsonparser::initParser(QString gameId)
{
    QByteArray jsonArray = getJson(gameId);
    QJsonDocument doc(QJsonDocument::fromJson(jsonArray));
    QJsonObject json = doc.object();
    QJsonValue value = json.value("results");
    QJsonObject resultsObject = value.toObject();
    map = createMap(resultsObject);


    QJsonValue genreValue = resultsObject.value("genres");
    QJsonArray tempArray = genreValue.toArray();
    for(int i = 0; i < tempArray.count(); i++){
       QJsonValue tempGenreValue = tempArray[i];
       QJsonObject tempGenreObject = tempGenreValue.toObject();
       genreList.append(tempGenreObject["name"].toString());
    }



    QJsonValue platformValue = resultsObject.value("platforms");
    QJsonArray tempPlatformArray = platformValue.toArray();
    for(int i = 0; i < tempPlatformArray.count(); i++){
        QJsonValue tempPlatformValue = tempPlatformArray[i];
        QJsonObject tempPlatformObject = tempPlatformValue.toObject();
        platformList.append(tempPlatformObject["name"].toString());
    }
}



QString jsonparser::getID()
{

}

QString jsonparser::getName()
{
    return map["name"];
}

QString jsonparser::getPlatform()
{

}

QString jsonparser::getDeveloper()
{
    return map["developer"];
}

QString jsonparser::getPublisher()
{
    return map["publisher"];
}

QString jsonparser::getSeries()
{
    return map["franchise"];
}

QString jsonparser::getDeck()
{
    return map["deck"];
}

QString jsonparser::getSynopsis()
{
    return map["description"];
}

QString jsonparser::getImage()
{
    return map["image"];
}

QMap<QString, QString> jsonparser::getMap()
{
    return map;
}

QList<QString> jsonparser::getGenre()
{
    return genreList;
}

QList<QString> jsonparser::getPlatformList()
{
    return platformList;
}

void jsonparser::setPlatform(QString platform)
{
    map["platform"] = platform;
    qDebug()<<map["platform"];
}

QByteArray getJson(QString gameID){
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString("https://www.giantbomb.com/api/game/" +gameID+ "/?api_key=2eb2277e5d566e4046904bde421a1c9223e09105&field_list=name,deck,developers,themes,franchises,genres,image,platforms,publishers,description%2Cname&format=json") ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();
    QByteArray strReply =reply->readAll();
    return strReply;
}



QString parseOverview(QString description){
    QString overview = description.mid(0, description.indexOf("<h2>Gameplay"));
    overview.remove(QRegExp("<[^>]*>"));
    return overview;
}

QMap<QString, QString> createMap(QJsonObject jsonObject){
    QMap<QString, QString> map;
    map["name"] = jsonObject["name"].toString();
    map["deck"] = jsonObject["deck"].toString();
    map["description"] = parseOverview(jsonObject["description"].toString());



    QJsonValue imageValue = jsonObject.value("image");
    QJsonObject imageObject = imageValue.toObject();
    map["image"] = imageObject["small_url"].toString();

    QJsonValue developerValue = jsonObject.value("developers");
    QJsonArray array = developerValue.toArray();
    QJsonValue developer0Value = array[0];
    QJsonObject developer0Object = developer0Value.toObject();
    map["developer"] = developer0Object["name"].toString();

    QJsonValue franchiseValue = jsonObject.value("franchises");
    QJsonArray franchiseArray = franchiseValue.toArray();
    QJsonValue franchises0Value = franchiseArray[0];
    QJsonObject franchises0Object = franchises0Value.toObject();
    map["franchise"] = franchises0Object["name"].toString();

    QJsonValue publisherValue = jsonObject.value("publishers");
    QJsonArray publisherArray = publisherValue.toArray();
    QJsonValue publisher0Value = publisherArray[0];
    QJsonObject publisher0Object = publisher0Value.toObject();
    map["publisher"] = publisher0Object["name"].toString();
    //TODO: Add other fields.

    return map;

}

void imageDownloader(QString url, QString name){
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( (QUrl(QString(url))));
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();
    if(reply->error() != QNetworkReply::NoError)
     {
         qDebug()<<"ERROR!!!!!!!!!!!!!!";
     }
    else
       {
           QByteArray responseData = reply->readAll();

           QString newName = prettyString(name);

           QString myPath = QCoreApplication::applicationDirPath();
           QString folderPath = myPath + "/" + "Images" +"/"+ newName;
           QString path =folderPath + "/" + newName + ".jpg";

           if(url.contains("png",Qt::CaseInsensitive)){
               path = folderPath + "/" + newName + ".png";
           }

           QDir dir(folderPath);

           if(!QDir(folderPath).exists()){
             qDebug()<< dir.mkpath(folderPath);
               qDebug()<<folderPath;
           }


           QFile file(path);
           qDebug()<<path;
           file.open(QIODevice::WriteOnly);
           file.write((responseData));
           file.close();
           qDebug()<<"DONE!!!!!!!!!!!";
       }

}

QPixmap imageViewer(QString name){
    QString newName = prettyString(name);
    qDebug()<<newName;
    QString myPath = QCoreApplication::applicationDirPath();
    QString folderPath = myPath + "/" + "Images" +"/"+ newName;
    QString path =folderPath + "/" + newName + ".jpg";

    if(!QDir(path).exists()){
       path = folderPath + "/" + newName + ".png";
    }

    qDebug()<<path;
    QPixmap pixmap(path);
    QPixmap newp = pixmap.scaled(250,250,Qt::KeepAspectRatio);
    return newp;
   // ui->label->setPixmap(newp);
}





QString prettyString(QString string){


    string.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]")));
    string.remove(" ");
    return string;

}

//QImage imageConverter(){
//    QEventLoop eventLoop;
//    QNetworkAccessManager mgr;
//    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
//    QNetworkRequest req( QUrl( QString("https://process.filestackapi.com/AqS13LTPNRUy2nk4fTbAaz/output=format:jpg/https://www.giantbomb.com/api/image/scale_small/2348791-box_persona4g.png") ) );
//    QNetworkReply *reply = mgr.get(req);
//    eventLoop.exec();
//    QImage file =reply->readAll();
//    return file;
//}
