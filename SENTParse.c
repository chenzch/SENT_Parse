//---------------------------------------------------------------------------------------------------------------------
//
// WTMEC CORPORATION CONFIDENTIAL
// ________________________________
//
// [2025] Wtmec Corporation
// All Rights Reserved.
//
// NOTICE: This is an unpublished work of authorship, which contains trade secrets.
// Wtmec Corporation owns all rights to this work and intends to maintain it in confidence to
// preserve its trade secret status. Wtmec Corporation reserves the right, under the copyright
// laws of the United States or those of any other country that may have jurisdiction, to protect
// this work as an unpublished work, in the event of an inadvertent or deliberate unauthorized
// publication. Wtmec Corporation also reserves its rights under all copyright laws to protect
// this work as a published work, when appropriate. Those having access to this work may not copy
// it, use it, modify it, or disclose the information contained in it without the written
// authorization of Wtmec Corporation.
//
//---------------------------------------------------------------------------------------------------------------------
#include <stdint.h>
#include "SENTParse.h"
#include "SENTParseCfg.h"

void SENTParse_Init(LPSENTParseData_t pSENTParseData,
    SENTParseResetCallback_t ResetCallback,
    SENTParseDataCallback_t DataCallback) {

    pSENTParseData->Status = SENT_PARSE_SYNC;
    pSENTParseData->LastRollingCount = 0;
    pSENTParseData->ResetCallback = ResetCallback;
    pSENTParseData->DataCallback = DataCallback;

}

void SENTParse_Receive(LPSENTParseData_t pSENTParseData, uint32_t RollingCount) {
    uint32_t Delta;
    Delta = (RollingCount - pSENTParseData->LastRollingCount) & SENT_PARSE_ROLLING_COUNT_MASK;
    pSENTParseData->LastRollingCount = RollingCount;
    if (pSENTParseData->Status == SENT_PARSE_DATA) {
        // (Delta * (64 - 8) + TL56 / 2) / TL56 - 12U))
        Delta = ((Delta << 6) - (Delta << 3) + (pSENTParseData->TickLength56 >> 1)) / pSENTParseData->TickLength56 - 12U;
        if (Delta > 0xF) {
            pSENTParseData->Status = SENT_PARSE_SYNC;
            if (pSENTParseData->ResetCallback) {
                pSENTParseData->ResetCallback();
            }
        } else {
            if (pSENTParseData->DataCallback) {
                pSENTParseData->DataCallback((uint8_t)Delta);
            }
        }
    } else {
        if ((Delta > SENT_PARSE_SYNC_LENGTH_MAX) || (Delta < SENT_PARSE_SYNC_LENGTH_MIN)) {
            pSENTParseData->Status = SENT_PARSE_SYNC;
            if (pSENTParseData->ResetCallback) {
                pSENTParseData->ResetCallback();
            }
        } else {
            pSENTParseData->Status = SENT_PARSE_DATA;
            pSENTParseData->TickLength56 = Delta;
        }
    }
}
