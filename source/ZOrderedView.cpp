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

#include <vector>
#include "pch.h"
#include "Color.h"
#include "ZOrderedView.h"

// ==== CZOrderedView ====

//: Constructor
CZOrderedView::CZOrderedView(BRect frame, const char *name, uint32 resizingMode, uint32 flags) :
	BView(frame, name, resizingMode, flags)
{
	above = below = NULL;
}

CZOrderedView::~CZOrderedView()
{
	RemoveFromZOrder();
}

//: Removes the view from the z-order.
// This function ensures, that the double-linked list of views remains intact.
void CZOrderedView::RemoveFromZOrder()
{
	if(above)	above->SetBelowView(below);
	if(below)	below->SetAboveView(above);
	
	above = below = NULL;
}

//: Applies a new clipping region.
// This method takes the passed region and applies it to this view and all its
// children. To start this recursion you must set 'view' to NULL.
// The passed clipping region must be in screen coordinates.
void CZOrderedView::ApplyClippingRegion(BView *view, BRegion &region)
{
	BPoint viewLeftTop = B_ORIGIN;

	if(view == NULL) {
		viewLeftTop = ScreenRect().LeftTop();
		view = this;
	} else {
		view->ConvertToScreen(&viewLeftTop);
	}

	BRegion viewRegion = region;
	
	viewRegion.OffsetBy(-viewLeftTop.x, -viewLeftTop.y);

	view->ConstrainClippingRegion(&viewRegion);

	for(int i=0 ; i<view->CountChildren() ; i++) {
		ApplyClippingRegion(view->ChildAt(i), region);
	}
}

//: Updates the cached screen rectangle.
// Updates the cached screen rectangle stored in 'screenRect'. This method
// should is automatically called, when this view is moved inside its parent.
// But if the parent moves, the parent must call this function to ensure
// that the cached rectangle is correct.
void CZOrderedView::UpdateScreenRect()
{
	if(Window() != NULL && !IsHidden()) {
		// If the view is hidden the position returned by ConvertToScreen() 
		// is meaningless. It's just a random number. Therfore the
		// cached rect is ONLY updated, if the view is visible.
	
		screenRect = Bounds();
		ConvertToScreen(&screenRect);
	}
}

//: BeOS hook function
// Sets the view color to transparent and initializes 'screenRect'.
void CZOrderedView::AttachedToWindow()
{
	BView::AttachedToWindow();

	SetViewColor(CColor::Transparent);

	UpdateScreenRect();	
}

//: BeOS hook function
// Calls UpdateScreenRect.
void CZOrderedView::FrameMoved(BPoint parentPoint)
{
	BView::FrameMoved(parentPoint);

	UpdateScreenRect();
}

//: BeOS hook function
// Calls UpdateScreenRect.
void CZOrderedView::FrameResized(float width, float height)
{
	BView::FrameResized(width, height);

	UpdateScreenRect();
}

//: Returns the clipping region for this view.
// Returns the clipping region for this view or any of its children. This is
// the inverted region to that one returned by ObscuredRegion.
void CZOrderedView::ClippingRegion(const BView *clip, BRegion &clipping) const
{
	BRegion obscured;
	
	ObscuredRegion(clip, false, obscured);
	
	clipping.Include(clip->Bounds());
	clipping.Exclude(&obscured);
}

//: Returns the region of this view, which is obscured by other views.
// Returns the region which is obscured by other z-ordered views. If view is NULL,
// it returns the obscured region of this view, otherwise of the child view,
// which is passed in 'view'. If screenRelative is true, all coordinates are screen
// coordinates, otherwise view coordinates.<P>
// Before this method is used, the caller must ensure, that the cached rects are
// up-to-date.
void CZOrderedView::ObscuredRegion(const BView *view, bool screenRelative, BRegion &obscured) const
{
	if(view == NULL)
		view = this;
	
	BRect viewRect = view->Bounds();
	
	if(screenRelative)
		view->ConvertToScreen(&viewRect);
		
	for(CZOrderedView *aboveView = Above() ; aboveView ; aboveView = aboveView->Above()) {
		if(!aboveView->IsHidden()) {
			BRect obscuredRect = aboveView->ScreenRect();
		
			if(!screenRelative)
				view->ConvertFromScreen(&obscuredRect);

			if(viewRect.Intersects(obscuredRect))
				obscured.Include(obscuredRect & viewRect);
		}
	}
}

