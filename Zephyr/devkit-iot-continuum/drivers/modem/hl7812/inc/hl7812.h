/** @file
 * @brief HL7812 modem public API header file.
 *
 * Allows an application to control the HL7812 modem.
 *
 * Copyright (c) 2020 Laird Connectivity
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_MODEM_HL7812_H_
#define ZEPHYR_INCLUDE_DRIVERS_MODEM_HL7812_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/types.h>
#include <zephyr/net/net_if.h>
#include <time.h>

/* The size includes the NUL character, the strlen doesn't */
#define MDM_HL7812_REVISION_MAX_SIZE       29
#define MDM_HL7812_REVISION_MAX_STRLEN     (MDM_HL7812_REVISION_MAX_SIZE - 1)

#define MDM_HL7812_IMEI_SIZE               16
#define MDM_HL7812_IMEI_STRLEN             (MDM_HL7812_IMEI_SIZE - 1)

#define MDM_HL7812_ICCID_SIZE              21
#define MDM_HL7812_ICCID_STRLEN            (MDM_HL7812_ICCID_SIZE - 1)

#define MDM_HL7812_SERIAL_NUMBER_SIZE      15
#define MDM_HL7812_SERIAL_NUMBER_STRLEN    (MDM_HL7812_SERIAL_NUMBER_SIZE - 1)

#define MDM_HL7812_APN_MAX_SIZE            64
#define MDM_HL7812_APN_USERNAME_MAX_SIZE   65
#define MDM_HL7812_APN_PASSWORD_MAX_SIZE   65

#define MDM_HL7812_APN_MAX_STRLEN          (MDM_HL7812_APN_MAX_SIZE - 1)
#define MDM_HL7812_APN_USERNAME_MAX_STRLEN (MDM_HL7812_APN_USERNAME_MAX_SIZE - 1)
#define MDM_HL7812_APN_PASSWORD_MAX_STRLEN (MDM_HL7812_APN_PASSWORD_MAX_SIZE - 1)

#define MDM_HL7812_APN_CMD_MAX_SIZE \
   (32 + MDM_HL7812_APN_USERNAME_MAX_STRLEN + MDM_HL7812_APN_PASSWORD_MAX_STRLEN)

#define MDM_HL7812_APN_CMD_MAX_STRLEN (MDM_HL7812_APN_CMD_MAX_SIZE - 1)

struct mdm_hl7812_apn
{
   char value[MDM_HL7812_APN_MAX_SIZE];
   char username[MDM_HL7812_APN_USERNAME_MAX_SIZE];
   char password[MDM_HL7812_APN_PASSWORD_MAX_SIZE];
};

#define MDM_HL7812_LTE_BAND_STR_SIZE                   21
#define MDM_HL7812_LTE_BAND_STRLEN                     (MDM_HL7812_LTE_BAND_STR_SIZE - 1)

#define MDM_HL7812_OPERATOR_INDEX_SIZE                 3
#define MDM_HL7812_OPERATOR_INDEX_STRLEN               (MDM_HL7812_OPERATOR_INDEX_SIZE - 1)

#define MDM_HL7812_IMSI_MIN_STR_SIZE                   15
#define MDM_HL7812_IMSI_MAX_STR_SIZE                   16
#define MDM_HL7812_IMSI_MAX_STRLEN                     (MDM_HL7812_IMSI_MAX_STR_SIZE - 1)

#define MDM_HL7812_MODEM_FUNCTIONALITY_SIZE            2
#define MDM_HL7812_MODEM_FUNCTIONALITY_STRLEN          (MDM_HL7812_MODEM_FUNCTIONALITY_SIZE - 1)

#define MDM_HL7812_MAX_GPS_STR_SIZE                    33

#define MDM_HL7812_MAX_POLTE_USER_ID_SIZE              16
#define MDM_HL7812_MAX_POLTE_PASSWORD_SIZE             16
#define MDM_HL7812_MAX_POLTE_LOCATION_STR_SIZE         33

#define MDM_HL7812_MAX_URL_DOMAIN_SIZE                 64
#define MDM_HL7812_MAX_URL_PATH_SIZE                   64

/* Assign the server error code (location response) to a value
 * that isn't used by locate response so that a single status
 * callback can be used.
 */
#define MDM_HL7812_POLTE_SERVER_ERROR                  10

#define MDM_HL7812_SET_POLTE_USER_AND_PASSWORD_FMT_STR "AT%%POLTECMD=\"SERVERAUTH\",\"%s\",\"%s\""

struct mdm_hl7812_site_survey
{
   uint32_t earfcn; /* EUTRA Absolute Radio Frequency Channel Number */
   uint32_t cell_id;
   int      rsrp;
   int      rsrq;
};

