/**
 * Copyright 2020 Roman Ondráček <ondracek.roman@centrum.cz>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ble_gatts_srv.h"

///Declare the static function
static void gattsProfileDeviceInfoEventHandler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);
static void gattsProfileVoltageEventHandler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);
static void gattsProfileLightEventHandler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);

static uint8_t adv_config_done = 0;
#define adv_config_flag      (1 << 0)
#define scan_rsp_config_flag (1 << 1)

static uint8_t adv_service_uuid128[48] = {
        /* LSB <--------------------------------------------------------------------------------> MSB */
        0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0x18, 0x0A, 0x00, 0x00,
        0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0x18, 0x3B, 0x00, 0x00,
        0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0x18, 0x1C, 0x00, 0x00,
};

//adv data
static esp_ble_adv_data_t adv_data = {
        .set_scan_rsp = false,
        .include_name = true,
        .include_txpower = false,
        .min_interval = 0x0006, //slave connection min interval, Time = min_interval * 1.25 msec
        .max_interval = 0x0010, //slave connection max interval, Time = max_interval * 1.25 msec
        .appearance = 0x00,
        .manufacturer_len = 0,
        .p_manufacturer_data = NULL,
        .service_data_len = 0,
        .p_service_data = NULL,
        .service_uuid_len = sizeof(adv_service_uuid128),
        .p_service_uuid = adv_service_uuid128,
        .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};
// scan response data
static esp_ble_adv_data_t scan_rsp_data = {
        .set_scan_rsp = true,
        .include_name = true,
        .include_txpower = true,
        //.min_interval = 0x0006,
        //.max_interval = 0x0010,
        .appearance = 0x00,
        .manufacturer_len = 0,
        .p_manufacturer_data = NULL,
        .service_data_len = 0,
        .p_service_data = NULL,
        .service_uuid_len = sizeof(adv_service_uuid128),
        .p_service_uuid = adv_service_uuid128,
        .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

static esp_ble_adv_params_t adv_params = {
        .adv_int_min        = 0x20,
        .adv_int_max        = 0x40,
        .adv_type           = ADV_TYPE_IND,
        .own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
        //.peer_addr            =
        //.peer_addr_type       =
        .channel_map        = ADV_CHNL_ALL,
        .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

#define PROFILE_NUM                 3
#define PROFILE_DEVICE_INFO_APP_ID  0
#define PROFILE_SENSOR_APP_ID       1
#define PROFILE_LIGHT_APP_ID        2

struct gatts_profile_inst {
    esp_gatts_cb_t gatts_cb;
    uint16_t gatts_if;
    uint16_t app_id;
    uint16_t conn_id;
    uint16_t service_handle;
    esp_gatt_srvc_id_t service_id;
    uint16_t char_handle;
    esp_bt_uuid_t* char_uuid;
    esp_gatt_perm_t perm;
    esp_gatt_char_prop_t property;
    uint16_t descr_handle;
    esp_bt_uuid_t descr_uuid;
};

/* One gatt-based profile one app_id and one gatts_if, this array will store the gatts_if returned by ESP_GATTS_REG_EVT */
static struct gatts_profile_inst gl_profile_tab[PROFILE_NUM] = {
        [PROFILE_DEVICE_INFO_APP_ID] = {
                .gatts_cb = gattsProfileDeviceInfoEventHandler,
                .gatts_if = ESP_GATT_IF_NONE,
        },
        [PROFILE_SENSOR_APP_ID] = {
                .gatts_cb = gattsProfileVoltageEventHandler,
                .gatts_if = ESP_GATT_IF_NONE,
        },
        [PROFILE_LIGHT_APP_ID] = {
                .gatts_cb = gattsProfileLightEventHandler,
                .gatts_if = ESP_GATT_IF_NONE,
        },
};

static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
    switch (event) {
        case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
            adv_config_done &= (~adv_config_flag);
            if (adv_config_done == 0) {
                ESP_ERROR_CHECK(esp_ble_gap_start_advertising(&adv_params));
            }
            break;
        case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
            adv_config_done &= (~scan_rsp_config_flag);
            if (adv_config_done == 0) {
                ESP_ERROR_CHECK(esp_ble_gap_start_advertising(&adv_params));
            }
            break;
        case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
            //advertising start complete event to indicate advertising start successfully or failed
            if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
                ESP_LOGE(GATTS_TAG, "Advertising start failed\n");
            }
            break;
        case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
            if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
                ESP_LOGE(GATTS_TAG, "Advertising stop failed\n");
            } else {
                ESP_LOGI(GATTS_TAG, "Stop adv successfully\n");
            }
            break;
        case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
            ESP_LOGI(GATTS_TAG, "update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
                     param->update_conn_params.status, param->update_conn_params.min_int, param->update_conn_params.max_int,
                     param->update_conn_params.conn_int, param->update_conn_params.latency, param->update_conn_params.timeout);
            break;
        default:
            break;
    }
}

