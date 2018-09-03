#include <iostream>
#include<boost/filesystem.hpp>
#include<map>
#include<string>
#include<fstream>

using namespace std;

void getDirAllFile(boost::filesystem::path path,std::map<std::string,long> &fileCount,std::ofstream &file)
{
    try
    {
        if(boost::filesystem::exists(path))
        {
            boost::filesystem::directory_iterator itEnd;
            for(boost::filesystem::directory_iterator it(path);it!=itEnd;++it)
            {
                if(boost::filesystem::is_directory(*it))
                {
                    getDirAllFile(*it,fileCount,file);
                    continue;
                }
                boost::filesystem::path filePath=it->path();
                auto p=filePath.extension().string();
                auto mapIt=fileCount.find(filePath.extension().string());
                if(mapIt!=fileCount.end())
                {
                    (*mapIt).second=(*mapIt).second+1;
                }
                else
                {
                    fileCount.insert(std::pair<std::string,int>(filePath.extension().string(),1));
                }

                std::cout<<filePath.string()<<std::endl;
                file<<filePath.string()<<std::endl;
            }
        }
    }
    catch(std::exception &e)
    {
        std::cout<<e.what()<<"--"<<path.string()<<std::endl;
    }
}

int main()
{
    std::string path="";
    std::cout<<"请输入扫描目录:";
    std::cin>>path;
    boost::filesystem::path dir(path);
    if(!boost::filesystem::is_directory(dir))
    {
        std::cout<<"提供的目录有误"<<std::endl;
        return -1;
    }

    std::map<std::string,long> fileCount;

    std::ofstream file("files.txt");
    if(!file)
        return -1;

    std::cout<<"文件列表:"<<std::endl;
    file<<"文件列表:\n";
    getDirAllFile(dir,fileCount,file);
    std::cout<<std::endl;
    file<<std::endl;

    std::cout<<std::endl<<std::endl;
    file<<"后缀名列表:"<<std::endl;

    for(auto it=fileCount.begin();it!=fileCount.end();++it)
    {
        std::cout<<(*it).first<<":"<<(*it).second<<std::endl;
        file<<(*it).first<<":"<<(*it).second<<std::endl;
    }

    return 0;
}

