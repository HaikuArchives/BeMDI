/***********************************************************************/
/*                                NOTICE                               */
/*                                ------                               */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/*                    This software was developed by                   */
/*                            3rd-Evolution                            */
/*                                                                     */
/* Any reproduction of this software in whole or in part must contain  */
/*                   this notice in its entirety.                      */
/*                                                                     */
/* 3rd-Evolution  is  providing this  software "as is"  and  makes no  */
/* warranty, express or  implied,  as  to  the  accuracy,  capability, */
/* efficiency,  merchantability,  or  functioning  of  this  software  */
/* and/or documentation. In no event will 3rd-evolution be liable for  */
/* any  general,  consequential,   indirect,  incidental,   exemplary, */
/* or special damages, even  if 3rd-evolution has been advised of the  */
/* possibility  of such damages,  irrespective  of  the cause of such  */
/* damages.  For short: 3rd-evolution is impeccable and so any damage  */
/* is your fault.                                                      */
/*                                                                     */
/* Permission  to use, copy, modify, and distribute this software for  */
/* any purpose and without  fee is hereby  granted. For  any comments, */
/* bugs or thanks, please email us: info@3rd-evolution.de              */
/*                                                                     */
/***********************************************************************/

#include "pch.h"
#include "Color.h"
#include "MDIClientView.h"
#include "MaximizeButtonView.h"

// ===== globals =====

const char * const MDI_MSG_DATA_VIEW = "MDI:View";

// ===== CMDIClientView =====

bool CMDIClientView::mouseRedirect = true;

//: Constructor
// Passes all parameters directly to the constructor of BView.
CMDIClientView::CMDIClientView(BRect frame, const char *name, uint32 resizingMode, uint32 flags) :
	CZOrderedViewManager(frame, name, resizingMode, flags | B_FRAME_EVENTS)
{
	activeView			= NULL;
	filter 				= NULL;
	originalWindowTitle	= NULL;
	restoreButton		= NULL;
	scrollView			= NULL;
	
	restoreInfo.originalParent = NULL;
	restoreInfo.maximizedView  = NULL;
	restoreInfo.replacedView   = NULL;
}

CMDIClientView::~CMDIClientView()
{
	delete [] originalWindowTitle;
}

//: BeOS hook function
// Sets the view color to a dark gray and attaches the mouse redirect filter to the
// window.
void CMDIClientView::AttachedToWindow()
{
	SetViewColor(128, 128, 128);
	
	filter = new CMDIWindowFilter(this);
	
	Window()->AddCommonFilter(filter);
	
	UpdateDataRect();
	UpdateWindowTitle();
}

//: BeOS hook function
// Detaches the mouse redirect filter from the window.
void CMDIClientView::DetachedFromWindow()
{
	if(filter) {
		Window()->RemoveCommonFilter(filter);

		delete filter;
		filter = NULL;
	}
}

//: BeOS hook function
// Sets the member 'scrollView'.
void CMDIClientView::TargetedByScrollView(BScrollView *newScrollView)
{
	scrollView = newScrollView;
}

//: BeOS hook function
// Updates the scroll range, when the window is activated the first time.
void CMDIClientView::WindowActivated(bool active)
{
	if(firstActivate)
		UpdateDataRect();

	CZOrderedViewManager::WindowActivated(active);

	if(activeView)
		activeView->Activate(active);
}

//: BeOS hook function
// Updates the scrollers. In order to avoid recursion during the update, if a scroller is
// hidden or shown, the B_FRAME_EVENTS flag is removed until the update is finished.
void CMDIClientView::FrameResized(float width, float height)
{
	// Disable frame events during update of scrollers. 
	// This avoids recursive calls.
	uint32 oldFlags = Flags();
	SetFlags(oldFlags & ~B_FRAME_EVENTS);

	UpdateScrollBars();
	
	SetFlags(oldFlags);
}