enum mdm_hl7812_radio_mode
{
   MDM_RAT_CAT_M1 = 0,
   MDM_RAT_CAT_NB1
};

enum mdm_hl7812_event
{
   HL7812_EVENT_RESERVED = 0,
   HL7812_EVENT_NETWORK_STATE_CHANGE,
   HL7812_EVENT_APN_UPDATE,
   HL7812_EVENT_RSSI,
   HL7812_EVENT_SINR,
   HL7812_EVENT_STARTUP_STATE_CHANGE,
   HL7812_EVENT_SLEEP_STATE_CHANGE,
   HL7812_EVENT_RAT,
   HL7812_EVENT_BANDS,
   HL7812_EVENT_ACTIVE_BANDS,
   HL7812_EVENT_FOTA_STATE,
   HL7812_EVENT_FOTA_COUNT,
   HL7812_EVENT_REVISION,
   HL7812_EVENT_GPS,
   HL7812_EVENT_GPS_POSITION_STATUS,
   HL7812_EVENT_POLTE_REGISTRATION,
   HL7812_EVENT_POLTE_LOCATE_STATUS,
   HL7812_EVENT_POLTE,
   HL7812_EVENT_SITE_SURVEY,
};

enum mdm_hl7812_startup_state
{
   HL7812_STARTUP_STATE_READY = 0,
   HL7812_STARTUP_STATE_WAITING_FOR_ACCESS_CODE,
   HL7812_STARTUP_STATE_SIM_NOT_PRESENT,
   HL7812_STARTUP_STATE_SIMLOCK,
   HL7812_STARTUP_STATE_UNRECOVERABLE_ERROR,
   HL7812_STARTUP_STATE_UNKNOWN,
   HL7812_STARTUP_STATE_INACTIVE_SIM
};

enum mdm_hl7812_network_state
{
   HL7812_NOT_REGISTERED = 0,
   HL7812_HOME_NETWORK,
   HL7812_SEARCHING,
   HL7812_REGISTRATION_DENIED,
   HL7812_OUT_OF_COVERAGE,
   HL7812_ROAMING,
   HL7812_EMERGENCY           = 8,
   /* Laird defined states */
   HL7812_UNABLE_TO_CONFIGURE = 0xf0
};

enum mdm_hl7812_sleep
{
   HL7812_SLEEP_UNINITIALIZED = 0,
   HL7812_SLEEP_HIBERNATE,
   HL7812_SLEEP_AWAKE,
   HL7812_SLEEP_LITE_HIBERNATE,
   HL7812_SLEEP_SLEEP,
};

enum mdm_hl7812_fota_state
{
   HL7812_FOTA_IDLE,
   HL7812_FOTA_START,
   HL7812_FOTA_WIP,
   HL7812_FOTA_PAD,
   HL7812_FOTA_SEND_EOT,
   HL7812_FOTA_FILE_ERROR,
   HL7812_FOTA_INSTALL,
   HL7812_FOTA_REBOOT_AND_RECONFIGURE,
   HL7812_FOTA_COMPLETE,
};

enum mdm_hl7812_functionality
{
   HL7812_FUNCTIONALITY_MINIMUM  = 0,
   HL7812_FUNCTIONALITY_FULL     = 1,
   HL7812_FUNCTIONALITY_AIRPLANE = 4
};

/* The modem reports state values as an enumeration and a string.
 * GPS values are reported with a type of value and string.
 */
struct mdm_hl7812_compound_event
{
   uint8_t code;
   char   *string;
};

enum mdm_hl7812_gnss_event
{
   HL7812_GNSS_EVENT_INVALID = -1,
   HL7812_GNSS_EVENT_INIT,
   HL7812_GNSS_EVENT_START,
   HL7812_GNSS_EVENT_STOP,
   HL7812_GNSS_EVENT_POSITION,
};

enum mdm_hl7812_gnss_status
{
   HL7812_GNSS_STATUS_INVALID = -1,
   HL7812_GNSS_STATUS_FAILURE,
   HL7812_GNSS_STATUS_SUCCESS,
};

enum mdm_hl7812_gnss_position_event
{
   HL7812_GNSS_POSITION_EVENT_INVALID = -1,
   HL7812_GNSS_POSITION_EVENT_LOST_OR_NOT_AVAILABLE_YET,
   HL7812_GNSS_POSITION_EVENT_PREDICTION_AVAILABLE,
   HL7812_GNSS_POSITION_EVENT_2D_AVAILABLE,
   HL7812_GNSS_POSITION_EVENT_3D_AVAILABLE,
   HL7812_GNSS_POSITION_EVENT_FIXED_TO_INVALID,
};

