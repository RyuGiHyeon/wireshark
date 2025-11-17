/* packet-xgt.c
 * Routines for XGT (LS ELECTRIC PLC) protocol packet disassembly
 * Copyright 2025
 *
 * XGT is a proprietary protocol used by LS ELECTRIC (formerly LS Industrial Systems)
 * for communication with their XGT series PLCs over Ethernet.
 *
 * Protocol specifications based on:
 * "XGT FEnet I/F Module Protocol Specification" (2005.3.30)
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "config.h"
#include <epan/packet.h>
#include <epan/prefs.h>
#include <epan/wmem_scopes.h>
#include <epan/tfs.h>
#include <epan/expert.h>
#include "packet-xgt.h"

/* Define array_length macro if not available */
#ifndef array_length
#define array_length(x) (sizeof(x) / sizeof((x)[0]))
#endif

void proto_register_xgt(void);
void proto_reg_handoff_xgt(void);

/* Protocol handles */
static int proto_xgt = -1;

/* Header fields */
static int hf_xgt_company_id = -1;
static int hf_xgt_reserved1 = -1;
static int hf_xgt_plc_info = -1;
static int hf_xgt_plc_info_cpu_type = -1;
static int hf_xgt_plc_info_redundancy = -1;
static int hf_xgt_plc_info_cpu_error = -1;
static int hf_xgt_plc_info_sys_state = -1;
static int hf_xgt_cpu_info = -1;
static int hf_xgt_source = -1;
static int hf_xgt_invoke_id = -1;
static int hf_xgt_length = -1;
static int hf_xgt_fenet_position = -1;
static int hf_xgt_fenet_slot = -1;
static int hf_xgt_fenet_base = -1;
static int hf_xgt_reserved2 = -1;

/* Instruction fields */
static int hf_xgt_command = -1;
static int hf_xgt_data_type = -1;
static int hf_xgt_reserved_area = -1;
static int hf_xgt_error_status = -1;
static int hf_xgt_error_code = -1;
static int hf_xgt_block_count = -1;
static int hf_xgt_variable_count = -1;
static int hf_xgt_variable_length = -1;
static int hf_xgt_variable_name = -1;
static int hf_xgt_data_length = -1;
static int hf_xgt_data = -1;
static int hf_xgt_data_value_uint8 = -1;
static int hf_xgt_data_value_uint16 = -1;
static int hf_xgt_data_value_uint32 = -1;
static int hf_xgt_data_value_uint64 = -1;

/* Status fields */
static int hf_xgt_status_data = -1;
static int hf_xgt_slot_info = -1;
static int hf_xgt_cpu_type = -1;
static int hf_xgt_ver_num = -1;
static int hf_xgt_sys_state = -1;
static int hf_xgt_padt_cnf = -1;
static int hf_xgt_cnf_er = -1;
static int hf_xgt_cnf_war = -1;

/* Subtree indices */
static gint ett_xgt = -1;
static gint ett_xgt_header = -1;
static gint ett_xgt_instruction = -1;
static gint ett_xgt_plc_info = -1;
static gint ett_xgt_fenet_position = -1;
static gint ett_xgt_block = -1;
static gint ett_xgt_status = -1;

/* Expert info fields */
static expert_field ei_xgt_invalid_length = EI_INIT;
static expert_field ei_xgt_error_response = EI_INIT;
static expert_field ei_xgt_truncated_data = EI_INIT;
static expert_field ei_xgt_invalid_command = EI_INIT;
static expert_field ei_xgt_cpu_error = EI_INIT;
static expert_field ei_xgt_suspicious_count = EI_INIT;

/* Value strings */
static const value_string xgt_command_vals[] = {
    { XGT_CMD_READ_REQUEST,    "Read Request" },
    { XGT_CMD_READ_RESPONSE,   "Read Response" },
    { XGT_CMD_WRITE_REQUEST,   "Write Request" },
    { XGT_CMD_WRITE_RESPONSE,  "Write Response" },
    { XGT_CMD_STATUS_REQUEST,  "Status Request" },
    { XGT_CMD_STATUS_RESPONSE, "Status Response" },
    { 0, NULL }
};