//: BeOS hook function
// Handles the CMDIClientView specific messages like MDI_MSG_ACTIVATE_VIEW.
void CMDIClientView::MessageReceived(BMessage *message)
{
	switch(message->what) {
		case MDI_MSG_TILE_VIEWS_HORIZONTAL:
			TileViews(true);
			break;
		case MDI_MSG_TILE_VIEWS_VERTICAL:
			TileViews(false);
			break;
		case MDI_MSG_STACK_VIEWS:
			StackViews();
			break;
		case MDI_MSG_ACTIVATE_VIEW:
			{
				CMDIView *view=NULL;
			
				if(message->FindPointer(MDI_MSG_DATA_VIEW, (void **)&view) == B_OK && view)
					ActivateView(view);
			}
			break;
		case MDI_MSG_MAXIMIZE_VIEW:
			{
				CMDIView *view=NULL;
			
				if(message->FindPointer(MDI_MSG_DATA_VIEW, (void **)&view) == B_OK && view)
					MaximizeView(view);
			}
			break;
		case MDI_MSG_MINIMIZE_VIEW:
			{
				CMDIView *view=NULL;
			
				if(message->FindPointer(MDI_MSG_DATA_VIEW, (void **)&view) == B_OK && view)
					MinimizeView(view);
			}
			break;
		case MDI_MSG_RESTORE_VIEW:
			RestoreView();
			break;
		default:
			CZOrderedViewManager::MessageReceived(message);
	}
}

//: Tiles the views either horizontal or vertical.
// This method is called when a MDI_MSG_TILE_VIEWS message is received, but it can also
// be called directly. This method has no effect, if its called when some view is maximized.
void CMDIClientView::TileViews(bool horz)
{
	float width  = Bounds().Width();
	float height = Bounds().Height();

	int32 count = CountVisibleMDIViews();

	float addHorz = horz ? 0.0 : width / count;
	float addVert = horz ? height / count : 0.0;

	float viewResize=0.0;
	bool firstView = true;

	CMDIView *currentView = NULL;

	float vertPos=0.0, horzPos=0.0;

	while((currentView = GetNextVisibleMDIView(currentView)) != NULL) {
		if(firstView) {
			if(horz) {
				CTitleView *titleView = currentView->TitleView();
				
				if(titleView) {
					float titleTabHeight = titleView->Bounds().Height();
					vertPos = titleTabHeight;
					
					addVert = viewResize = (height - titleTabHeight) / count;
				} else {
					viewResize = height / count;
				}
			} else {
				viewResize = width / count;
			}
			
			firstView = false;
		}
	
		if(horz) {
			MoveViewTo(currentView, horzPos, vertPos);
			ResizeViewTo(currentView, width, viewResize);
		} else {
			CTitleView *titleView = currentView->TitleView();
			
			if(titleView) {
				float titleTabHeight = titleView->Bounds().Height();
				
				MoveViewTo(currentView, horzPos, vertPos+titleTabHeight);
				ResizeViewTo(currentView, viewResize, height-titleTabHeight);
			} else {
				MoveViewTo(currentView, horzPos, vertPos);
				ResizeViewTo(currentView, viewResize, height);
			}
		}
		
		horzPos += addHorz;
		vertPos += addVert;
	}

	UpdateDataRect();
}

//: Stack the views.
// This method is called when a MDI_MSG_STACK_VIEWS message is received, but it can also
// be called directly. This method has no effect, if its called when some view is maximized.
void CMDIClientView::StackViews()
{
	float width  = Bounds().Width();
	float height = Bounds().Height();

	int32 count = CountVisibleMDIViews();

	bool firstView = true;

	const float distance = 30;

	float posHorz=0.0, posVert=0.0;

	float viewWidth  = width-distance*(count-1);
	float viewHeight = 0.0;

	CMDIView *currentView = NULL;

	while((currentView = GetNextVisibleMDIView(currentView)) != NULL) {
		if(firstView) {
			CTitleView *titleView = currentView->TitleView();
				
			if(titleView) {
				float titleTabHeight = titleView->Bounds().Height();
				
				posVert = titleTabHeight;
				viewHeight = height-titleTabHeight-distance*(count-1);
			} else {
				viewHeight = height-distance*(count-1);
			}			

			firstView = false;
		}
		
		MoveViewTo(currentView, posHorz, posVert);
		ResizeViewTo(currentView, viewWidth, viewHeight);
		
		posHorz += distance;
		posVert += distance;
	}
	
	UpdateDataRect();
}