// ==== CZOrderedViewManager ====

//: Constructor
// This constructor passes all parameters directly to the constructor of BView.
CZOrderedViewManager::CZOrderedViewManager(BRect frame, const char *name, uint32 resizingMode, uint32 flags) :
	BView(frame, name, resizingMode, flags)
{
	topMostView		= NULL;
	backMostView	= NULL;
	firstActivate	= true;
	
	cachedOrigin = BPoint(-1042, -1024);
}

//: BeOS hook function
// If the window is activated the first time this class does some initialization, which
// can't be done in AttachedToWindow or the constructor. This includes a full repaint
// of all child views. After the initialization is finished 'firstActivate' is set
// to false.
void CZOrderedViewManager::WindowActivated(bool active)
{
	if(firstActivate) {
		// Calc clipping for each view
		Z_RecalcClipping(topMostView);
		
		firstActivate = false;
		
		Z_InvalidateChildren(this);
	}
}

//: Reclip 'changedView' and all views below.
// Does a <B>full</B> reclip on 'changedView' and all views below. This function is very slow.
// If you want to reclip just one view call Z_UpdateClipping or Z_ViewPositionChanged.
void CZOrderedViewManager::Z_RecalcClipping(CZOrderedView *changedView)
{
	if(changedView == NULL)
		return;

	if(Window() == NULL || changedView->Window() == NULL)
		return;

	Z_UpdateCachedRects();

	// in,out parameters for Z_ReclipFromAbove
	CZOrderedView *startView = NULL;
	BRegion clippingRegion;

	for(CZOrderedView *view = changedView ; view ; view = view->Below()) {
		startView = Z_ReclipFromAbove(view, startView, clippingRegion, NULL);
	}
}

//: Recalc the clipping of a view and for the obscured/revealed areas.
// This method is normally called after a view is hidden or shown.
// Calls Z_ViewPositionChanged to do the job.
void CZOrderedViewManager::Z_UpdateClipping(CZOrderedView *changedView)
{
	if(changedView == NULL)
		return;

	if(Window() == NULL || changedView->Window() == NULL)
		return;

	Z_UpdateCachedRects();
	Z_ViewPositionChanged(changedView, changedView->ScreenRect(), changedView->ScreenRect());
}

//: Adds a new child view.
// Don't use AddChild directly. If you do that, the views aren't added to the
// z-order linked list. Use Z_AddChild instead. This method enshures, that the
// views are added correctly to the z-order. The new view is the topmost view.
void CZOrderedViewManager::Z_AddChild(CZOrderedView *view)
{
	AddChild(view);
	Z_BringToFront(view);
}

//: Invalidates a view and all its children.
void CZOrderedViewManager::Z_InvalidateChildren(BView *view)
{
	view->Invalidate();

	for(int i=0 ; i<view->CountChildren() ; i++) {
		Z_InvalidateChildren(view->ChildAt(i));
	}
}

//: Invalidates a region of a view and its children.
// Invalidate all areas of 'view' and its children, which intersect with 'obscured'. 
// This method is used to redraw revealed areas. The passed region is in screen 
// coordinates.
void CZOrderedViewManager::Z_InvalidateChildren(BView *view, /*in*/ BRegion &obscured)
{
	BRect viewRect = view->Bounds();
	
	view->ConvertToScreen(&viewRect);
	
	for(int i=0 ; i<obscured.CountRects() ; i++) {
		BRect obscuredRect=obscured.RectAt(i);

		if(obscuredRect.Intersects(viewRect)) {
			view->ConvertFromScreen(&obscuredRect);
			view->Invalidate(obscuredRect);
		}
	}
	
	for(int i=0 ; i<view->CountChildren() ; i++) {
		Z_InvalidateChildren(view->ChildAt(i), obscured);
	}
}

