//
// Created by jieggii on 9/2/24.
//

#ifndef ELO_WIFISETTINGS_H
#define ELO_WIFISETTINGS_H

struct HostWiFiCredentials {
    char const *SSID;
    char const *PASSWORD;
};

struct ClientWiFiCredentials {
    char *SSID;
    char *PASSWORD;
};

enum class WiFiMode {
    HOST,
    CLIENT,
};

struct WiFiSettings {
    WiFiMode mode;

    union {
        HostWiFiCredentials hostWiFiSettings;
        ClientWiFiCredentials clientWifiSettings;
    };
};

#endif  // ELO_WIFISETTINGS_H