//: Returns the number of MDI views inside this view.
// This method really counts the views in a loop. Therfore you should cache the returned
// value, if you need it more than once.
int32 CMDIClientView::CountMDIViews() const
{
	CMDIView *currentView = NULL;
	int32 count = 0;

	while((currentView = GetNextMDIView(currentView)) != NULL)
		count++;
		
	return count;
}

//: Walk through the list of MDI views.
// This function returns the MDI view beneath 'startView' in the z-order. If you pass
// NULL as 'startView' this method returns the top-most view.
CMDIView *CMDIClientView::GetNextMDIView(CZOrderedView *startView) const
{
	for(CZOrderedView *view = startView ? startView->Below() : topMostView ; 
	      view ; view = view->Below()) {
		CMDIView *mdiView = dynamic_cast<CMDIView *>(view);
		
		if(mdiView)
			return mdiView;
	}
	
	return NULL;
}

//: Returns the number of visible MDI views.
// This method really counts the views in a loop. Therfore you should cache the returned
// value, if you need it more than once.
int32 CMDIClientView::CountVisibleMDIViews() const
{
	CMDIView *currentView = NULL;
	int32 count = 0;

	while((currentView = GetNextVisibleMDIView(currentView)) != NULL) {
		count++;
	}
		
	return count;
}

//: Walk through the list of visible MDI views.
// This function returns the next visible MDI view beneath 'startView' in the z-order. 
// If you pass NULL as 'startView' this method returns the top-most visible view.
CMDIView *CMDIClientView::GetNextVisibleMDIView(CZOrderedView *startView) const
{
	CZOrderedView *currentView = startView;

	while((currentView = GetNextMDIView(currentView)) != NULL && currentView->IsHidden()) ;
	
	return dynamic_cast<CMDIView *>(currentView);
}

//: Adds a new MDI view.
// This method adds a new MDI view to this view. That MDI view is added as topmost view in
// active state.
// If the MDI view hasn't set the MDI_NO_TITLE_TAB flag, this method also creates
// the title view for the MDI view. It uses the CreateTitleView method to do that.
void CMDIClientView::AddMDIView(CMDIView *mdiView)
{
	if(!(mdiView->MDIFlags() & MDI_NO_TITLE_TAB)) {
		// Create title tab
		CTitleView *titleView = CreateTitleView(mdiView);
	
		titleView->ResizeToPreferred();
		titleView->MoveTo(mdiView->Frame().left,
						  mdiView->Frame().top - titleView->Bounds().Height());
					  
		Z_AddChild(titleView);
	}
	
	Z_AddChild(mdiView);

	// The added view is topmost and active
	// (ActivateView will call BringToFront)
	ActivateView(mdiView);
	
	UpdateDataRect();
}

//: Removes a MDI view.
// Removes the view from the z-order. If the removed view is the active view, it
// activates the next visible view below it. This method doesn't delete the MDI view
// nor its title view.
void CMDIClientView::RemoveMDIView(CMDIView *mdiView)
{
	CTitleView *titleView = mdiView->TitleView();

	CMDIView *nextVisible = NULL;
	bool activateNextVisible = false;
	
	if(mdiView == activeView) {
		nextVisible = GetNextVisibleMDIView(activeView);	
		activateNextVisible = true;
	}

	Z_RemoveView(mdiView);
	Z_RemoveView(titleView);

	if(activateNextVisible) {
		// Activate next visible MDI view.
		ActivateView(nextVisible);
	}
	
	UpdateDataRect();
}

//: Activates a MDI view.
// Brings the MDI view to front and calls its CMDIView::Activate method. If the activated
// view is minimized, it is restored.
void CMDIClientView::ActivateView(CMDIView *mdiView)
{
	if(activeView)
		activeView->Activate(false);

	activeView = mdiView;
	
	if(activeView) {
		activeView->Activate(true);
		BringToFront(activeView);

		if(activeView->IsHidden())
			ShowView(activeView);

		if(SomeViewMaximized()) {
			MaximizeView(mdiView);
		}
	}
	
	UpdateWindowTitle();
}

