/*
 * StockEngine.h
 *
 *  Created on: Oct 30, 2017
 *      Author: mrowacz
 */

#ifndef STOCKENGINE_H_
#define STOCKENGINE_H_

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/options/find.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

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

	mongocxx::instance inst;
	mongocxx::client conn;
	mongocxx::database db;

	long long start_date;
};

#endif /* STOCKENGINE_H_ */
