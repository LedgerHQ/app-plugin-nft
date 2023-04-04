#include "ledger_nft_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;
    msg->uiType = ETH_UI_TYPE_GENERIC;
    switch (context->selectorIndex) {
        case FINALIZE_AUCTION:
            msg->numScreens = 1;
            break;
        case MINT:
        case PRE_SALE_MINT:
        case STABLE_MINT_SIGN:
        case STABLE_MINT:
        case MINT_SIGN:
        case BID:
            msg->numScreens = 2;
            break;
        case MINT_V2:
            msg->numScreens = 3;
            break;
        case MINT_SIGN_V2:
            msg->numScreens = 4;
            break;
        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}