//: Brings a view to front.
// This method doesn't change activation. It brings the view to front but doesn't
// activate it. Call ActivateView to do this.
void CMDIClientView::BringToFront(CMDIView *mdiView)
{
	Z_BringToFront(mdiView);

	if(mdiView->TitleView())
		Z_BringToFront(mdiView->TitleView());
}

//: Sends a view to back.
// This method (unlike BringToFront) automatically changes
// activates the new topmost MDI view.
void CMDIClientView::SendToBack(CMDIView *mdiView)
{
	CMDIView *newActive = GetNextVisibleMDIView(mdiView);

	if(mdiView->TitleView())
		Z_SendToBack(mdiView->TitleView());

	Z_SendToBack(mdiView);
	
	if(newActive && activeView == mdiView) {
		ActivateView(newActive);
	}
}


//: Displays a hidden MDI view.
// When hidden view is displayed again, the clipping of all views beneath it need to
// be updated. Therefore you shouldn't call BView::Show directly. If the MDI view
// has a title view, the title view is also displayed.
void CMDIClientView::ShowView(CMDIView *mdiView)
{
	mdiView->Show();
	Z_UpdateClipping(mdiView);

	if(mdiView->TitleView()) {
		mdiView->TitleView()->Show();
		Z_UpdateClipping(mdiView->TitleView());
	}
		
	UpdateDataRect();
}

//: Hides a MDI view.
// When view is hidden, the clipping of all views beneath it need to
// be updated. Therefore you shouldn't call BView::Hide directly. If the MDI view
// has a title view, the title view is also hidden.
void CMDIClientView::HideView(CMDIView *mdiView)
{
	if(mdiView->TitleView()) {
		mdiView->TitleView()->Hide();
		Z_UpdateClipping(mdiView->TitleView());
	}
		
	mdiView->Hide();
	Z_UpdateClipping(mdiView);
	
	if(activeView == mdiView) {
		ActivateView(GetNextVisibleMDIView(activeView));
	}
	
	UpdateDataRect();
}

//: Minimizes a view
// This method is called when a MDI_MSG_MINIMIZE_VIEW message is received, but it can also
// be called directly. This implementation simply hides the view, but a derived class could
// use overwrite this method to draw an icon of the minized view. If 'view' is NULL this
// method does nothing.
void CMDIClientView::MinimizeView(CMDIView *view)
{
	if(!view || view->IsHidden())
		return;
		
	HideView(view);
}

//: Maximizes a view.
// This method is called when a MDI_MSG_MAXIMIZE_VIEW message is received, but it can also
// be called directly. When a MDI view is maximized, its first child replaces the MDIClient view 
// in the view hierarchy and the client view is hidden. The MDI view displays a button right
// of the key-menubar of its window which restores the maximized view. If you call this function
// when a view is maximized the passed view replaces the currenctly maximized view. If you
// pass NULL as 'view' the currently maximized view is restored, but no additional actions
// (like updating the scroller or updating the clipping) are taken. In order to restore
// the currently maximized view call 'RestoreView'.
void CMDIClientView::MaximizeView(CMDIView *view)
{
	if(restoreInfo.maximizedView != NULL) {
		BRect clientRect = restoreInfo.originalParent->ClientRect();
	
		restoreInfo.maximizedView->RemoveSelf();
		restoreInfo.originalParent->AddChild(restoreInfo.maximizedView);
		restoreInfo.maximizedView->MoveTo(clientRect.LeftTop());
		restoreInfo.maximizedView->ResizeTo(clientRect.Width(), clientRect.Height());

		restoreInfo.maximizedView   = NULL;
		restoreInfo.originalParent  = NULL;
	}
	
	if(view != NULL) {
		// View which should be maximized.
		BView *maximize = view->ChildAt(0);

		// find parent for maximized view
		BView *parent 	= Parent();
		bool useWindow	= false;

		BPoint maximizeLeftTop = Frame().LeftTop();
		float maximizeWidth = Frame().Width()-1;
		float maximizeHeight = Frame().Height()-1;
		
		if(parent == scrollView) {
			// The scroll view is no valid parent. It's also hidden, if
			// the view is maximized.
			if(scrollView->Parent() != NULL) {
				parent = scrollView->Parent();
				maximizeLeftTop = scrollView->Frame().LeftTop();
			} else {
				// Use window as parent
				useWindow = true;
				
				maximizeLeftTop = Frame().LeftTop();
				Parent()->ConvertToScreen(&maximizeLeftTop);
				Window()->ConvertFromScreen(&maximizeLeftTop);
			}

			maximizeWidth = scrollView->Frame().Width()-1;
			maximizeHeight = scrollView->Frame().Height()-1;

			restoreInfo.replacedView = scrollView;
		} else {
			restoreInfo.replacedView = this;
		}
		
		if(!parent || !maximize)
			return;

		maximize->RemoveSelf();

		if(!restoreInfo.replacedView->IsHidden())
			restoreInfo.replacedView->Hide();

		if(!useWindow)
			parent->AddChild(maximize);
		else 
			Window()->AddChild(maximize);
			
		// The parent should replace the client view in the parent.
		maximize->MoveTo(maximizeLeftTop);
		maximize->ResizeTo(maximizeWidth, maximizeHeight);
		maximize->ConstrainClippingRegion(NULL);
		
		restoreInfo.originalParent = view;
		restoreInfo.maximizedView  = maximize;
	}
	
	if(SomeViewMaximized()) {
		ShowRestoreButton();
	} else {
		HideRestoreButton();
	}
}