static void gattsProfileDeviceInfoEventHandler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
    switch (event) {
        case ESP_GATTS_REG_EVT:
            ESP_LOGI(GATTS_TAG, "REGISTER_APP_EVT, status %d, app_id %d\n", param->reg.status, param->reg.app_id);
            gl_profile_tab[PROFILE_DEVICE_INFO_APP_ID].service_id.is_primary = true;
            gl_profile_tab[PROFILE_DEVICE_INFO_APP_ID].service_id.id.inst_id = 0x00;
            gl_profile_tab[PROFILE_DEVICE_INFO_APP_ID].service_id.id.uuid.len = ESP_UUID_LEN_16;
            gl_profile_tab[PROFILE_DEVICE_INFO_APP_ID].service_id.id.uuid.uuid.uuid16 = GATTS_SERVICE_UUID_DEVICE_INFO;

            esp_err_t set_dev_name_ret = esp_ble_gap_set_device_name(DEVICE_NAME);
            if (set_dev_name_ret) {
                ESP_LOGE(GATTS_TAG, "set device name failed, error code = %x", set_dev_name_ret);
            }
            //config adv data
            esp_err_t ret = esp_ble_gap_config_adv_data(&adv_data);
            if (ret) {
                ESP_LOGE(GATTS_TAG, "config adv data failed, error code = %x", ret);
            }
            adv_config_done |= adv_config_flag;
            //config scan response data
            ret = esp_ble_gap_config_adv_data(&scan_rsp_data);
            if (ret) {
                ESP_LOGE(GATTS_TAG, "config scan response data failed, error code = %x", ret);
            }
            adv_config_done |= scan_rsp_config_flag;
            ESP_ERROR_CHECK(esp_ble_gatts_create_service(gatts_if, &gl_profile_tab[PROFILE_DEVICE_INFO_APP_ID].service_id, GATTS_NUM_HANDLE_DEVICE_INFO));
            break;
        case ESP_GATTS_READ_EVT: {
            ESP_LOGI(GATTS_TAG, "GATT_READ_EVT, conn_id %d, trans_id %d, handle %d\n", param->read.conn_id, param->read.trans_id, param->read.handle);
            esp_gatt_rsp_t rsp;
            memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
            rsp.attr_value.handle = param->read.handle;
            char manufacturer[] = "Roman Ondracek";
            rsp.attr_value.len = strlen(manufacturer);
            strcpy((char *)rsp.attr_value.value, manufacturer);
            esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
            break;
        }
        case ESP_GATTS_MTU_EVT:
            ESP_LOGI(GATTS_TAG, "ESP_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
            break;
        case ESP_GATTS_CREATE_EVT:
            ESP_LOGI(GATTS_TAG, "CREATE_SERVICE_EVT, status %d,  service_handle %d\n", param->create.status, param->create.service_handle);
            gl_profile_tab[PROFILE_DEVICE_INFO_APP_ID].service_handle = param->create.service_handle;
            gl_profile_tab[PROFILE_DEVICE_INFO_APP_ID].char_uuid = (esp_bt_uuid_t *) malloc(sizeof(esp_bt_uuid_t));
            gl_profile_tab[PROFILE_DEVICE_INFO_APP_ID].char_uuid[0].len = ESP_UUID_LEN_16;
            gl_profile_tab[PROFILE_DEVICE_INFO_APP_ID].char_uuid[0].uuid.uuid16 = GATTS_CHAR_UUID_MANUFACTURER;

            esp_ble_gatts_start_service(gl_profile_tab[PROFILE_DEVICE_INFO_APP_ID].service_handle);
            esp_err_t add_char_ret = esp_ble_gatts_add_char(gl_profile_tab[PROFILE_DEVICE_INFO_APP_ID].service_handle,
                                                            &gl_profile_tab[PROFILE_DEVICE_INFO_APP_ID].char_uuid[0],
                                                            ESP_GATT_PERM_READ, ESP_GATT_CHAR_PROP_BIT_READ, NULL, NULL);
            if (add_char_ret) {
                ESP_LOGE(GATTS_TAG, "add char failed, error code =%x", add_char_ret);
            }
            break;
        case ESP_GATTS_START_EVT:
            ESP_LOGI(GATTS_TAG, "SERVICE_START_EVT, status %d, service_handle %d\n", param->start.status, param->start.service_handle);
            break;
        case ESP_GATTS_CONNECT_EVT: {
            ESP_LOGI(GATTS_TAG, "CONNECT_EVT, conn_id %d, remote %02x:%02x:%02x:%02x:%02x:%02x:", param->connect.conn_id,
                     param->connect.remote_bda[0], param->connect.remote_bda[1], param->connect.remote_bda[2],
                     param->connect.remote_bda[3], param->connect.remote_bda[4], param->connect.remote_bda[5]);
            gl_profile_tab[PROFILE_DEVICE_INFO_APP_ID].conn_id = param->connect.conn_id;
            ESP_ERROR_CHECK(esp_ble_gap_start_advertising(&adv_params));
            break;
        }
        case ESP_GATTS_DISCONNECT_EVT:
            ESP_LOGI(GATTS_TAG, "ESP_GATTS_DISCONNECT_EVT, disconnect reason 0x%x", param->disconnect.reason);
            esp_ble_gap_start_advertising(&adv_params);
            break;
        case ESP_GATTS_CONF_EVT:
            ESP_LOGI(GATTS_TAG, "ESP_GATTS_CONF_EVT status %d attr_handle %d", param->conf.status, param->conf.handle);
            if (param->conf.status != ESP_GATT_OK) {
                esp_log_buffer_hex(GATTS_TAG, param->conf.value, param->conf.len);
            }
            break;
        default:
            break;
    }
}