static const value_string xgt_data_type_vals[] = {
    { XGT_DTYPE_BIT,    "BIT" },
    { XGT_DTYPE_BYTE,   "BYTE" },
    { XGT_DTYPE_WORD,   "WORD" },
    { XGT_DTYPE_DWORD,  "DWORD" },
    { XGT_DTYPE_LWORD,  "LWORD" },
    { XGT_DTYPE_CONTINUOUS, "Continuous Block" },
    { 0, NULL }
};

static const value_string xgt_source_vals[] = {
    { XGT_SOURCE_CLIENT, "Client (HMI -> PLC)" },
    { XGT_SOURCE_SERVER, "Server (PLC -> HMI)" },
    { 0, NULL }
};

static const value_string xgt_cpu_info_vals[] = {
    { XGT_CPU_INFO_XGK, "XGK CPU" },
    { XGT_CPU_INFO_XGI, "XGI CPU" },
    { XGT_CPU_INFO_XGR, "XGR CPU" },
    { 0, NULL }
};

static const value_string xgt_cpu_type_vals[] = {
    { XGT_CPU_TYPE_XGK_CPUH, "XGK-CPUH" },
    { XGT_CPU_TYPE_XGK_CPUS, "XGK-CPUS" },
    { XGT_CPU_TYPE_XGI_CPUU, "XGI-CPUU" },
    { 0, NULL }
};

static const value_string xgt_sys_state_vals[] = {
    { XGT_SYS_STATE_RUN,   "RUN" },
    { XGT_SYS_STATE_STOP,  "STOP" },
    { XGT_SYS_STATE_ERROR, "ERROR" },
    { XGT_SYS_STATE_DEBUG, "DEBUG" },
    { 0, NULL }
};

static const value_string xgt_error_status_vals[] = {
    { XGT_ERROR_NONE,   "Success" },
    { XGT_ERROR_EXISTS, "Error" },
    { 0, NULL }
};

/* XGT Error codes (common error codes from protocol spec) */
static const value_string xgt_error_code_vals[] = {
    { 0x0000, "No Error" },
    { 0x1101, "There is no XGT instruction" },
    { 0x1102, "There is no XGT device" },
    { 0x1104, "Invalid data size" },
    { 0x1105, "Invalid data range" },
    { 0x1106, "Data is protected" },
    { 0x1107, "Invalid block number" },
    { 0x1108, "Variable name error" },
    { 0x1109, "Duplicated variable" },
    { 0x110A, "Read not allowed" },
    { 0x110B, "Write not allowed" },
    { 0x1201, "CPU is in STOP mode" },
    { 0x1202, "CPU is in RUN mode" },
    { 0x1203, "CPU module error" },
    { 0x1301, "Password error" },
    { 0x1302, "Mode change not allowed" },
    { 0x1303, "Communication timeout" },
    { 0, NULL }
};

/* True/False strings */
static const true_false_string tfs_slave_master = {
    "Slave",
    "Master"
};

static const true_false_string tfs_error_normal = {
    "Error",
    "Normal"
};