//: Restores the currenctly maximized view.
// This method is called when a MDI_MSG_RESTORE_VIEW message is received, but it can also
// be called directly. If no view is maximized this method does nothing.
// This method does a full reclipping and updates the scrollers, after the view is restored.
void CMDIClientView::RestoreView()
{
	if(SomeViewMaximized()) {
		MaximizeView(NULL);

		if(restoreInfo.replacedView && restoreInfo.replacedView->IsHidden()) {
			restoreInfo.replacedView->Show();
		}
		
		Z_RecalcClipping(topMostView);
		UpdateScrollBars();
	}
}

//: Internal method
BView *CMDIClientView::Internal_ViewFromPoint(BView *view, BPoint &point)
{
	for(int i=0 ; i<view->CountChildren() ; i++) {
		BView *child = view->ChildAt(i);
	
		BRect screenRect = child->Bounds();
		child->ConvertToScreen(&screenRect);
	
		if(screenRect.Contains(point)) {
			return Internal_ViewFromPoint(child, point);
		}
	}
	
	return view;
}

//: Returns the view which contains the specified point.
// In 'parent' the MDI view which contains the point is returned. That view
// is either the parent of the returned view or the view itself. If this method
// returns NULL no view was found.
//!param: point  - Point in screen coordinates
//!param: parent - Pointer to memory location where a pointer to the parent view is stored.
BView *CMDIClientView::ViewFromPoint(BPoint &point, CZOrderedView **parent)
{
	Z_UpdateCachedRects();
	
	if(parent) *parent = NULL;

	BRect ownScreenRect = Bounds();
	ConvertToScreen(&ownScreenRect);
	
	if(ownScreenRect.Contains(point)) {
		// This view contains the point.
	
		// Crawl down from the topmost window to the bottommost, until
		// we find a view which contains 'point'.
		for(CZOrderedView *current=topMostView ; current ; current = current->Below()) {
			if(!current->IsHidden()) {
				BRect screenRect = current->ScreenRect();
	
				if(screenRect.Contains(point)) {
					// I found the MDI view which contains 'point'.
					// If this view has sub-views one of these could be
					// the real target.
				
					if(parent)
						*parent = current;
				
					return Internal_ViewFromPoint(current, point);
				}
			}
		}
	}
	
	return NULL;
}

//: Adds the MDI title to the window title
// This method is called when a MDI view is activated. The current implementation
// adds the MDI view's title to the window title.
void CMDIClientView::UpdateWindowTitle()
{
	if(!Window())
		return;

	if(!originalWindowTitle) {
		originalWindowTitle = new char[strlen(Window()->Title())+1];
		strcpy(originalWindowTitle, Window()->Title());
	}

	if(activeView) {
		BString newTitle;
		newTitle << originalWindowTitle << " - " << activeView->Title();
	
		Window()->SetTitle(newTitle.String());
	} else {
		Window()->SetTitle(originalWindowTitle);
	}
}

