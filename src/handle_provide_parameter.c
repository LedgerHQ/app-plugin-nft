#include "ledger_nft_plugin.h"

void handle_amount(const ethPluginProvideParameter_t *msg, context_t *context) {
    copy_parameter(context->amount, msg->parameter, sizeof(context->amount));
}

void handle_mint(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case AMOUNT:  // tokenA
            handle_amount(msg, context);
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    msg->result = ETH_PLUGIN_RESULT_OK;

    if (context->skip) {
        // Skip this step, and don't forget to decrease skipping counter.
        context->skip--;
    } else {
        if ((context->offset) && msg->parameterOffset != context->checkpoint + context->offset) {
            PRINTF("offset: %d, checkpoint: %d, parameterOffset: %d\n",
                   context->offset,
                   context->checkpoint,
                   msg->parameterOffset);
            return;
        }
        context->offset = 0;  // Reset offset
        switch (context->selectorIndex) {
            case MINT:
            case PRE_SALE_MINT:
                handle_mint(msg, context);
                break;
            default:
                PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                break;
        }
    }
}
