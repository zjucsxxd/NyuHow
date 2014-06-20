#include "UIProps.hpp"
#include <wx/intl.h>
#include "version.h"
#include <wx/tooltip.h>
#include <wx/log.h>

namespace UIProps{
	// Current language
	wxLanguage glob_lang;

	void SetLanguage(wxLanguage lang){
		// Initialize language support
		static wxLocale* locale = NULL;
		if(!locale){
			// Set localization to english for usual number/date format
			locale = new wxLocale(wxLANGUAGE_ENGLISH);
			// Set one languages folder
			wxFileTranslationsLoader::AddCatalogLookupPathPrefix(EXE_DIR + "lang");
		}
		// Update translation unit
		wxTranslations* trans = new wxTranslations;
		trans->SetLanguage(lang);
		trans->AddCatalog(APP_NAME);
		wxTranslations::Set(trans);
		glob_lang = lang;
	}

	wxLanguage GetLanguage(){
		return glob_lang;
	}

	wxLanguage GetLanguageId(const wxString lang){
		for(unsigned char lang_id = wxLANGUAGE_ABKHAZIAN; lang_id <= wxLANGUAGE_ZULU; ++lang_id)
			if(lang == wxLocale::GetLanguageName(lang_id))
				return static_cast<wxLanguage>(lang_id);
		return wxLANGUAGE_UNKNOWN;
	}

	wxString GetLanguageName(wxLanguage lang){
		return wxLocale::GetLanguageName(lang);
	}

	void SetTooltips(long wait_before, long duration, long wait_between, int max_width){
		if(duration > 0){	// Tooltips have a duration?
			wxToolTip::Enable(true);	// Enable tooltips
			wxToolTip::SetDelay(wait_before);	// Duration before tooltip shows
			wxToolTip::SetAutoPop(duration);	// Duration of tooltip visibility
			wxToolTip::SetReshow(wait_between);	// Duration before next tooltip shows
			wxToolTip::SetMaxWidth(max_width);	// Maximal pixel width of tooltips
		}else
			wxToolTip::Enable(false);	// Disable tooltips
	}

	bool EnableLogging(bool enable){
		return wxLog::EnableLogging(enable);
	}
}