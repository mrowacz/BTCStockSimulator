#include "crow.h"
#include "StockEngine.h"

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
