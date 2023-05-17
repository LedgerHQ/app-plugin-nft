import { processTest, populateTransaction } from "./test.fixture";

const contractName = "MultiMintContractNFT";

const testLabel = "MintMM1155"; // <= Name of the test
const testDirSuffix = "mint_mm1155"; // <= directory to compare device snapshots to
const signedPlugin = false;
const testNetwork = "ethereum_goerli";

const contractAddr = "0x12b180053db389b6200e6f646949e6ab7b385d40";
const chainID = 1;

// Selector: 0x08dc9f42
// [0] 0000000000000000000000000000000000000000000000000000000000000015 tokenId
// [1] 0000000000000000000000000000000000000000000000000000000000000002 amount
// [2] 0000000000000000000000000000000000000000000000000000000000000060 offset to data
// [3] 0000000000000000000000000000000000000000000000000000000000000008 data length
// [4] 746573745f6e6674000000000000000000000000000000000000000000000000 data

const inputData = "0x08dc9f420000000000000000000000000000000000000000000000000000000000000015000000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000600000000000000000000000000000000000000000000000000000000000000008746573745f6e6674000000000000000000000000000000000000000000000000";
const value = "12.0";

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID, value);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 9, // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanox",
        label: "Nano X",
        steps: 7, // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanosp",
        label: "Nano S+",
        steps: 7, // <= Define the number of steps for this test case and this device
    },

];

devices.forEach((device) => {
    processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});