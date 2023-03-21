#include "ledger_nft_plugin.h"

void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    strlcpy(msg->name, "[ L ] Market", msg->nameLength);

    switch (context->selectorIndex) {
        case MINT:
            if (memcmp((uint8_t *) PIC(LEDGER_NFT_CONTRACTS[MULTI_MINT_CONTRACT_NFT]),
                       msg->pluginSharedRO->txContent->destination,
                       ADDRESS_LENGTH) == 0) {
                strlcpy(msg->version, "MultiMintContractNFT - Mint", msg->versionLength);
                break;
            } else if (memcmp((uint8_t *) PIC(LEDGER_NFT_CONTRACTS[STABLE_MULTI_MINT_ERC_721]),
                              msg->pluginSharedRO->txContent->destination,
                              ADDRESS_LENGTH) == 0) {
                strlcpy(msg->version, "StableMultiMintERC721 - Mint", msg->versionLength);
                break;
            } else {
                PRINTF("Unsupported contract address\n");
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                return;
            }
        case PRE_SALE_MINT:
            strlcpy(msg->version, "Presale Mint", msg->versionLength);
            break;
        case STABLE_MINT_SIGN:
            strlcpy(msg->version, "Stable Mint Sign", msg->versionLength);
            break;
        case STABLE_MINT:
            strlcpy(msg->version, "Stable Mint", msg->versionLength);
            break;
        case MINT_SIGN:
            strlcpy(msg->version, "StableMultiMintERC721 - Mint Sign", msg->versionLength);
            break;
        case MINT_SIGN_V2:
            strlcpy(msg->version, "MultiMint1155 - Mint Sign", msg->versionLength);
            break;
        case BID:
            strlcpy(msg->version, "Bid", msg->versionLength);
            break;
        case FINALIZE_AUCTION:
            strlcpy(msg->version, "Finalize Auction", msg->versionLength);
            break;
        case MINT_V2:
            strlcpy(msg->version, "MultiMint1155 - Mint", msg->versionLength);
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}