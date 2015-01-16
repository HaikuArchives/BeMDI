/***********************************************************************/
/* MDIClientView.h                                                     */
/*                                                                     */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/* Author : Thomas Krammer                                             */
/*                                                                     */
/* For any comments, bugs or thanks, please email us.                  */
/* Email :   info@3rd-evolution.de                                     */
/*                                                                     */
/***********************************************************************/

#ifndef MDI_CLIENT_VIEW_H
#define MDI_CLIENT_VIEW_H

//! file=MDIClientView.h

#include <mdi/MDITitleView.h>
#include <mdi/MDIView.h>

class CMaximizeButtonView;

//: Manager for MDI Views
// <P>A CMDIClientView contains all MDI views of an application. The MDI views and their title
// tabs are children of this view. Because this class is derived from CZOrderedViewManager it
// ensures that the clippling of its child views is correct.</P>
// <P>A CMDIClientView normally is a direct child of a BScrollView scroll view. The MDI client view 
// automatically hides the scrollbars, if they aren't needed. If the client view isnt' targeted
// by a scroll view, the user can still move the MDI views outside the visible area. Therefore
// you should either use the scrolling or implement your own way to get those views back.</P>
// <P>MDI views can be minimized by a double-click on their title tab or by calling 
// MinimizeView. Minimized views are simply hidden. In order to allow the user to
// get them back you must add a CMDIViewMenu sub-menu to your menu bar.</P>
// <P>MDI views can also be maximized. If a MDI view is maximized the first child (ChildAt(0))
// of the MDI view replaces the MDI client view in the view hierarchy. To restore the
// maximized view to its orginal size and position a button is displayed right of the
// key menubar of the parent window.</P>
// <P>Like any CZOrderedView a MDI view maintains a double linked list to the views above and
// beneath itself. It also depends on the CZOrderedViewManager to update its clipping if
// needed. Therefore you shouldn't call any methods which change the position or size (like
// BView::MoveTo or BView::ResizeTo) directly. Instead use the methods of this class to
// modify the size or position of a MDI view.</P>
// <P>A normal MDI view has a title tab, with allows the user to move the view around,
// maximize, minimize and close it. That title view is created, when the MDI view is added
// via the AddMDIView method. Don't use AddChild directly. All views added via AddMDIView
// must be derived from CMDIView.</P>
// <P>When a CMDIClientView is attached to a window, it attaches a message filter to it. 
// That is necessary, because BeOS doesn't know anything about the z-order of the views and directs
// the messages to the first view it finds that contains the mouse. The message filter redirects
// the message to the correct view.</P>
class CMDIClientView : public CZOrderedViewManager
{
	public:
	CMDIClientView(BRect frame, const char *name, uint32 resizingMode=B_FOLLOW_ALL, uint32 flags=B_FRAME_EVENTS);

	//: Destructor
	virtual ~CMDIClientView();
	
	virtual void AttachedToWindow();
	virtual void DetachedFromWindow();
	virtual void MessageReceived(BMessage *message);
	virtual void WindowActivated(bool active);
	virtual void FrameResized(float width, float height);
	virtual void TargetedByScrollView(BScrollView *scrollView);
	
	virtual void AddMDIView(CMDIView *mdiView);
	virtual void RemoveMDIView(CMDIView *mdiView);
	virtual void ActivateView(CMDIView *mdiView);
	virtual void BringToFront(CMDIView *mdiView);
	virtual void SendToBack(CMDIView *mdiView);
	virtual void ShowView(CMDIView *view);
	virtual void HideView(CMDIView *view);
	virtual void MaximizeView(CMDIView *view);
	virtual void MinimizeView(CMDIView *view);
	virtual void RestoreView();
	
	virtual void ResizeViewTo(CZOrderedView *mdiView, float width, float height);
	inline  void ResizeViewBy(CZOrderedView *mdiView, float horz, float vert);
	virtual void MoveViewTo(CZOrderedView *mdiView, BPoint point);
	inline  void MoveViewTo(CZOrderedView *mdiView, float horz, float vert);
	inline  void MoveViewBy(CZOrderedView *mdiView, float horz, float vert);

	virtual void BeginViewMove(CMDIView *mdiView);
	virtual void EndViewMove(CMDIView *mdiView);
	virtual void BeginViewResize(CMDIView *mdiView);
	virtual void EndViewResize(CMDIView *mdiView);

	virtual void UpdateWindowTitle();

