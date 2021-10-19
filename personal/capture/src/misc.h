#ifndef MISC_H
#define MISC_H
#include <iostream>
#include <mutex>


class DBDirectoryDistributor
{

public:
  static DBDirectoryDistributor* getInstance();
  ///
  int setBaseDir(const std::string &v_dir);
  std::string getDir();


private:
  DBDirectoryDistributor();

  std::string __base_dir;
  std::string __dir_record;
  std::mutex __mutex;
  static DBDirectoryDistributor *__instance;

};


#endif
