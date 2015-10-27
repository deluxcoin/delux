// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x2f;
        pchMessageStart[1] = 0x35;
        pchMessageStart[2] = 0x11;
        pchMessageStart[3] = 0x9a;
        vAlertPubKey = ParseHex("04ef12d6151e061baa9ae98f2078de81ad80d10d52cc93593e271feaeb9a7316e5106206b55381a5683c089e12eeb5d40429ba826cf5733c6c0ee9d9251fe092c2");
        vchSyncCheckpointPubKey = ParseHex("04d4fab16f64370022b40e686356dec3fbdcbd368c33865c2733f29f4a1fe2f7fd5d6465c5e20c8d69f5afcaa6b313f47cf68bfec098083f4fc388d02231d0ed99");
        nDefaultPort = 30005;
        nRPCPort = 30007;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        const char* pszTimestamp = "Delux 2015";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1445745948, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1445745948;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 263302;
		hashGenesisBlock = uint256("0x000058dd1c7d047a2dbad45aeca66c7fff988ef50e15acd39fff9ecd8879f51a");


        assert(hashGenesisBlock == uint256("0x000058dd1c7d047a2dbad45aeca66c7fff988ef50e15acd39fff9ecd8879f51a"));
        assert(genesis.hashMerkleRoot == uint256("0xcba856cca7e28a131f4fa994b854d5ed081928d7c074c0b371b660b7bf32c0cf"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(30);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(85);
        base58Prefixes[SECRET_KEY] =     list_of(224);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        bnProofOfStakeLimit = CBigNum(~uint256(0));
        bnProofOfStakeLimitV2 = CBigNum(~uint256(0));

        nBasicPoWReward = 200 * COIN;
        nLaunchTime = genesis.nTime;
        nMinDelay = 2; //seconds

        nCoinbaseMaturity = 60;
        nStakeMinConfirmations = 60;

        nStakeMinAge = 30 * 60; // 30 minutes
        nModifierInterval = 10 * 60; // time to elapse before new modifier is computed

        nStakeCoinYearReward = 10 * CENT;

        nLastPOWBlock = 20000;
        nFirstPoSBlock = 5000;

        nTargetSpacing = 60;
        nTargetTimespan = 60 * nTargetSpacing;

        nMaxMoney = nLastPOWBlock * nBasicPoWReward;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x9d;
        pchMessageStart[1] = 0x86;
        pchMessageStart[2] = 0x1a;
        pchMessageStart[3] = 0x30;

        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 10);
        vAlertPubKey = ParseHex("04ef12d6151e061baa9ae98f2078de81ad80d10d52cc93593e271feaeb9a7316e5106206b55381a5683c089e12eeb5d40429ba826cf5733c6c0ee9d9251fe092c2");
        nDefaultPort = 30010;
        nRPCPort = 30012;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 515572;
        hashGenesisBlock = uint256("0x003f0f343fa88f3ac5d418cc610d1af8697562828f463f8759dfe0031ea3280a");

        assert(hashGenesisBlock == uint256("0x003f0f343fa88f3ac5d418cc610d1af8697562828f463f8759dfe0031ea3280a"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(127);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(255);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);

        nCoinbaseMaturity = 10;
        nStakeMinConfirmations = 10;

        nStakeMinAge = 60 * 60;
        nModifierInterval = 10 * 60;

        nStakeCoinYearReward = 10 * CENT; // 10% per year

        nLastPOWBlock = 0x7fffffff;

        nMaxMoney = 2000000000 * COIN;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xf0;
        pchMessageStart[1] = 0xf1;
        pchMessageStart[2] = 0xf2;
        pchMessageStart[3] = 0xf3;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1411111111;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 516114;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
		
		hashGenesisBlock = uint256("0x112153c91ef9cec4b88d0b8cbbbb0d2503f0d8e0b167a64bfe8671b10eba6e0b");

        assert(hashGenesisBlock == uint256("0x112153c91ef9cec4b88d0b8cbbbb0d2503f0d8e0b167a64bfe8671b10eba6e0b"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
