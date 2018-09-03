#include <iostream>
#include<boost/filesystem.hpp>
#include<map>
#include<string>
#include<fstream>
#include<chrono>
#include<algorithm>
#include<vector>

const int MAX_DUMP = 50000;

using namespace std;
std::vector<std::string> cache;

void out(std::ofstream & file)
{
	for (auto& v : cache)
	{
		file << v << std::endl;
	}
	cache.clear();
}

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
                    mapIt->second=mapIt->second+1;
                }
                else
                {
                    fileCount.insert(std::pair<std::string,int>(filePath.extension().string(),1));
                }

				if (cache.size() > MAX_DUMP)
					out(file);
				else
					cache.push_back(filePath.string());
            }
        }
    }
    catch(std::exception &e)
    {
        std::cout<<e.what()<<std::endl;
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

    file<<"文件列表:\n";

    auto startTime=std::chrono::steady_clock::now();
    getDirAllFile(dir,fileCount,file);
	out(file);
    auto endTime=std::chrono::steady_clock::now();
    auto duration=std::chrono::duration_cast<std::chrono::microseconds>(endTime-startTime);

    file<<std::endl;

    file<<"后缀名列表:"<<std::endl;

    std::vector<std::pair<std::string,long> > list;

    for(auto it=fileCount.begin();it!=fileCount.end();++it)
    {
        list.push_back(std::make_pair(it->first,it->second));
    }

    auto fun=[](std::pair<std::string,long> &x1,std::pair<std::string,long> &x2)
    {
        return x1.second>x2.second;
    };

    std::sort(list.begin(),list.end(),fun);

    for(auto it=list.begin();it!=list.end();++it)
    {
        std::cout<<it->first<<":"<<it->second<<std::endl;
        file<<it->first<<":"<<it->second<<std::endl;
    }

    file<<"遍历耗时:"<<std::chrono::duration<double>(duration).count()<<"s"<<std::endl;

    return 0;
}