enum mdm_hl7812_gps_string_types
{
   HL7812_GPS_STR_LATITUDE,
   HL7812_GPS_STR_LONGITUDE,
   HL7812_GPS_STR_GPS_TIME,
   HL7812_GPS_STR_FIX_TYPE,
   HL7812_GPS_STR_HEPE,
   HL7812_GPS_STR_ALTITUDE,
   HL7812_GPS_STR_ALT_UNC,
   HL7812_GPS_STR_DIRECTION,
   HL7812_GPS_STR_HOR_SPEED,
   HL7812_GPS_STR_VER_SPEED
};

/* status: negative errno, 0 on success
 * user and password aren't valid if status is non-zero.
 */
struct mdm_hl7812_polte_registration_event_data
{
   int   status;
   char *user;
   char *password;
};

/* status: negative errno, 0 on success, non-zero error code
 * Data is not valid if status is non-zero.
 */
struct mdm_hl7812_polte_location_data
{
   uint32_t timestamp;
   int      status;
   char     latitude[MDM_HL7812_MAX_POLTE_LOCATION_STR_SIZE];
   char     longitude[MDM_HL7812_MAX_POLTE_LOCATION_STR_SIZE];
   char     confidence_in_meters[MDM_HL7812_MAX_POLTE_LOCATION_STR_SIZE];
};

/**
 * event - The type of event
 * event_data - Pointer to event specific data structure
 * HL7812_EVENT_NETWORK_STATE_CHANGE - compound event
 * HL7812_EVENT_APN_UPDATE - struct mdm_hl7812_apn
 * HL7812_EVENT_RSSI - int
 * HL7812_EVENT_SINR - int
 * HL7812_EVENT_STARTUP_STATE_CHANGE - compound event
 * HL7812_EVENT_SLEEP_STATE_CHANGE - compound event
 * HL7812_EVENT_RAT - int
 * HL7812_EVENT_BANDS - string
 * HL7812_EVENT_ACTIVE_BANDS - string
 * HL7812_EVENT_FOTA_STATE - compound event
 * HL7812_EVENT_FOTA_COUNT - uint32_t
 * HL7812_EVENT_REVISION - string
 * HL7812_EVENT_GPS - compound event
 * HL7812_EVENT_GPS_POSITION_STATUS int
 * HL7812_EVENT_POLTE_REGISTRATION mdm_hl7812_polte_registration_event_data
 * HL7812_EVENT_POLTE mdm_hl7812_polte_location_data
 * HL7812_EVENT_POLTE_LOCATE_STATUS int
 * HL7812_EVENT_SITE_SURVEY mdm_hl7812_site_survey
 */
typedef void (*mdm_hl7812_event_callback_t)(enum mdm_hl7812_event event, void *event_data);

struct mdm_hl7812_callback_agent
{
   sys_snode_t                 node;
   mdm_hl7812_event_callback_t event_callback;
};

/**
 * @brief Power off the HL7812
 *
 * @return int32_t 0 for success
 */
int32_t mdm_hl7812_power_off(void);

/**
 * @brief Reset the HL7812 (and allow it to reconfigure).
 *
 * @return int32_t 0 for success
 */
int32_t mdm_hl7812_reset(void);

/**
 * @brief Control the wake signals to the HL7812.
 * @note this API should only be used for debug purposes.
 *
 * @param awake True to keep the HL7812 awake, False to allow sleep
 */
void mdm_hl7812_wakeup(bool awake);

/**
 * @brief Send an AT command to the HL7812.
 * @note this API should only be used for debug purposes.
 *
 * @param data AT command string
 * @return int32_t 0 for success
 */
int32_t mdm_hl7812_send_at_cmd(uint8_t const *data);

/**
 * @brief Send certificate to the HL7812 (AT+KCERTSTORE).
 *
 * @param certificate string
 * @return int32_t 0 for success
 */
int32_t mdm_hl7812_send_certificate(uint8_t const *certificate);

/**
 * @brief Send sslcrypto configuration to the HL7812 (AT+KSSLCRYPTO).
 *
 * @return int32_t 0 for success
 */
int32_t mdm_hl7812_send_sslcrypto(void);

/**
 * @brief Send apn configuration to the HL7812 (AT+KCNXCFG and AT+CGDCONT).
 *
 * @param apn string
 * @return int32_t 0 for success
 */
int32_t mdm_hl7812_set_apn(uint8_t const *apn);

/**
 * @brief Set http configuration to the HL7812 (AT+KHTTPCFG).
 *
 * @param url_domain string
 * @return int32_t 0 for success
 */
