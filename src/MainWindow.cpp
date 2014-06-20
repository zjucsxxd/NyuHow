#include "MainWindow.hpp"
#include "version.h"
#include <wx/menu.h>

MainWindowFileDrop::MainWindowFileDrop(MainWindow* target) : target(target){}

bool MainWindowFileDrop::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& files){

	// TODO

	return true;
}

MainWindow::MainWindow(const wxString filename) : wxFrame(NULL, wxID_ANY, filename.empty() ? APP_NAME_FULL : wxString::Format("%s - %s", APP_NAME_FULL, filename), wxDefaultPosition, wxSize(1024, 768), wxCAPTION | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX | wxSYSTEM_MENU | wxRESIZE_BORDER | wxTAB_TRAVERSAL | wxCLIP_CHILDREN){
	// Set window titlebar icon
#pragma message "Outside of windows, load application icon extern!!!"
	this->SetIcon(wxICON(APP_ICON));
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
	enum{MENU_CLOSE};
	wxMenu* file_menu = new wxMenu;
	menu_bar->Append(file_menu, _("File"));
	wxMenuItem* close_menu_item = new wxMenuItem(file_menu, MENU_CLOSE, _("Quit") + "\tCTRL+Q", _("Closes application."));
#pragma message "Outside of windows, load menu icons extern!!!"
	close_menu_item->SetBitmap(wxBITMAP(MENU_CLOSE));
	this->Bind(wxEVT_MENU, [this](wxCommandEvent& event) -> void{
			this->Close();
		}, MENU_CLOSE);
	file_menu->Append(close_menu_item);


	// TODO

	// Create child windows

	// TODO

}
