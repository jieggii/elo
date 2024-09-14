//
// Created by jieggii on 9/2/24.
//

#ifndef ELO_WIFISETTINGS_H
#define ELO_WIFISETTINGS_H

struct HostWiFiSettings {
    char *SSID;
    char *PASSWORD;
};

struct ClientWiFiSettings {
    char *SSID;
    char *PASSWORD;
};

enum class WifiMode {
    HOST,
    CLIENT,
};

struct WiFiSettings {
    WifiMode mode;

    union {
        HostWiFiSettings hostWiFiSettings;
        ClientWiFiSettings clientWifiSettings;
    };
};

#endif  // ELO_WIFISETTINGS_H
