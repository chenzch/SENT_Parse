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
#if !defined(SENTPARSECFG_H)
#define SENTPARSECFG_H (1)

#define SENT_PARSE_ROLLING_COUNT_MASK (0xFFFFU)
#define SENT_PARSE_TICK_LENGTH (10)
#define SENT_PARSE_THRESHOLD_PERCENT (10) // 10% of the tick length

#define SENT_PARSE_SYNC_LENGTH_MAX (56U * SENT_PARSE_TICK_LENGTH * (100 + SENT_PARSE_THRESHOLD_PERCENT) / 100) // 56 ticks max
#define SENT_PARSE_SYNC_LENGTH_MIN (56U * SENT_PARSE_TICK_LENGTH * (100 - SENT_PARSE_THRESHOLD_PERCENT) / 100) // 56 ticks min


#endif // SENTPARSECFG_H