//: Called when the user begins to move a MDI view.
// The implemenation of CMDIClientView does nothing.
void CMDIClientView::BeginViewMove(CMDIView *mdiView)
{
}

//: Called when the user stops to move a MDI view.
// Updates the scrollbars.
void CMDIClientView::EndViewMove(CMDIView *mdiView)
{
	UpdateDataRect();
}

//: Called when the user begins to resize a MDI view.
// The implemenation of CMDIClientView does nothing.
void CMDIClientView::BeginViewResize(CMDIView *mdiView)
{
}

//: Called when the user stops to resize a MDI view.
// Updates the scrollbars.
void CMDIClientView::EndViewResize(CMDIView *mdiView)
{
	UpdateDataRect();
}

//: Shows a scrollbar.
void CMDIClientView::ShowScrollBar(bool horz)
{
	// If the window is hidden all its views are hidden. This means
	// the condition below is always true.
	// Therefore a scroller could be displayed multiple times.
	if(Window() && Window()->IsHidden())
		return;

	BScrollBar *horzScroller = ScrollBar(B_HORIZONTAL);
	BScrollBar *vertScroller = ScrollBar(B_VERTICAL);
	
	BScrollBar *scroller = horz ? horzScroller : vertScroller;
	
	if(!scroller)
		return;
	
	// Display the scrollbar only if this view is visible.
	if(scroller->IsHidden() && !IsHidden()) {
		scroller->Show();
		
		float horzScrollerSize = horzScroller ? horzScroller->Bounds().Height() : 0.0;
		float vertScrollerSize = vertScroller ? vertScroller->Bounds().Width() : 0.0;

		BRect bounds = Bounds();
		
		if(horz)
			ResizeTo(bounds.Width(), bounds.Height()-horzScrollerSize);
		else
			ResizeTo(bounds.Width()-vertScrollerSize, bounds.Height());
	}
}

//: Hides a scrollbar.
void CMDIClientView::HideScrollBar(bool horz)
{
	if(Window() && Window()->IsHidden())
		return;

	BScrollBar *horzScroller = ScrollBar(B_HORIZONTAL);
	BScrollBar *vertScroller = ScrollBar(B_VERTICAL);
	
	BScrollBar *scroller = horz ? horzScroller : vertScroller;
	
	if(!scroller)
		return;

	if(!scroller->IsHidden()) {
		scroller->Hide();
		
		float horzScrollerSize = horzScroller ? horzScroller->Bounds().Height() : 0.0;
		float vertScrollerSize = vertScroller ? vertScroller->Bounds().Width() : 0.0;

		BRect bounds = Bounds();
		
		if(horz)
			ResizeTo(bounds.Width(), bounds.Height()+horzScrollerSize);
		else
			ResizeTo(bounds.Width()+vertScrollerSize, bounds.Height());
	}
}

//: Displays the restore button
// Displays the restore button right of the key-menubar of the window. This method
// does nothing, it the restore button is already displayed.
// The restore button sends a MDI_MSG_RESTORE_VIEW to this view when its activated.
void CMDIClientView::ShowRestoreButton()
{
	if(restoreButton && !restoreButton->IsHidden())
		return;

	BMenuBar *menuBar = Window()->KeyMenuBar();
		
	menuBar->ResizeBy(-menuBar->Bounds().Height()-1, 0);

	BRect menuBarBounds = menuBar->Bounds();
	float x, y, width, height;
		
	width = height = menuBarBounds.Height();

	x = menuBarBounds.right;
	y = menuBarBounds.top;

	if(!restoreButton) {
		BRect restoreButtonRect(x, y, x+width, y+height);
		
		restoreButton = new CMaximizeButtonView(restoreButtonRect, "RestoreButton", 
								new BMessage(MDI_MSG_RESTORE_VIEW), B_FOLLOW_TOP | B_FOLLOW_RIGHT);
			
		Window()->AddChild(restoreButton);
		restoreButton->SetTarget(this);
	} else {
		restoreButton->MoveTo(x, y);
		restoreButton->ResizeTo(width, height);

		if(restoreButton->IsHidden())
			restoreButton->Show();
	}
}

