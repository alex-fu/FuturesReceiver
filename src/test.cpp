/*
 * test.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: fuyf
 */

#include <iostream>

using namespace std;

extern int testCTPMdUserSpi();
extern int testCTPTraderSpi();

int main()
{
    cout << "Test CTPTraderSpi" << endl;
    testCTPTraderSpi();

    cout << "Test CTPMdUserSpi" << endl;
    testCTPMdUserSpi();


    return 0;
}
