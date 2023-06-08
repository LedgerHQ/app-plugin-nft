#include "ledger_nft_plugin.h"

void handle_amount(const ethPluginProvideParameter_t *msg, context_t *context) {
    copy_parameter(context->amount, msg->parameter, sizeof(context->amount));
}

void handle_token_id(const ethPluginProvideParameter_t *msg, context_t *context) {
    copy_parameter(context->token_id, msg->parameter, sizeof(context->token_id));
}

void handle_nb_tokens(const ethPluginProvideParameter_t *msg, context_t *context) {
    context->nb_tokens = U2BE(msg->parameter, PARAMETER_LENGTH - sizeof(context->nb_tokens));
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

void handle_mint_sign_v2(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case OFFSET:
            // Offset to the args tuple
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - sizeof(context->offset));
            context->next_param = NB_TOKENS;
            break;
        case NB_TOKENS:
            // Nb of objects in args tuple
            handle_nb_tokens(msg, context);
            context->next_param = TOKEN_ID;
            break;
        case TOKEN_ID:
            handle_token_id(msg, context);
            context->next_param = AMOUNT;
            break;
        case AMOUNT:
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

void handle_auction(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case AUCTION_ID:
            // Using context->token_id to store the auctionId
            handle_token_id(msg, context);
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

void handle_mint_v2(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case TOKEN_ID:
            // Using context->token_id to store the auctionId
            handle_token_id(msg, context);
            context->next_param = AMOUNT;
            break;
        case AMOUNT:
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
        if ((context->offset) &&
            msg->parameterOffset != context->checkpoint + context->offset + SELECTOR_SIZE) {
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
            case STABLE_MINT_SIGN:
            case STABLE_MINT:
            case MINT_SIGN:
                handle_mint(msg, context);
                break;
            case MINT_SIGN_V2:
                handle_mint_sign_v2(msg, context);
                break;
            case BID:
            case FINALIZE_AUCTION:
                handle_auction(msg, context);
                break;
            case MINT_V2:
                handle_mint_v2(msg, context);
                break;
            default:
                PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                break;
        }
    }
}