//: Hides the restore button.
// This method is called when the currently maximzed view is restored. It hides the
// restore button and resizes the menubar to its original size.
void CMDIClientView::HideRestoreButton()
{
	if(restoreButton && !restoreButton->IsHidden()) {
		BMenuBar *menuBar = Window()->KeyMenuBar();
		menuBar->ResizeBy(menuBar->Bounds().Height()+1, 0);
		
		restoreButton->Hide();
	}
}

//: Update virtual size.
// Calculates a data rect, that is big enough to hold all views inside this one.
// The new data rect is stored in the member 'dataRect'.
void CMDIClientView::UpdateDataRect(bool updateScrollers)
{
	BScrollBar *horzScroller = ScrollBar(B_HORIZONTAL);
	BScrollBar *vertScroller = ScrollBar(B_VERTICAL);

	float scroll_x = horzScroller ? horzScroller->Value() : 0.0;
	float scroll_y = vertScroller ? vertScroller->Value() : 0.0;

	// Set data rect to invalid rect
	dataRect.Set(0, 0, -16, -16);

	for(CZOrderedView *view=topMostView ; view ; view=view->Below()) {
		if(!view->IsHidden()) {
			dataRect = dataRect | view->Frame();
		}
	}

	dataRect = dataRect.OffsetBySelf(scroll_x, scroll_y);

	if(updateScrollers)
		UpdateScrollBars();
}

//: Update scrollers.
// Update scrollers. Call this function, when the view is resized or the
// dataRect changed.
void CMDIClientView::UpdateScrollBars()
{
	BScrollBar *horzScroller = ScrollBar(B_HORIZONTAL);
	BScrollBar *vertScroller = ScrollBar(B_VERTICAL);

	BRect bounds = Bounds();

	float width = bounds.Width();
	float height = bounds.Height();

	// This full rect also include the bounds rectangle. This means, that the
	// view never "jumps", because the current position is always included in
	// the scroll range.
	// The second added rect enshures that the user can always scroll back to
	// the original position.
	BRect fullRect = dataRect | bounds | BRect(0, 0, width, height);

	float scrollWidth  = fullRect.Width()-width;
	float scrollHeight = fullRect.Height()-height;

	if(horzScroller) {
		if(scrollWidth > 0) {
			float oldValue = horzScroller->Value();
			float minValue = fullRect.left;
			float maxValue = fullRect.left+scrollWidth;
		
			horzScroller->SetRange(minValue, maxValue);
			horzScroller->SetProportion(width / fullRect.Width());
			horzScroller->SetValue(MAX(MIN(oldValue,maxValue),minValue));
			
			ShowScrollBar(true);
		} else {
			horzScroller->SetRange(0, 0);
			HideScrollBar(true);
		}
	}

	if(vertScroller)	{
		if(scrollHeight > 0) {
			float oldValue = vertScroller->Value();
			float minValue = fullRect.top;
			float maxValue = fullRect.top+scrollHeight;
		
			vertScroller->SetRange(minValue, maxValue);
			vertScroller->SetProportion(height / fullRect.Height());
			vertScroller->SetValue(MAX(MIN(oldValue,maxValue),minValue));

			ShowScrollBar(false);
		} else {
			vertScroller->SetRange(0, 0);
			HideScrollBar(false);
		}
	}
}

//: Factory method for title tabs.
// This method is called by AddMDIView to create the title tab for a new MDI view.
CTitleView *CMDIClientView::CreateTitleView(CTitledView *target) const
{
	return new CMDITitleView(BRect(0,0,30,30), target);
}

//: Resizes a view.
void CMDIClientView::ResizeViewTo(CZOrderedView *view, float width, float height)
{
	CMDIView *mdiView = dynamic_cast<CMDIView *>(view);
	
	if(mdiView) {
		if(mdiView->MDIFlags() & MDI_NOT_RESIZABLE) {
			// don't change size
			return;
		}
		
		// Ajust size to size limits
		float minWidth, maxWidth, minHeight, maxHeight;
		
		mdiView->GetSizeLimits(&minWidth, &maxWidth, &minHeight, &maxHeight);
		
		if(width > maxWidth)	width = maxWidth;
		if(height > maxHeight)  height = maxHeight;

		if(width < minWidth)	width = minWidth;
		if(height < minHeight)	height = minHeight;
	}

	Z_ResizeViewTo(view, width, height);
}

