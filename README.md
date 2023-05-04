# Badges
[![Code style check](https://github.com/blooo-io/LedgerHQ-app-plugin-nft/actions/workflows/lint-workflow.yml/badge.svg)](https://github.com/blooo-io/LedgerHQ-app-plugin-nft/actions/workflows/lint-workflow.yml)
[![Compilation & tests](https://github.com/blooo-io/LedgerHQ-app-plugin-nft/actions/workflows/ci-workflow.yml/badge.svg)](https://github.com/blooo-io/LedgerHQ-app-plugin-nft/actions/workflows/ci-workflow.yml)
# LedgerHQ-app-plugin-nft
Ledger NFT Plugin

This is a plugin for the Ethereum application which helps parsing and displaying relevant information when signing a NFT transaction.
## Prerequisite

Clone the plugin to a new folder.

```shell
git clone https://github.com/blooo-io/LedgerHQ-app-plugin-nft.git
```

Then in the same folder clone two more repositories, which is the plugin-tools and app-ethereum.

```shell
git clone https://github.com/LedgerHQ/plugin-tools.git                          #plugin-tools
git clone --recurse-submodules https://github.com/LedgerHQ/app-ethereum.git     #app-ethereum
```
## Documentation

Need more information about the interface, the architecture, or general stuff about ethereum plugins? You can find more about them in the [ethereum-app documentation](https://github.com/LedgerHQ/app-ethereum/blob/master/doc/ethapp_plugins.asc).

## Smart Contracts

Smart contracts covered by this plugin are:

|  Network | Version | Smart Contract | Address |
|   ----   |   ---   |      ----      |   ---   |
| Goerli   | V0  | MultiMintContractNFT  | `0x6c304a1f99cecd3a9983001e943f3de00ed811d0` |
| Goerli   | V0  | StableMultiMintERC721 | `0x9ea4571a739a1d644e17d34a86e7dee97609b256` |
| Goerli   | V0  | MultiMint1155         | `0x12b180053db389b6200e6f646949e6ab7b385d40` |
| Goerli   | V0  | AuctionCore           | `0xc5ae7ff025d5c373762a73557e3dd3049cda1f2d` |


On these smart contracts, the functions covered by this plugin are:

|Contract |    Function   | Selector  | Displayed Parameters |
|   ---   |    ---        | ---       | --- |
|MultiMintContractNFT  |mint           | 0xa0712d68| <table><tbody> <tr><td><code>uint256 amount</code></td></tr> </tbody></table> |
|MultiMintContractNFT  |preSaleMint    | 0x827481ea| <table><tbody> <tr><td><code>uint256 amount</code></td></tr> </tbody></table> |
|StableMultiMintERC721 |stableMintSign | 0x11413601| <table><tbody> <tr><td><code>uint256 amount</code></td></tr> </tbody></table> |
|StableMultiMintERC721 |stableMint     | 0x804b936f| <table><tbody> <tr><td><code>uint256 amount</code></td></tr> </tbody></table> |
|StableMultiMintERC721 |mintSign       | 0xf39247a9| <table><tbody> <tr><td><code>uint256 amount</code></td></tr> </tbody></table> |
|StableMultiMintERC721 |mint           | 0xa0712d68| <table><tbody> <tr><td><code>uint256 amount</code></td></tr> </tbody></table> |
|MultiMint1155         | mintSign (v2)  | 0x657bb113| <table><tbody> <tr><td><code>uint256 tokenId</code></td></tr> <tr><td><code>uint256 amount</code></td></tr> <tr><td><code>address pass</code></td></tr></tbody></table> |
|AuctionCore           |bid            | 0x454a2ab3| <table><tbody> <tr><td><code>uint256 auctionId</code></td></tr> </tbody></table> |
|AuctionCore           |finalizeAuction| 0xe8083863| <table><tbody> <tr><td><code>uint256 auctionId</code></td></tr> </tbody></table> |
|MultiMint1155         | mint (v2)  | 0x08dc9f42| <table><tbody> <tr><td><code>uint256 tokenId</code></td></tr> <tr><td><code>uint256 amount</code></td></tr></tbody></table> |

> **Note:** Only the third `mint` function is labelled as v2 because the first two share the same selector and behave identically.

## Build

Go to the plugin-tools folder and run the "./start" script.
```shell
cd plugin-tools  # go to plugin folder
./start.sh       # run the script start.sh
```
The script will build a docker image and attach a console.
When the docker image is running go to the "LedgerHQ-app-plugin-nft" folder and build the ".elf" files.
```shell
cd LedgerHQ-app-plugin-nft/tests       # go to the tests folder in LedgerHQ-app-plugin-nft
./build_local_test_elfs.sh      # run the script build_local_test_elfs.sh
```

## Tests

To test the plugin go to the tests folder from the "LedgerHQ-app-plugin-nft" and run the script "test"
```shell
cd LedgerHQ-app-plugin-nft/tests       # go to the tests folder in LedgerHQ-app-plugin-nft
yarn                            # install dependencies
yarn test                       # run the script test
```
## Continuous Integration


The flow processed in [GitHub Actions](https://github.com/features/actions) is the following:

- Code formatting with [clang-format](http://clang.llvm.org/docs/ClangFormat.html)
- Compilation of the application for Ledger Nano S in [ledger-app-builder](https://github.com/LedgerHQ/ledger-app-builder)
