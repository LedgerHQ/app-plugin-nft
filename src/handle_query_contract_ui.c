#include <stdbool.h>
#include "ledger_nft_plugin.h"

// Set UI for "Payable Amount" screen.
static bool set_payable_amount_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Amount", msg->titleLength);

    // set network ticker (ETH, BNB, etc) if needed
    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_sent)) {
        strlcpy(context->ticker_sent, msg->network_ticker, sizeof(context->ticker_sent));
    }

    return amountToString(msg->pluginSharedRO->txContent->value.value,
                          msg->pluginSharedRO->txContent->value.length,
                          WEI_TO_ETHER,
                          context->ticker_sent,
                          msg->msg,
                          msg->msgLength);
}

static bool set_amount_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Quantity", msg->titleLength);

    if (context->selectorIndex == MINT_SIGN_V2) {
        // Convert the amount to a uint32_t
        uint32_t amountInt;
        if (!U4BE_from_parameter(context->amount, &amountInt)) {
            PRINTF("Error: Invalid amount format\n");
            return false;
        }

        // Multiply by the amount by the number of tokens (there should never be a transaction with
        // multiple tokens with different amounts)
        uint32_t multipliedAmount;
        if (__builtin_umul_overflow(amountInt, context->nb_tokens, &multipliedAmount)) {
            PRINTF("Error: Amount overflow\n");
            return false;
        }

        // Convert the amount back to a uint8_t[32] buffer
        uint8_t amountBuffer[PARAMETER_LENGTH] = {0};
        U4BE_ENCODE(amountBuffer,
                    sizeof(amountBuffer) - sizeof(multipliedAmount),
                    multipliedAmount);

        if (!amountToString(amountBuffer, sizeof(amountBuffer), 0, "", msg->msg, msg->msgLength)) {
            return false;
        }
    } else {
        if (!amountToString(context->amount,
                            sizeof(context->amount),
                            0,
                            "",
                            msg->msg,
                            msg->msgLength)) {
            return false;
        }
    }
    return true;
}

static bool set_token_id_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Token ID", msg->titleLength);

    return amountToString(context->token_id,
                          sizeof(context->token_id),
                          0,
                          "",
                          msg->msg,
                          msg->msgLength);
}

static bool set_auction_id_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Auction ID", msg->titleLength);
    // context->token_id is used to store the auction id
    return amountToString(context->token_id,
                          sizeof(context->token_id),
                          0,
                          "",
                          msg->msg,
                          msg->msgLength);
}

static bool set_address_ui(ethQueryContractUI_t *msg) {
    strlcpy(msg->title, "Contract", msg->titleLength);
    msg->msg[0] = '0';
    msg->msg[1] = 'x';
    return getEthAddressStringFromBinary((uint8_t *) msg->pluginSharedRO->txContent->destination,
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
                    return ADDRESS_SCREEN;
                case 1:
                    return AMOUNT_SCREEN;
                case 2:
                    return PAYABLE_AMOUNT_SCREEN;
                default:
                    return ERROR;
            }
            break;
        case MINT_SIGN_V2:
            switch (index) {
                case 0:
                    return ADDRESS_SCREEN;
                case 1:
                    return TOKEN_ID_SCREEN;
                case 2:
                    return AMOUNT_SCREEN;
                case 3:
                    return PAYABLE_AMOUNT_SCREEN;
                default:
                    return ERROR;
            }
            break;
        case BID:
            switch (index) {
                case 0:
                    return ADDRESS_SCREEN;
                case 1:
                    return AUCTION_ID_SCREEN;
                case 2:
                    return PAYABLE_AMOUNT_SCREEN;
                default:
                    return ERROR;
            }
            break;
        case FINALIZE_AUCTION:
            switch (index) {
                case 0:
                    return ADDRESS_SCREEN;
                case 1:
                    return AUCTION_ID_SCREEN;
                default:
                    return ERROR;
            }
            break;
        case MINT_V2:
            switch (index) {
                case 0:
                    return ADDRESS_SCREEN;
                case 1:
                    return TOKEN_ID_SCREEN;
                case 2:
                    return AMOUNT_SCREEN;
                case 3:
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

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    bool ret = false;

    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    screens_t screen = get_screen(msg, context);
    switch (screen) {
        case PAYABLE_AMOUNT_SCREEN:
            ret = set_payable_amount_ui(msg, context);
            break;
        case TOKEN_ID_SCREEN:
            ret = set_token_id_ui(msg, context);
            break;
        case AMOUNT_SCREEN:
            ret = set_amount_ui(msg, context);
            break;
        case ADDRESS_SCREEN:
            ret = set_address_ui(msg);
            break;
        case AUCTION_ID_SCREEN:
            ret = set_auction_id_ui(msg, context);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
