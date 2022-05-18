#ifndef __DAS_PRIVATE_H__
#define __DAS_PRIVATE_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "../src/LinkSDK/core/sysdep/core_stdinc.h"

#include "../src/LinkSDK/core/aiot_state_api.h"
#include "../src/LinkSDK/core/aiot_sysdep_api.h"
#include "aiot_das_api.h"

#include <pthread.h>

typedef struct {
    aiot_sysdep_portfile_t *sysdep;
    void *mqtt;
    void *das;
    int inited;
    void *userdata;
} das_handle_t;

#define DAS_MODULE_NAME                    "das"  /* 用于内存统计的模块名字符串 */

#if defined(__cplusplus)
}
#endif
#endif  /* __DAS_PRIVATE_H__ */

