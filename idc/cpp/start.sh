#此脚本用于启动数据共享平台全部的服务程序

#启动守护模块

/project/tools/bin/procctl 10 /project/tools/bin/checkproc /tmp/log/checkproc.log

#生成气象站点观测的分钟数据，程序每分钟运行一次
/project/tools/bin/procctl 60 /project/idc/bin/crtsurfdata /project/idc/ini/stcode.ini /tmp/idc/surfdata /log/idc/crtsurfdata.log csv,xml,json

## 清理原始的气象观测数据目录（/tmp/idc/surfdata）中的历史数据文件。
/project/tools/bin/procctl 300 /project/tools/bin/deletefiles /tmp/idc/surfdata "*" 0.02

# 压缩后台服务程序的备份日志。
/project/tools/bin/procctl 300 /project/tools/bin/gzipfiles /log/idc "*.log.20*" 0.02

