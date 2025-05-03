#include <stdio.h>
#include <stdint.h>
#include "SENTParse.h"


void SENTResetCallback() {
    printf("SENT Reset Callback\n");
}

void SENTDataCallback(uint8_t Data) {
    printf("SENT Data Callback: %u\n", Data);
}

int main() {

	SENTParseData_t SENT1;

	SENTParse_Init(&SENT1, SENTResetCallback, SENTDataCallback);

	uint32_t Positions[] = {1000, 1560, 1680, 1810, 1950, 2100, 2260, 2430, 2610, 3610};
    for (uint32_t i = 0; i < sizeof(Positions) / sizeof(Positions[0]); i++) {
		SENTParse_Receive(&SENT1, Positions[i]);
    }
	

	return 0;
}
