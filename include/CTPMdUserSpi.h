/*
 * CTPMdUserSpi.h
 *
 *  Created on: Apr 3, 2013
 *      Author: fuyf
 */

#ifndef CTPMDUSERSPI_H_
#define CTPMDUSERSPI_H_

#include <string>
#include "ThostFtdcMdApi.h"

class CTPMdUserSpi : public CThostFtdcMdSpi
{
public:
	CTPMdUserSpi(CThostFtdcMdApi *api);
	virtual ~CTPMdUserSpi();

	virtual void OnFrontConnected();
	virtual void OnFrontDisconnected(int nReason);
	virtual void OnHeartBeatWarning(int nTimeLapse);
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

public:
	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, std::string funcName);

private:
	CThostFtdcMdApi *pMdUserApi;
	CThostFtdcRspUserLoginField loginField;
};

#endif /* CTPMDUSERSPI_H_ */