//: Moves a view.
void CMDIClientView::MoveViewTo(CZOrderedView *view, BPoint point)
{
	CMDIView *mdiView = dynamic_cast<CMDIView *>(view);

	if(mdiView && mdiView->TitleView()) {
		CTitleView *titleView = mdiView->TitleView();
	
		Z_MoveViewTo(titleView, BPoint(point.x, point.y-titleView->Bounds().Height()));
	}

	Z_MoveViewTo(view, point);
}

// ===== CMDIClientView::CMDIWindowFilter =====

//: Constructor
CMDIClientView::CMDIWindowFilter::CMDIWindowFilter(CMDIClientView *_view) :
	BMessageFilter(B_ANY_DELIVERY, B_ANY_SOURCE, (filter_hook)NULL)
{
	view = _view;
}

//: BeOS hook function
// Filters the mouse messages (B_MOUSE_MOVED, B_MOUSE_UP and B_MOUSE_DOWN) and redirects
// them to the correct CZOrderedView, considering their z-order.
filter_result CMDIClientView::CMDIWindowFilter::Filter(BMessage *message, BHandler **target)
{
	if(!view->MouseRedirectEnabled())
		return B_DISPATCH_MESSAGE;

	switch(message->what) {
		case B_MOUSE_UP:
		case B_MOUSE_DOWN:
			{
				// message->PrintToStream();
			
				BPoint where;
				
				if(message->FindPoint("where", &where) == B_OK) {
					BView *targetView = dynamic_cast<BView *>(*target);
					
					if(targetView) {
						targetView->ConvertToScreen(&where);
						
						CZOrderedView *parent;
					
						BView *newTarget = view->ViewFromPoint(where, &parent);

						if(parent && parent != newTarget && message->what == B_MOUSE_DOWN) {
							// 'newTarget' is subview of 'parent'
							
							CMDIView *parentMDI = dynamic_cast<CMDIView *>(parent);
							
							if(parentMDI && !parentMDI->Active()) {
								// the parent must be active in order to receive
								// mouse messages.
								view->ActivateView(parentMDI);
							}
						}

						if(newTarget && *target != newTarget) {
							*target = newTarget;
							
							newTarget->ConvertFromScreen(&where);
							
							message->ReplacePoint("where", where);
							message->ReplacePoint("be:view_where", where);
						}
					}
				}
			}
		
			break;
		case B_MOUSE_MOVED:
			{
				// message->PrintToStream();
				
				static BPoint oldPos(-1,-1);
			
				BPoint newPos;
				int32 transit;
	
				if( message->FindPoint("where", &newPos) == B_OK &&
					message->FindInt32("be:transit", &transit) == B_OK) {

					BView *newTarget = NULL;

					BWindow *window = dynamic_cast<BWindow *>(Looper());
					window->ConvertToScreen(&newPos);

					if(transit == B_EXITED_VIEW) {
						// if the mouse exited a view, a B_MOUSE_MOVED message
						// is sent to the view the mouse left and to the view
						// the mouse entered.
						// Both messages contain the NEW mouse position. If
						// I use the new mouse position to find the view the
						// mouse left, I will find the wrong view.
						
						newTarget = view->ViewFromPoint(oldPos);
					} else {

						newTarget = view->ViewFromPoint(newPos);
					}
						
						
					if(newTarget && *target != newTarget) {
						// The point 'where' is expressed in WINDOW coordinates.
						// The point 'be:view_where' is expressed in VIEW coordinates
						// and must be transformed.
						
						newTarget->ConvertFromScreen(&newPos);

						message->ReplacePoint("be:view_where", newPos);
							
						*target = newTarget;
					}
					
					oldPos = newPos;
				}
			}
			
			break;
	}
	
	return B_DISPATCH_MESSAGE;
}