static void gattsProfileVoltageEventHandler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
    switch (event) {
        case ESP_GATTS_REG_EVT:
            ESP_LOGI(GATTS_TAG, "REGISTER_APP_EVT, status %d, app_id %d\n", param->reg.status, param->reg.app_id);
            gl_profile_tab[PROFILE_SENSOR_APP_ID].service_id.is_primary = true;
            gl_profile_tab[PROFILE_SENSOR_APP_ID].service_id.id.inst_id = 0x00;
            gl_profile_tab[PROFILE_SENSOR_APP_ID].service_id.id.uuid.len = ESP_UUID_LEN_16;
            gl_profile_tab[PROFILE_SENSOR_APP_ID].service_id.id.uuid.uuid.uuid16 = GATTS_SERVICE_UUID_SENSOR;

            ESP_ERROR_CHECK(esp_ble_gatts_create_service(gatts_if, &gl_profile_tab[PROFILE_SENSOR_APP_ID].service_id, GATTS_NUM_HANDLE_SENSOR));
            break;
        case ESP_GATTS_READ_EVT: {
            ESP_LOGI(GATTS_TAG, "GATT_READ_EVT, conn_id %d, trans_id %d, handle %d\n", param->read.conn_id, param->read.trans_id, param->read.handle);
            esp_gatt_rsp_t rsp;
            memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
            rsp.attr_value.handle = param->read.handle;
            rsp.attr_value.len = 2;
            switch (param->read.handle) {
                case 46: {
                    uint16_t voltage = adcReadVoltage();
                    rsp.attr_value.value[0] = (voltage >> 8) & 0xff;
                    rsp.attr_value.value[1] = voltage & 0xff;
                    break;
                }
                case 48: {
                    uint16_t voltage = ina219ReadBusVoltage();
                    rsp.attr_value.value[0] = (voltage >> 8) & 0xff;
                    rsp.attr_value.value[1] = voltage & 0xff;
                    break;
                }
                case 50: {
                    int16_t current = ina219ReadCurrent();
                    rsp.attr_value.value[0] = (current >> 8) & 0xff;
                    rsp.attr_value.value[1] = current & 0xff;
                    break;
                }
            }
            esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
            break;
        }
        case ESP_GATTS_MTU_EVT:
            ESP_LOGI(GATTS_TAG, "ESP_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
            break;
        case ESP_GATTS_CREATE_EVT:
            ESP_LOGI(GATTS_TAG, "CREATE_SERVICE_EVT, status %d,  service_handle %d\n", param->create.status, param->create.service_handle);
            gl_profile_tab[PROFILE_SENSOR_APP_ID].service_handle = param->create.service_handle;
            gl_profile_tab[PROFILE_SENSOR_APP_ID].char_uuid = (esp_bt_uuid_t *) malloc(3 * sizeof(esp_bt_uuid_t));
            gl_profile_tab[PROFILE_SENSOR_APP_ID].char_uuid[0].len = ESP_UUID_LEN_16;
            gl_profile_tab[PROFILE_SENSOR_APP_ID].char_uuid[0].uuid.uuid16 = GATTS_CHAR_UUID_VOLTAGE;
            gl_profile_tab[PROFILE_SENSOR_APP_ID].char_uuid[1].len = ESP_UUID_LEN_16;
            gl_profile_tab[PROFILE_SENSOR_APP_ID].char_uuid[1].uuid.uuid16 = GATTS_CHAR_UUID_VOLTAGE;
            gl_profile_tab[PROFILE_SENSOR_APP_ID].char_uuid[2].len = ESP_UUID_LEN_16;
            gl_profile_tab[PROFILE_SENSOR_APP_ID].char_uuid[2].uuid.uuid16 = GATTS_CHAR_UUID_CURRENT;

            esp_ble_gatts_start_service(gl_profile_tab[PROFILE_SENSOR_APP_ID].service_handle);
            esp_err_t add_char_ret = esp_ble_gatts_add_char(gl_profile_tab[PROFILE_SENSOR_APP_ID].service_handle,
                                                            &gl_profile_tab[PROFILE_SENSOR_APP_ID].char_uuid[0],
                                                            ESP_GATT_PERM_READ, ESP_GATT_CHAR_PROP_BIT_READ, NULL, NULL);
            if (add_char_ret) {
                ESP_LOGE(GATTS_TAG, "add char failed, error code =%x", add_char_ret);
            }
            add_char_ret = esp_ble_gatts_add_char(gl_profile_tab[PROFILE_SENSOR_APP_ID].service_handle,
                                                  &gl_profile_tab[PROFILE_SENSOR_APP_ID].char_uuid[1],
                                                  ESP_GATT_PERM_READ, ESP_GATT_CHAR_PROP_BIT_READ, NULL, NULL);
            if (add_char_ret) {
                ESP_LOGE(GATTS_TAG, "add char failed, error code =%x", add_char_ret);
            }
            add_char_ret = esp_ble_gatts_add_char(gl_profile_tab[PROFILE_SENSOR_APP_ID].service_handle,
                                                  &gl_profile_tab[PROFILE_SENSOR_APP_ID].char_uuid[2],
                                                  ESP_GATT_PERM_READ, ESP_GATT_CHAR_PROP_BIT_READ, NULL, NULL);
            if (add_char_ret) {
                ESP_LOGE(GATTS_TAG, "add char failed, error code =%x", add_char_ret);
            }
            break;
        case ESP_GATTS_START_EVT:
            ESP_LOGI(GATTS_TAG, "SERVICE_START_EVT, status %d, service_handle %d\n", param->start.status, param->start.service_handle);
            break;
        case ESP_GATTS_CONNECT_EVT:
            ESP_LOGI(GATTS_TAG, "CONNECT_EVT, conn_id %d, remote %02x:%02x:%02x:%02x:%02x:%02x:", param->connect.conn_id,
                     param->connect.remote_bda[0], param->connect.remote_bda[1], param->connect.remote_bda[2],
                     param->connect.remote_bda[3], param->connect.remote_bda[4], param->connect.remote_bda[5]);
            gl_profile_tab[PROFILE_SENSOR_APP_ID].conn_id = param->connect.conn_id;
            break;
        case ESP_GATTS_CONF_EVT:
            ESP_LOGI(GATTS_TAG, "ESP_GATTS_CONF_EVT status %d attr_handle %d", param->conf.status, param->conf.handle);
            if (param->conf.status != ESP_GATT_OK) {
                esp_log_buffer_hex(GATTS_TAG, param->conf.value, param->conf.len);
            }
            break;
        default:
            break;
    }
}

