#include "MainWindow.hpp"
#include "version.h"
#include <wx/menu.h>
#include <wx/artprov.h>

MainWindowFileDrop::MainWindowFileDrop(MainWindow* target) : target(target){}

bool MainWindowFileDrop::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& files){

	// TODO

	return true;
}

MainWindow::MainWindow(const wxString filename) : wxFrame(NULL, wxID_ANY, filename.empty() ? APP_NAME_FULL : wxString::Format("%s - %s", APP_NAME_FULL, filename), wxDefaultPosition, wxSize(1024, 768), wxCAPTION | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX | wxSYSTEM_MENU | wxRESIZE_BORDER | wxTAB_TRAVERSAL | wxCLIP_CHILDREN){
	// Set window titlebar icon
	this->SetIcon(
#ifdef _WIN32
	wxICON(APP_ICON)
#else
	wxIcon("/usr/share/" APP_NAME "/app.ico");
#endif
	);
	// Set frame background
	this->SetBackgroundColour(wxColour(60,60,70));
	// Set frame cursor
	this->SetCursor(wxCURSOR_HAND);
	// Center window on screen
	this->Center();
	// Create status bar at bottom of frame
	this->CreateStatusBar(1, wxSTB_SIZEGRIP | wxSTB_ELLIPSIZE_START | wxFULL_REPAINT_ON_RESIZE);
	// Create file drop handler
	this->SetDropTarget(new MainWindowFileDrop(this));
	// Create frame menu
	wxMenuBar* menu_bar = new wxMenuBar;
	this->SetMenuBar(menu_bar);
	// Create sub menus
	enum{MENU_CLOSE, MENU_ABOUT};
	// Create file menu
	wxMenu* file_menu = new wxMenu;
	menu_bar->Append(file_menu, _("File"));
	file_menu->AppendSeparator();
	wxMenuItem* close_menu_item = new wxMenuItem(file_menu, MENU_CLOSE, _("Quit") + "\tCTRL+Q", _("Closes application."));
	close_menu_item->SetBitmap(wxArtProvider::GetBitmap(wxART_CLOSE, wxART_MENU));
	this->Bind(wxEVT_MENU, [this](wxCommandEvent& event) -> void{
			this->Close();
		}, MENU_CLOSE);
	file_menu->Append(close_menu_item);
	// Create help menu
	wxMenu* help_menu = new wxMenu;
	menu_bar->Append(help_menu, _("Help"));
	help_menu->AppendSeparator();
	wxMenuItem* about_menu_item = new wxMenuItem(help_menu, MENU_ABOUT, _("About...") + "\tCTRL+A", _("Application informations."));
	about_menu_item->SetBitmap(wxArtProvider::GetBitmap(wxART_QUESTION, wxART_MENU));
	this->Bind(wxEVT_MENU, [this](wxCommandEvent& event) -> void{

			// TODO

		}, MENU_ABOUT);
	help_menu->Append(about_menu_item);

	// TODO

	// Create child windows

	// TODO

}
