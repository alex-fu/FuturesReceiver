#include <iostream>
#include <cstring>
#include "CTPMdUserSpi.h"

using namespace std;


int testCTPMdUserSpi()
{
    char mdServerAddr[]="tcp://180.168.102.230:26213";
    TThostFtdcBrokerIDType  brokerId = "1001";
    TThostFtdcInvestorIDType userId = "00000054";
    TThostFtdcPasswordType  password = "123456";
    char *instruments[] = {"cu1308"};
    int tRequestID = 0;


    CThostFtdcMdApi* pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();
    CThostFtdcMdSpi* pUserSpi = new CTPMdUserSpi(pUserApi);

	pUserApi->RegisterSpi(pUserSpi);
	pUserApi->RegisterFront(mdServerAddr);
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

    //Subscribe instruments
    sleep(2);
    cout << "Subscribe instruments" << endl;
    ret = pUserApi->SubscribeMarketData(instruments, 1);
    if(ret == 0)
    {
        cout << "Subscribe market data success" << endl;
    }
    else
    {
        cerr << "Subscribe market data failed" << endl;
    }

    //Unsubscribe instruments
//    sleep(100);
//    cout << "Subscribe instruments" << endl;
//    ret = pUserApi->UnSubscribeMarketData(NULL, 0);
//    if(ret == 0)
//    {
//        cout << "Unsubscribe market data success" << endl;
//    }
//    else
//    {
//        cerr << "Unsubscribe market data failed" << endl;
//    }

    //Logout
    //TODO:

	pUserApi->Join();  
	pUserApi->Release();

	return 0;
}