	virtual void TileViews(bool horz);
	virtual void StackViews();

	virtual int32 CountMDIViews() const;
	virtual CMDIView *GetNextMDIView(CZOrderedView *startView) const;
	virtual int32 CountVisibleMDIViews() const;
	virtual CMDIView *GetNextVisibleMDIView(CZOrderedView *startView) const;

	virtual BView *ViewFromPoint(BPoint &point, CZOrderedView **parent=NULL);

	//: Enable mouse redirect
	// <P>This view attaches a message filter to its parent window. That filter forwards
	// mouse messages to the MDI view the mouse is over. That is necessary, because
	// BeOS doesn't know anything about the z-order of the views and directs
	// the messages to the first view it finds, that contains the mouse.</P>
	// <P>But during drag operations normally some view has used SetMouseEventMask
	// to receive all mouse messages, regardless if the mouse is over that view.
	// In that case you must disable the mouse redirect filter, because the
	// filter would change the target again to that view the mouse is over.</P>
	static void EnableMouseRedirect(bool enable) { mouseRedirect = enable; }
	
	//: Returns true, if the mouse redirect filter is enabled.
	static bool MouseRedirectEnabled() { return mouseRedirect; }
	
	protected:

	//: Message filter for mouse messages.
	// This message filter redirects all mouse messages to the 
	// correct view, considering their z-order.
	class CMDIWindowFilter : public BMessageFilter
	{
		public:
		CMDIWindowFilter(CMDIClientView *view);
		
		virtual filter_result Filter(BMessage *message, BHandler **target);
		
		protected:
		//: MDI client view.
		CMDIClientView *view;
	};
	
	virtual void UpdateDataRect(bool updateScrollers=true);
	virtual void UpdateScrollBars();
	virtual void ShowScrollBar(bool horz);
	virtual void HideScrollBar(bool horz);
	virtual void ShowRestoreButton();
	virtual void HideRestoreButton();
	
	//: Returns true, if some MDI view is maximized.
	virtual bool SomeViewMaximized() { return restoreInfo.maximizedView != NULL; }
	
	virtual CTitleView *CreateTitleView(CTitledView *target) const;
	
	BView *Internal_ViewFromPoint(BView *view, BPoint &point);

	//: Contains all information needed to restore the maximized view.
	struct restore_info
	{
		//: Current maximized MDI view.
		CMDIView *originalParent;

		//: Current maximized view (a child view of originalView).
		BView    *maximizedView;
		
		//: View which was replaced by the maximized view.
		BView *replacedView;
	};
	
	//: Information needed to restore the maximized view.
	restore_info restoreInfo;
	
	//: Pointer to the filter which was attached to the window.
	CMDIWindowFilter *filter;

	//: Current active view.
	CMDIView *activeView;

	//: The scroll view, which targets this view.
	BScrollView *scrollView;

	//: The restore button, which is shown right of the menu bar.
	CMaximizeButtonView *restoreButton;
	
	//:  True if mouse message redirection is enabled.
	// It can be useful to
	// disable mouse redirect, if you set SetMouseEventMask(B_POINTER_EVENTS, ...)
	// for some view. If you don't disable mouse redirect in that case, the
	// target is still determined from the mouse position.
	static bool mouseRedirect;
	
	//: Virtual size of this view (for scrolling).
	BRect dataRect;
	
	//: Window title before UpdateWindowTitle was called the first time.
	char *originalWindowTitle;
	
	private:
	//: Hide AddChild.
	// Hides AddChild from the user. Call AddMDIView instead.
	void AddChild(BView *view) { CZOrderedViewManager::AddChild(view); }
};

//: Moves a view.
// Calls MoveViewTo.
void CMDIClientView::MoveViewTo(CZOrderedView *mdiView, float horz, float vert)
{
	MoveViewTo(mdiView, BPoint(horz, vert));
}

//: Moves a view.
// Calls MoveViewTo.
void CMDIClientView::MoveViewBy(CZOrderedView *mdiView, float horz, float vert)
{
	MoveViewTo(mdiView, mdiView->Frame().left+horz, mdiView->Frame().top+vert);
}

//: Resizes a view.
// Calls ResizeViewTo.
void CMDIClientView::ResizeViewBy(CZOrderedView *mdiView, float horz, float vert)
{
	ResizeViewTo(mdiView, mdiView->Bounds().Width()+horz, mdiView->Bounds().Height()+vert);
}

#endif // MDI_CLIENT_VIEW_H
