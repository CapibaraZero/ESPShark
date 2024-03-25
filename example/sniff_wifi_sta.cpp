/*
 * This file is part of the Capibara zero
 * project(https://capibarazero.github.io/).
 *
 * Copyright (c) 2024 Andrea Canale.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Arduino.h"
#include "WiFi.h"
#include "ESPShark.hpp"

ESPShark *sniffer;
void setup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin("AGNELLI WIFI", "agnelliwifi");
    Serial0.println("Connecting to WiFi network");
    while (WiFi.status() != WL_CONNECTED);
    Serial0.println("Connected! Starting DoS");
    sniffer = new ESPShark("/eth_sniff.pcap");
}

void loop() {
    Serial0.println("Avoid Watchdog trigger");
    delay(1000);
}