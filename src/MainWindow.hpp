#pragma once

#include <wx/dnd.h>
#include <wx/frame.h>

// Declaration for use below
class MainWindow;

// File drop handler for window below
class MainWindowFileDrop : public wxFileDropTarget{
	private:
		MainWindow* target;
	public:
		MainWindowFileDrop(MainWindow* target);
		bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& files);
};

// Application top level window
class MainWindow : public wxFrame{
	public:
		MainWindow(const wxString filename = "");
};