#include "misc.h"
#include <mutex>
#include <QDateTime>


DBDirectoryDistributor *DBDirectoryDistributor::__instance=nullptr;

DBDirectoryDistributor* DBDirectoryDistributor::getInstance()
{

  if (__instance == nullptr) {
    __instance=new DBDirectoryDistributor();
  }
  return __instance;
}

///
int DBDirectoryDistributor::setBaseDir(const std::string &v_dir)
{

  std::unique_lock<std::mutex> lck(__mutex);
  __base_dir=v_dir;
  return 0;
}

//"[year]/[day]/[hour].[minute].[second].[remain]"
std::string DBDirectoryDistributor::getDir()
{
  std::unique_lock<std::mutex> lck(__mutex);
  std::string str_dir;
  do{
    QDateTime dateTime = QDateTime::currentDateTime();
    // 字符串格式化
    QString timestamp = dateTime.toString("yyyy/MM/dd/hh.mm.ss.zzz");

    str_dir=__base_dir+timestamp.toStdString();
  }while (__dir_record ==str_dir) ;

  __dir_record=str_dir;

  return str_dir;

}


DBDirectoryDistributor::DBDirectoryDistributor()
{
  __base_dir="./";
}


class USBCamera
{

};