/* Dissect XGT Application Header */
static int
dissect_xgt_header(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, guint offset)
{
    proto_item *ti, *plc_info_item;
    proto_tree *header_tree, *plc_info_tree, *fenet_tree;
    guint8 source;
    guint8 fenet_pos;
    guint16 plc_info, data_length;

    /* Bounds check - ensure we have enough data for the header */
    if (tvb_reported_length_remaining(tvb, offset) < XGT_HEADER_LEN) {
        expert_add_info(pinfo, tree, &ei_xgt_truncated_data);
        return tvb_captured_length(tvb);
    }

    ti = proto_tree_add_item(tree, proto_xgt, tvb, offset, XGT_HEADER_LEN, ENC_NA);
    header_tree = proto_item_add_subtree(ti, ett_xgt_header);

    /* Company ID */
    proto_tree_add_item(header_tree, hf_xgt_company_id, tvb, offset, 8, ENC_ASCII);
    offset += 8;

    /* Reserved */
    proto_tree_add_item(header_tree, hf_xgt_reserved1, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    offset += 2;

    /* PLC Info */
    plc_info = tvb_get_letohs(tvb, offset);
    plc_info_item = proto_tree_add_item(header_tree, hf_xgt_plc_info, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    plc_info_tree = proto_item_add_subtree(plc_info_item, ett_xgt_plc_info);

    proto_tree_add_item(plc_info_tree, hf_xgt_plc_info_cpu_type, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(plc_info_tree, hf_xgt_plc_info_redundancy, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(plc_info_tree, hf_xgt_plc_info_cpu_error, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(plc_info_tree, hf_xgt_plc_info_sys_state, tvb, offset, 2, ENC_LITTLE_ENDIAN);

    /* Check for CPU error and add expert info */
    if (plc_info & 0x0080) {
        expert_add_info(pinfo, plc_info_item, &ei_xgt_cpu_error);
    }
    offset += 2;

    /* CPU Info */
    proto_tree_add_item(header_tree, hf_xgt_cpu_info, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset += 1;

    /* Source of Frame */
    source = tvb_get_uint8(tvb, offset);
    proto_tree_add_item(header_tree, hf_xgt_source, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset += 1;

    /* Update info column based on source */
    if (source == XGT_SOURCE_CLIENT) {
        col_set_str(pinfo->cinfo, COL_INFO, "Request: ");
    } else if (source == XGT_SOURCE_SERVER) {
        col_set_str(pinfo->cinfo, COL_INFO, "Response: ");
    }

    /* Invoke ID */
    proto_tree_add_item(header_tree, hf_xgt_invoke_id, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    offset += 2;

    /* Length - validate against remaining data */
    data_length = tvb_get_letohs(tvb, offset);
    ti = proto_tree_add_item(header_tree, hf_xgt_length, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    if (data_length > tvb_reported_length_remaining(tvb, offset + 4)) {
        expert_add_info(pinfo, ti, &ei_xgt_invalid_length);
    }
    offset += 2;

    /* FEnet Position */
    fenet_pos = tvb_get_uint8(tvb, offset);
    ti = proto_tree_add_item(header_tree, hf_xgt_fenet_position, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    fenet_tree = proto_item_add_subtree(ti, ett_xgt_fenet_position);

    proto_tree_add_uint(fenet_tree, hf_xgt_fenet_slot, tvb, offset, 1, fenet_pos & 0x0F);
    proto_tree_add_uint(fenet_tree, hf_xgt_fenet_base, tvb, offset, 1, (fenet_pos >> 4) & 0x0F);
    offset += 1;

    /* Reserved2 / BCC */
    proto_tree_add_item(header_tree, hf_xgt_reserved2, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset += 1;

    return offset;
}

/* Parse data values based on data type for better readability */
static void
parse_data_values(tvbuff_t *tvb, proto_tree *tree, guint offset, guint16 data_length, guint16 data_type)
{
    guint i;
    guint value_size;

    /* Determine value size based on data type */
    switch (data_type) {
        case XGT_DTYPE_BIT:
        case XGT_DTYPE_BYTE:
            value_size = 1;
            break;
        case XGT_DTYPE_WORD:
            value_size = 2;
            break;
        case XGT_DTYPE_DWORD:
            value_size = 4;
            break;
        case XGT_DTYPE_LWORD:
            value_size = 8;
            break;
        case XGT_DTYPE_CONTINUOUS:
        default:
            /* For continuous or unknown types, just show raw data */
            return;
    }

    /* Parse individual values */
    if (value_size > 0 && data_length >= value_size) {
        for (i = 0; i < data_length && i + value_size <= data_length; i += value_size) {
            switch (value_size) {
                case 1:
                    proto_tree_add_item(tree, hf_xgt_data_value_uint8, tvb, offset + i, 1, ENC_LITTLE_ENDIAN);
                    break;
                case 2:
                    proto_tree_add_item(tree, hf_xgt_data_value_uint16, tvb, offset + i, 2, ENC_LITTLE_ENDIAN);
                    break;
                case 4:
                    proto_tree_add_item(tree, hf_xgt_data_value_uint32, tvb, offset + i, 4, ENC_LITTLE_ENDIAN);
                    break;
                case 8:
                    proto_tree_add_item(tree, hf_xgt_data_value_uint64, tvb, offset + i, 8, ENC_LITTLE_ENDIAN);
                    break;
            }
        }
    }
}

/* Dissect individual read/write block */
static int
dissect_xgt_block(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, guint offset, gboolean is_request, gboolean is_write, guint16 data_type)
{
    proto_item *ti, *length_item;
    proto_tree *block_tree;
    guint16 var_length, data_length;
    guint8 *var_name;
    guint start_offset = offset;

    /* Bounds check - need at least 2 bytes for length field */
    if (tvb_reported_length_remaining(tvb, offset) < 2) {
        expert_add_info(pinfo, tree, &ei_xgt_truncated_data);
        return tvb_captured_length(tvb);
    }

    block_tree = proto_tree_add_subtree(tree, tvb, offset, 0, ett_xgt_block, &ti, "Variable Block");

    /* Variable length and name (only in requests or write response) */
    if (is_request || is_write) {
        var_length = tvb_get_letohs(tvb, offset);
        length_item = proto_tree_add_item(block_tree, hf_xgt_variable_length, tvb, offset, 2, ENC_LITTLE_ENDIAN);
        offset += 2;

        /* Validate variable length */
        if (var_length > 16) {
            expert_add_info(pinfo, length_item, &ei_xgt_invalid_length);
            proto_item_set_len(ti, offset - start_offset);
            return offset;
        }

        if (var_length > 0) {
            /* Bounds check for variable name */
            if (tvb_reported_length_remaining(tvb, offset) < var_length) {
                expert_add_info(pinfo, length_item, &ei_xgt_truncated_data);
                proto_item_set_len(ti, offset - start_offset);
                return tvb_captured_length(tvb);
            }

            var_name = (guint8 *)tvb_get_string_enc(pinfo->pool, tvb, offset, var_length, ENC_ASCII);
            proto_tree_add_item(block_tree, hf_xgt_variable_name, tvb, offset, var_length, ENC_ASCII);
            proto_item_append_text(ti, ": %s", var_name);
            col_append_fstr(pinfo->cinfo, COL_INFO, " %s", var_name);
            offset += var_length;
        }
    }

    /* Data length and data (in write requests and all responses) */
    if (is_write || !is_request) {
        /* Bounds check for data length field */
        if (tvb_reported_length_remaining(tvb, offset) < 2) {
            expert_add_info(pinfo, ti, &ei_xgt_truncated_data);
            proto_item_set_len(ti, offset - start_offset);
            return tvb_captured_length(tvb);
        }

        data_length = tvb_get_letohs(tvb, offset);
        length_item = proto_tree_add_item(block_tree, hf_xgt_data_length, tvb, offset, 2, ENC_LITTLE_ENDIAN);
        offset += 2;

        /* Validate data length - reasonable upper limit */
        if (data_length > 8192) {
            expert_add_info(pinfo, length_item, &ei_xgt_invalid_length);
        }

        if (data_length > 0) {
            /* Bounds check for data */
            if (tvb_reported_length_remaining(tvb, offset) < data_length) {
                expert_add_info(pinfo, length_item, &ei_xgt_truncated_data);
                proto_item_set_len(ti, offset - start_offset);
                return tvb_captured_length(tvb);
            }

            /* Show raw data first */
            proto_tree_add_item(block_tree, hf_xgt_data, tvb, offset, data_length, ENC_NA);

            /* Then parse individual values based on data type */
            parse_data_values(tvb, block_tree, offset, data_length, data_type);

            /* Add data value to Info column for responses */
            if (!is_request && data_length >= 2) {
                guint16 value = tvb_get_letohs(tvb, offset);
                col_append_fstr(pinfo->cinfo, COL_INFO, " = %u", value);
            }

            offset += data_length;
        }
    }

    proto_item_set_len(ti, offset - start_offset);
    return offset;
}

/* Dissect XGT Instruction (Command and Data) */
static int
dissect_xgt_instruction(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, guint offset)
{
    proto_tree *inst_tree, *status_tree;
    proto_item *ti, *cmd_item, *count_item, *error_item;
    guint16 command, error_status, error_code, block_count, data_type;
    guint i;
    gboolean is_request, is_write, is_status;
    const gchar *cmd_str;

    /* Bounds check - need at least 8 bytes (command, data type, reserved, error/count) */
    if (tvb_reported_length_remaining(tvb, offset) < 8) {
        expert_add_info(pinfo, tree, &ei_xgt_truncated_data);
        return tvb_captured_length(tvb);
    }

    ti = proto_tree_add_item(tree, proto_xgt, tvb, offset, -1, ENC_NA);
    inst_tree = proto_item_add_subtree(ti, ett_xgt_instruction);

    /* Command */
    command = tvb_get_letohs(tvb, offset);
    cmd_str = val_to_str_const(command, xgt_command_vals, "Unknown");
    cmd_item = proto_tree_add_item(inst_tree, hf_xgt_command, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    col_append_str(pinfo->cinfo, COL_INFO, cmd_str);

    /* Warn about unknown commands */
    if (try_val_to_str(command, xgt_command_vals) == NULL) {
        expert_add_info(pinfo, cmd_item, &ei_xgt_invalid_command);
    }
    offset += 2;

    /* Determine request/response and command type */
    is_request = (command == XGT_CMD_READ_REQUEST || command == XGT_CMD_WRITE_REQUEST ||
                  command == XGT_CMD_STATUS_REQUEST);
    is_write = (command == XGT_CMD_WRITE_REQUEST || command == XGT_CMD_WRITE_RESPONSE);
    is_status = (command == XGT_CMD_STATUS_REQUEST || command == XGT_CMD_STATUS_RESPONSE);

    /* Data Type */
    data_type = tvb_get_letohs(tvb, offset);
    proto_tree_add_item(inst_tree, hf_xgt_data_type, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    offset += 2;

    /* Reserved Area */
    proto_tree_add_item(inst_tree, hf_xgt_reserved_area, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    offset += 2;

    /* Error Status (responses only) */
    if (!is_request) {
        error_status = tvb_get_letohs(tvb, offset);
        error_item = proto_tree_add_item(inst_tree, hf_xgt_error_status, tvb, offset, 2, ENC_LITTLE_ENDIAN);
        offset += 2;

        /* Error Code (if error exists) */
        if (error_status != XGT_ERROR_NONE) {
            /* Bounds check for error code */
            if (tvb_reported_length_remaining(tvb, offset) < 2) {
                expert_add_info(pinfo, error_item, &ei_xgt_truncated_data);
                return tvb_captured_length(tvb);
            }

            error_code = tvb_get_letohs(tvb, offset);
            ti = proto_tree_add_item(inst_tree, hf_xgt_error_code, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            expert_add_info_format(pinfo, error_item, &ei_xgt_error_response,
                                   "XGT Error Response: Error Code 0x%04x", error_code);
            col_append_fstr(pinfo->cinfo, COL_INFO, " (Error: 0x%04x)", error_code);
            offset += 2;
            return offset;
        }
    }

    /* Handle Status command separately */
    if (is_status) {
        if (!is_request) {
            /* Bounds check for data size field */
            if (tvb_reported_length_remaining(tvb, offset) < 2) {
                expert_add_info(pinfo, inst_tree, &ei_xgt_truncated_data);
                return tvb_captured_length(tvb);
            }

            /* Status response data */
            guint16 data_size = tvb_get_letohs(tvb, offset);
            ti = proto_tree_add_item(inst_tree, hf_xgt_data_length, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset += 2;

            if (data_size >= 24) {
                /* Bounds check for status data */
                if (tvb_reported_length_remaining(tvb, offset) < 24) {
                    expert_add_info(pinfo, ti, &ei_xgt_truncated_data);
                    return tvb_captured_length(tvb);
                }

                ti = proto_tree_add_item(inst_tree, hf_xgt_status_data, tvb, offset, 24, ENC_NA);
                status_tree = proto_item_add_subtree(ti, ett_xgt_status);

                proto_tree_add_item(status_tree, hf_xgt_slot_info, tvb, offset, 4, ENC_LITTLE_ENDIAN);
                offset += 4;
                proto_tree_add_item(status_tree, hf_xgt_cpu_type, tvb, offset, 2, ENC_LITTLE_ENDIAN);
                offset += 2;
                proto_tree_add_item(status_tree, hf_xgt_ver_num, tvb, offset, 2, ENC_LITTLE_ENDIAN);
                offset += 2;
                proto_tree_add_item(status_tree, hf_xgt_sys_state, tvb, offset, 4, ENC_LITTLE_ENDIAN);
                offset += 4;
                proto_tree_add_item(status_tree, hf_xgt_padt_cnf, tvb, offset, 2, ENC_LITTLE_ENDIAN);
                offset += 2;
                proto_tree_add_item(status_tree, hf_xgt_cnf_er, tvb, offset, 4, ENC_LITTLE_ENDIAN);
                offset += 4;
                proto_tree_add_item(status_tree, hf_xgt_cnf_war, tvb, offset, 4, ENC_LITTLE_ENDIAN);
                offset += 4;
                /* Reserved 2 bytes */
                if (tvb_reported_length_remaining(tvb, offset) >= 2) {
                    offset += 2;
                }
            }
        }
        return offset;
    }

    /* Bounds check for block count field */
    if (tvb_reported_length_remaining(tvb, offset) < 2) {
        expert_add_info(pinfo, inst_tree, &ei_xgt_truncated_data);
        return tvb_captured_length(tvb);
    }

    /* Block/Variable Count */
    block_count = tvb_get_letohs(tvb, offset);
    if (is_request) {
        count_item = proto_tree_add_item(inst_tree, hf_xgt_variable_count, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    } else {
        count_item = proto_tree_add_item(inst_tree, hf_xgt_block_count, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    }

    /* Warn about suspicious counts */
    if (block_count > 100) {
        expert_add_info_format(pinfo, count_item, &ei_xgt_suspicious_count,
                               "Suspicious block count: %u (possible malformed packet)", block_count);
    }
    offset += 2;

    /* Process blocks/variables with bounds checking */
    for (i = 0; i < block_count && i < 256; i++) {
        /* Check if we have remaining data */
        if (tvb_reported_length_remaining(tvb, offset) < 2) {
            expert_add_info(pinfo, count_item, &ei_xgt_truncated_data);
            break;
        }
        offset = dissect_xgt_block(tvb, pinfo, inst_tree, offset, is_request, is_write, data_type);

        /* Safety check to prevent infinite loops */
        if (offset >= tvb_captured_length(tvb)) {
            break;
        }
    }

    return offset;
}

/* Main XGT dissector */
static int
dissect_xgt(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
    proto_item *ti;
    proto_tree *xgt_tree;
    guint offset = 0;
    guint8 company_id[9];

    /* Check minimum packet length */
    if (tvb_captured_length(tvb) < XGT_HEADER_LEN) {
        return 0;
    }

    /* Verify Company ID */
    tvb_memcpy(tvb, company_id, 0, 8);
    company_id[8] = '\0';
    if (strncmp((char*)company_id, XGT_COMPANY_ID, 8) != 0) {
        return 0;
    }

    /* Set protocol column */
    col_set_str(pinfo->cinfo, COL_PROTOCOL, "XGT");
    col_clear(pinfo->cinfo, COL_INFO);

    /* Create protocol tree */
    ti = proto_tree_add_item(tree, proto_xgt, tvb, 0, -1, ENC_NA);
    xgt_tree = proto_item_add_subtree(ti, ett_xgt);

    /* Dissect header */
    offset = dissect_xgt_header(tvb, pinfo, xgt_tree, offset);

    /* Dissect instruction if present */
    if (tvb_reported_length_remaining(tvb, offset) > 0) {
        offset = dissect_xgt_instruction(tvb, pinfo, xgt_tree, offset);
    }

    return tvb_captured_length(tvb);
}

/* Register protocol */
void
proto_register_xgt(void)
{
    static hf_register_info hf[] = {
        /* Header fields */
        { &hf_xgt_company_id,
          { "Company ID", "xgt.company_id",
            FT_STRING, BASE_NONE, NULL, 0x0,
            "Company identification string", HFILL }
        },
        { &hf_xgt_reserved1,
          { "Reserved", "xgt.reserved1",
            FT_UINT16, BASE_HEX, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_xgt_plc_info,
          { "PLC Info", "xgt.plc_info",
            FT_UINT16, BASE_HEX, NULL, 0x0,
            "PLC information field", HFILL }
        },
        { &hf_xgt_plc_info_cpu_type,
          { "CPU Type", "xgt.plc_info.cpu_type",
            FT_UINT16, BASE_DEC, VALS(xgt_cpu_type_vals), 0x003F,
            NULL, HFILL }
        },
        { &hf_xgt_plc_info_redundancy,
          { "Redundancy", "xgt.plc_info.redundancy",
            FT_BOOLEAN, 16, TFS(&tfs_slave_master), 0x0040,
            "Redundancy status", HFILL }
        },
        { &hf_xgt_plc_info_cpu_error,
          { "CPU Error", "xgt.plc_info.cpu_error",
            FT_BOOLEAN, 16, TFS(&tfs_error_normal), 0x0080,
            "CPU operation error status", HFILL }
        },
        { &hf_xgt_plc_info_sys_state,
          { "System State", "xgt.plc_info.sys_state",
            FT_UINT16, BASE_HEX, VALS(xgt_sys_state_vals), 0x1F00,
            NULL, HFILL }
        },
        { &hf_xgt_cpu_info,
          { "CPU Info", "xgt.cpu_info",
            FT_UINT8, BASE_HEX, VALS(xgt_cpu_info_vals), 0x0,
            NULL, HFILL }
        },
        { &hf_xgt_source,
          { "Source", "xgt.source",
            FT_UINT8, BASE_HEX, VALS(xgt_source_vals), 0x0,
            "Source of frame", HFILL }
        },
        { &hf_xgt_invoke_id,
          { "Invoke ID", "xgt.invoke_id",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Frame sequence identifier", HFILL }
        },
        { &hf_xgt_length,
          { "Length", "xgt.length",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Application instruction length", HFILL }
        },
        { &hf_xgt_fenet_position,
          { "FEnet Position", "xgt.fenet_position",
            FT_UINT8, BASE_HEX, NULL, 0x0,
            "FEnet module position", HFILL }
        },
        { &hf_xgt_fenet_slot,
          { "Slot", "xgt.fenet_position.slot",
            FT_UINT8, BASE_DEC, NULL, 0x0F,
            "FEnet module slot number", HFILL }
        },
        { &hf_xgt_fenet_base,
          { "Base", "xgt.fenet_position.base",
            FT_UINT8, BASE_DEC, NULL, 0xF0,
            "FEnet module base number", HFILL }
        },
        { &hf_xgt_reserved2,
          { "Reserved/BCC", "xgt.reserved2",
            FT_UINT8, BASE_HEX, NULL, 0x0,
            NULL, HFILL }
        },

        /* Instruction fields */
        { &hf_xgt_command,
          { "Command", "xgt.command",
            FT_UINT16, BASE_HEX, VALS(xgt_command_vals), 0x0,
            "Command code", HFILL }
        },
        { &hf_xgt_data_type,
          { "Data Type", "xgt.data_type",
            FT_UINT16, BASE_HEX, VALS(xgt_data_type_vals), 0x0,
            NULL, HFILL }
        },
        { &hf_xgt_reserved_area,
          { "Reserved", "xgt.reserved_area",
            FT_UINT16, BASE_HEX, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_xgt_error_status,
          { "Error Status", "xgt.error_status",
            FT_UINT16, BASE_HEX, VALS(xgt_error_status_vals), 0x0,
            NULL, HFILL }
        },
        { &hf_xgt_error_code,
          { "Error Code", "xgt.error_code",
            FT_UINT16, BASE_HEX, VALS(xgt_error_code_vals), 0x0,
            "XGT protocol error code", HFILL }
        },
        { &hf_xgt_block_count,
          { "Block Count", "xgt.block_count",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_xgt_variable_count,
          { "Variable Count", "xgt.variable_count",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_xgt_variable_length,
          { "Variable Length", "xgt.variable_length",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Length of variable name", HFILL }
        },
        { &hf_xgt_variable_name,
          { "Variable Name", "xgt.variable_name",
            FT_STRING, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_xgt_data_length,
          { "Data Length", "xgt.data_length",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Length of data in bytes", HFILL }
        },
        { &hf_xgt_data,
          { "Data", "xgt.data",
            FT_BYTES, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },

        /* Status fields */
        { &hf_xgt_status_data,
          { "Status Data", "xgt.status_data",
            FT_BYTES, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_xgt_slot_info,
          { "Slot Info", "xgt.status.slot_info",
            FT_UINT32, BASE_HEX, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_xgt_cpu_type,
          { "CPU Type", "xgt.status.cpu_type",
            FT_UINT16, BASE_HEX, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_xgt_ver_num,
          { "Version Number", "xgt.status.ver_num",
            FT_UINT16, BASE_HEX, NULL, 0x0,
            "OS version number", HFILL }
        },
        { &hf_xgt_sys_state,
          { "System State", "xgt.status.sys_state",
            FT_UINT32, BASE_HEX, NULL, 0x0,
            "PLC mode and operation state", HFILL }
        },
        { &hf_xgt_padt_cnf,
          { "PADT Connection", "xgt.status.padt_cnf",
            FT_UINT16, BASE_HEX, NULL, 0x0,
            "XG5000 connection status", HFILL }
        },
        { &hf_xgt_cnf_er,
          { "Error Flags", "xgt.status.cnf_er",
            FT_UINT32, BASE_HEX, NULL, 0x0,
            "System error flags", HFILL }
        },
        { &hf_xgt_cnf_war,
          { "Warning Flags", "xgt.status.cnf_war",
            FT_UINT32, BASE_HEX, NULL, 0x0,
            "System warning flags", HFILL }
        },

        /* Data value fields */
        { &hf_xgt_data_value_uint8,
          { "Value (BYTE)", "xgt.data.value.uint8",
            FT_UINT8, BASE_DEC, NULL, 0x0,
            "Data value as 8-bit unsigned integer", HFILL }
        },
        { &hf_xgt_data_value_uint16,
          { "Value (WORD)", "xgt.data.value.uint16",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Data value as 16-bit unsigned integer", HFILL }
        },
        { &hf_xgt_data_value_uint32,
          { "Value (DWORD)", "xgt.data.value.uint32",
            FT_UINT32, BASE_DEC, NULL, 0x0,
            "Data value as 32-bit unsigned integer", HFILL }
        },
        { &hf_xgt_data_value_uint64,
          { "Value (LWORD)", "xgt.data.value.uint64",
            FT_UINT64, BASE_DEC, NULL, 0x0,
            "Data value as 64-bit unsigned integer", HFILL }
        }
    };

    static gint *ett[] = {
        &ett_xgt,
        &ett_xgt_header,
        &ett_xgt_instruction,
        &ett_xgt_plc_info,
        &ett_xgt_fenet_position,
        &ett_xgt_block,
        &ett_xgt_status
    };

    static ei_register_info ei[] = {
        { &ei_xgt_invalid_length,
          { "xgt.invalid_length", PI_MALFORMED, PI_ERROR,
            "Invalid length field", EXPFILL }
        },
        { &ei_xgt_error_response,
          { "xgt.error_response", PI_RESPONSE_CODE, PI_WARN,
            "XGT Error Response", EXPFILL }
        },
        { &ei_xgt_truncated_data,
          { "xgt.truncated_data", PI_MALFORMED, PI_ERROR,
            "Truncated data (packet too short)", EXPFILL }
        },
        { &ei_xgt_invalid_command,
          { "xgt.invalid_command", PI_MALFORMED, PI_WARN,
            "Unknown or invalid command code", EXPFILL }
        },
        { &ei_xgt_cpu_error,
          { "xgt.cpu_error", PI_RESPONSE_CODE, PI_WARN,
            "CPU Error detected", EXPFILL }
        },
        { &ei_xgt_suspicious_count,
          { "xgt.suspicious_count", PI_MALFORMED, PI_WARN,
            "Suspicious count value", EXPFILL }
        }
    };

    expert_module_t *expert_xgt;

    /* Register protocol */
    proto_xgt = proto_register_protocol(
        "XGT Protocol",    /* name */
        "XGT",             /* short name */
        "xgt"              /* filter name */
    );

    proto_register_field_array(proto_xgt, hf, array_length(hf));
    proto_register_subtree_array(ett, array_length(ett));

    /* Register expert info */
    expert_xgt = expert_register_protocol(proto_xgt);
    expert_register_field_array(expert_xgt, ei, array_length(ei));
}

void
proto_reg_handoff_xgt(void)
{
    static dissector_handle_t xgt_handle;

    xgt_handle = create_dissector_handle(dissect_xgt, proto_xgt);
    dissector_add_uint("tcp.port", XGT_TCP_PORT, xgt_handle);
    dissector_add_uint("udp.port", XGT_UDP_PORT, xgt_handle);
}