static void gattsProfileLightEventHandler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
    switch (event) {
        case ESP_GATTS_REG_EVT:
            ESP_LOGI(GATTS_TAG, "REGISTER_APP_EVT, status %d, app_id %d\n", param->reg.status, param->reg.app_id);
            gl_profile_tab[PROFILE_LIGHT_APP_ID].service_id.is_primary = true;
            gl_profile_tab[PROFILE_LIGHT_APP_ID].service_id.id.inst_id = 0x00;
            gl_profile_tab[PROFILE_LIGHT_APP_ID].service_id.id.uuid.len = ESP_UUID_LEN_16;
            gl_profile_tab[PROFILE_LIGHT_APP_ID].service_id.id.uuid.uuid.uuid16 = GATTS_SERVICE_UUID_LIGHT_DATA;

            ESP_ERROR_CHECK(esp_ble_gatts_create_service(gatts_if, &gl_profile_tab[PROFILE_LIGHT_APP_ID].service_id, GATTS_NUM_HANDLE_LIGHT_DATA));
            break;
        case ESP_GATTS_READ_EVT: {
            ESP_LOGI(GATTS_TAG, "GATT_READ_EVT, conn_id %d, trans_id %d, handle %d\n", param->read.conn_id, param->read.trans_id, param->read.handle);
            esp_gatt_rsp_t rsp;
            memset(&rsp, 0, sizeof(esp_gatt_rsp_t));
            rsp.attr_value.handle = param->read.handle;
            rsp.attr_value.len = LED_CHANNELS;
            for (uint8_t channel = 0; channel < LED_CHANNELS; channel++) {
                uint8_t dutyCycle = ledcGetDutyCycle(channel) / 10;
                rsp.attr_value.value[channel] = dutyCycle;
            }
            esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id, ESP_GATT_OK, &rsp);
            break;
        }
        case ESP_GATTS_WRITE_EVT: {
            ESP_LOGI(GATTS_TAG, "GATT_WRITE_EVT, conn_id %d, trans_id %d, handle %d\n", param->write.conn_id, param->write.trans_id, param->write.handle);
            if (!param->write.is_prep){
                ESP_LOGI(GATTS_TAG, "GATT_WRITE_EVT, value len %d, value:", param->write.len);
                esp_log_buffer_hex(GATTS_TAG, param->write.value, param->write.len);
                for (uint8_t channel = 0; channel < LED_CHANNELS; channel++) {
                    uint8_t dutyCycle = channel < param->write.len ? param->write.value[channel] : 0xff;
                    if (dutyCycle > 100) {
                        continue;
                    }
                    ledcSetDutyCycle(channel, dutyCycle * 10);
                }
            }
            esp_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, ESP_GATT_OK, NULL);
            break;
        }
        case ESP_GATTS_EXEC_WRITE_EVT:
            ESP_LOGI(GATTS_TAG,"ESP_GATTS_EXEC_WRITE_EVT");
            esp_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, ESP_GATT_OK, NULL);
            break;
        case ESP_GATTS_MTU_EVT:
            ESP_LOGI(GATTS_TAG, "ESP_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
            break;
        case ESP_GATTS_CREATE_EVT:
            ESP_LOGI(GATTS_TAG, "CREATE_SERVICE_EVT, status %d,  service_handle %d\n", param->create.status, param->create.service_handle);
            gl_profile_tab[PROFILE_LIGHT_APP_ID].service_handle = param->create.service_handle;
            gl_profile_tab[PROFILE_LIGHT_APP_ID].char_uuid = (esp_bt_uuid_t *) malloc(sizeof(esp_bt_uuid_t));
            gl_profile_tab[PROFILE_LIGHT_APP_ID].char_uuid[0].len = ESP_UUID_LEN_16;
            gl_profile_tab[PROFILE_LIGHT_APP_ID].char_uuid[0].uuid.uuid16 = GATTS_CHAR_UUID_LIGHT_INTENSITY;

            esp_ble_gatts_start_service(gl_profile_tab[PROFILE_LIGHT_APP_ID].service_handle);
            esp_err_t add_char_ret = esp_ble_gatts_add_char(gl_profile_tab[PROFILE_LIGHT_APP_ID].service_handle,
                                                            &gl_profile_tab[PROFILE_LIGHT_APP_ID].char_uuid[0],
                                                            ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
                                                            ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE, NULL, NULL);
            if (add_char_ret) {
                ESP_LOGE(GATTS_TAG, "add char failed, error code =%x", add_char_ret);
            }
            break;
        case ESP_GATTS_START_EVT:
            ESP_LOGI(GATTS_TAG, "SERVICE_START_EVT, status %d, service_handle %d\n", param->start.status, param->start.service_handle);
            break;
        case ESP_GATTS_CONNECT_EVT:
            ESP_LOGI(GATTS_TAG, "CONNECT_EVT, conn_id %d, remote %02x:%02x:%02x:%02x:%02x:%02x:", param->connect.conn_id,
                     param->connect.remote_bda[0], param->connect.remote_bda[1], param->connect.remote_bda[2],
                     param->connect.remote_bda[3], param->connect.remote_bda[4], param->connect.remote_bda[5]);
            gl_profile_tab[PROFILE_LIGHT_APP_ID].conn_id = param->connect.conn_id;
            break;
        case ESP_GATTS_CONF_EVT:
            ESP_LOGI(GATTS_TAG, "ESP_GATTS_CONF_EVT status %d attr_handle %d", param->conf.status, param->conf.handle);
            if (param->conf.status != ESP_GATT_OK) {
                esp_log_buffer_hex(GATTS_TAG, param->conf.value, param->conf.len);
            }
            break;
        default:
            break;
    }
}