//: Calculates the clipping region for a view.
// This is a special optimized function for Z_ViewPositionChanged. It calculates
// the clipping region only once for multiple views. It starts decending the
// z-order at 'startView'. If 'startView' is NULL, the topmost view is used.
// It calculates the clipping area and stores it in 'clipRegion'. 'clipView' is the
// view which is clipped. It must be below 'startView' in the z-order.
// If an 'updateRect' is passed, only views within that rect are processed.
// All coordinates are in screen coordinates.<P>
// The function returns the new 'startView'.
CZOrderedView *CZOrderedViewManager::Z_ReclipFromAbove(CZOrderedView *clipView, CZOrderedView *startView, /*in,out */ BRegion &clipRegion, /*in*/ BRect *updateRect)
{
	if(startView == NULL) {
		startView = topMostView;
		
		BRect fullView = /*Bounds()*/BRect(-16384, -16384, 16384, 16384);
		ConvertToScreen(&fullView);
		
		clipRegion.Include(fullView);
	}
	
	for(CZOrderedView *current = startView ; current ; current = current->Below()) {
		if(current == clipView) {
			// The clipping region contains the regions of all
			// views above this view. 
			current->ApplyClippingRegion(NULL, clipRegion);

			return current;
		}
		
		if(!current->IsHidden()) {
			BRect obscuredRect = current->ScreenRect();

			if(!updateRect || updateRect->Intersects(obscuredRect)) {
				clipRegion.Exclude(obscuredRect);
			}
		}
	}

	return NULL;
}

//: Update clipping after a view was resized or moved.
// Called to recalculate clipping for a view that moved or was resized. It is also called by
// Z_UpdateClipping to update the clipping when a view was hidden or closed.
//!param: oldPos			- Position of the view before it was resize or moved. In screen coordiantes.
//!param: newPos			- New position of the view. In screen coordiantes. If this method is called, because
//!param:                     a view was hidden or closed 'oldPos' and 'newPos' should both contain 
//!param:                     the position before the view was modified.
//!param: redrawRevealed	- If set to true the revealed areas are invalidated.
void CZOrderedViewManager::Z_ViewPositionChanged(CZOrderedView *view, BRect oldPos, 
	BRect newPos, bool redrawRevealed)
{
	// Update chached screen rects, before using them.
	Z_UpdateCachedRects();

	// Calc area which was changed (either obscured or revealed).
	BRect changedRect = oldPos | newPos;

	BRegion revealedRegion;
	
	if(view->RedrawBelow() || redrawRevealed) {
		revealedRegion.Include(newPos);
		revealedRegion.Include(oldPos);
	}

	// in,out parameters for Z_ReclipFromAbove
	CZOrderedView *startView = NULL;
	BRegion clippingRegion;

	BRect updateRect=changedRect;			// outline rectangle of updated views
	vector<CZOrderedView *> updatedViews;	// List of views that need reclipping

	// Calc new clipping for changed areas (including the modified view).
	for(CZOrderedView *current = view ; current ; current = current->Below()) {
		BRect viewRect = current->ScreenRect();
		
		if(changedRect.Intersects(viewRect)) {
			// current view needs to be processed.
			updatedViews.push_back(current);
			
			updateRect = updateRect | viewRect;
		}
	}

	for(unsigned int i=0 ; i<updatedViews.size() ; i++) {
		// Add all view areas between startView and current as excluded rects
		// to clippingRegion and use it as clipping region for the current
		// updatedView.
		startView = Z_ReclipFromAbove(updatedViews[i], startView, clippingRegion, &updateRect);
		
		if(view->RedrawBelow() || redrawRevealed) {
			Z_InvalidateChildren(updatedViews[i], revealedRegion);
		}
	}
}

//: Modifies the size of a view
// This function is similar to BView::ResizeViewTo, but unlike that method it enshures
// that the clipping region or all views beneath the resized get updated.
void CZOrderedViewManager::Z_ResizeViewTo(CZOrderedView *view, float width, float height)
{
	Z_UpdateCachedRects();

	BRect oldPos = view->ScreenRect();

	view->ResizeTo(width, height);

	view->UpdateScreenRect();
	BRect newPos = view->ScreenRect();
	
	if(oldPos != newPos)
		Z_ViewPositionChanged(view, oldPos, newPos);
}

