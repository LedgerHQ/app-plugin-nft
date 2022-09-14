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
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}