static void gattsEventHandler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
    /* If event is register event, store the gatts_if for each profile */
    if (event == ESP_GATTS_REG_EVT) {
        if (param->reg.status == ESP_GATT_OK) {
            gl_profile_tab[param->reg.app_id].gatts_if = gatts_if;
        } else {
            ESP_LOGI(GATTS_TAG, "Reg app failed, app_id %04x, status %d\n", param->reg.app_id, param->reg.status);
            return;
        }
    }

    /* If the gatts_if equal to profile A, call profile A cb handler,
     * so here call each profile's callback */
    do {
        for (unsigned idx = 0; idx < PROFILE_NUM; idx++) {
            /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
            if (gatts_if == ESP_GATT_IF_NONE || gatts_if == gl_profile_tab[idx].gatts_if) {
                if (gl_profile_tab[idx].gatts_cb) {
                    gl_profile_tab[idx].gatts_cb(event, gatts_if, param);
                }
            }
        }
    } while (0);
}

void gatts_register(void) {
    int ret = esp_ble_gatts_register_callback(gattsEventHandler);
    if (ret) {
        ESP_LOGE(GATTS_TAG, "gatts register error, error code = %x", ret);
        return;
    }
    ret = esp_ble_gap_register_callback(gap_event_handler);
    if (ret) {
        ESP_LOGE(GATTS_TAG, "gap register error, error code = %x", ret);
        return;
    }
    ret = esp_ble_gatts_app_register(PROFILE_DEVICE_INFO_APP_ID);
    if (ret) {
        ESP_LOGE(GATTS_TAG, "Device info GATTS app register error, error code = %x", ret);
        return;
    }
    ret = esp_ble_gatts_app_register(PROFILE_SENSOR_APP_ID);
    if (ret) {
        ESP_LOGE(GATTS_TAG, "Sensors GATTS app register error, error code = %x", ret);
        return;
    }
    ret = esp_ble_gatts_app_register(PROFILE_LIGHT_APP_ID);
    if (ret) {
        ESP_LOGE(GATTS_TAG, "Lights GATTS app register error, error code = %x", ret);
        return;
    }
}
