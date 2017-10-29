配置Typora真是费了劲了......

始终apt-get不到，直接下载了.tar.gz，没想到Linux跟Windows的“选择默认程序”不一样，不能指定文件，索性在/usr/share/applications下手动创建了桌面配置文件Typora.desktop

1. 桌面配置文件每行末尾的空格一定要收拾干净，不然无法识别。
2. 若希望该程序显示在右键open with，需要在Exec的路径之后加上%U