int32_t mdm_hl7812_set_http_cfg(uint8_t const *url_domain);

/**
 * @brief Send http header by the HL7812 (AT+KHTTPHEADER).
 *
 * @param data string
 * @return int32_t 0 for success
 */
int32_t mdm_hl7812_send_http_header(uint8_t const *data);

/**
 * @brief Send http post by the HL7812 (AT+KHTTPPOST).
 *
 * @param url_path string
 * @param data string
 * @return int32_t 0 for success
 */
int32_t mdm_hl7812_send_http_post(uint8_t const *url_path, uint8_t const *data);

/**
 * @brief Send http get by the HL7812 (AT+KHTTPGET).
 *
 * @param url_path string
 * @return int32_t 0 for success
 */
int32_t mdm_hl7812_send_http_get(uint8_t const *url_path);

/**
 * @brief Close HTTP connection  (AT+KHTTPCLOSE and AT+KHTTPDEL).
 *
 * @param url_path string
 * @return int32_t 0 for success
 */
int32_t mdm_hl7812_close_http(void);

/**
 * @brief Get the signal quality of the HL7812.
 * If CONFIG_MODEM_HL7812_RSSI_RATE_SECONDS is non-zero, then
 * this function returns the value from the last periodic read.
 * If CONFIG_MODEM_HL7812_RSSI_RATE_SECONDS is 0, then this
 * may cause the modem to be woken so that the values can be queried.
 *
 * @param rsrp Reference Signals Received Power (dBm)
 *             Range = -140 dBm to -44 dBm
 * @param sinr Signal to Interference plus Noise Ratio (dB)
 *             Range = -128 dB to 40 dB
 */
void mdm_hl7812_get_signal_quality(int *rsrp, int *sinr);

/**
 * @brief Get the SIM card ICCID
 *
 */
char *mdm_hl7812_get_iccid(void);

/**
 * @brief Get the HL7812 serial number
 *
 */
char *mdm_hl7812_get_sn(void);

/**
 * @brief Get the HL7812 IMEI
 *
 */
char *mdm_hl7812_get_imei(void);

/**
 * @brief Get the HL7812 firmware version
 *
 */
char *mdm_hl7812_get_fw_version(void);

/**
 * @brief Get the IMSI
 *
 */
char *mdm_hl7812_get_imsi(void);

/**
 * @brief Get the network state
 *
 * @return int8_t enum mdm_hl7812_network_state
 */
int8_t mdm_hl7812_get_network_state(void);

/**
 * @brief Get the network state
 *
 * @param struct in_addr ip address
 */
void mdm_hl7812_get_ip_addr_v4(struct in_addr *ip_addr);

/**
 * @brief Update the Access Point Name in the modem.
 *
 * @retval 0 on success, negative on failure.
 */
int32_t mdm_hl7812_update_apn(char *access_point_name);

/**
 * @brief Update the Radio Access Technology (mode).
 *
 * @retval 0 on success, negative on failure.
 */
int32_t mdm_hl7812_update_rat(enum mdm_hl7812_radio_mode value);

/**
 * @retval true if RAT value is valid
 */
bool mdm_hl7812_valid_rat(uint8_t value);

/**
 * @brief Register a function that is called when a modem event occurs.
 * Multiple users registering for callbacks is supported.
 *
 * @param agent event callback agent
 */
void mdm_hl7812_register_event_callback(struct mdm_hl7812_callback_agent *agent);

/**
 * @brief Unregister a callback event function
 *
 * @param agent event callback agent
 */
void mdm_hl7812_unregister_event_callback(struct mdm_hl7812_callback_agent *agent);

/**
 * @brief Force modem module to generate status events.
 *
 * @note This can be used to get the current state when a module initializes
 * later than the modem.
 */
void mdm_hl7812_generate_status_events(void);

/**
 * @brief Get the local time from the modem's real time clock.
 *
 * @param tm time structure
 * @param offset The amount the local time is offset from GMT/UTC in seconds.
 * @return int32_t 0 if successful
 */
int32_t mdm_hl7812_get_local_time(struct tm *tm, int32_t *offset);

#ifdef CONFIG_MODEM_HL7812_FW_UPDATE
/**
 * @brief Update the HL7812 via XMODEM protocol.  During the firmware update
 * no other modem fuctions will be available.
 *
 * @param file_path Absolute path of the update file
 *
 * @param 0 if successful
 */
int32_t mdm_hl7812_update_fw(char *file_path);
#endif

/**
 * @brief Read the operator index from the modem.
 *
 * @retval negative error code, 0 on success
 */
