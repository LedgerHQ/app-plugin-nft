import { processTest, populateTransaction } from "./test.fixture";

const contractName = "StableMultiMintERC721";

const testLabel = "mintSMM721"; // <= Name of the test
const testDirSuffix = "mint_smm721"; // <= directory to compare device snapshots to
const signedPlugin = false;
const testNetwork = "ethereum_goerli";

const contractAddr = "0x9ea4571a739a1d644e17d34a86e7dee97609b256";
const chainID = 1;

// [0] 0000000000000000000000000000000000000000000000000000000000000003  Amount
const inputData = "0xa0712d680000000000000000000000000000000000000000000000000000000000000003"
const value = "0.6";

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID, value);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 8, // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanox",
        label: "Nano X",
        steps: 6, // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanosp",
        label: "Nano S+",
        steps: 6, // <= Define the number of steps for this test case and this device
    },

];

devices.forEach((device) => {
    processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});