//: Moves a view
// This function is similar to BView::MoveViewTo, but unlike that method it enshures
// that the clipping region or all views beneath the moved get updated.
void CZOrderedViewManager::Z_MoveViewTo(CZOrderedView *view, BPoint point)
{
	Z_UpdateCachedRects();

	BRect oldPos = view->ScreenRect();

	view->MoveTo(point);

	view->UpdateScreenRect();
	BRect newPos = view->ScreenRect();
	
	if(oldPos != newPos)
		Z_ViewPositionChanged(view, oldPos, newPos);
}

//: Removes a view
// Removes a view from the z-order and calls BView::RemoveSelf for that view.
// The view isn't deleted.
void CZOrderedViewManager::Z_RemoveView(CZOrderedView *view)
{
	if(view == NULL)
		return;
		
	if(!view->IsHidden()) {
		CZOrderedView *below = view->Below();
		view->Hide();

		if(below) {
			// recalc clipping for all views below the removed view
			Z_UpdateClipping(view);
		}
	}

	if(view == topMostView)
		topMostView = view->Below();
		
	if(view == backMostView)
		backMostView = view->Above();

	view->RemoveSelf();
	view->RemoveFromZOrder();
}

//: Updates the cached screen rectangles for all ZOrderedViews.
// Every CZOrderedView object contains a cached version of its screen rectangle.
// These rectangles get invalid, if their parent view (the CZOrderedViewManager) is
// moved. This method tests, if the view was moved and updates the cached
// retangles of all child views accordingly. This method must always be called,
// before the cached rectangles are used.
void CZOrderedViewManager::Z_UpdateCachedRects()
{
	// look if this view moved on the screen. If that is the
	// case, all cached screen rectangles are invalid and must be
	// updated.
	
	if(!Window())
		return;
	
	BPoint origin = B_ORIGIN;
	ConvertToScreen(&origin);
	
	if(cachedOrigin != origin) {
		// this view has been moved!

		for(CZOrderedView *view = topMostView ; view ; view = view->Below()) {
			view->UpdateScreenRect();
		}
		
		cachedOrigin = origin;
	}
}

//: Brings a view to front
void CZOrderedViewManager::Z_BringToFront(CZOrderedView *view)
{
	if(topMostView == view || view == NULL) {
		// this view is already topmost! (or not a valid view...)
		return;
	}

	Z_UpdateCachedRects();

	// Get region of view, which is currently obscured by
	// other views.
	BRegion obscured;
	
	// Get obscured region, before z-order is changed.
	if(view->Window())
		view->ObscuredRegion(NULL, true, obscured);

	if(view == backMostView)
		backMostView = view->Above();

	// Remove view from orginal position in z-order
	view->RemoveFromZOrder();

	// Add view as topmost view
	view->SetAboveView(NULL);
	view->SetBelowView(topMostView);

	if(topMostView)
		topMostView->SetAboveView(view);

	if(backMostView == NULL) {
		// If this is the first view than the topmost view is 
		// also the backmost view.
		backMostView = view;
	}

	topMostView = view;
	
	if(view->Window()) {
		Z_UpdateClipping(view);
		Z_InvalidateChildren(view, obscured);
	}
}

//: Sends a view to back.
void CZOrderedViewManager::Z_SendToBack(CZOrderedView *view)
{
	if(backMostView == view || view == NULL) {
		// This view is already backmost! (or not a valid view...)
		return;
	}
	
	Z_UpdateCachedRects();

	if(view == topMostView)
		topMostView = view->Below();
	
	// This view must be reclipped after the z-order is
	// changed.
	CZOrderedView *below = view->Below();

	// Remove view from orginal position in z-order
	view->RemoveFromZOrder();
	
	// Add view as backmost view
	view->SetAboveView(backMostView);
	view->SetBelowView(NULL);
	
	if(backMostView)
		backMostView->SetBelowView(view);

	if(topMostView == NULL) {
		// If this is the first view than the topmost view is 
		// also the backmost view.
		topMostView = view;
	}
		
	backMostView = view;
	
	if(view->Window()) {
		Z_ViewPositionChanged(below, view->ScreenRect(), view->ScreenRect(), true);
	}
}