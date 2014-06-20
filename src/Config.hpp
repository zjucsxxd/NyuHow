#pragma once

#include <map>
#include <wx/any.h>

// Global configuration
namespace Config{
	// Read configuration file / collect configuration values
	bool Load(const wxString filename);
	// Write to configuration file / save configuration values
	bool Save(const wxString filename);
	// Returns collected configuration values
	std::map<wxString, std::map<wxString, wxAny>>& GetValues();
}
