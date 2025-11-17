/* packet-xgt.h
 * Definitions for XGT (LS ELECTRIC) protocol packet disassembly
 * Copyright 2025
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef __PACKET_XGT_H__
#define __PACKET_XGT_H__

/* XGT Protocol Ports */
#define XGT_TCP_PORT 2004
#define XGT_UDP_PORT 2005

/* Company ID */
#define XGT_COMPANY_ID "LSIS-XGT"
#define XGT_COMPANY_ID_LEN 8

/* Header sizes */
#define XGT_HEADER_LEN 20

/* Source of Frame values */
#define XGT_SOURCE_CLIENT 0x33
#define XGT_SOURCE_SERVER 0x11

/* CPU Info */
#define XGT_CPU_INFO_XGK 0xA0
#define XGT_CPU_INFO_XGI 0xA4
#define XGT_CPU_INFO_XGR 0xA8

/* Command codes */
#define XGT_CMD_READ_REQUEST    0x0054
#define XGT_CMD_READ_RESPONSE   0x0055
#define XGT_CMD_WRITE_REQUEST   0x0058
#define XGT_CMD_WRITE_RESPONSE  0x0059
#define XGT_CMD_STATUS_REQUEST  0x00B0
#define XGT_CMD_STATUS_RESPONSE 0x00B1

/* Data types */
#define XGT_DTYPE_BIT    0x00
#define XGT_DTYPE_BYTE   0x01
#define XGT_DTYPE_WORD   0x02
#define XGT_DTYPE_DWORD  0x03
#define XGT_DTYPE_LWORD  0x04
#define XGT_DTYPE_CONTINUOUS 0x14

/* Error status */
#define XGT_ERROR_NONE   0x0000
#define XGT_ERROR_EXISTS 0xFFFF

/* CPU Types */
#define XGT_CPU_TYPE_XGK_CPUH 0x01
#define XGT_CPU_TYPE_XGK_CPUS 0x02
#define XGT_CPU_TYPE_XGI_CPUU 0x05

/* System States */
#define XGT_SYS_STATE_RUN   0x01
#define XGT_SYS_STATE_STOP  0x02
#define XGT_SYS_STATE_ERROR 0x04
#define XGT_SYS_STATE_DEBUG 0x08

#endif /* __PACKET_XGT_H__ */