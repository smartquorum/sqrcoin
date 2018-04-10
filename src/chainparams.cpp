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

static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;

        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        pchMessageStart[0] = 0x32;
        pchMessageStart[1] = 0x11;
        pchMessageStart[2] = 0x2c;
        pchMessageStart[3] = 0x10;
        vAlertPubKey = ParseHex("04b69dea0171dcd59bf11fd207762108ad695262351238867dece8536cce6a1eeda6c5001a9cbd8ec0925358935dee923d0a50308b6881bcba78493b3a7a3cdef7");
        nDefaultPort = 41791;
        nRPCPort = 41792;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        const char* pszTimestamp = "SQRcoin network is launched on 01 Apr 2018.";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1522528200, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1522528200;
        genesis.nBits    = 520159231;
        genesis.nNonce   = 12908;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000d6b6020d5985f66382e7bfc5a6bc6ac8b0fa499e3588d0a4c5a3d5ca5c01"));
        assert(genesis.hashMerkleRoot == uint256("0xbd7f269c91de1a49e659a2baec8c2bad311c2cb4ca57c65a65e5c0d57278a151"));
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,10);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,153);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        vSeeds.push_back(CDNSSeedData("0",  "84.22.97.7"));
        vSeeds.push_back(CDNSSeedData("1",  "46.19.33.29"));
        vSeeds.push_back(CDNSSeedData("2",  "37.252.120.32"));
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);
        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "56D207762101DCd59F11fd174b8A9dEa0b";
        nLastPOWBlock = 480;
        nPOSStartBlock = 100;
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
        pchMessageStart[0] = 0x34;
        pchMessageStart[1] = 0x15;
        pchMessageStart[2] = 0x2e;
        pchMessageStart[3] = 0x12;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04b69dea0171dcd59bf11fd207762108ad695262351238867dece8536cce6a1eeda6c5001a9cbd8ec0925358935dee923d0a50308b6881bcba78493b3a7a3cdef7");
        nDefaultPort = 41793;
        nRPCPort = 41794;
        strDataDir = "testnet";
        genesis.nBits  = 520159231;
        genesis.nNonce = 12908;
        assert(hashGenesisBlock == uint256("0x0000d6b6020d5985f66382e7bfc5a6bc6ac8b0fa499e3588d0a4c5a3d5ca5c01"));
        vFixedSeeds.clear();
        vSeeds.clear();
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,10);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);
        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


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
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
