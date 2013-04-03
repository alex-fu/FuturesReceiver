/*
 * CTPMdUserSpi.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: fuyf
 */
#include <iostream>
#include <cstring>
#include "CTPMdUserSpi.h"
using namespace std;

CTPMdUserSpi::CTPMdUserSpi(CThostFtdcMdApi *api)
    : pMdUserApi(api)
{
}

CTPMdUserSpi::~CTPMdUserSpi()
{
}


void CTPMdUserSpi::OnFrontConnected()
{
#ifdef _DEBUG
	cout << "Connected" << endl;
#endif
}

void CTPMdUserSpi::OnFrontDisconnected(int nReason)
{
#ifdef _DEBUG
	cout << "Disconnected! Reason: " << nReason << endl;
#endif
}

void CTPMdUserSpi::OnHeartBeatWarning(int nTimeLapse)
{
#ifdef _DEBUG
	cerr << "Heartbeat warning! TimeLapse: " << nTimeLapse << endl;
#endif
}

void CTPMdUserSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if(!IsErrorRspInfo(pRspInfo, __FUNCTION__) && (pRspUserLogin != NULL))
    {
        memcpy((char *)&loginField, pRspUserLogin, sizeof(CThostFtdcRspUserLoginField));
#ifdef _DEBUG
        cout << __FUNCTION__ << endl;
        cout << __FUNCTION__ << " - TradingDay: " << loginField.TradingDay << endl;
        cout << __FUNCTION__ << " - LoginTime: " << loginField.LoginTime << endl;
        cout << __FUNCTION__ << " - BrokerID: " << loginField.BrokerID << endl;
        cout << __FUNCTION__ << " - UserID: " << loginField.UserID << endl;
        cout << __FUNCTION__ << " - SystemName: " << loginField.SystemName << endl;
        cout << __FUNCTION__ << " - FrontID: " << loginField.FrontID << endl;
        cout << __FUNCTION__ << " - SessionID: " << loginField.SessionID << endl;
        cout << __FUNCTION__ << " - MaxOrderRef: " << loginField.MaxOrderRef << endl;
        cout << __FUNCTION__ << " - SHFETime: " << loginField.SHFETime << endl;
        cout << __FUNCTION__ << " - DCETime: " << loginField.DCETime << endl;
        cout << __FUNCTION__ << " - CZCETime: " << loginField.CZCETime << endl;
        cout << __FUNCTION__ << " - FFEXTime: " << loginField.FFEXTime << endl;
#endif
    }
    if(pRspUserLogin == NULL)
    {
        cerr << __FUNCTION__ << ": No user login response info" << endl;
    }
#ifdef _DEBUG
    cout << __FUNCTION__ << " - nRequestID: " << nRequestID << endl;
    cout << __FUNCTION__ << " - bIsLast: " << (bIsLast ? "True" : "False") << endl;
#endif
}

void CTPMdUserSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if(!IsErrorRspInfo(pRspInfo, __FUNCTION__) && (pUserLogout != NULL))
    {
#ifdef _DEBUG
        cout << __FUNCTION__ << endl;
        cout << __FUNCTION__ << " - BrokerID: " << pUserLogout->BrokerID << endl;
        cout << __FUNCTION__ << " - UserID: " << pUserLogout->UserID << endl;
#endif
    }

    if(pUserLogout == NULL)
    {
        cerr << __FUNCTION__ << ": No user logout response info" << endl;
    }
#ifdef _DEBUG
    cout << __FUNCTION__ << " - nRequestID: " << nRequestID << endl;
    cout << __FUNCTION__ << " - bIsLast: " << (bIsLast ? "True" : "False") << endl;
#endif
}

void CTPMdUserSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
    if (ret)
    {
        cerr<<"Error response! Error ID: " << pRspInfo->ErrorID << ". Error Message: "<<pRspInfo->ErrorMsg<<endl;
    }

#ifdef _DEBUG
    cout << __FUNCTION__ << endl;
    cout << __FUNCTION__ << " - nRequestID: " << nRequestID << endl;
    cout << __FUNCTION__ << " - bIsLast: " << (bIsLast ? "True" : "False") << endl;
#endif
}

void CTPMdUserSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if(!IsErrorRspInfo(pRspInfo, __FUNCTION__) && (pSpecificInstrument != NULL))
    {
#ifdef _DEBUG
        cout << __FUNCTION__ << endl;
        cout << __FUNCTION__ << " - InstrumentID: " << pSpecificInstrument->InstrumentID << endl;
#endif
    }

    if(pSpecificInstrument == NULL)
    {
        cerr << __FUNCTION__ << ": Didn't subscribe instrument this time!" << endl;
    }
#ifdef _DEBUG
    cout << __FUNCTION__ << " - nRequestID: " << nRequestID << endl;
    cout << __FUNCTION__ << " - bIsLast: " << (bIsLast ? "True" : "False") << endl;
#endif
}

void CTPMdUserSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if(!IsErrorRspInfo(pRspInfo, __FUNCTION__) && (pSpecificInstrument != NULL))
    {
#ifdef _DEBUG
        cout << __FUNCTION__ << endl;
        cout << __FUNCTION__ << " - InstrumentID: " << pSpecificInstrument->InstrumentID << endl;
#endif
    }

    if(pSpecificInstrument == NULL)
    {
        cerr << __FUNCTION__ << ": Didn't unsubscribe instrument this time!" << endl;
    }
#ifdef _DEBUG
    cout << __FUNCTION__ << " - nRequestID: " << nRequestID << endl;
    cout << __FUNCTION__ << " - bIsLast: " << (bIsLast ? "True" : "False") << endl;
