/*
 * CTPTraderSpi.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: fuyf
 */

#include <iostream>
#include <cstring>
#include "CTPTraderSpi.h"

using namespace std;

CTPTraderSpi::CTPTraderSpi(CThostFtdcTraderApi *api)
    : pTraderApi(api)
{
}

CTPTraderSpi::~CTPTraderSpi()
{
}


void CTPTraderSpi::OnFrontConnected()
{
#ifdef _DEBUG
    cout << "Connected" << endl;
#endif
}

void CTPTraderSpi::OnFrontDisconnected(int nReason)
{
#ifdef _DEBUG
    cout << "Disconnected! Reason: " << nReason << endl;
#endif
}

void CTPTraderSpi::OnHeartBeatWarning(int nTimeLapse)
{
#ifdef _DEBUG
    cerr << "Heartbeat warning! TimeLapse: " << nTimeLapse << endl;
#endif
}

void CTPTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void CTPTraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

/**
 * Callback on response for query instrument
 *
 * @param pInstrument
 * @param pRspInfo
 * @param nRequestID
 * @param bIsLast
 */
void CTPTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if(!IsErrorRspInfo(pRspInfo, __FUNCTION__) && (pInstrument != NULL))
    {
#ifdef _DEBUG
        cout << __FUNCTION__ << endl;
        cout << __FUNCTION__ << " - InstrumentID: " << pInstrument->InstrumentID << endl;
        cout << __FUNCTION__ << " - ExchangeID: " << pInstrument->ExchangeID << endl;
        cout << __FUNCTION__ << " - InstrumentName: " << pInstrument->InstrumentName << endl;
        cout << __FUNCTION__ << " - ExchangeInstID: " << pInstrument->ExchangeInstID << endl;
        cout << __FUNCTION__ << " - ProductID: " << pInstrument->ProductID << endl;
        cout << __FUNCTION__ << " - ProductClass: " << pInstrument->ProductClass << endl;

        cout << __FUNCTION__ << " - DeliveryYear: " << pInstrument->DeliveryYear << endl;
        cout << __FUNCTION__ << " - DeliveryMonth: " << pInstrument->DeliveryMonth << endl;
        cout << __FUNCTION__ << " - MaxMarketOrderVolume: " << pInstrument->MaxMarketOrderVolume << endl;
        cout << __FUNCTION__ << " - MinMarketOrderVolume: " << pInstrument->MinMarketOrderVolume << endl;
        cout << __FUNCTION__ << " - MaxLimitOrderVolume: " << pInstrument->MaxLimitOrderVolume << endl;
        cout << __FUNCTION__ << " - MinLimitOrderVolume: " << pInstrument->MinLimitOrderVolume << endl;
        cout << __FUNCTION__ << " - VolumeMultiple: " << pInstrument->VolumeMultiple << endl;

        cout << __FUNCTION__ << " - PriceTick: " << pInstrument->PriceTick << endl;
        cout << __FUNCTION__ << " - CreateDate: " << pInstrument->CreateDate << endl;
        cout << __FUNCTION__ << " - OpenDate: " << pInstrument->OpenDate << endl;
        cout << __FUNCTION__ << " - ExpireDate: " << pInstrument->ExpireDate << endl;
        cout << __FUNCTION__ << " - StartDelivDate: " << pInstrument->StartDelivDate << endl;
        cout << __FUNCTION__ << " - EndDelivDate: " << pInstrument->EndDelivDate << endl;
        cout << __FUNCTION__ << " - InstLifePhase: " << pInstrument->InstLifePhase << endl;
        cout << __FUNCTION__ << " - IsTrading: " << pInstrument->IsTrading << endl;
        cout << __FUNCTION__ << " - PositionType: " << pInstrument->PositionType << endl;
        cout << __FUNCTION__ << " - PositionDateType: " << pInstrument->PositionDateType << endl;
        cout << __FUNCTION__ << " - LongMarginRatio: " << pInstrument->LongMarginRatio << endl;
        cout << __FUNCTION__ << " - ShortMarginRatio: " << pInstrument->ShortMarginRatio << endl;
#endif
    }

    if(pInstrument == NULL)
    {
        cerr << __FUNCTION__ << ": No instrument response info" << endl;
    }
#ifdef _DEBUG
    cout << __FUNCTION__ << " - nRequestID: " << nRequestID << endl;
    cout << __FUNCTION__ << " - bIsLast: " << (bIsLast ? "True" : "False") << endl;
#endif
}

void CTPTraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

bool CTPTraderSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, string funcName)
{
    bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
    if (ret){
        cerr<<"Error response in function " << funcName << "! Error ID: "
                << pRspInfo->ErrorID << ". Error Message: "<<pRspInfo->ErrorMsg<<endl;
    }
    return ret;
}
