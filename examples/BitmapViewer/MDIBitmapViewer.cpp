/* COPYRIGHT 2000 by 3rd-evolution
 * Author: Thomas Krammer (tkrammer@3rd-evolution.de)
 */

#include "pch.h"
#include <mdi/Color.h>
#include <mdi/MDIClientView.h>
#include <mdi/MDIViewMenu.h>

#include "MDIBitmapViewer.h"

// ==== CBitmapView ====

CBitmapView::CBitmapView(BRect frame, BBitmap *bm) :
	BView(frame, "BitmapView", B_FOLLOW_ALL_SIDES , B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE)
{
	bitmap = bm;
}

CBitmapView::~CBitmapView()
{
	delete bitmap;
}

void CBitmapView::AttachedToWindow()
{
	SetViewColor(CColor::Transparent);
}
		
void CBitmapView::Draw(BRect updateRect)
{
	DrawBitmap(bitmap, Bounds());
}

// ==== CBitmapViewerWindow ====

CBitmapViewerWindow::CBitmapViewerWindow(BRect frame) :
	BWindow(frame, "MDI Bitmap Viewer", B_DOCUMENT_WINDOW, B_ASYNCHRONOUS_CONTROLS)
{
	// ---- Create menu bar ----

	BMenuBar *menuBar = new BMenuBar(BRect(0,0,0,0), "MainMenuBar");

	AddChild(menuBar);
	SetKeyMenuBar(menuBar);

	// ---- Setup MDI client view ----

	BRect clientRect(0, menuBar->Bounds().Height() + 1, frame.Width()-B_V_SCROLL_BAR_WIDTH, frame.Height()-B_H_SCROLL_BAR_HEIGHT);
	
	client = new CMDIClientView(clientRect, "ClientView");

	// The MDI client view is target of a scroll view. The scroller of this scroll view
	// are automatically hidden, when they are not needed. They are only shown if the
	// user moves a MDI view outside the visible area.
	BScrollView *scrollView = new BScrollView("MDIScroller", client, 
									B_FOLLOW_ALL, 0, true, true, B_NO_BORDER);

	// ---- Setup menu bar ----

	BMenu *fileSubMenu		= new BMenu("File");

	fileSubMenu->AddItem(new BMenuItem("Open...", new BMessage(MSG_FILE_OPEN), 'O'));
	fileSubMenu->AddSeparatorItem();
	fileSubMenu->AddItem(new BMenuItem("Quit", new BMessage(B_QUIT_REQUESTED), 'Q'));
	
	// Using a CMDIViewMenu as "Window" menu allows us to add a list of all MDI views
	// inside the CMDIClientView to the menu.
	BMenu *windowSubMenu	= new CMDIViewMenu(client, "Window");
		
	// The MDI_MSG_xxxx messages are supported by the MDI client view.		
	windowSubMenu->AddItem(new BMenuItem("Tile vertical", new BMessage(MDI_MSG_TILE_VIEWS_VERTICAL)));
	windowSubMenu->AddItem(new BMenuItem("Tile horizontal", new BMessage(MDI_MSG_TILE_VIEWS_HORIZONTAL)));
	windowSubMenu->AddItem(new BMenuItem("Stack", new BMessage(MDI_MSG_STACK_VIEWS)));
	//windowSubMenu->SetTargetForItems(client);
		
	menuBar->AddItem(fileSubMenu);
	menuBar->AddItem(windowSubMenu);
		
	AddChild(scrollView);

	openPanel = NULL;
}
	
CBitmapViewerWindow::~CBitmapViewerWindow()
{
	delete openPanel;
}
	
bool CBitmapViewerWindow::QuitRequested()
{
	// exit application
	be_app->PostMessage(B_QUIT_REQUESTED);
	
	return true;
}
	
void CBitmapViewerWindow::MenusBeginning()
{
	// Update dynamic menu entries in the "Window" menu.
	CMDIViewMenu *windowMenu = dynamic_cast<CMDIViewMenu *>(KeyMenuBar()->ItemAt(1)->Submenu());

	windowMenu->SetTargetForItems(client);
	windowMenu->UpdateViewItems();
}

void CBitmapViewerWindow::MessageReceived(BMessage *message)
{
	switch(message->what) {
		case B_REFS_RECEIVED:
			{
				// The user selected one or more files in the open file panel.
			
				entry_ref ref;
				int32 i=0;
				BTranslatorRoster *roster = BTranslatorRoster::Default(); 
		
				while(message->FindRef("refs", i++, &ref) == B_OK){
					BFile file(&ref, B_READ_ONLY); 
					BBitmapStream stream; 
					BBitmap *result = NULL; 
					
					// Use translation library to get the bitmap.
					if (roster->Translate(&file, NULL, NULL, &stream, B_TRANSLATOR_BITMAP) == B_OK) {
						// File was successfully translated.
						
						BEntry entry(&ref);
						BPath path(&entry);
						
						stream.DetachBitmap(&result); 

						// Create new MDI view.
						CBitmapView *bitmapView = new CBitmapView(result->Bounds(), result);
						CMDIView *mdiView = new CMDIView(BRect(30,50,40,60), path.Leaf(), bitmapView);
						
						client->AddMDIView(mdiView);
					} 
				}
			}
			break;
		case MSG_FILE_OPEN:
			{
				// Display a file panel. When the user selects a file, a
				// B_REFS_RECEIVED message is sent to this window.
			
				if(openPanel == NULL) {
					BMessenger target(this);
				
					openPanel = new BFilePanel(
						B_OPEN_PANEL, 		// panel mode
						&target, 			// target
						NULL, 				// panel_dir
						B_FILE_NODE,		// node_flavor
						true,				// allow_multiselect
						NULL,				// message
						NULL,				// filter
						true,				// modal?
						true				// hide when done
					);
				}
				
				openPanel->Show();
			}
			break;
		default:
			BWindow::MessageReceived(message);
	}
}

// ==== CBitmapViewerApp ====

CBitmapViewerApp::CBitmapViewerApp()
	: BApplication("application/x-vnd.mdi_test_app")
{
	mainWindow = NULL;
}
	
void CBitmapViewerApp::ReadyToRun()
{
	// Create and display main window
	mainWindow = new CBitmapViewerWindow();
	mainWindow->Show();
}

void CBitmapViewerApp::ArgvReceived(int32 argc, char **argv)
{
	BMessage msg(B_REFS_RECEIVED);
	
	// each argument is a filename
	for(int i=1 ; i<argc ; i++) {
		BEntry entry(argv[i]);
	
		if(entry.InitCheck() == B_OK) {
			entry_ref ref;
			entry.GetRef(&ref);
			
			msg.AddRef("refs", &ref);
		}
	}

	// Send the message to the applications looper. 
	// It's forwareded to the window after the application is fully constructed.
	PostMessage(&msg);
}

void CBitmapViewerApp::RefsReceived(BMessage *msg)
{
	// Forward message to window
	status_t retVal;
	
	if((retVal = mainWindow->PostMessage(msg)) != B_OK)
		printf("PostMessage failed: %s\n", strerror(retVal));
}

// ==== main ====

int main()
{
	new CBitmapViewerApp();

	be_app->Run();
	
	delete be_app;
	
	return 0;
}
