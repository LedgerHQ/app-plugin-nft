import { processTest, populateTransaction } from "./test.fixture";

const contractName = "AuctionCore";

const testLabel = "finalizeAuction"; // <= Name of the test
const testDirSuffix = "finalize_auction"; // <= directory to compare device snapshots to
const signedPlugin = false;
const testNetwork = "ethereum_goerli";

const contractAddr = "0xc5ae7ff025d5c373762a73557e3dd3049cda1f2d";
const chainID = 1;

// [0] 000000000000000000000000000000000000000000000000000000000000007b  auctionId
const inputData = "0xe8083863000000000000000000000000000000000000000000000000000000000000007b"

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 4, // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanox",
        label: "Nano X",
        steps: 4, // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanosp",
        label: "Nano S+",
        steps: 4, // <= Define the number of steps for this test case and this device
    },

];

devices.forEach((device) => {
    processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});