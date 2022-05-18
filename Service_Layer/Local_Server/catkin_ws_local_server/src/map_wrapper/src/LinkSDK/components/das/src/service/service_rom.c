/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */

#include <../src/LinkSDK/components/das/inc/das/platform.h>
#include <../src/LinkSDK/components/das/inc/das/hardware.h>
#include <../src/LinkSDK/components/das/inc/das/service.h>

#if (DAS_SERVICE_ROM_ENABLED)

#define ROM_ATTEST_KEY_ROM  "mem:"
#define ROM_ATTEST_TYPE		"type:2"

typedef struct _rom_context_t {
    size_t read_offset;   /* rom addr, which next to be processed */
    uint8_t index;        /* rom block index */
    das_rom_bank_t banks[DAS_ROM_BANK_NUMBER];
} rom_context_t;

static rom_context_t rom_ctx = {0};

static void _data_convert(uint8_t *src, uint8_t *dst, size_t size)
{
    uint32_t i;

    for (i = 0; i < size; i++) {
        dst[i] = src[size - 1 - i];
    }
}

static int _rom_init(void)
{
    memset(&rom_ctx, 0, sizeof(rom_context_t));

    das_hal_rom_info(rom_ctx.banks);

    return 0;
}

static das_result_t _rom_attest(char *path, 
								size_t path_size, 
                                char* attribute,
								size_t attribute_size,
								das_sum_context_t *sum_context, 
								das_service_state_t *state)
{
    das_rom_bank_t *bk;
    size_t length, offset;
    uint8_t temp[16] = {0};

    if (path == NULL ||
        sum_context == NULL || state == NULL ||
		attribute == NULL || attribute_size < strlen(ROM_ATTEST_TYPE)) {
        return DAS_ERROR_BAD_PARAMETERS;
    }

    if (state->status == DAS_SRV_STATUS_START) {
        rom_ctx.index = 0;
        rom_ctx.read_offset = 0;
    }

    bk = rom_ctx.banks + rom_ctx.index;

    length = (bk->size - rom_ctx.read_offset) > DAS_SERVICE_ROM_STEP_SIZE ?
              DAS_SERVICE_ROM_STEP_SIZE : (bk->size - rom_ctx.read_offset);

    DAS_LOG("ROM Service - addr: 0x%lx size: 0x%lx\n",
            (long)bk->address + rom_ctx.read_offset, (long)length);

    das_sum_update(sum_context, bk->address + rom_ctx.read_offset, length);
    rom_ctx.read_offset += length;

    if (rom_ctx.read_offset >= bk->size) {
        length = strlen(ROM_ATTEST_KEY_ROM) + sizeof(size_t) * 4 + 4;
        if (path_size <= length) {
            DAS_LOG("No buffer for ROM path: 0x%x\n", (int)length);
            return DAS_ERROR_SHORT_BUFFER;
        }

        memcpy(path, ROM_ATTEST_KEY_ROM, strlen(ROM_ATTEST_KEY_ROM));
        offset = strlen(ROM_ATTEST_KEY_ROM);

        _data_convert((uint8_t*)&bk->address, temp, sizeof(uint8_t *));
        length = das_hex2string(path + offset, path_size - offset, temp, sizeof(uint8_t *));
        offset += length;
        *(path + offset++) = '/';

        _data_convert((uint8_t*)&bk->size, temp, sizeof(size_t));
        length = das_hex2string(path + offset, path_size - offset, temp, sizeof(size_t));
        offset += length;
        *(path + offset) = '\0';

        rom_ctx.index++;
        if (rom_ctx.index == DAS_ROM_BANK_NUMBER) {
            state->status = DAS_SRV_STATUS_FINISH;
        } else {
            rom_ctx.read_offset = 0;
            state->status = DAS_SRV_STATUS_PUBLISH;
        }
		memcpy(attribute, ROM_ATTEST_TYPE, strlen(ROM_ATTEST_TYPE) * sizeof(char));
    } else {
        state->status = DAS_SRV_STATUS_NEXT;
    }

    return DAS_SUCCESS;
}

static das_result_t _rom_measure(das_sum_context_t *sum_context, das_mac_context_t *mac_context, das_service_state_t *state)
{
    das_rom_bank_t *bk;
    size_t length;

    if (sum_context == NULL || state == NULL) {
        return DAS_ERROR_BAD_PARAMETERS;
    }

    if (state->status == DAS_SRV_STATUS_START) {
        rom_ctx.index = 0;
        rom_ctx.read_offset = 0;
    }

    bk = rom_ctx.banks + rom_ctx.index;

    length = (bk->size - rom_ctx.read_offset) > DAS_SERVICE_ROM_STEP_SIZE ?
              DAS_SERVICE_ROM_STEP_SIZE : (bk->size - rom_ctx.read_offset);

    DAS_LOG("ROM Service - addr: 0x%lx  size: 0x%lx\n",
            (long)bk->address + rom_ctx.read_offset, (long)length);

    das_sum_update(sum_context, bk->address + rom_ctx.read_offset, length);
    das_sum_update(mac_context, bk->address + rom_ctx.read_offset, length);
    rom_ctx.read_offset += length;

    if (rom_ctx.read_offset >= bk->size) {
        rom_ctx.index++;
        if (rom_ctx.index == DAS_ROM_BANK_NUMBER) {
            state->status = DAS_SRV_STATUS_FINISH;
        } else {
            rom_ctx.read_offset = 0;
            state->status = DAS_SRV_STATUS_PUBLISH;
        }
    } else {
        state->status = DAS_SRV_STATUS_NEXT;
    }

    return DAS_SUCCESS;
}

das_service_t service_rom = {
    .name = "ROM",
    .init  = _rom_init,
    .info = NULL,
    .attest = _rom_attest,
    .measure = _rom_measure,
};

#endif // end DAS_SERVICE_ROM_ENABLED