int32_t mdm_hl7812_get_operator_index(void);

/**
 * @brief Get modem functionality
 *
 * @return int32_t negative errno on failure, else mdm_hl7812_functionality
 */
int32_t mdm_hl7812_get_functionality(void);

/**
 * @brief Set airplane, normal, or reduced functionality mode.
 * Airplane mode persists when reset.
 *
 * @note Boot functionality is also controlled by Kconfig
 * MODEM_HL7812_BOOT_IN_AIRPLANE_MODE.
 *
 * @param mode
 * @return int32_t negative errno, 0 on success
 */
int32_t mdm_hl7812_set_functionality(enum mdm_hl7812_functionality mode);

/**
 * @brief When rate is non-zero: Put modem into Airplane mode. Enable GPS and
 * generate HL7812_EVENT_GPS events.
 * When zero: Disable GPS and put modem into normal mode.
 *
 * @note Airplane mode isn't cleared when the modem is reset.
 *
 * @param rate in seconds to query location
 * @return int32_t negative errno, 0 on success
 */
int32_t mdm_hl7812_set_gps_rate(uint32_t rate);

/**
 * @brief Register modem/SIM with polte.io
 *
 * @note It takes around 30 seconds for HL7812_EVENT_POLTE_REGISTRATION to
 * be generated.  If the applications saves the user and password
 * information into non-volatile memory, then this command
 * only needs to be run once.
 *
 * @return int32_t negative errno, 0 on success
 */
int32_t mdm_hl7812_polte_register(void);

/**
 * @brief Enable PoLTE.
 *
 * @param user from polte.io or register command callback
 * @param password from polte.io register command callback
 * @return int32_t negative errno, 0 on success
 */
int32_t mdm_hl7812_polte_enable(char *user, char *password);

/**
 * @brief Locate device using PoLTE.
 *
 * @note The first HL7812_EVENT_POLTE_LOCATE_STATUS event indicates
 * the status of issuing the locate command. The second event
 * requires 20-120 seconds to be generated and it contains the
 * location information (or indicates server failure).
 *
 * @return int32_t negative errno, 0 on success
 */
int32_t mdm_hl7812_polte_locate(void);

/**
 * @brief Perform a site survey.  This command may return different values
 * each time it is run (depending on what is in range).
 *
 * HL7812_EVENT_SITE_SURVEY is generated for each response received from modem.
 *
 * @retval negative error code, 0 on success
 */
int32_t mdm_hl7812_perform_site_survey(void);

/**
 * @brief Set desired sleep level. Requires MODEM_HL7812_LOW_POWER_MODE
 *
 * @param level (sleep, lite hibernate, or hibernate)
 * @return int negative errno, 0 on success
 */
int mdm_hl7812_set_desired_sleep_level(enum mdm_hl7812_sleep level);

/**
 * @brief Allows mapping of WAKE_UP signal
 * to a user accessible test point on the development board.
 *
 * @param func to be called when application requests modem wake/sleep.
 * The state parameter of the callback is 1 when modem should stay awake,
 * 0 when modem can sleep
 */
void mdm_hl7812_register_wake_test_point_callback(void (*func)(int state));

/**
 * @brief Allows mapping of P1.12_GPIO6 signal
 * to a user accessible test point on the development board.
 *
 * @param func to be called when modem wakes/sleeps is sleep level is
 * hibernate or lite hibernate.
 * The state parameter of the callback follows gpio_pin_get definitions,
 * but will default high if there is an error reading pin
 */
void mdm_hl7812_register_gpio6_callback(void (*func)(int state));

/**
 * @brief Allows mapping of UART1_CTS signal
 * to a user accessible test point on the development board.
 *
 * @param func to be called when CTS state changes if sleep level is sleep.
 * The state parameter of the callback follows gpio_pin_get definitions,
 * but will default low if there is an error reading pin
 */
void mdm_hl7812_register_cts_callback(void (*func)(int state));

/**
 * @brief Set the bands available for the LTE connection
 *
 * @param bands Band bitmap in hexadecimal format without the 0x prefix.
 * Leading 0's for the value can be ommited.
 *
 * @return int32_t negative errno, 0 on success
 */
int32_t mdm_hl7812_set_bands(char const *bands);

/**
 * @brief Set the log level for the modem.
 *
 * @note It cannot be set higher than CONFIG_MODEM_LOG_LEVEL.
 * If debug level is desired, then it must be compiled with that level.
 *
 * @param level 0 (None) - 4 (Debug)
 *
 * @retval new log level
 */
uint32_t mdm_hl7812_log_filter_set(uint32_t level);

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_MODEM_HL7812_H_ */
