#include "ledger_nft_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    msg->uiType = ETH_UI_TYPE_GENERIC;

    // 2 additional screens are required to display the `token and `beneficiary` fields
    msg->numScreens = 2;
    msg->result = ETH_PLUGIN_RESULT_OK;
}
