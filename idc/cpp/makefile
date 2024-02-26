#开发框架头文件路径
PUBLIC = -l/project/public	#变量名用全大写，-l表示链接的是/project/public的库文件，省略了lib前缀和扩展名

#开发框架cpp文件名，这里直接包含进来，没有采用链接库，是为了方便调试
PUBCPP = /project/public/_public.cpp

#编译参数。-g：使生成的可执行文件包含调试信息
CFLAGS = -g

all:crtsurfdata

#g++:-o指定输出的文件名为crtsurfdata。crtsurfdata.cpp是要编译的源文件名。
#$(PUBINCL)开发框架头文件路径。$(PUBCPP)公共源文件路径。
#-lm链接数学库。-lc链接C库
#cp...:将生成的crtsurfdata强制复制到../bin/目录中
crtsurfdata:crtsurfdata.cpp
	g++ $(CFLAGS) -o crtsurfdata crtsurfdata.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	
	cp -f crtsurfdata ../bin/.	

clean:
	rm -f crtsurfdata