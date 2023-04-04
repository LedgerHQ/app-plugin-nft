#include "ledger_nft_plugin.h"

// Set UI for "Payable Amount" screen.
static void set_payable_amount_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Amount", msg->titleLength);

    // set network ticker (ETH, BNB, etc) if needed
    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_sent)) {
        strlcpy(context->ticker_sent, msg->network_ticker, sizeof(context->ticker_sent));
    }

    amountToString(msg->pluginSharedRO->txContent->value.value,
                   msg->pluginSharedRO->txContent->value.length,
                   WEI_TO_ETHER,
                   context->ticker_sent,
                   msg->msg,
                   msg->msgLength);
}

static void set_amount_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Quantity", msg->titleLength);

    amountToString(context->amount, sizeof(context->amount), 0, "", msg->msg, msg->msgLength);
}

static void set_token_id_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Token ID", msg->titleLength);

    amountToString(context->token_id, sizeof(context->token_id), 0, "", msg->msg, msg->msgLength);
}

static void set_auction_id_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Auction ID", msg->titleLength);
    // context->token_id is used to store the auction id
    amountToString(context->token_id, sizeof(context->token_id), 0, "", msg->msg, msg->msgLength);
}

static void set_address_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Address", msg->titleLength);
    msg->msg[0] = '0';
    msg->msg[1] = 'x';
    getEthAddressStringFromBinary((uint8_t *) context->address,
                                  msg->msg + 2,
                                  msg->pluginSharedRW->sha3,
                                  0);
}

// Helper function that returns the enum corresponding to the screen that should be displayed.
static screens_t get_screen(const ethQueryContractUI_t *msg,
                            const context_t *context __attribute__((unused))) {
    uint8_t index = msg->screenIndex;
    switch (context->selectorIndex) {
        case MINT:
        case PRE_SALE_MINT:
        case STABLE_MINT_SIGN:
        case STABLE_MINT:
        case MINT_SIGN:
            switch (index) {
                case 0:
                    return AMOUNT_SCREEN;
                case 1:
                    return PAYABLE_AMOUNT_SCREEN;
                default:
                    return ERROR;
            }
            break;
        case MINT_SIGN_V2:
            switch (index) {
                case 0:
                    return TOKEN_ID_SCREEN;
                case 1:
                    return AMOUNT_SCREEN;
                case 2:
                    return PAYABLE_AMOUNT_SCREEN;
                case 3:
                    return ADDRESS_SCREEN;
                default:
                    return ERROR;
            }
            break;
        case BID:
            switch (index) {
                case 0:
                    return AUCTION_ID_SCREEN;
                case 1:
                    return PAYABLE_AMOUNT_SCREEN;
                default:
                    return ERROR;
            }
            break;
        case FINALIZE_AUCTION:
            switch (index) {
                case 0:
                    return AUCTION_ID_SCREEN;
                default:
                    return ERROR;
            }
            break;
        case MINT_V2:
            switch (index) {
                case 0:
                    return TOKEN_ID_SCREEN;
                case 1:
                    return AMOUNT_SCREEN;
                case 2:
                    return PAYABLE_AMOUNT_SCREEN;
                default:
                    return ERROR;
            }
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            return ERROR;
    }
}

void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);
    msg->result = ETH_PLUGIN_RESULT_OK;

    screens_t screen = get_screen(msg, context);
    switch (screen) {
        case PAYABLE_AMOUNT_SCREEN:
            set_payable_amount_ui(msg, context);
            break;
        case TOKEN_ID_SCREEN:
            set_token_id_ui(msg, context);
            break;
        case AMOUNT_SCREEN:
            set_amount_ui(msg, context);
            break;
        case ADDRESS_SCREEN:
            set_address_ui(msg, context);
            break;
        case AUCTION_ID_SCREEN:
            set_auction_id_ui(msg, context);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
}