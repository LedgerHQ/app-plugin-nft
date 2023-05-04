import { processTest, populateTransaction } from "./test.fixture";

const contractName = "AuctionCore";

const testLabel = "bid"; // <= Name of the test
const testDirSuffix = "bid"; // <= directory to compare device snapshots to
const signedPlugin = false;
const testNetwork = "ethereum_goerli";

const contractAddr = "0xc5ae7ff025d5c373762a73557e3dd3049cda1f2d";
const chainID = 1;

// [0] 0000000000000000000000000000000000000000000000000000000000000194  auctionId
const inputData = "0x454a2ab30000000000000000000000000000000000000000000000000000000000000194"
const value = "1.2";

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