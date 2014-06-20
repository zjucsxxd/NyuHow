#include "Config.hpp"
#include <wx/wfstream.h>
#include <wx/fileconf.h>

namespace Config{
	// Configuration values
	std::map<wxString, std::map<wxString, wxAny>> config_values;

	bool Load(const wxString filename){
		// Open file stream
		wxFileInputStream input_file(filename);
		if(input_file.IsOk()){
			// Extract file configuration values
			wxFileConfig config(input_file);
			wxString group_key; long group_index;
			if(config.GetFirstGroup(group_key, group_index))
				do{
					std::map<wxString, wxAny> group;
					config.SetPath(group_key);
					wxString entry_key; long entry_index;
					if(config.GetFirstEntry(entry_key, entry_index))
						do{
							switch(config.GetEntryType(entry_key)){
								case wxConfigBase::Type_String:
									{
										wxString value;
										if(config.Read(entry_key, &value))
											group[entry_key] = value;
									}
									break;
								case wxConfigBase::Type_Boolean:
									{
										bool value;
										if(config.Read(entry_key, &value))
											group[entry_key] = value;
									}
									break;
								case wxConfigBase::Type_Integer:
									{
										long value;
										if(config.Read(entry_key, &value))
											group[entry_key] = value;
									}
									break;
								case wxConfigBase::Type_Float:
									{
										double value;
										if(config.Read(entry_key, &value))
											group[entry_key] = value;
									}
									break;
                                case wxConfigBase::Type_Unknown:
                                    break;
							}
						}while(config.GetNextEntry(entry_key, entry_index));
					config_values[group_key] = group;
				}while(config.GetNextGroup(group_key, group_index));
			return true;
		}else
			return false;
	}

	bool Save(const wxString filename){
		// Open/create configuration file
		wxFileConfig config(wxEmptyString, wxEmptyString, filename, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
		// Write configuration values to file
		for(auto group_it = config_values.begin(); group_it != config_values.end(); ++group_it){
			config.SetPath(group_it->first);
			std::map<wxString, wxAny>& entries = group_it->second;
			for(auto entry_it = entries.begin(); entry_it != entries.end(); ++entry_it){
				wxAny& value = entry_it->second;
				if(value.CheckType<wxString>())
					config.Write(entry_it->first, value.As<wxString>());
				else if(value.CheckType<bool>())
					config.Write(entry_it->first, value.As<bool>());
				else if(value.CheckType<long>())
					config.Write(entry_it->first, value.As<long>());
				else if(value.CheckType<double>())
					config.Write(entry_it->first, value.As<double>());
			}
		}
		return true;
	}

	std::map<wxString, std::map<wxString, wxAny>>& GetValues(){
		return config_values;
	}
}
