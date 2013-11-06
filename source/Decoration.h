/***********************************************************************/
/* Decoration.h                                                        */
/*                                                                     */
/* Classes and interfaces for decoration delegation.                   */
/*                                                                     */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/* Author : Thomas Krammer                                             */
/*                                                                     */
/* For any comments, bugs or thanks, please email us.                  */
/* Email :   info@3rd-evolution.de                                     */
/*                                                                     */
/***********************************************************************/

#ifndef MAXIMIZE_BUTTON_H
#define MAXIMIZE_BUTTON_H

//! file=Decoration.h

#include "Color.h"

//: Interface for all decorations
// A decoration acts as a light-weight subview. It doesn't process
// messages or clip its drawing operations. But it can be attached
// to a normal view and draw itself.
class IDecoration
{
	public:
	//: Draw the decoration.
	virtual void Draw() = 0;
};

//: Interface for all button decorations
// A button decoration can be in two states: pressed and not-pressed.
// It also has a background color and a position.
class IButtonDecoration : public IDecoration
{
	public:
	//: Set background color of the button.
	virtual void SetBackgroundColor(CColor bgColor) = 0;
	//: Background color of the button.
	virtual CColor BackgroundColor() = 0;
	//: Returns true if the button is pressed.
	virtual bool Pressed() const = 0;
	//: Set pressed state.
	virtual void SetPressed(bool pressed) = 0;
	//: Set the postion of the view.
	//!param: point - Position in parent coordiantes.
	virtual void SetPosition(BPoint point) = 0;
	//: Returns the bound rectangle.	
	virtual BRect Bounds() const = 0;
	//: Width of the button.
	virtual float Width() const = 0;
	//: Height of the button.
	virtual float Height() const = 0;
};

//: Decoration which displays a BeOS style maximize button.
class CMaximizeButton : public IButtonDecoration
{
	public:
	CMaximizeButton(BView *v);

	//: Returns true if the button is pressed.
	virtual bool Pressed() const { return pressed; }
	virtual void SetPressed(bool pressed);

	//: Width of the button.
	virtual float Width() const { return 13; }
	//: Height of the button.
	virtual float Height() const { return 13; }
	//: Returns the bound rectangle.	
	virtual BRect Bounds() const { return BRect(pos.x,pos.y,pos.x+Width(),pos.y+Height()); }
	//: Set the postion of the view.
	//!param: point - Position in parent coordiantes.
	virtual void SetPosition(BPoint point) { pos = point; } 
	//: Background color of the button.
	// This method doesn't invalidate the button. You have to do
	// this yourself.
	virtual void SetBackgroundColor(CColor color) { bgColor = color; }
	//: Background color of the button.
	virtual CColor BackgroundColor() { return bgColor; }

	virtual void Draw();

	protected:
	//: True, if the button is pressed.
	bool pressed;
	//: View that this decoration is attached to.
	BView *view;
	//: Postion inside parent view.	
	BPoint pos;
	//: Background color of the button.	
	CColor bgColor;
};

//: Decoration which displays a BeOS style close button.
class CCloseButton : public IButtonDecoration
{
	public:
	CCloseButton(BView *v);

	//: Returns true if the button is pressed.
	virtual bool Pressed() const { return pressed; }
	virtual void SetPressed(bool pressed);
	//: Width of the button.
	virtual float Width() const { return 13; }
	//: Height of the button.
	virtual float Height() const { return 13; }
	//: Returns the bound rectangle.	
	virtual BRect Bounds() const { return BRect(pos.x,pos.y,pos.x+Width(),pos.y+Height()); }
	//: Set the postion of the view.
	//!param: point - Position in parent coordiantes.
	virtual void SetPosition(BPoint point) { pos = point; } 
	//: Background color of the button.
	// This method doesn't invalidate the button. You have to do
	// this yourself.
	virtual void SetBackgroundColor(CColor color) { bgColor = color; }
	//: Background color of the button.
	virtual CColor BackgroundColor() { return bgColor; }

	virtual void Draw();

	protected:
	//: True, if the button is pressed.
	bool pressed;
	//: View that this decoration is attached to.
	BView *view;
	//: Postion inside parent view.	
	BPoint pos;
	//: Background color of the button.	
	CColor bgColor;
};

//: Interface for decoration factories.
// All decorations are created through this factory interface. This
// allows the user to change the global factory object in order
// to display different decorations. It would even be possible
// to create 'proxy' decorations and change the decorations
// during runtime.
class IDecorationFactory
{
	public:
	//: Creates a new close button.
	virtual IButtonDecoration *CreateCloseButton(BView *parent) = 0;
	//: Creates a new maximize button.
	virtual IButtonDecoration *CreateMaximizeButton(BView *parent) = 0;
};

//: Default implementation of IDecorationFactory.
// See IDecorationFactory for details.
class CDefaultDecorationFactory : public IDecorationFactory
{
	public:
	//: Creates a new close button.
	virtual IButtonDecoration *CreateCloseButton(BView *parent) { return new CCloseButton(parent); }
	//: Creates a new maximize button.
	virtual IButtonDecoration *CreateMaximizeButton(BView *parent)  { return new CMaximizeButton(parent); }
};

extern IDecorationFactory *global_DecorationFactory;

void SetDecorationFactory(IDecorationFactory *factory);
IDecorationFactory *DecorationFactory();

#endif // MAXIMIZE_BUTTON_H