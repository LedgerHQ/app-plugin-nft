#include "ledger_nft_plugin.h"

// Function: mint
// Selector: 0xa0712d68
static const uint8_t MINT_SELECTOR[SELECTOR_SIZE] = {0xa0, 0x71, 0x2d, 0x68};

// Function: preSaleMint
// Selector: 0x827481ea
static const uint8_t PRE_SALE_MINT_SELECTOR[SELECTOR_SIZE] = {0x82, 0x74, 0x81, 0xea};

// Plugin uses 0x00000 as a dummy address to reprecent ETH.
const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Array of all the different nft selectors.
const uint8_t *const LEDGER_NFT_SELECTORS[NUM_SELECTORS] = {
    MINT_SELECTOR,
    PRE_SALE_MINT_SELECTOR,
};
