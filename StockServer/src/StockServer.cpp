#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/options/find.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include "crow.h"
#include "StockEngine.h"

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::finalize;

static constexpr int SERVER_PORT = 8081;

int main(int, char**)
{
	crow::SimpleApp app;
	StockEngine eng;

	CROW_ROUTE(app, "/")([](){
		return "BTC Stock Server";
	});

	CROW_ROUTE(app, "/stock")
	.methods("GET"_method, "POST"_method)
	([&](const crow::request& req){
		if (req.method == "GET"_method)
		{
			return crow::response(eng.get());
		} else if (req.method == "POST"_method)
		{
			auto x = crow::json::load(req.body);
			if (!x)
				return crow::response(400);
			eng.action(x);
		}
		else return crow::response(400);
	});

	app.port(SERVER_PORT).multithreaded().run();
}
