#ifndef _CORE_LOG_H_
#define _CORE_LOG_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include "../src/LinkSDK/core/sysdep/core_stdinc.h"
#include "../src/LinkSDK/core/utils/core_string.h"
#include "../src/LinkSDK/core/aiot_state_api.h"
#include "../src/LinkSDK/core/aiot_sysdep_api.h"

#define CORE_LOG_MODULE_NAME "LOG"
#define CORE_LOG_MAXLEN (160)

typedef struct {
    uint64_t time_start;
    uint64_t time_interval;
    uint64_t timestamp;
} core_log_t;

void core_log_set_timestamp(aiot_sysdep_portfile_t *sysdep, uint64_t timestamp);
uint64_t core_log_get_timestamp(aiot_sysdep_portfile_t *sysdep);
void core_log(aiot_sysdep_portfile_t *sysdep, int32_t code, char *data);
void core_log1(aiot_sysdep_portfile_t *sysdep, int32_t code, char *fmt, void *data);
void core_log2(aiot_sysdep_portfile_t *sysdep, int32_t code, char *fmt, void *data1, void *data2);
void core_log3(aiot_sysdep_portfile_t *sysdep, int32_t code, char *fmt, void *data1, void *data2, void *data3);
void core_log4(aiot_sysdep_portfile_t *sysdep, int32_t code, char *fmt, void *data1, void *data2, void *data3, void *data4);
void core_log_hexdump(int32_t code, char prefix, uint8_t *buffer, uint32_t len);
void _core_log_append_date(aiot_sysdep_portfile_t *sysdep, uint64_t timestamp, char *buffer);

#if defined(__cplusplus)
}
#endif

#endif

