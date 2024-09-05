//
// Created by jieggii on 8/31/24.
//

#include "HttpServer.h"
// #include <ESP8266WebServer.h>

HttpServer::HttpServer(int port) : server(port) {}

void HttpServer::registerHandlers() { server.on("/"); }