#endif
}

void CTPMdUserSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    cout << "========" << __FUNCTION__ << "========" << endl;
    if(pDepthMarketData != NULL)
    {
#ifdef _DEBUG
        cout << __FUNCTION__ << " - TradingDay: " << pDepthMarketData->TradingDay << endl;
        cout << __FUNCTION__ << " - InstrumentID: " << pDepthMarketData->InstrumentID << endl;
        cout << __FUNCTION__ << " - ExchangeID: " << pDepthMarketData->ExchangeID << endl;
        cout << __FUNCTION__ << " - ExchangeInstID: " << pDepthMarketData->ExchangeInstID << endl;
        cout << __FUNCTION__ << " - LastPrice: " << pDepthMarketData->LastPrice << endl;
        cout << __FUNCTION__ << " - PreSettlementPrice: " << pDepthMarketData->PreSettlementPrice << endl;
        cout << __FUNCTION__ << " - PreClosePrice: " << pDepthMarketData->PreClosePrice << endl;
        cout << __FUNCTION__ << " - PreOpenInterest: " << pDepthMarketData->PreOpenInterest << endl;
        cout << __FUNCTION__ << " - OpenPrice: " << pDepthMarketData->OpenPrice << endl;
        cout << __FUNCTION__ << " - HighestPrice: " << pDepthMarketData->HighestPrice << endl;
        cout << __FUNCTION__ << " - LowestPrice: " << pDepthMarketData->LowestPrice << endl;
        cout << __FUNCTION__ << " - Volume: " << pDepthMarketData->Volume << endl;
        cout << __FUNCTION__ << " - Turnover: " << pDepthMarketData->Turnover << endl;
        cout << __FUNCTION__ << " - OpenInterest: " << pDepthMarketData->OpenInterest << endl;
        cout << __FUNCTION__ << " - ClosePrice: " << pDepthMarketData->ClosePrice << endl;
        cout << __FUNCTION__ << " - SettlementPrice: " << pDepthMarketData->SettlementPrice << endl;
        cout << __FUNCTION__ << " - UpperLimitPrice: " << pDepthMarketData->UpperLimitPrice << endl;
        cout << __FUNCTION__ << " - LowerLimitPrice: " << pDepthMarketData->LowerLimitPrice << endl;
        cout << __FUNCTION__ << " - PreDelta: " << pDepthMarketData->PreDelta << endl;
        cout << __FUNCTION__ << " - CurrDelta: " << pDepthMarketData->CurrDelta << endl;
        cout << __FUNCTION__ << " - UpdateTime: " << pDepthMarketData->UpdateTime << endl;
        cout << __FUNCTION__ << " - UpdateMillisec: " << pDepthMarketData->UpdateMillisec << endl;

        cout << __FUNCTION__ << " - BidPrice1: " << pDepthMarketData->BidPrice1 << endl;
        cout << __FUNCTION__ << " - BidVolume1: " << pDepthMarketData->BidVolume1 << endl;
        cout << __FUNCTION__ << " - AskPrice1: " << pDepthMarketData->AskPrice1 << endl;
        cout << __FUNCTION__ << " - AskVolume1: " << pDepthMarketData->AskVolume1 << endl;

        cout << __FUNCTION__ << " - BidPrice2: " << pDepthMarketData->BidPrice2 << endl;
        cout << __FUNCTION__ << " - BidVolume2: " << pDepthMarketData->BidVolume2 << endl;
        cout << __FUNCTION__ << " - AskPrice2: " << pDepthMarketData->AskPrice2 << endl;
        cout << __FUNCTION__ << " - AskVolume2: " << pDepthMarketData->AskVolume2 << endl;

        cout << __FUNCTION__ << " - BidPrice3: " << pDepthMarketData->BidPrice3 << endl;
        cout << __FUNCTION__ << " - BidVolume3: " << pDepthMarketData->BidVolume3 << endl;
        cout << __FUNCTION__ << " - AskPrice3: " << pDepthMarketData->AskPrice3 << endl;
        cout << __FUNCTION__ << " - AskVolume3: " << pDepthMarketData->AskVolume3 << endl;

        cout << __FUNCTION__ << " - BidPrice4: " << pDepthMarketData->BidPrice4 << endl;
        cout << __FUNCTION__ << " - BidVolume4: " << pDepthMarketData->BidVolume4 << endl;
        cout << __FUNCTION__ << " - AskPrice4: " << pDepthMarketData->AskPrice4 << endl;
        cout << __FUNCTION__ << " - AskVolume4: " << pDepthMarketData->AskVolume4 << endl;

        cout << __FUNCTION__ << " - BidPrice5: " << pDepthMarketData->BidPrice5 << endl;
        cout << __FUNCTION__ << " - BidVolume5: " << pDepthMarketData->BidVolume5 << endl;
        cout << __FUNCTION__ << " - AskPrice5: " << pDepthMarketData->AskPrice5 << endl;
        cout << __FUNCTION__ << " - AskVolume5: " << pDepthMarketData->AskVolume5 << endl;

        cout << __FUNCTION__ << " - AveragePrice: " << pDepthMarketData->AveragePrice << endl;
#endif
    }
}

bool CTPMdUserSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, string funcName)
{
    bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
    if (ret){
        cerr<<"Error response in function " << funcName << "! Error ID: "
                << pRspInfo->ErrorID << ". Error Message: "<<pRspInfo->ErrorMsg<<endl;
    }
    return ret;
}
