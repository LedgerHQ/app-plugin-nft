import { processTest, populateTransaction } from "./test.fixture";

const contractName = "StableMultiMintERC721";

const testLabel = "mintSign"; // <= Name of the test
const testDirSuffix = "mint_sign"; // <= directory to compare device snapshots to
const signedPlugin = false;
const testNetwork = "ethereum_goerli";

const contractAddr = "0x9ea4571a739a1d644e17d34a86e7dee97609b256";
const chainID = 1;

// [0] 0000000000000000000000000000000000000000000000000000000000000001  Amount
// [1] 00000000000000000000000000000000000000000000000000000000000007d0  MaxAmount
// [2] 0000000000000000000000000000000000000000000000000000000000000060  Signature offset (3)
// [3] 0000000000000000000000000000000000000000000000000000000000000041  Signature byte length
// [4] 56efc3f267021a912109919202b8e74e1ddf474486f43d0880bbfa1c1bd54b44  Signature (first 32 bytes)
// [5] f62881888f136d40a9b8e02a792bbf175284fe736ad470fb551ba57751f81717  Signature  (next 32 bytes)
// [6] a300000000000000000000000000000000000000000000000000000000000000  Signature  (last  1 byte)
const inputData = "0xf39247a9000000000000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000007d00000000000000000000000000000000000000000000000000000000000000060000000000000000000000000000000000000000000000000000000000000004156efc3f267021a912109919202b8e74e1ddf474486f43d0880bbfa1c1bd54b44f62881888f136d40a9b8e02a792bbf175284fe736ad470fb551ba57751f81717a300000000000000000000000000000000000000000000000000000000000000"
const value = "2.3";

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