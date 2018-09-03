# fileCount

练手系列.jpg

这是一个使用boost::filesystem遍历指定文件夹路径里的所有文件，统计出各后缀文件的数量
所有文件的路径及统计均会写进files.txt里（请注意隐私问题XD）
getDirAllFile里使用了递归的思维

PS1：boost库的作者们真的很厉害TAT
PS2：关于boost::filesystem的使用
boost::filesystem::path类提供了一个文件的路径操作，详情善用搜索
boost::filesystem::directory_iterator类提供了文件遍历，第一次用感觉也不错