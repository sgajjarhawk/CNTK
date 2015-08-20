// ExperimentalNetworkBuilder.h -- interface to new version of NDL (and config) parser  --fseide

#pragma once

#include "Basics.h"
#include "IComputationNetBuilder.h"

namespace Microsoft { namespace MSR { namespace CNTK {

    template<typename ElemType>
    class ExperimentalNetworkBuilder : public IComputationNetBuilder<ElemType>
    {
        typedef shared_ptr<ComputationNetwork<ElemType>> ComputationNetworkPtr;
        DEVICEID_TYPE m_deviceId;
        ComputationNetworkPtr m_net;
        std::wstring m_sourceCode;
    public:
        // the constructor expects the entire source code as a wstring; if you want to read it from a file, use 'include "file"' inside
        ExperimentalNetworkBuilder(const wstring & sourceCode, DEVICEID_TYPE deviceId) : m_sourceCode(sourceCode), m_deviceId(deviceId) { }

        // build a ComputationNetwork from description language
        // TODO: change return type of these interfaces to shared_ptrs
        virtual /*IComputationNetBuilder::*/ComputationNetwork<ElemType>* BuildNetworkFromDescription(ComputationNetwork<ElemType>* = nullptr);

        // nothing experimental about loading an existing file--this is the same code as for NDLNetworkBuilder.h
        virtual /*IComputationNetBuilder::*/ComputationNetwork<ElemType>* LoadNetworkFromFile(const wstring& modelFileName, bool forceLoad = true,
                                                                                              bool bAllowNoCriterionNode = false, ComputationNetwork<ElemType>* anotherNetwork = nullptr)
        {
            if (!m_net || m_net->GetTotalNumberOfNodes() == 0 || forceLoad) //not built or force load
                m_net->LoadFromFile(modelFileName, FileOptions::fileOptionsBinary, bAllowNoCriterionNode, anotherNetwork);
            m_net->ResetEvalTimeStamp();
            return m_net.get();
        }
    };

    template class ExperimentalNetworkBuilder<float>;
    template class ExperimentalNetworkBuilder<double>;

}}}
