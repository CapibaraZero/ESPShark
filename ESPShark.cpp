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

#include "ESPShark.hpp"
#include "esp_private/wifi.h"
#include "PCAP.h"
#include <TimeLib.h>

static PCAP pcap = PCAP();
static unsigned long int last_save = millis();
unsigned long int sniffed_packets = 0;

static esp_err_t wifi_recv_callback(void *buffer, uint16_t len, void *eb)
{
    uint32_t timestamp = now();                                          // current timestamp
    uint32_t microseconds = (unsigned int)(micros() - millis() * 1000);  // micro seconds offset (0 - 999)
    pcap.newPacketSD(timestamp, microseconds, len, (uint8_t *)buffer);
    sniffed_packets++;
    if (millis() - last_save >= 2000) {
        pcap.flushFile();
        last_save = millis();
    }
    esp_wifi_internal_free_rx_buffer(eb);
    return ESP_OK;
}

ESPShark::ESPShark(const char *filename) {
    File fptr = SD.open(filename, FILE_WRITE);
    fptr.close();
    pcap.filename = filename;
    pcap.network = 1;
    pcap.openFile(SD);
    esp_wifi_internal_reg_rxcb(WIFI_IF_STA, wifi_recv_callback);
}

ESPShark::ESPShark(const char *filename, wifi_interface_t interface) {
    File fptr = SD.open(filename, FILE_WRITE);
    fptr.close();
    pcap.filename = filename;
    pcap.network = 1;
    pcap.openFile(SD);
    esp_wifi_internal_reg_rxcb(interface, wifi_recv_callback);
}

ESPShark::ESPShark(const char *filename, wifi_rxcb_t cb) {
    File fptr = SD.open(filename, FILE_WRITE);
    fptr.close();
    pcap.filename = filename;
    pcap.network = 1;
    pcap.openFile(SD);
    esp_wifi_internal_reg_rxcb(WIFI_IF_STA, cb);
}

ESPShark::ESPShark(const char *filename, wifi_rxcb_t cb, wifi_interface_t interface) {
    File fptr = SD.open(filename, FILE_WRITE);
    fptr.close();
    pcap.filename = filename;
    pcap.network = 1;
    pcap.openFile(SD);
    esp_wifi_internal_reg_rxcb(interface, cb);
}

ESPShark::~ESPShark() {
    pcap.closeFile();
    esp_wifi_internal_reg_rxcb(WIFI_IF_STA, NULL);
}

unsigned long int ESPShark::get_sniffed_packets() {
    return sniffed_packets;
}