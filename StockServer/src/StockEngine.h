/*
 * StockEngine.h
 *
 *  Created on: Oct 30, 2017
 *      Author: mrowacz
 */

#ifndef STOCKENGINE_H_
#define STOCKENGINE_H_

#include "crow.h"

class StockEngine {
public:
	StockEngine();

    crow::json::wvalue get();
    // switch to the next timestamp
    void next();
    crow::json::wvalue action(crow::json::rvalue cmd);

	virtual ~StockEngine();
private:
	long timestamp;
	float btc;
	float usd;

	float btc_usd;
};

#endif /* STOCKENGINE_H_ */
