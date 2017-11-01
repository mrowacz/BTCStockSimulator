/*
 * StockEngine.cpp
 *
 *  Created on: Oct 30, 2017
 *      Author: mrowacz
 */

#include <ctime>
#include <string>
#include <iostream>

#include <bsoncxx/array/view.hpp>
#include <bsoncxx/array/view.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/document/value.hpp>
#include <bsoncxx/document/view.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/string_view.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/types/value.hpp>

#include "crow.h"
#include "StockEngine.h"

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::finalize;

static constexpr const char * COLLECTION = "btc-usd";

using namespace bsoncxx;

StockEngine::StockEngine() :
										inst(), conn(mongocxx::uri{}), db(conn["btc-stock-db"]),
										start_date(0), btc_usd(0), usd(0), btc(0), timestamp(0)
{
	mongocxx::options::find opts;
	bsoncxx::builder::stream::document order_builder;
	order_builder << "timestamp" << 1;
	opts.sort(order_builder.view());
	opts.limit(1);
	auto cursor = db[COLLECTION].find({}, opts);
	auto docItr = cursor.begin();

	std::cout << bsoncxx::to_json(*docItr) << std::endl;
	auto dateEntry = (*docItr)["date"];

	for (auto ele : *docItr)
	{
		stdx::string_view field_key{ele.key()};
		std::cout << "Got key, key = " << field_key << std::endl;
		types::value ele_val{ele.get_value()};
		switch (ele.type()) {
		case type::k_utf8:
			std::cout << "Got String!" << std::endl;
			break;
		case type::k_oid:
			std::cout << "Got ObjectId!" << std::endl;
			break;
		case type::k_date: {
			auto now = ele.get_date().value;
			typedef std::chrono::duration<float> float_seconds;
			auto secs = std::chrono::duration_cast<float_seconds>(now);
			std::cout << secs.count() << std::endl;

		    std::time_t test = secs.count();
		    std::cout << std::ctime(&test);

			break;
		}
		case type::k_array: {
			std::cout << "Got Array!" << std::endl;
			// if we have a subarray, we can access it by getting a view of it.
			array::view subarr{ele.get_array().value};
			for (array::element ele : subarr) {
				std::cout << "array element: " << ele.get_utf8().value.to_string() << std::endl;
			}
			break;
		}
		default:
			std::cout << "We messed up!" << std::endl;
		}
	}
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

