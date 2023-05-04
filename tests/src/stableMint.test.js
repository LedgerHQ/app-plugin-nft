import { processTest, populateTransaction } from "./test.fixture";

const contractName = "StableMultiMintERC721";

const testLabel = "StableMint"; // <= Name of the test
const testDirSuffix = "stable_mint"; // <= directory to compare device snapshots to
const signedPlugin = false;
const testNetwork = "ethereum_goerli";

const contractAddr = "0x9ea4571a739a1d644e17d34a86e7dee97609b256";
const chainID = 1;

// [0]  0000000000000000000000000000000000000000000000000000000000000003  Amount
// [1]  000000000000000000000000be2f0aa33ade86b3c324f50f25eeb1a366b7ebe8  Owner
// [2]  000000000000000000000000000000000000000000000000000000000000000c  Value
// [3]  0000000000000000000000000000000000000000000000000000000063f4a5f5  Deadline
// [4]  0000000000000000000000000000000000000000000000000000000000000038  V
// [5]  efc3f267021a912109919202b8e74e1ddf474486f43d0880bbfa1c1bd54b44f6  R
// [6]  2881888f136d40a9b8e02a792bbf175284fe736ad470fb551ba57751f81717a3  S
const inputData = "0x804b936f0000000000000000000000000000000000000000000000000000000000000003000000000000000000000000be2f0aa33ade86b3c324f50f25eeb1a366b7ebe8000000000000000000000000000000000000000000000000000000000000000c0000000000000000000000000000000000000000000000000000000063f4a5f50000000000000000000000000000000000000000000000000000000000000038efc3f267021a912109919202b8e74e1ddf474486f43d0880bbfa1c1bd54b44f62881888f136d40a9b8e02a792bbf175284fe736ad470fb551ba57751f81717a3"
const value = "12.0";

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