/*
 * StockEngine.cpp
 *
 *  Created on: Oct 30, 2017
 *      Author: mrowacz
 */

#include <string>

#include "StockEngine.h"

StockEngine::StockEngine()
{
}

StockEngine::~StockEngine()
{
}

crow::json::wvalue StockEngine::get()
{
	crow::json::wvalue x;
	x["btc"] = std::to_string(btc);
	x["usd"] = std::to_string(usd);
	x["btc_usd"] = std::to_string(btc_usd);
	x["timestamp"] = std::to_string(timestamp);

	return x;
}

void StockEngine::next()
{
}

crow::json::wvalue StockEngine::action(crow::json::rvalue cmd)
{

	return crow::json::wvalue();
}

