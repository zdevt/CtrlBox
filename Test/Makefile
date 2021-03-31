
UP:
	@g++ Upgrade.cpp Network.cpp -o upgrade

H:
	@g++ HeartBeatAdmin.cpp Network.cpp NetCommon.cpp -o HeartBeatAdmin -DTEST -lpthread

TCPCMD:
	@../arm-2014.05/bin/arm-none-linux-gnueabi-g++ TestTcpCmd.cpp -o testtcparm -g
	@g++ TestTcpCmd.cpp -o testtcp -g 

f:
	@../APP/astyle *.cpp -cs2bCSKNwYMm2pPDHk1n >/dev/null
	@../APP/astyle *.h   -cs2bCSKNwYMm2pPDHk1n >/dev/null

clean:
	@rm -f testtcp testtcparm upgrade HeartBeatAdmin

