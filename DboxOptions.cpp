/// \file DboxOptions.cpp
//-----------------------------------------------------------------------------

#include "PasswordSafe.h"

#include "ThisMfcApp.h"
#if defined(POCKET_PC)
  #include "pocketpc/resource.h"
#else
  #include "resource.h"
#endif

#include "corelib/PWSprefs.h"

// dialog boxen
#include "DboxMain.h"
#include "OptionsSecurity.h"
#include "OptionsDisplay.h"
#include "OptionsUsername.h"
#include "OptionsPasswordPolicy.h"
#include "OptionsMisc.h"


#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void
DboxMain::OnOptions() 
{
   CPropertySheet optionsDlg(_T("Options"), this);
   COptionsDisplay         display;
   COptionsSecurity        security;
   COptionsPasswordPolicy  passwordpolicy;
   COptionsUsername        username;
   COptionsMisc            misc;
   PWSprefs               *prefs = PWSprefs::GetInstance();

   /*
   **  Initialize the property pages values.
   */
   display.m_alwaysontop = m_bAlwaysOnTop;
   display.m_pwshowinedit = prefs->
     GetPref(PWSprefs::BoolPrefs::ShowPWDefault) ? TRUE : FALSE;
   display.m_pwshowinlist = prefs->
     GetPref(PWSprefs::BoolPrefs::ShowPWInList) ? TRUE : FALSE;
#if defined(POCKET_PC)
   display.m_dcshowspassword = prefs->
     GetPref(PWSprefs::BoolPrefs::DCShowsPassword) ? TRUE : FALSE;
#endif
   display.m_usesystemtray = prefs->
     GetPref(PWSprefs::BoolPrefs::UseSystemTray) ? TRUE : FALSE;

   security.m_clearclipboard = prefs->
     GetPref(PWSprefs::BoolPrefs::DontAskMinimizeClearYesNo) ? TRUE : FALSE;
   security.m_lockdatabase = prefs->
     GetPref(PWSprefs::BoolPrefs::DatabaseClear) ? TRUE : FALSE;
   security.m_confirmsaveonminimize = prefs->
     GetPref(PWSprefs::BoolPrefs::DontAskSaveMinimize) ? FALSE : TRUE;
   security.m_confirmcopy = prefs->
     GetPref(PWSprefs::BoolPrefs::DontAskQuestion) ? FALSE : TRUE;
   security.m_LockOnWindowLock = prefs->
	   GetPref(PWSprefs::BoolPrefs::LockOnWindowLock) ? TRUE : FALSE;


    passwordpolicy.m_pwlendefault = prefs->
      GetPref(PWSprefs::IntPrefs::PWLenDefault);
    passwordpolicy.m_pwuselowercase = prefs->
      GetPref(PWSprefs::BoolPrefs::PWUseLowercase);
    passwordpolicy.m_pwuseuppercase = prefs->
      GetPref(PWSprefs::BoolPrefs::PWUseUppercase);
    passwordpolicy.m_pwusedigits = prefs->
      GetPref(PWSprefs::BoolPrefs::PWUseDigits);
    passwordpolicy.m_pwusesymbols = prefs->
      GetPref(PWSprefs::BoolPrefs::PWUseSymbols);
    passwordpolicy.m_pwusehexdigits = prefs->
      GetPref(PWSprefs::BoolPrefs::PWUseHexDigits);
    passwordpolicy.m_pweasyvision = prefs->
      GetPref(PWSprefs::BoolPrefs::PWEasyVision);

   username.m_usedefuser = prefs->
     GetPref(PWSprefs::BoolPrefs::UseDefUser);
   username.m_defusername = CString(prefs->
				    GetPref(PWSprefs::StringPrefs::DefUserName));
   username.m_querysetdef = prefs->
     GetPref(PWSprefs::BoolPrefs::QuerySetDef);

   misc.m_confirmdelete = prefs->
     GetPref(PWSprefs::BoolPrefs::DeleteQuestion) ? FALSE : TRUE;
   misc.m_saveimmediately = prefs->
     GetPref(PWSprefs::BoolPrefs::SaveImmediately) ? TRUE : FALSE;

   optionsDlg.AddPage( &display );
   optionsDlg.AddPage( &security );
   optionsDlg.AddPage( &passwordpolicy );
   optionsDlg.AddPage( &username );
   optionsDlg.AddPage( &misc );


   /*
   **  Remove the "Apply Now" button.
   */
   optionsDlg.m_psh.dwFlags |= PSH_NOAPPLYNOW;
   int rc = optionsDlg.DoModal();

   if (rc == IDOK)
   {
      /*
      **  First save all the options.
      */
     prefs->SetPref(PWSprefs::BoolPrefs::AlwaysOnTop,
		    display.m_alwaysontop == TRUE);
     prefs->SetPref(PWSprefs::BoolPrefs::ShowPWDefault,
		    display.m_pwshowinedit == TRUE);
     prefs->SetPref(PWSprefs::BoolPrefs::ShowPWInList,
		    display.m_pwshowinlist == TRUE);
#if defined(POCKET_PC)
     prefs->SetPref(PWSprefs::BoolPrefs::DCShowsPassword,
		    display.m_dcshowspassword == TRUE);
#endif
     prefs->SetPref(PWSprefs::BoolPrefs::UseSystemTray,
		    display.m_usesystemtray == TRUE);

     prefs->SetPref(PWSprefs::BoolPrefs::DontAskMinimizeClearYesNo,
		    security.m_clearclipboard == TRUE);
     prefs->SetPref(PWSprefs::BoolPrefs::DatabaseClear,
		    security.m_lockdatabase == TRUE);
     prefs->SetPref(PWSprefs::BoolPrefs::DontAskSaveMinimize,
		    security.m_confirmsaveonminimize == FALSE);
     prefs->SetPref(PWSprefs::BoolPrefs::DontAskQuestion,
		    security.m_confirmcopy == FALSE);
	 prefs->SetPref(PWSprefs::BoolPrefs::LockOnWindowLock,
			security.m_LockOnWindowLock == TRUE);


     prefs->SetPref(PWSprefs::IntPrefs::PWLenDefault,
		    passwordpolicy.m_pwlendefault);
     prefs->SetPref(PWSprefs::BoolPrefs::PWUseLowercase,
		    passwordpolicy.m_pwuselowercase == TRUE);
     prefs->SetPref(PWSprefs::BoolPrefs::PWUseUppercase,
		    passwordpolicy.m_pwuseuppercase == TRUE);
     prefs->SetPref(PWSprefs::BoolPrefs::PWUseDigits,
		    passwordpolicy.m_pwusedigits == TRUE);
     prefs->SetPref(PWSprefs::BoolPrefs::PWUseSymbols,
		    passwordpolicy.m_pwusesymbols == TRUE);
     prefs->SetPref(PWSprefs::BoolPrefs::PWUseHexDigits,
		    passwordpolicy.m_pwusehexdigits == TRUE);
     prefs-> SetPref(PWSprefs::BoolPrefs::PWEasyVision,
		     passwordpolicy.m_pweasyvision == TRUE);

     prefs->SetPref(PWSprefs::BoolPrefs::UseDefUser,
		    username.m_usedefuser == TRUE);
     prefs->SetPref(PWSprefs::StringPrefs::DefUserName,
		    username.m_defusername);
     prefs->SetPref(PWSprefs::BoolPrefs::QuerySetDef,
		    username.m_querysetdef == TRUE);

     prefs->SetPref(PWSprefs::BoolPrefs::DeleteQuestion,
		    misc.m_confirmdelete == FALSE);
     prefs->SetPref(PWSprefs::BoolPrefs::SaveImmediately,
		    misc.m_saveimmediately == TRUE);

     /*
     ** Update string in database, if necessary
     */
     if (prefs->IsChanged()) {
       // save changed preferences to file
       // Note that we currently can only write the entire file, so any changes
       // the user made to the database are also saved here
       if (app.m_core.WriteCurFile() != PWScore::SUCCESS)
	 MessageBox(_T("Failed to save changed preferences"), AfxGetAppName());
       else
	 prefs->ClearChanged();
     }
      /*
      **  Now update the application according to the options.
      */
      m_bAlwaysOnTop = display.m_alwaysontop == TRUE;
      UpdateAlwaysOnTop();
      bool bOldShowPasswordInList = m_bShowPasswordInList;
      m_bShowPasswordInList = prefs->
	GetPref(PWSprefs::BoolPrefs::ShowPWInList);

      if (bOldShowPasswordInList != m_bShowPasswordInList)
		RefreshList();
	
      if (display.m_usesystemtray == TRUE) {
		if (app.m_TrayIcon.Visible() == FALSE)
			app.m_TrayIcon.ShowIcon();
	  } else { // user doesn't want to display
		if (app.m_TrayIcon.Visible() == TRUE)
			app.m_TrayIcon.HideIcon();
      }

      /*
       * Here are the old (pre 2.0) semantics:
       * The username entered in this dialog box will be added to all the entries
       * in the username-less database that you just opened. Click Ok to add the
       * username or Cancel to leave them as is.
       *
       * You can also set this username to be the default username by clicking the
       * check box.  In this case, you will not see the username that you just added
       * in the main dialog (though it is still part of the entries), and it will
       * automatically be inserted in the Add dialog for new entries.
       *
       * To me (ronys), these seem too complicated, and not useful once password files
       * have been converted to the old (username-less) format to 1.9 (with usernames).
       * (Not to mention 2.0).
       * Therefore, the username will now only be a default value to be used in new entries,
       * and in converting pre-2.0 databases.
       */

      m_core.SetDefUsername(username.m_defusername);
      m_core.SetUseDefUser(username.m_usedefuser == TRUE ? true : false);

   }
   else if (rc == IDCANCEL)
   {
   }
}

