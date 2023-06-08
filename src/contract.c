#include "ledger_nft_plugin.h"

// Function: mint (MultiMintContractNFT, StableMultiMintERC721)
// Selector: 0xa0712d68
static const uint8_t MINT_SELECTOR[SELECTOR_SIZE] = {0xa0, 0x71, 0x2d, 0x68};

// Function: preSaleMint
// Selector: 0x827481ea
static const uint8_t PRE_SALE_MINT_SELECTOR[SELECTOR_SIZE] = {0x82, 0x74, 0x81, 0xea};

// Function: stableMintSign
// Selector: 0x11413601
static const uint8_t STABLE_MINT_SIGN_SELECTOR[SELECTOR_SIZE] = {0x11, 0x41, 0x36, 0x01};

// Function: stableMint
// Selector: 0x804b936f
static const uint8_t STABLE_MINT_SELECTOR[SELECTOR_SIZE] = {0x80, 0x4b, 0x93, 0x6f};

// Function: mintSign
// Selector: 0xf39247a9
static const uint8_t MINT_SIGN_SELECTOR[SELECTOR_SIZE] = {0xf3, 0x92, 0x47, 0xa9};

// Function: mintSign (v2)
// Selector: 0x657bb113
static const uint8_t MINT_SIGN_V2_SELECTOR[SELECTOR_SIZE] = {0x65, 0x7b, 0xb1, 0x13};

// Function: bid
// Selector: 0x454a2ab3
static const uint8_t BID_SELECTOR[SELECTOR_SIZE] = {0x45, 0x4a, 0x2a, 0xb3};

// Function: finalizeAuction
// Selector: 0xe8083863
static const uint8_t FINALIZE_AUCTION_SELECTOR[SELECTOR_SIZE] = {0xe8, 0x08, 0x38, 0x63};

// Function: mint (MultiMint1155)
// Selector: 0x08dc9f42
static const uint8_t MINT_V2_SELECTOR[SELECTOR_SIZE] = {0x08, 0xdc, 0x9f, 0x42};

// Plugin uses 0x00000 as a dummy address to reprecent ETH.
const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Array of all the different nft selectors.
const uint8_t *const LEDGER_NFT_SELECTORS[NUM_SELECTORS] = {
    MINT_SELECTOR,
    PRE_SALE_MINT_SELECTOR,
    STABLE_MINT_SIGN_SELECTOR,
    STABLE_MINT_SELECTOR,
    MINT_SIGN_SELECTOR,
    MINT_SIGN_V2_SELECTOR,
    BID_SELECTOR,
    FINALIZE_AUCTION_SELECTOR,
    MINT_V2_SELECTOR,
};