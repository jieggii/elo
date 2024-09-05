//
// Created by jieggii on 8/31/24.
//

#ifndef ELO_HTTPSERVER_H
#define ELO_HTTPSERVER_H

#include "ESP8266WebServer.h"

class HttpServer {
   private:
    ESP8266WebServer server;

   public:
    HttpServer(int port);
    void start();
    void registerHandlers();
};

#endif  // ELO_HTTPSERVER_H
