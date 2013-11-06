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
#include "GlyphMenuItem.h"

//: Constructor
// The CGlyphMenuItem takes the normal BMenuItem constructor
// parameters and the additional parameters mentioned in the parameter
// section.
//!param: glyph_bm - Icon displayed in front of the label. This class
//!param: takes responsibilty for the passed object. The caller
//!param: should not modify the bitmap after it was passed to
//!param: this method.
//!param: isDefaultEntry - If set to true, the label is displayed 
//!param: using a bold font.
//!param: _offset - Offset of the label from the default location.
CGlyphMenuItem::CGlyphMenuItem(const char *label, BBitmap *glyph_bm,
	bool isDefaultEntry, BMessage *message, char shortcut, 
	uint32 modifiers, BPoint _offset) :
	BMenuItem(label, message, shortcut, modifiers)
{
	glyph		= glyph_bm;
	isDefault	= isDefaultEntry;
	offset      = _offset;
}

CGlyphMenuItem::~CGlyphMenuItem()
{
	if(glyph) delete glyph;
}

//: BeOS hook function
void CGlyphMenuItem::DrawContent()
{
	BPoint pos = ContentLocation();

	pos += offset;

	BFont oldFont = SetDrawFont();

	if(glyph) {
		Menu()->SetDrawingMode(B_OP_COPY);
		Menu()->MovePenTo(pos.x+glyph->Bounds().Width()+5.0, pos.y);
		BMenuItem::DrawContent();
	
		Menu()->SetDrawingMode(B_OP_OVER);
		Menu()->DrawBitmap(glyph, pos);
	} else {
		BMenuItem::DrawContent();
	}
	
	Menu()->SetFont(&oldFont);
}

//: BeOS hook function
void CGlyphMenuItem::GetContentSize(float *width, float *height)
{
	BFont oldFont;
	
	oldFont = SetDrawFont();

	BMenuItem::GetContentSize(width, height);

	Menu()->SetFont(&oldFont);
	
	if(glyph) {
		*width += glyph->Bounds().Width() + 5.0 + offset.x;
		*height = MAX(*height, glyph->Bounds().Height()) + offset.y;
	}
}

//: Sets the correct drawing font
// This method sets the correct drawing font for the menu.
// It returns the previously selected font.
BFont CGlyphMenuItem::SetDrawFont()
{
	BFont oldFont;
	
	Menu()->GetFont(&oldFont);

	if(isDefault) {
		BFont boldFont = oldFont;
		
		boldFont.SetFace(B_BOLD_FACE);
		
		Menu()->SetFont(&boldFont);
	}
	
	return oldFont;
}