#pragma once

#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/language.h>

#define EXE_DIR (wxPathOnly(wxStandardPaths::Get().GetExecutablePath()) + wxFileName::GetPathSeparator())	// F.e.: "C:\Program Files\Test\"

// Global GUI properties
namespace UIProps{
	// Set global language
	void SetLanguage(wxLanguage lang);
	// Get global language
	wxLanguage GetLanguage();
	// Get language id by human name
	wxLanguage GetLanguageId(const wxString lang);
	// Get language human name by id
	wxString GetLanguageName(wxLanguage lang);
	// Set tooltips durations
	void SetTooltips(long wait_before, long duration, long wait_between, int max_width);
	// Enable or disable global logging (+ messages)
	bool EnableLogging(bool enable);
}
