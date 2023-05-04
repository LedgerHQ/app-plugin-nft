import { processTest, populateTransaction } from "./test.fixture";

const contractName = "MultiMintContractNFT";

const testLabel = "PreSaleMint"; // <= Name of the test
const testDirSuffix = "pre_sale_mint"; // <= directory to compare device snapshots to
const signedPlugin = false;
const testNetwork = "ethereum_goerli";

const contractAddr = "0x6c304a1f99cecd3a9983001e943f3de00ed811d0";
const chainID = 1;

const selector = "0x827481ea";
const quantity = "0000000000000000000000000000000000000000000000000000000000000005";
const max_quantity = "0000000000000000000000000000000000000000000000000000000000000006";
const signature = "000000000000000000000000000000000000000000000000000000000000002000000000000000000000000000000000000000000000000000000000000000040010101000000000000000000000000000000000000000000000000000000000"
const value = "18.0";

const inputData = selector + quantity + max_quantity + signature;

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID, value);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 5, // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanox",
        label: "Nano X",
        steps: 5, // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanosp",
        label: "Nano S+",
        steps: 5, // <= Define the number of steps for this test case and this device
    },

];

devices.forEach((device) => {
    processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});