#此脚本用于停止数据共享平台全部的服务程序

#停止调度程序
killall -9 procctl

#停止其他服务程序
killall crtsurfdata deletefiles gzipfiles ftpgetfile ftpputfiles
killall fileserver tcpputfiles tcpgetfiles

sleep 5

killall -9 crtsurfdata deletefiles gzipfiles ftpgetfile ftpputfiles
killall -9 fileserver tcpputfiles tcpgetfiles