/***********************************************************************/
/* ZOrderedView.h                                                      */
/*                                                                     */
/* Contains the classes CZOrderedView and CZOrderViewManager. These    */
/* two classes provide clipping of BViews based on their z-order.      */
/*                                                                     */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/* Author : Thomas Krammer                                             */
/*                                                                     */
/* For any comments, bugs or thanks, please email us.                  */
/* Email :   info@3rd-evolution.de                                     */
/*                                                                     */
/***********************************************************************/

#ifndef Z_ORDERED_VIEW_H
#define Z_ORDERED_VIEW_H

//! file=ZOrderedView.h

//: This view maintains a z-order.
// Normal views don't maintain a z-order. But this class contains two pointers: one to
// the view above and another to the one below this view. This double-linked list
// defines the z-order of the views.<P>
// Views of this class should only be used inside a CZOrderedViewManager. The 
// ZOrderedViewManager uses the double linked list to calculate the correct clipping
// for the views inside it.<P>
// It's very slow to convert the bounds rectangle from view to screen coordinates.
// But this operation is very common during the calculation of the clipping region.
// Therefore this class caches its screen rectangle.<P>
class CZOrderedView : public BView
{
	public:
	CZOrderedView(BRect frame, const char *name, uint32 resizingMode, uint32 flags=B_FRAME_EVENTS);

	//: Destructor
	// Calls RemoveFromZOrder.
	virtual ~CZOrderedView();

	virtual void AttachedToWindow();
	virtual void FrameMoved(BPoint parentPoint);
	virtual void FrameResized(float widht, float height);

	virtual void ClippingRegion(const BView *clip, BRegion &clipping) const;
	virtual void ObscuredRegion(const BView *view, bool windowRelative, BRegion &obscured) const;
	
	virtual void ApplyClippingRegion(BView *view, BRegion &region);

	//: Sets the view above this one.
	virtual void SetAboveView(CZOrderedView *view)	{ above = view; }
	//: Sets the view beneath this one.
	virtual void SetBelowView(CZOrderedView *view)	{ below = view; }

	//: Returns true, if the views beneath must be redrawn.
	// If this method returns true, all revealed areas during a 
	// move or resize are invalidated and redrawn. This isn't
	// necessary, if the ZOrderedView sets and all its children set their
	// view color to transparent. This implementation returns always false.
	// A derived class should overwrite this method as necessary.
	virtual bool RedrawBelow() { return false; }

	virtual void RemoveFromZOrder();

	//: Returns the view above this one.
	CZOrderedView *Above() const	{ return above; }
	//: Returns the view beneath this one.
	CZOrderedView *Below() const	{ return below; }

	//: Returns the cached screen retangle.
	BRect  ScreenRect() const		{ return screenRect; }
	
	void UpdateScreenRect();
	
	protected:

	//: Position of this view in screen coordinates.
	BRect screenRect;
	
	private:
	//: The view above this one.
	// This member is private. Use the access methods instead.
	CZOrderedView *above;
	//: The view beneath this one.
	// This member is private. Use the access methods instead.
	CZOrderedView *below;
};

//: This class manages a list of ZOrderedViews.
// <P>Normal BeOS views don't maintain a z-order. All siblings have the same position in the
// z-order. This means that siblings can overdraw each other. Normally views don't overlap, so
// this isn't an issue.</P>
// <P>But MDI views must not overdraw each other. Therefore they are derived from CZOrderedView.
// ZOrderedViews can only live inside a CZOrderedViewManager.</P>
// <P>A ZOrderedViewManager takes all its child views and does the necessary clipping. This
// class mirrors all view operations, which could affect clipping (moving a view, resizing it etc.).
// Normally shouldn't you don't call the view's operation directly. Call the ViewManager's method
// instead. This asures that the clipping remains intact.</P>
// <P>Normally you shouldn't use CZOrderedView directly. Instead use CMDIClientView, which
// is derived from this class.</P>
class CZOrderedViewManager : public BView
{
	public:	
	CZOrderedViewManager(BRect frame, const char *name, uint32 resizingMode, uint32 flags);
	
	virtual void WindowActivated(bool active);

	protected:
	virtual void Z_AddChild(CZOrderedView *view);
	virtual void Z_RemoveView(CZOrderedView *view);

	virtual void Z_BringToFront(CZOrderedView *view);
	virtual void Z_SendToBack(CZOrderedView *view);
	virtual void Z_RecalcClipping(CZOrderedView *changedView);
	virtual void Z_UpdateClipping(CZOrderedView *changedView);
	virtual void Z_InvalidateChildren(BView *view, BRegion &obscured);
	virtual void Z_InvalidateChildren(BView *view);
	virtual void Z_ViewPositionChanged(CZOrderedView *view, BRect oldPos, BRect newPos, bool redrawRevealed=false);

	virtual void Z_ResizeViewTo(CZOrderedView *view, float width, float height);
	virtual void Z_MoveViewTo(CZOrderedView *view, BPoint point);

	virtual void Z_UpdateCachedRects();

	CZOrderedView *Z_ReclipFromAbove(CZOrderedView *clipView, CZOrderedView *startView, /*in,out */ BRegion &clipRegion, BRect *updateRect);

	//: Top most view.
	CZOrderedView *topMostView;
	
	//: Back most view.
	CZOrderedView *backMostView;
	
	//: True if this view never was activated.
	bool firstActivate;		

	//: Position on screen at last update of the cached screen rects.
	// If the postion of this view or any of its parents changes, the chached screen rects
	// of the CZOrderedView objects get invalid. Therefore Z_UpdateCachedRects uses
	// this member to determine if this view was moved.
	BPoint cachedOrigin;
};

#endif // Z_ORDERED_VIEW_H