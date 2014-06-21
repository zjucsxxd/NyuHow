#include <wx/app.h>
#include "Config.hpp"
#include "UIProps.hpp"
#include "MainWindow.hpp"

// Application control (mostly just for initializations and deinitializations)
class App : public wxApp{
	public:
		// Application initialization
		bool OnInit(){
			// Disable logging to avoid annoying messages
			UIProps::EnableLogging(false);
			// Read configuration file
			Config::Load(EXE_DIR + "config.ini");
			// Set application language
			std::map<wxString, std::map<wxString, wxAny>> config = Config::GetValues();
			if(config.count("Settings") && config["Settings"].count("language") && config["Settings"]["language"].CheckType<wxString>()){
				wxLanguage lang_id = UIProps::GetLanguageId(config["Settings"]["language"].As<wxString>());
				UIProps::SetLanguage(lang_id != wxLANGUAGE_UNKNOWN ? lang_id : wxLANGUAGE_ENGLISH);
			}else
				UIProps::SetLanguage(wxLANGUAGE_ENGLISH);
			// Put command line arguments in an easier format
			wxArrayString cmdline = this->argv.GetArguments();
			// On console execution
			if(cmdline.GetCount() > 2){

				// TODO

				// End application
				return false;
			// On GUI execution
			}else{
				// Set global GUI properties
				UIProps::SetTooltips(1000, 5000, 0, 200);
				// Create and show application main window
				MainWindow* main_wnd = cmdline.GetCount() > 1 ? new MainWindow(cmdline[1]) : new MainWindow();
				main_wnd->ShowWithEffect(wxSHOW_EFFECT_BLEND, 500);
				main_wnd->SetFocus();
				this->SetTopWindow(main_wnd);
				// Continue application with top window event loop and OnExit
				return true;
			}
		}
		// Application end
		int OnExit(){
			// Write to configuration file
			Config::Save(EXE_DIR + "config.ini");
			// Application ended successfully
			return 0;
		}
};

// Define application control class
wxIMPLEMENT_APP(App);
