#include <iostream>
#include <cstring>
#include "CTPTraderSpi.h"

using namespace std;

int testCTPTraderSpi()
{
    char traderServerAddr[]="tcp://180.168.102.230:26205";
    TThostFtdcBrokerIDType  brokerId = "1001";
    TThostFtdcInvestorIDType userId = "00000054";
    TThostFtdcPasswordType  password = "123456";
    int tRequestID = 0;

    CThostFtdcTraderApi* pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
    CThostFtdcTraderSpi* pUserSpi = new CTPTraderSpi(pUserApi);

	pUserApi->RegisterSpi(pUserSpi);
	pUserApi->RegisterFront(traderServerAddr);
	pUserApi->Init();
	
	//Login
	sleep(2);
	cout << "Login" << endl;
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    memcpy(req.BrokerID, brokerId, sizeof(brokerId));
    memcpy(req.UserID, userId, sizeof(userId));
    memcpy(req.Password, password, sizeof(password));
    int ret = pUserApi->ReqUserLogin(&req, ++tRequestID);
    if(ret == 0)
    {
        cout << "Request for user login success" << endl;
    }
    else
    {
        cerr << "Request for user login failed" << endl;
    }

    //Get trading day
    cout << "Trading day: " << pUserApi->GetTradingDay() << endl;


    //Logout
    //TODO:

//	pUserApi->Join();
	pUserApi->Release();

	return 0;
}
