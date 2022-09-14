import { processTest, populateTransaction } from "./test.fixture";

const contractName = "MultiMintContractNFT";

const testLabel = "Mint"; // <= Name of the test
const testDirSuffix = "mint"; // <= directory to compare device snapshots to
const signedPlugin = false;
const testNetwork= "ethereum";

const contractAddr = "0x6c304a1f99cecd3a9983001e943f3de00ed811d0";
const chainID = 1;

const selector = "0xa0712d68";
const quantity = "0000000000000000000000000000000000000000000000000000000000000005";

const inputData = selector+quantity;
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

devices.forEach((device) =>{
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});