#include <iostream>
#include "IconCompare/IconCompare.h"



int main(int argc, char *argv[])
{
  IconCompare container;

  std::map<std::string,std::string> map={
    {"area","./resources/area.png"},
    {"list","./resources/list.png"},
    {"search","./resources/search.png"}
  };
  container.setBenchMark(map,cv::Size(32,32));

  std::string mean;
  int ret=container.getIconMeaning("./resources/search_target.png",mean);
  if(ret == 0){
    std::cout<<"mean:"<<mean<<std::endl;
  }

  return 0;
}
