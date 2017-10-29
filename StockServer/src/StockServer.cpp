//============================================================================
// Name        : StockServer.cpp
// Author      : mrowacz@gmail.com
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include "crow.h"

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

using namespace std;

int main() {
//    crow::SimpleApp app;
//
//    CROW_ROUTE(app, "/")([](){
//        return "Hello world";
//    });
//
//    app.port(18080).multithreaded().run();
	mongocxx::client conn{};

	auto db = conn["test"];
	auto index_spec = document{} << "cost" << "-1" << finalize;
	db["shortestpaths"].create_index(index_spec.view(), {});

    return 0;
}
