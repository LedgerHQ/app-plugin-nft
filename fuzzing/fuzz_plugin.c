#include "ledger_nft_plugin.h"

void *pic(void *x) {
    return x;
}

#define ADDRESS_LENGTH 20

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    ethPluginInitContract_t init_contract;
    ethPluginProvideParameter_t provide_param;
    ethPluginFinalize_t finalize;
    ethQueryContractUI_t query_ui;
    txContent_t content = {0};

    // Fake sha3 context
    cx_sha3_t sha3;

    ethPluginSharedRO_t shared_ro;
    shared_ro.txContent = &content;

    ethPluginSharedRW_t shared_rw;
    shared_rw.sha3 = &sha3;

    context_t context;
    const uint8_t address[ADDRESS_LENGTH] = {0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
                                             0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
                                             0xee, 0xee, 0xee, 0xee, 0xee, 0xee};

    // see fullAmount / fullAddress in
    char title[32] = {0};
    char msg[79] = {0};  // 2^256 is 78 digits long

    // Data must be big enough to hold a selector
    if (Size < 4) {
        return 0;
    }

    init_contract.interfaceVersion = ETH_PLUGIN_INTERFACE_VERSION_LATEST;
    init_contract.selector = Data;
    init_contract.pluginContext = (uint8_t *) &context;
    init_contract.pluginContextLength = sizeof(context);

    handle_init_contract(&init_contract);
    if (init_contract.result != ETH_PLUGIN_RESULT_OK) {
        return 0;
    }

    size_t i = 4;
    while (Size - i >= 32) {
        provide_param.parameter = Data + i;
        provide_param.parameterOffset = i;
        provide_param.pluginContext = (uint8_t *) &context;
        handle_provide_parameter(&provide_param);
        if (provide_param.result != ETH_PLUGIN_RESULT_OK) {
            return 0;
        }
        i += 32;
    }

    finalize.pluginContext = (uint8_t *) &context;
    finalize.address = address;
    handle_finalize(&finalize);
    if (finalize.result != ETH_PLUGIN_RESULT_OK) {
        return 0;
    }

    for (int i = 0; i < finalize.numScreens; i++) {
        query_ui.title = title;
        query_ui.titleLength = sizeof(title);
        query_ui.msg = msg;
        query_ui.msgLength = sizeof(msg);
        query_ui.pluginContext = (uint8_t *) &context;
        query_ui.pluginSharedRO = &shared_ro;
        query_ui.pluginSharedRW = &shared_rw;

        query_ui.screenIndex = i;
        handle_query_contract_ui(&query_ui);
        if (query_ui.result != ETH_PLUGIN_RESULT_OK) {
            return 0;
        }
        printf("%s: %s\n", title, msg);
    }

    return 0;
}