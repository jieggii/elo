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

struct WiFiSettings {
    enum class Mode {
        HOST,
        CLIENT,
    };

    Mode mode;
    union {
        HostWiFiSettings hostWiFiSettings;
        ClientWiFiSettings clientWifiSettings;
    };
};

#endif  // ELO_WIFISETTINGS_H
