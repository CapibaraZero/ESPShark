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

#ifndef ESPSHARK_H
#define ESPSHARK_H

#include "esp_private/wifi.h"

class ESPShark {
   public:
    ESPShark(const char *filename);
    ESPShark(const char *filename, wifi_interface_t interface);
    ESPShark(const char *filename, wifi_rxcb_t cb);
    ESPShark(const char *filename, wifi_rxcb_t cb, wifi_interface_t interface);
    ~ESPShark();
    unsigned long int get_sniffed_packets();
};

#endif