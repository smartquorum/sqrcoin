// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
		(0, uint256("0x0000d6b6020d5985f66382e7bfc5a6bc6ac8b0fa499e3588d0a4c5a3d5ca5c01"))
		(10, uint256("0xcb61faa853a2d9d36b81c6a1e007474ab25dc7a21eb64c1d80ccdc104b35e851"))
		(20, uint256("0x379d68f4c4fc8cd7b811938ad9a0c5d37a14c2de8a819ca68d08c890938fbeba"))
		(30, uint256("0xdbdaf952d0db3d32687bdb167a388a48dfd853ca8b5e18811ca83e6e618667f2"))
		(40, uint256("0xd0afeac4f8df26f68ee4a1ca7acd960ea36f5402f027004301dcd3d584ddccd2"))
		(50, uint256("0x1bfa00e8c9a17dd9d2b5dbb7538e02b029414fe6bf415411fc4515941725df4f"))
		(60, uint256("0xa578f0bc0949b49fc72d5a2152718aedaa16f336f0ad6c81be4a1393fd919225"))
                (70, uint256("0xea781b502cc559dfdd108b960927da565a4262be0e1f7435dce8eee0c809a13f"))
                (80, uint256("0x51d4fc68e7b780d39e7e14ed23fbc5f9e4196e2e5b0d7a4fd5b3f19812c5cb23"))
                (90, uint256("0x5f316bcb2e2d5804d71f152ca5d8ea209b3e9fc853bb545233d35841eff73df2"))
                (100, uint256("0x5df3c03fe7665dc5e325e2fe2b4296ddc582a41cc6eaaa8937a488de19f96b5a"))
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
