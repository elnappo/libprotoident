/* 
 * This file is part of libprotoident
 *
 * Copyright (c) 2011 The University of Waikato, Hamilton, New Zealand.
 * Author: Shane Alcock
 *
 * With contributions from:
 *      Aaron Murrihy
 *      Donald Neal
 *
 * All rights reserved.
 *
 * This code has been developed by the University of Waikato WAND 
 * research group. For further information please see http://www.wand.net.nz/
 *
 * libprotoident is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libprotoident is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libprotoident; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id$
 */

#include <string.h>

#include "libprotoident.h"
#include "proto_manager.h"
#include "proto_common.h"

#define NUMBER_OF_NETWORKS_IPV4 124

static const char* networks_ipv4[NUMBER_OF_NETWORKS_IPV4] = {
    "23.246.2.0/24",
    "23.246.3.0/24",
    "23.246.4.0/24",
    "23.246.5.0/24",
    "23.246.6.0/24",
    "23.246.7.0/24",
    "23.246.8.0/24",
    "23.246.9.0/24",
    "23.246.10.0/24",
    "23.246.11.0/24",
    "23.246.12.0/24",
    "23.246.13.0/24",
    "23.246.14.0/24",
    "23.246.15.0/24",
    "23.246.16.0/24",
    "23.246.17.0/24",
    "23.246.18.0/24",
    "23.246.19.0/24",
    "23.246.20.0/24",
    "23.246.22.0/24",
    "23.246.23.0/24",
    "23.246.24.0/24",
    "23.246.25.0/24",
    "23.246.26.0/24",
    "23.246.27.0/24",
    "23.246.28.0/22",
    "23.246.28.0/24",
    "23.246.29.0/24",
    "23.246.30.0/24",
    "23.246.31.0/24",
    "23.246.32.0/20",
    "23.246.36.0/24",
    "23.246.37.0/24",
    "23.246.48.0/20",
    "23.246.58.0/24",
    "23.246.59.0/24",
    "23.246.62.0/24",
    "23.246.63.0/24",
    "37.77.184.0/24",
    "37.77.185.0/24",
    "37.77.186.0/24",
    "37.77.187.0/24",
    "37.77.188.0/24",
    "37.77.189.0/24",
    "37.77.190.0/24",
    "37.77.191.0/24",
    "64.120.128.0/17",
    "66.197.128.0/17",
    "69.53.224.0/24",
    "69.53.225.0/24",
    "69.53.226.0/24",
    "69.53.229.0/24",
    "69.53.231.0/24",
    "69.53.234.0/24",
    "69.53.236.0/24",
    "69.53.237.0/24",
    "69.53.238.0/24",
    "69.53.249.0/24",
    "69.53.255.0/24",
    "108.175.32.0/24",
    "108.175.33.0/24",
    "108.175.34.0/24",
    "108.175.35.0/24",
    "108.175.38.0/24",
    "108.175.39.0/24",
    "108.175.40.0/24",
    "108.175.41.0/24",
    "108.175.42.0/24",
    "108.175.43.0/24",
    "108.175.44.0/24",
    "108.175.46.0/24",
    "108.175.47.0/24",
    "185.2.220.0/24",
    "185.2.221.0/24",
    "185.2.222.0/24",
    "185.2.223.0/24",
    "185.9.188.0/24",
    "185.9.189.0/24",
    "185.9.190.0/23",
    "192.173.64.0/20",
    "192.173.64.0/24",
    "192.173.80.0/20",
    "192.173.96.0/20",
    "192.173.112.0/20",
    "198.38.96.0/24",
    "198.38.97.0/24",
    "198.38.98.0/24",
    "198.38.99.0/24",
    "198.38.100.0/24",
    "198.38.101.0/24",
    "198.38.102.0/23",
    "198.38.102.0/24",
    "198.38.108.0/24",
    "198.38.109.0/24",
    "198.38.110.0/24",
    "198.38.111.0/24",
    "198.38.112.0/24",
    "198.38.113.0/24",
    "198.38.114.0/24",
    "198.38.115.0/24",
    "198.38.116.0/24",
    "198.38.117.0/24",
    "198.38.118.0/24",
    "198.38.119.0/24",
    "198.38.120.0/24",
    "198.38.121.0/24",
    "198.38.122.0/24",
    "198.38.123.0/24",
    "198.38.124.0/24",
    "198.38.125.0/24",
    "198.45.48.0/24",
    "198.45.49.0/24",
    "198.45.50.0/24",
    "198.45.52.0/24",
    "198.45.53.0/24",
    "198.45.54.0/24",
    "198.45.55.0/24",
    "198.45.56.0/24",
    "198.45.57.0/24",
    "198.45.58.0/24",
    "198.45.61.0/24",
    "198.45.62.0/24",
    "198.45.63.0/24",
    "208.75.77.0/24"
};

static inline bool match_netflix(lpi_data_t *data, lpi_module_t *mod UNUSED) 
{

    if (match_ip_either_to_networks(data, networks_ipv4, NUMBER_OF_NETWORKS_IPV4))
        return true;

    //if (match_ip6_either_to_networks(data, networks_ipv6, NUMBER_OF_NETWORKS))
    //    return true;

	return false;
}

static lpi_module_t lpi_netflix = {
	LPI_PROTO_NETFLIX,
	LPI_CATEGORY_STREAMING,
	"Netflix",
    1,
	match_netflix
};

void register_netflix(LPIModuleMap *mod_map) {
	register_protocol(&lpi_netflix, mod_map);
}

