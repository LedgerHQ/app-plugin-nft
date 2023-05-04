#include "ledger_nft_plugin.h"

// Called once to init.
void handle_init_contract(void *parameters) {
    ethPluginInitContract_t *msg = (ethPluginInitContract_t *) parameters;

    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    if (msg->pluginContextLength < sizeof(context_t)) {
        PRINTF("Plugin parameters structure is bigger than allowed size\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    if (!is_tx_contract_address_supported(msg->pluginSharedRO->txContent->destination)) {
        PRINTF("Contract 0x%.*H unsupported\n",
               ADDRESS_LENGTH,
               msg->pluginSharedRO->txContent->destination);
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    context_t *context = (context_t *) msg->pluginContext;

    memset(context, 0, sizeof(*context));

    uint8_t i;
    for (i = 0; i < NUM_SELECTORS; i++) {
        if (memcmp((uint8_t *) PIC(LEDGER_NFT_SELECTORS[i]), msg->selector, SELECTOR_SIZE) == 0) {
            context->selectorIndex = i;
            break;
        }
    }
    if (i == NUM_SELECTORS) {
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
    }

    // Set `next_param` to be the first field we expect to parse.
    switch (context->selectorIndex) {
        case MINT:
        case PRE_SALE_MINT:
        case STABLE_MINT_SIGN:
        case STABLE_MINT:
        case MINT_SIGN:
            context->next_param = AMOUNT;
            break;
        case MINT_SIGN_V2:
            context->next_param = OFFSET;
            break;
        case BID:
        case FINALIZE_AUCTION:
            context->next_param = AUCTION_ID;
            break;
        case MINT_V2:
            context->next_param = TOKEN_ID;
            break;
        default:
            PRINTF("Missing selectorIndex: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
