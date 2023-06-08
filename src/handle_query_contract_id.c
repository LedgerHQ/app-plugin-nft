#include "ledger_nft_plugin.h"

void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    strlcpy(msg->name, "[ L ] Market", msg->nameLength);

    switch (context->selectorIndex) {
        case MINT:
            strlcpy(msg->version, "Mint", msg->versionLength);
            break;
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
            strlcpy(msg->version, "Mint Sign", msg->versionLength);
            break;
        case MINT_SIGN_V2:
            strlcpy(msg->version, "Mint Sign", msg->versionLength);
            break;
        case BID:
            strlcpy(msg->version, "Bid", msg->versionLength);
            break;
        case FINALIZE_AUCTION:
            strlcpy(msg->version, "Finalize Auction", msg->versionLength);
            break;
        case MINT_V2:
            strlcpy(msg->version, "Mint", msg->versionLength);
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}