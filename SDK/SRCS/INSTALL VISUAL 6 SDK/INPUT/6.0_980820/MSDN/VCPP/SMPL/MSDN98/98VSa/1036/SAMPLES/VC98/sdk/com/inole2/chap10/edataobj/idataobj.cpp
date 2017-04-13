/*
 * IDATAOBJ.CPP
 * Data Object Chapter 10
 *
 * Implementation of the IDataObject interface for CDataObject.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "dataobj.h"



/*
 * CImpIDataObject::CImpIDataObject
 * CImpIDataObject::~CImpIDataObject
 *
 * Parameters (Constructor):
 *  pObj            PCDataObject of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIDataObject::CImpIDataObject(PCDataObject pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIDataObject::~CImpIDataObject(void)
    {
    return;
    }






/*
 * CImpIDataObject::QueryInterface
 * CImpIDataObject::AddRef
 * CImpIDataObject::Release
 *
 * Purpose:
 *  IUnknown members for CImpIDataObject object.
 */

STDMETHODIMP CImpIDataObject::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIDataObject::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIDataObject::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }





/*
 * CImpIDataObject::GetData
 *
 * Purpose:
 *  Retrieves data described by a specific FormatEtc into a StgMedium
 *  allocated by this function.  Used like GetClipboardData.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the desired data.
 *  pSTM            LPSTGMEDIUM in which to return the data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::GetData(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM)
    {
    UINT            cf=pFE->cfFormat;

    //Check the aspects we support.
    if (!(DVASPECT_CONTENT & pFE->dwAspect))
        return ResultFromScode(DATA_E_FORMATETC);

    switch (cf)
        {
        case CF_METAFILEPICT:
            if (!(TYMED_MFPICT & pFE->tymed))
                break;

            return m_pObj->RenderMetafilePict(pSTM);

        case CF_BITMAP:
            if (!(TYMED_GDI & pFE->tymed))
                break;

            return m_pObj->RenderBitmap(pSTM);

        case CF_TEXT:
            if (!(TYMED_HGLOBAL & pFE->tymed))
                break;

            return m_pObj->RenderText(pSTM);

        default:
            break;
        }

    return ResultFromScode(DATA_E_FORMATETC);
    }




/*
 * CImpIDataObject::GetDataHere
 *
 * Purpose:
 *  Renders the specific FormatEtc into caller-allocated medium
 *  provided in pSTM.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the desired data.
 *  pSTM            LPSTGMEDIUM providing the medium into which
 *                  wer render the data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::GetDataHere(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIDataObject::QueryGetData
 *
 * Purpose:
 *  Tests if a call to GetData with this FormatEtc will provide
 *  any rendering; used like IsClipboardFormatAvailable.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the desired data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::QueryGetData(LPFORMATETC pFE)
    {
    UINT            cf=pFE->cfFormat;
    BOOL            fRet=FALSE;

    //Check the aspects we support.
    if (!(DVASPECT_CONTENT & pFE->dwAspect))
        return ResultFromScode(DATA_E_FORMATETC);

    switch (cf)
        {
        case CF_METAFILEPICT:
            fRet=(BOOL)(pFE->tymed & TYMED_MFPICT);
            break;

        case CF_BITMAP:
            fRet=(BOOL)(pFE->tymed & TYMED_GDI);
            break;

        case CF_TEXT:
            fRet=(BOOL)(pFE->tymed & TYMED_HGLOBAL);
            break;

        default:
            fRet=FALSE;
            break;
        }

    return fRet ? NOERROR : ResultFromScode(S_FALSE);
    }






/*
 * CImpIDataObject::GetCanonicalFormatEtc
 *
 * Purpose:
 *  Provides the caller with an equivalent FormatEtc to the one
 *  provided when different FormatEtcs will produce exactly the
 *  same renderings.
 *
 * Parameters:
 *  pFEIn            LPFORMATETC of the first description.
 *  pFEOut           LPFORMATETC of the equal description.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::GetCanonicalFormatEtc
    (LPFORMATETC pFEIn, LPFORMATETC pFEOut)
    {
    if (NULL==pFEOut)
        return ResultFromScode(E_INVALIDARG);

    pFEOut->ptd=NULL;
    return ResultFromScode(DATA_S_SAMEFORMATETC);
    }






/*
 * CImpIDataObject::SetData
 *
 * Purpose:
 *  Places data described by a FormatEtc and living in a StgMedium
 *  into the object.  The object may be responsible to clean up the
 *  StgMedium before exiting.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the data to set.
 *  pSTM            LPSTGMEDIUM containing the data.
 *  fRelease        BOOL indicating if this function is responsible
 *                  for freeing the data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::SetData(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM, BOOL fRelease)
    {
    return ResultFromScode(DATA_E_FORMATETC);
    }






/*
 * CImpIDataObject::EnumFormatEtc
 *
 * Purpose:
 *  Returns an IEnumFORMATETC object through which the caller can
 *  iterate to learn about all the data formats this object can
 *  provide through either GetData[Here] or SetData.
 *
 * Parameters:
 *  dwDir           DWORD describing a data direction, either
 *                  DATADIR_SET or DATADIR_GET.
 *  ppEnum          LPENUMFORMATETC * in which to return the
 *                  pointer to the enumerator.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::EnumFormatEtc(DWORD dwDir
    , LPENUMFORMATETC *ppEnum)
    {
    switch (dwDir)
        {
        case DATADIR_GET:
            *ppEnum=new CEnumFormatEtc(m_pObj->m_cfeGet
                , m_pObj->m_rgfeGet);
            break;

        case DATADIR_SET:
            *ppEnum=NULL;
            break;

        default:
            *ppEnum=NULL;
            break;
        }

    if (NULL==*ppEnum)
        return ResultFromScode(E_FAIL);
    else
        (*ppEnum)->AddRef();

    return NOERROR;
    }





/*
 * CImpIDataObject::DAdvise
 *
 * Purpose:
 *  Provides the data object with an IAdviseSink object that we are
 *  responsible to notify when the data changes.
 *
 * Parameters:
 *  ppFE            LPFORMATETC
 *  dwFlags         DWORD carrying flags indicating how the advise
 *                  sink wants to be treated.
 *  pIAdviseSink    LPADVISESINK to the object to notify.
 *  pdwConn         LPDWORD into which we store a DWORD key
 *                  identifying the advise connection.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::DAdvise(LPFORMATETC pFE, DWORD dwFlags
    , LPADVISESINK pIAdviseSink, LPDWORD pdwConn)
    {
    HRESULT         hr;

    if (NULL==m_pObj->m_pIDataAdviseHolder)
        {
        hr=CreateDataAdviseHolder(&m_pObj->m_pIDataAdviseHolder);

        if (FAILED(hr))
            return ResultFromScode(E_OUTOFMEMORY);
        }

    hr=m_pObj->m_pIDataAdviseHolder->Advise((LPDATAOBJECT)this, pFE
        , dwFlags, pIAdviseSink, pdwConn);

    return hr;
    }






/*
 * CImpIDataObject::DUnadvise
 *
 * Purpose:
 *  Turns off advising previously set up with Advise.
 *
 * Parameters:
 *  dwConn          DWORD connection key returned from Advise.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::DUnadvise(DWORD dwConn)
    {
    HRESULT         hr;

    if (NULL==m_pObj->m_pIDataAdviseHolder)
        return ResultFromScode(E_FAIL);

    hr=m_pObj->m_pIDataAdviseHolder->Unadvise(dwConn);

    return hr;
    }






/*
 * CImpIDataObject::EnumDAdvise
 *
 * Purpose:
 *  Returns an enumerator object through which the caller can find
 *  all the agents currently receiving advises on this data object.
 *
 * Parameters:
 *  ppEnum          LPENUMSTATDATA * in which to return the
 *                  enumerator.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::EnumDAdvise(LPENUMSTATDATA *ppEnum)
    {
    HRESULT         hr;

    if (NULL==m_pObj->m_pIDataAdviseHolder)
        return ResultFromScode(E_FAIL);

    hr=m_pObj->m_pIDataAdviseHolder->EnumAdvise(ppEnum);
    return hr;
    }