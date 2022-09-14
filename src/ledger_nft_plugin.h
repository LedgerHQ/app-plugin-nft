#pragma once

#include <string.h>
#include "eth_internals.h"
#include "eth_plugin_interface.h"

#define NUM_SELECTORS    2
#define PLUGIN_NAME      "Ledger NFT"
#define TOKEN_FOUND      1 << 1
#define SELECTOR_SIZE    4
#define PARAMETER_LENGTH 32
#define RUN_APPLICATION  1

// Plugin uses 0x00000 as a dummy address to reprecent ETH.
extern const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH];

#define ADDRESS_IS_NETWORK_TOKEN(_addr) (!memcmp(_addr, NULL_ETH_ADDRESS, ADDRESS_LENGTH))
typedef enum {
    MINT,
    PRE_SALE_MINT,
} selector_t;

// Enumeration used to parse the smart contract data.
typedef enum {
    PAYABLE_AMOUNT,
    AMOUNT,
    NONE,
} parameter;

typedef enum {
    AMOUNT_SCREEN,
    PAYABLE_AMOUNT_SCREEN,
    ERROR,
} screens_t;

extern const uint8_t *const LEDGER_NFT_SELECTORS[NUM_SELECTORS];

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_t {
    // For display.
    uint8_t amount[PARAMETER_LENGTH];
    uint8_t payable_amount[PARAMETER_LENGTH];
    uint8_t contract_address_sent[ADDRESS_LENGTH];
    char ticker_sent[MAX_TICKER_LEN];

    // For parsing data.
    uint16_t offset;
    uint16_t checkpoint;
    uint8_t skip;
    uint8_t decimals;
    uint8_t next_param;
    uint8_t tokens_found;

    // For both parsing and display.
    selector_t selectorIndex;
} context_t;

// Piece of code that will check that the above structure is not bigger than 5 * 32. Do not remove
// this check.
_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_query_contract_id(void *parameters);

static inline void printf_hex_array(const char *title __attribute__((unused)),
                                    size_t len __attribute__((unused)),
                                    const uint8_t *data __attribute__((unused))) {
    PRINTF(title);
    for (size_t i = 0; i < len; ++i) {
        PRINTF("%02x", data[i]);
    };
    PRINTF("\n");
}