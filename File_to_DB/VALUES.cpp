// VALUES.h : Implementation of the CVALUES class



// CVALUES implementation

// code generated on Monday, April 10, 2017, 9:10 PM

#include "stdafx.h"
#include "VALUES.h"
IMPLEMENT_DYNAMIC(CVALUES, CRecordset)

CVALUES::CVALUES(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_nid = 0;
	m_value = L"";
	m_Text = L"";
	m_binFile;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CVALUES::GetDefaultConnect()
{
	return _T("DSN=test;UID=sa;PWD=ionut;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DESKTOP-GF0594Q;DATABASE=TEST;");
}

CString CVALUES::GetDefaultSQL()
{
	return _T("[dbo].[VALUES]");
}

void CVALUES::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[nid]"), m_nid);
	RFX_Text(pFX, _T("[value]"), m_value);
	RFX_Text(pFX, _T("[Text]"), m_Text);
	RFX_LongBinary(pFX, _T("[binFile]"), m_binFile);

}
/////////////////////////////////////////////////////////////////////////////
// CVALUES diagnostics

#ifdef _DEBUG
void CVALUES::AssertValid() const
{
	CRecordset::AssertValid();
}

void CVALUES::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


