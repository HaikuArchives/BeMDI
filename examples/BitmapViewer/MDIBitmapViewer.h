/* COPYRIGHT 2000 by 3rd-evolution
 * Author: Thomas Krammer (tkrammer@3rd-evolution.de)
 */

const int32 MSG_FILE_OPEN = 'mFOP';

class CBitmapView : public BView
{
	public:
	CBitmapView(BRect frame, BBitmap *bm);
	virtual ~CBitmapView();
	
	virtual void AttachedToWindow();
	virtual void Draw(BRect updateRect);
	
	protected:
	BBitmap *bitmap;
};

class CBitmapViewerWindow : public BWindow
{
	public:
	CBitmapViewerWindow(BRect frame = BRect(50, 50, 750, 750));
	virtual ~CBitmapViewerWindow();
	
	virtual void MessageReceived(BMessage *message);
	virtual bool QuitRequested();
	virtual void MenusBeginning();
	
	protected:
	CMDIClientView *client;
	BFilePanel *openPanel;
};

class CBitmapViewerApp : public BApplication
{
	public:
	CBitmapViewerApp();
	
	virtual void ReadyToRun();
	virtual void ArgvReceived(int32 argc, char **argv);
	virtual void RefsReceived(BMessage *msg);
	
	protected:
	BWindow *mainWindow;
};

