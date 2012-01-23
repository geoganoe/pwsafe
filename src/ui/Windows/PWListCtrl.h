/*
* Copyright (c) 2003-2012 Rony Shapiro <ronys@users.sourceforge.net>.
* All rights reserved. Use of the code is allowed under the
* Artistic License 2.0 terms, as specified in the LICENSE file
* distributed with this code, or available from
* http://www.opensource.org/licenses/artistic-license-2.0.php
*/

/*
*  Use of CInfoDisplay to replace MS's broken ToolTips support.
*  Based on CInfoDisplay class taken from Asynch Explorer by
*  Joseph M. Newcomer [MVP]; http://www.flounder.com
*  Additional enhancements to the use of this code have been made to 
*  allow for delayed showing of the display and for a limited period.
*/

#pragma once

#include "SecString.h"
#include "Fonts.h"

class DboxMain;
class CItemData;

class CPWListCtrl : public CListCtrl
{
public:
  CPWListCtrl();
  ~CPWListCtrl();

  void Initialize();
  void ActivateND(const bool bActivate);

  void SetFilterState(bool bState);
  void SetUpFont();
  void SetHighlightChanges(bool bvalue)
  {m_bUseHighLighting = bvalue;}

protected:
  //{{AFX_MSG(CPWListCtrl)
  afx_msg void OnDestroy();
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg void OnSelectionChanged(NMHDR *pNotifyStruct, LRESULT *pLResult);
  afx_msg void OnCustomDraw(NMHDR *pNotifyStruct, LRESULT *pLResult);
  afx_msg void OnPaint();
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
  //}}AFX_MSG

  LRESULT OnCharItemlist(WPARAM wParam, LPARAM lParam);
  BOOL PreTranslateMessage(MSG* pMsg);

  DECLARE_MESSAGE_MAP()

private:
  bool FindNext(const CString &cs_find, const int iSubItem);

  DboxMain *m_pDbx;
  CString m_csFind;
  UINT_PTR m_FindTimerID;

  // Notes Display
  UINT_PTR m_nHoverNDTimerID, m_nShowNDTimerID;
  CPoint m_HoverNDPoint;
  bool m_bShowNotes, m_bMouseInWindow;

  // Filter
  bool m_bFilterActive;

  CFont *GetFontBasedOnStatus(CItemData *pci, COLORREF &cf);
  bool m_bUseHighLighting;
};
